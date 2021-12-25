#include "MainWindow.h"

namespace fs = std::filesystem;
using namespace tinyxml2;

MainWindow::MainWindow() : WindowBase(NULL) {
    SetLabel("DJHCPP v" + DJHCPP_VERSION);
}

void MainWindow::OpenExtractedFiles( wxCommandEvent& event ){
    wxDirDialog* dialog = new wxDirDialog(this, "Open WII/PS3/X360 folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if(dialog->ShowModal() == wxID_OK){
        //std::filesystem::path p = std::filesystem::path(dialog->GetPath());
        basePath = fs::path(dialog->GetPath().ToStdString());
        
        tracklistingPath = basePath / "AUDIO" / "Audiotracks" / "tracklisting.xml";
        tracIDPath = basePath / "Text" / "TRAC" / "TRACID.txt";
        tracEPath = basePath / "Text" / "TRAC" / "TRACE.txt";
        //wxLogMessage(tracklistingPath.c_str());

        if(fs::exists(tracklistingPath) && fs::exists(tracIDPath) && fs::exists(tracEPath)){
            //wxLogMessage("Extracted Files found");
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
            tracklisting.LoadFile(tracklistingPath.generic_string().c_str());
            UpdateTable();
        } else {
            wxLogError("Tracklisting file not found (error 0x1)");
        }
    }
}

