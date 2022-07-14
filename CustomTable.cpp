#include "CustomTable.h"

int FuzzyExact(wxString query,wxString text){
    size_t searchIndex = 0;
    size_t textIndex = 0;

    query.MakeLower();
    text.MakeLower();

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
    : wxListCtrl(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxLC_VIRTUAL|wxLC_REPORT)
{
    AppendColumn("ID");
    AppendColumn("Artist 1");
    AppendColumn("Song 1");
    AppendColumn("Artist 2");
    AppendColumn("Song 2");
    AppendColumn("BPM");

    data = std::vector<TableRow>();
}

wxString CustomTable::OnGetItemText(long item, long column) const{
    TableRow row = data[item];
    switch(column){
        case 0: return row.id;
        case 1: return row.artist1;
        case 2: return row.song1;
        case 3: return row.artist2;
        case 4: return row.song2;
        case 5: return wxString() << row.bpm;
        default: return wxString();
    }
}

void CustomTable::Search(wxString query){
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