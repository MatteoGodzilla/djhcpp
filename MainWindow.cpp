#include "MainWindow.h"

namespace fs = std::filesystem;

MainWindow::MainWindow() : WindowBase(NULL) {
    //mainTable->AppendTextColumn("ID",wxDATAVIEW_CELL_INERT,-1,wxALIGN_LEFT,wxDATAVIEW_COL_SORTABLE);
    //mainTable->AppendTextColumn("Name 1",wxDATAVIEW_CELL_INERT,-1,wxALIGN_LEFT,wxDATAVIEW_COL_SORTABLE);
    //mainTable->AppendTextColumn("Name 2",wxDATAVIEW_CELL_INERT,-1,wxALIGN_LEFT,wxDATAVIEW_COL_SORTABLE);
    //mainTable->AppendTextColumn("Artist 1",wxDATAVIEW_CELL_INERT,-1,wxALIGN_LEFT,wxDATAVIEW_COL_SORTABLE);
    //mainTable->AppendTextColumn("Artist 2",wxDATAVIEW_CELL_INERT,-1,wxALIGN_LEFT,wxDATAVIEW_COL_SORTABLE);
    //mainTable->AppendTextColumn("BPM",wxDATAVIEW_CELL_INERT,-1,wxALIGN_LEFT,wxDATAVIEW_COL_SORTABLE);
}

void MainWindow::OpenExtractedFiles( wxCommandEvent& event ){
    wxDirDialog* dialog = new wxDirDialog(this, "Open WII/PS3/X360 folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if(dialog->ShowModal() == wxID_OK){
        //std::filesystem::path p = std::filesystem::path(dialog->GetPath());
        fs::path p = fs::path(dialog->GetPath().ToStdString());

        fs::path tracklistingPath = p / "AUDIO" / "Audiotracks" / "tracklisting.xml";
        fs::path tracIDPath = p / "Text" / "TRAC" / "TRACID.txt";
        fs::path tracEPath = p / "Text" / "TRAC" / "TRACE.txt";
        wxLogMessage(tracklistingPath.c_str());

        if(fs::exists(tracklistingPath) && fs::exists(tracIDPath) && fs::exists(tracEPath)){
            wxLogMessage("Extracted Files found");
            //load text string
            std::ifstream tracIDStream = std::ifstream(tracIDPath);
            std::ifstream tracEStream = std::ifstream(tracEPath);
            
            textData.clear();
            textData.insert(std::make_pair(std::string(""), std::string(""))); //default when string is empty

            while(!tracIDStream.eof()){
                std::string id;
                std::string value;
                std::getline(tracIDStream,id);
                std::getline(tracEStream,value,'\0');
                textData.insert(std::make_pair(id,value));
            }
            //load tracklisting
            tracklisting = wxXmlDocument(tracklistingPath.generic_string());
            UpdateTable();
        } else {
            wxLogWarning("Tracklisting file not found (error #1)");
        }
    }
}

void MainWindow::UpdateTable(){
    mainTable->DeleteAllItems();
    wxXmlNode* root = tracklisting.GetDocumentNode()->GetChildren();
    wxXmlNode* track = root->GetChildren();
    while(track != nullptr){
        wxVector<wxVariant> row;

        wxString id = "";
        wxString name1 = "";
        wxString name2 = "";
        wxString artist1 = "";
        wxString artist2 = "";
        wxString bpm = "";

        wxXmlNode* inner = track->GetChildren();
        while(inner != nullptr){
            wxString nodeName = inner->GetName();
            //wxXml is weird so to get the contents of <BPM>166.5</BPM>
            //you have to consider the contents as a child node, then get the contents
            
            if(nodeName.IsSameAs("IDTag")) id = inner->GetChildren()->GetContent();
            if(nodeName.IsSameAs("MixName")) {
                if(name1.IsSameAs(""))name1 = inner->GetChildren()->GetContent();
                else name2 = inner->GetChildren()->GetContent();
            }
            if(nodeName.IsSameAs("MixArtist")) {
                if(artist1.IsSameAs("")) artist1 = inner->GetChildren()->GetContent();
                else artist2 = inner->GetChildren()->GetContent();
            }
            if(nodeName.IsSameAs("BPM")) bpm = inner->GetChildren()->GetContent();
            inner = inner->GetNext();
        }
        

        row.push_back(wxVariant(id));
        row.push_back(wxVariant(textData[artist1.ToStdString()]));
        row.push_back(wxVariant(textData[name1.ToStdString()]));
        row.push_back(wxVariant(textData[artist2.ToStdString()]));
        row.push_back(wxVariant(textData[name2.ToStdString()]));
        row.push_back(wxVariant(bpm));
        mainTable->AppendItem(row);

        track = track->GetNext();
    }
}