void MainWindow::AddCustom(wxCommandEvent& event){
    wxDirDialog* dialog = new wxDirDialog(this, "Open Custom's folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST | wxDD_MULTIPLE);
    if(dialog->ShowModal() == wxID_OK){
        wxArrayString paths;
        dialog->GetPaths(paths);

        bool showOverwriteDialog = true;
        for(size_t i = 0; i < paths.GetCount(); i++){
            fs::path dir = fs::path(paths[i].ToStdString());
            if(fs::exists(dir/"DJH2")) dir /= "DJH2";
            
            ProcessCustom(dir);
        }
    }
}

void MainWindow::ProcessCustom(fs::path dir){
    //importing tracklisting info
    fs::path customTracklisting = dir / "Info for Tracklisting.xml";
    fs::path customTextData = dir / "Info for TRAC.csv";
    tinyxml2::XMLDocument doc;
    doc.LoadFile(customTracklisting.generic_string().c_str());

    XMLNode* track = doc.RootElement()->FirstChild();

    wxString addingTag = track->FirstChildElement("IDTag")->GetText();

    XMLElement* tracklistingRoot = tracklisting.RootElement();
    XMLNode* tracklistingTrack = tracklistingRoot->FirstChild();
    XMLNode* possibleRemove = nullptr;

    while(tracklistingTrack != nullptr){
        XMLElement* IDTag = tracklistingTrack->FirstChildElement("IDTag");
        if(IDTag != nullptr){
            wxString trackTestingID = IDTag->GetText();
            if(trackTestingID == addingTag){
                wxLogMessage("Replacing track node");
                possibleRemove = tracklistingTrack;
            }
        }
        tracklistingTrack = tracklistingTrack->NextSibling();
    }
    //to insert a node in tracklisting that node needs to be own already by tracklisting
    //with DeepClone we get a copy that is own by tracklisting
    //that is safe to add to the root;
    if(possibleRemove != nullptr) tracklistingRoot->DeleteChild(possibleRemove);

    XMLNode* copy = track->DeepClone(&tracklisting);
    tracklistingRoot->InsertEndChild(copy);

    //importing text data
    std::ifstream textDataStream = std::ifstream(customTextData.generic_string());
    std::string line;
    while(std::getline(textDataStream,line)){
        if(line.find("//") != std::string::npos) continue;
        if(line.length() == 0) continue;

        bool insideQuotes = false;
        std::vector<std::string> tokens;
        tokens.emplace_back("");
        char previousChar = '\0';

        for(size_t i = 0; i < line.length(); i++){
            char c = line[i];
            if(c == '"'){
                insideQuotes = !insideQuotes;
                if(previousChar == '"'){
                    //in the csv standard, if there are two "" that is considered as the " literal
                    tokens.back() += '"';
                    previousChar = '\0';                    
                } else previousChar = c;
            } else if(c == ',' && !insideQuotes){
                //we found the comma separator and we're not in something in quotes, 
                //so we're good to go to parse the next token (by pushing an empty string)
                tokens.emplace_back("");
                previousChar = c;
            } else {
                tokens.back() += c;
                previousChar = c;
            }
        }
        if(tokens.size() > 1){
            textData.insert_or_assign(tokens[0],tokens[1]);
        }
    }

    //copy files to location
    fs::path destination = basePath / "AUDIO" / "Audiotracks";

    for(auto& path : fs::directory_iterator(dir)){
        if(fs::is_directory(path)){
            //only copy inner subfolders and skip "info for ..." files
            fs::copy(path, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        }
    }
    UpdateTable();
    Export();
}

void MainWindow::Export(){
    tracklisting.SaveFile(tracklistingPath.generic_string().c_str());

    std::ofstream trackIDStream(tracIDPath);
    std::ofstream trackEStream(tracEPath);

    if(trackIDStream.is_open() && trackEStream.is_open()){
        for(auto& pair : textData){
            trackIDStream << pair.first << "\n";
            trackEStream << pair.second << '\0';
        }

        trackIDStream.close();
        trackEStream.close();
    }
    wxLogMessage("Successfully updated the game's files");
}

void MainWindow::UpdateTable(){
    mainTable->DeleteAllItems();

    XMLNode* track = tracklisting.RootElement()->FirstChild();
    while(track != nullptr){
        wxVector<wxVariant> row;

        wxString id = "";
        wxString name1 = "";
        wxString name2 = "";
        wxString artist1 = "";
        wxString artist2 = "";
        wxString bpm = "";

        XMLElement* token = track->FirstChildElement("IDTag");
        if(token != nullptr) id = token->GetText();
        
        token = track->FirstChildElement("MixName");
        if(token != nullptr) name1 = token->GetText();

        token = token->NextSiblingElement("MixName");
        if(token != nullptr) name2 = token->GetText();

        token = track->FirstChildElement("MixArtist");
        if(token != nullptr) artist1 = token->GetText();

        token = token->NextSiblingElement("MixArtist");
        if(token != nullptr) artist2 = token->GetText();

        token = track->FirstChildElement("BPM");
        if(token != nullptr) bpm = token->GetText();

        row.push_back(wxVariant(id));
        
        //if artist1 is empty -> ""
        //if artist1 is not empty
        //  if textData contains key -> textData[key]
        //  else "!MISSING!"

        if(artist1.empty()) row.push_back(wxVariant(""));
        else {
            if(textData.count(artist1.ToStdString()) == 1) row.push_back(wxVariant(textData[artist1.ToStdString()]));
            else row.push_back(wxVariant("[MISSING]"));
        }

        if(name1.empty()) row.push_back(wxVariant(""));
        else {
            if(textData.count(name1.ToStdString()) == 1) row.push_back(wxVariant(textData[name1.ToStdString()]));
            else row.push_back(wxVariant("[MISSING]"));
        }

        if(artist2.empty()) row.push_back(wxVariant(""));
        else {
            if(textData.count(artist2.ToStdString()) == 1) row.push_back(wxVariant(textData[artist2.ToStdString()]));
            else row.push_back(wxVariant("[MISSING]"));
        }

        if(name2.empty()) row.push_back(wxVariant(""));
        else {
            if(textData.count(name2.ToStdString()) == 1) row.push_back(wxVariant(textData[name2.ToStdString()]));
            else row.push_back(wxVariant("[MISSING]"));
        }
        
        row.push_back(wxVariant(bpm));
        mainTable->AppendItem(row);

        track = track->NextSibling();
    }
}