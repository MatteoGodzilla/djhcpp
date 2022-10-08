#include "CustomTable.h"

int FuzzyExact(std::string query,std::string text){
    size_t searchIndex = 0;
    size_t textIndex = 0;

    for(char& ch : query){
        ch = std::tolower(ch);
    }

    for(char& ch : text){
        ch = std::tolower(ch);
    }

    int score = 0;

    while(textIndex < text.size() && searchIndex < query.size()){
        if(query[searchIndex] == text[textIndex]){
            //reward exact letters, even better if they are consecutive
            searchIndex++;
            score += 100;
        } else {
            //penalize different letters
            score -= 10;
        }
        textIndex++;
    }
    return score;
}

CustomTable::CustomTable(wxWindow *parent)
    : wxListCtrl(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLC_VIRTUAL|wxLC_REPORT|wxLC_HRULES)
{
    //this first column is a hack because apparently wxwidgets adds an extra image on the first column
    //even if you dont want one there

    AppendColumn("",wxLIST_FORMAT_LEFT,0);
    AppendColumn("ID");
    AppendColumn("Artist 1");
    AppendColumn("Song 1");
    AppendColumn("Artist 2");
    AppendColumn("Song 2");
    AppendColumn("BPM");

    //used to show enabled column (disabled for now)
    //AppendColumn("Enabled");

    /*
    wxVector<wxBitmapBundle> images;

    wxImage enabled,disabled;
    wxImage::AddHandler(new wxPNGHandler());
    disabled.LoadFile("checkbox-disabled.png",wxBitmapType::wxBITMAP_TYPE_PNG);
    enabled.LoadFile("checkbox-enabled.png",wxBitmapType::wxBITMAP_TYPE_PNG);

    images.push_back(wxBitmapBundle::FromBitmap(disabled));
    images.push_back(wxBitmapBundle::FromBitmap(enabled));
    SetSmallImages(images);
    */

    Bind(wxEVT_LIST_COL_CLICK,wxListEventHandler(CustomTable::OnColumnClick),this,wxID_ANY);
    Bind(wxEVT_LIST_KEY_DOWN,wxListEventHandler(CustomTable::OnKeyDown),this,wxID_ANY);
    Bind(wxEVT_LIST_ITEM_ACTIVATED,wxListEventHandler(CustomTable::OnActivate),this,wxID_ANY);

    Bind(wxEVT_LIST_ITEM_SELECTED,wxListEventHandler(CustomTable::SelectRow),this,wxID_ANY);
    Bind(wxEVT_LIST_ITEM_DESELECTED,wxListEventHandler(CustomTable::DeselectRow),this,wxID_ANY);

    data = std::vector<TableRow>();
    selectedRows = std::list<long>();
}

wxString CustomTable::OnGetItemText(long item, long column) const{
    TableRow row = data[item];
    switch(column){
        case 1: return wxString::FromUTF8(row.id);
        case 2: return wxString::FromUTF8(row.artist1);
        case 3: return wxString::FromUTF8(row.song1);
        case 4: return wxString::FromUTF8(row.artist2);
        case 5: return wxString::FromUTF8(row.song2);
        case 6: return wxString() << row.bpm;
        default: return wxString();
    }
}

int CustomTable::OnGetItemColumnImage(long item, long column) const {
    return -1;
    /*
    TableRow row = data[item];
    //std::cout << item << "\t" << column << std::endl;
    switch(column){
        case 7:
            if(row.enabled) return 1;
            else return 0;
        default: return -1;
    }
    */
}

