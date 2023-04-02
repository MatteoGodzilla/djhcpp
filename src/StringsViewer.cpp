#include "StringsViewer.h"
#include "MainWindow.h"

StringsViewer::StringsViewer(MainWindow* parent) : TrackTextViewer(parent){
    mainWindowRef = parent;
    RebuildTable(std::string());
}

void StringsViewer::OnTextChange( wxCommandEvent& event ){
    //table->DeleteAllItems();
    RebuildTable(event.GetString().ToStdString());
}

void StringsViewer::RebuildTable(std::string query){
    table->DeleteAllItems();
    std::cout << query.size() << std::endl;
    for(auto& pair : mainWindowRef->textData){
        bool allowed = false;

        // check if the query is somewhat inside the current string
        // the query must be shorter than the text

        allowed = pair.first.find(query) != std::string::npos;
        allowed = allowed || pair.second.find(query) != std::string::npos;

        int idCharIndex = 0;
        for(size_t i = 0 ; i < pair.first.size(); i++){
            if(idCharIndex < query.size()){
                //check character
                if(tolower(pair.first[i]) == tolower(query[idCharIndex]))
                    idCharIndex++;
            } else {
                //we ran out of the query string
                allowed = true;
                break;
            }
        }

        if(!allowed){
            //check for the value
            int valueCharIndex = 0;
            for(size_t i = 0; i < pair.second.size(); i++){
                if(valueCharIndex < query.size()){
                    //check character
                    if(tolower(pair.second[i]) == tolower(query[valueCharIndex]))
                        valueCharIndex++;
                } else {
                    //we ran out of the query string
                    allowed = true;
                    break;
                }
            }
        }

        if(allowed){
            wxVector<wxVariant> row = wxVector<wxVariant>();
            row.push_back(wxString::FromUTF8(pair.first));
            row.push_back(wxString::FromUTF8(pair.second));
            table->AppendItem(row);
        }
    }
}