void CustomTable::Search(std::string query){
    //actually just sorts
    std::sort(data.begin(),data.end(),[&](const TableRow& a, const TableRow& b){
        //calculate max score for each row
        int maxScoreA = FuzzyExact(query,a.id);
        maxScoreA = std::max(maxScoreA,FuzzyExact(query,a.artist1));
        maxScoreA = std::max(maxScoreA,FuzzyExact(query,a.song1));
        maxScoreA = std::max(maxScoreA,FuzzyExact(query,a.artist2));
        maxScoreA = std::max(maxScoreA,FuzzyExact(query,a.song2));

        int maxScoreB = FuzzyExact(query,b.id);
        maxScoreB = std::max(maxScoreB,FuzzyExact(query,b.artist1));
        maxScoreB = std::max(maxScoreB,FuzzyExact(query,b.song1));
        maxScoreB = std::max(maxScoreB,FuzzyExact(query,b.artist2));
        maxScoreB = std::max(maxScoreB,FuzzyExact(query,b.song2));

        //true if a should come before b
        //in this case yes cause it has a bigger score aka better match
        return maxScoreA > maxScoreB;
    });
    Refresh();
}

void CustomTable::OnColumnClick(wxListEvent& event){
    //std::cout << "Column Clicked " << event.GetColumn() << std::endl;
    int col = event.GetColumn();
    int newDirection = sortingDirection;
    if(col == lastSortingColumn)
        newDirection *= -1;
    else
        newDirection = 1;
    std::cout << "SORTING " << col << "\t" << newDirection << std::endl;
    std::sort(data.begin(),data.end(),[col,newDirection](const TableRow& a, const TableRow& b){
        //std::cout << "---------------------------" << std::endl;
        //std::cout << a.id << "\t" << a.artist1 << "\t" << a.song1 << "\t" << a.artist2 << "\t" << a.song2 << "\t" << a.bpm << "\t" << std::endl;
        //std::cout << b.id << "\t" << b.artist1 << "\t" << b.song1 << "\t" << b.artist2 << "\t" << b.song2 << "\t" << b.bpm << "\t" << std::endl;
        return CustomTable::CompareRows(a,b,col,newDirection);
    });
    sortingDirection = newDirection;
    lastSortingColumn = col;
    Refresh();
}

void CustomTable::OnKeyDown(wxListEvent& event){
    tinyxml2::XMLElement* ref = data[event.GetIndex()].trackRef;
    wxCommandEvent ev = wxCommandEvent();
    TrackInfoViewer* viewer;
    switch(event.GetKeyCode()){
        case WXK_NUMPAD_DELETE:
        case WXK_DELETE:
            viewer = new TrackInfoViewer(this,ref);
            viewer->onDeleteTrack(ev);
            break;
        default: break;
    }
    //wxLogMessage(wxString() << "KEY DOWN" << " " << event.GetKeyCode());
}

void CustomTable::OnActivate(wxListEvent& event){
    //get xmlref from currently selected row
    tinyxml2::XMLElement* ref = data[event.GetIndex()].trackRef;

    TrackInfoViewer* viewer = new TrackInfoViewer(this,ref);
    viewer->Show();
}

void CustomTable::SelectRow(wxListEvent& event){
    long row = event.GetIndex();
    selectedRows.push_back(row);

    for(auto& dataRow : selectedRows){
        std::cout << dataRow << " ";
    }
    std::cout << std::endl;
}

void CustomTable::DeselectRow(wxListEvent& event){
    long row = event.GetIndex();
    if(row == -1){
        //clear everything
        selectedRows.clear();
    } else {
        //remove only the deselected row
        selectedRows.remove(row);
    }

    for(auto& dataRow : selectedRows){
        std::cout << dataRow << " ";
    }
    std::cout << std::endl;
}

bool CustomTable::CompareRows(const TableRow& a, const TableRow& b, int col, int dir){
    switch(col){
        case 1:
            return (dir * a.id.compare(b.id)) < 0;
        case 2:
            return (dir * a.artist1.compare(b.artist1)) < 0;
        case 3:
            return (dir * a.song1.compare(b.song1)) < 0;
        case 4:
            return (dir * a.artist2.compare(b.artist2)) < 0;
        case 5:
            return (dir * a.song2.compare(b.song2)) < 0;
        case 6:
            return (dir * (a.bpm - b.bpm)) < 0;
        case 7:
            if(dir > 0)
                return a.enabled && !b.enabled;
            else
                return b.enabled && !a.enabled;
    }
    return false;
}
