#include "MainWindow.h"

namespace fs = std::filesystem;
using namespace tinyxml2;

MainWindow::MainWindow() : WindowBase(NULL) {
    SetLabel("DJHCPP v" + DJHCPP_VERSION + "    [" + DJHCPP_BUILD + "]");
    
    mainTable = new CustomTable(this);
    middleSizer->Add(mainTable,1,wxALL|wxEXPAND,5);

    if(!fs::exists(SETTINGS_FILE_NAME)){
        //create one with defaults
        mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
        mINI::INIStructure ini;
        ini["Settings"]["baseFolder"] = "";
        backupFolderPath = fs::current_path() / "djhcpp_backups";
        fs::create_directory(backupFolderPath);
        ini["Settings"]["backupFolderPath"] = backupFolderPath.string();
        ini["Settings"]["automaticBackups"] = "true";
        automaticBackups = true;
        settings.write(ini);
    } else {
        mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
        mINI::INIStructure ini;
        settings.read(ini);
        basePath = ini["Settings"]["baseFolder"];
        backupFolderPath = fs::path(ini["Settings"]["backupFolderPath"]);
        automaticBackups = ini["Settings"]["automaticBackups"] == "true";
        
        if(basePath.empty()) return;

        ParseExtracted(basePath);
        
        //TODO: parse backups already present
        for(auto& dirEntry : fs::directory_iterator(backupFolderPath)){
            if(dirEntry.is_directory()){
                std::string text = dirEntry.path().filename().string();
                wxMenuItem* entry = new wxMenuItem(backupRestoreMenu,wxID_ANY,text,wxEmptyString,wxITEM_NORMAL);
                wxStringClientData* data = new wxStringClientData(wxString(dirEntry.path().string()));

                backupRestoreMenu->Append(entry);
                //i spent 2 hours trying to figure out how bind works. Rip me
                backupRestoreMenu->Bind(wxEVT_MENU,&MainWindow::RestoreBackup,this,entry->GetId(),-1,(wxObject*)data);
            }
        }
    }
}

void MainWindow::OpenExtractedFiles( wxCommandEvent& event ){
    wxDirDialog* dialog = new wxDirDialog(this, "Open WII/PS3/X360 folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if(dialog->ShowModal() == wxID_OK){
        //std::filesystem::path p = std::filesystem::path(dialog->GetPath());
        basePath = fs::path(dialog->GetPath().ToStdString());
        ParseExtracted(basePath);
    }
}

void MainWindow::ParseExtracted(fs::path path){
    tracklistingPath = path / "AUDIO" / "Audiotracks" / "tracklisting.xml";
    tracIDPath = path / "Text" / "TRAC" / "TRACID.txt";
    tracEPath = path / "Text" / "TRAC" / "TRACE.txt";
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
        
        wxLogMessage(wxString("Successfully loaded ") <<  textData.size() << " songs from tracklisting.");
        //load tracklisting
        tracklisting.LoadFile(tracklistingPath.generic_string().c_str());
        UpdateTable();
        //add backup
        CreateAutomaticBackup();
        baseFolderLabel->SetLabelText(wxString("Base Folder:  ") << path.c_str());

        //set in the settings
        mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
        mINI::INIStructure ini;
        settings.read(ini);
        ini["Settings"]["baseFolder"] = path.string();
        settings.write(ini);
    } else {
        wxLogError("Tracklisting file not found (error 0x1)");
    }
}

void MainWindow::CreateAutomaticBackup(){
    if(!automaticBackups) return;
    time_t t = time(NULL);
    tm* now = localtime(&t);
    char dateFolder[31];
    //format table is present here: https://cplusplus.com/reference/ctime/strftime/
    std::strftime(dateFolder,30,"%Y-%m-%d_%H-%M-%S",now);
    CreateBackup(backupFolderPath,dateFolder);
}

void MainWindow::AddCustom(wxCommandEvent& event){
    wxDirDialog* dialog = new wxDirDialog(this, "Open Custom's folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST | wxDD_MULTIPLE);
    if(dialog->ShowModal() == wxID_OK){
        wxArrayString paths;
        dialog->GetPaths(paths);

        bool showOverwriteDialog = true;
        for(size_t i = 0; i < paths.GetCount(); i++){
            fs::path dir = fs::path(paths[i].ToStdWstring());
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
    if(!fs::exists(customTracklisting)){
        wxLogError("'Info for Tracklisting.xml' file not found");
        return;
    }

    doc.LoadFile(customTracklisting.generic_string().c_str());

    XMLNode* track = doc.RootElement()->FirstChild();

    while(track != nullptr){
        //identical
        if(strcmp(track->Value(),"Track") == 0){
            std::string addingTag = track->FirstChildElement("IDTag")->GetText();

            XMLElement* tracklistingRoot = tracklisting.RootElement();
            XMLNode* tracklistingTrack = tracklistingRoot->FirstChild();
            XMLNode* possibleRemove = nullptr;

            while(tracklistingTrack != nullptr){
                XMLElement* IDTag = tracklistingTrack->FirstChildElement("IDTag");
                if(IDTag != nullptr){
                    std::string trackTestingID = IDTag->GetText();
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
        }
        track = track->NextSibling();
    }

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
    fs::path rootAudiotracks = basePath / "AUDIO" / "Audiotracks";

    for(auto& path : fs::directory_iterator(dir)){
        if(fs::is_directory(path)){
            //only copy inner subfolders and skip "info for ..." files
            fs::path destination = rootAudiotracks;
            destination /= path.path().filename().generic_string();
            //wxLogMessage(destination.generic_string().c_str());
            fs::copy(path, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        }
    }
    UpdateTable();
    Export();
}

void MainWindow::ManualUpdate(wxCommandEvent& e){
    Export();
}

void MainWindow::Export(){
    tracklisting.SaveFile(tracklistingPath.generic_string().c_str());

    std::ofstream trackIDStream(tracIDPath);
    std::ofstream trackEStream(tracEPath);

    if(trackIDStream.is_open() && trackEStream.is_open()){
        for(auto& pair : textData){
            if(pair.first != std::string("")){
                trackIDStream << pair.first << "\n";
                trackEStream << pair.second << '\0';
                //wxLogMessage(wxString() << pair.first << ":" << pair.second);
            }
        }

        trackIDStream.close();
        trackEStream.close();
    }
    wxLogMessage("Successfully updated the game's files");
}

void MainWindow::SetBackupFolder( wxCommandEvent& event){
    wxDirDialog* dialog = new wxDirDialog(this, "Open Custom's folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST );
    if(dialog->ShowModal() == wxID_OK){
        fs::path path = fs::path(dialog->GetPath().ToStdString());
        mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
        mINI::INIStructure ini;
        settings.read(ini);
        ini["Settings"]["backupFolderPath"] = path.string();
        settings.write(ini);
    }
}

void MainWindow::ManualBackup( wxCommandEvent& event ) {
    std::string text = wxGetTextFromUser("Please enter the name of the backup:","Caption",wxEmptyString, this).ToStdString();
    CreateBackup(backupFolderPath,text);
}

void MainWindow::CreateBackup(std::filesystem::path baseFolder, std::string name ){
    if(fs::exists(baseFolder)){
        fs::path thisBackup = baseFolder / name;
        fs::create_directory(thisBackup);
        
        fs::copy_file(tracklistingPath, thisBackup / "tracklisting.xml");
        fs::copy_file(tracIDPath, thisBackup / "TRACID.txt");
        fs::copy_file(tracEPath, thisBackup / "TRACE.txt");

        //add another entry to the menu
        wxMenuItem* entry = new wxMenuItem(backupRestoreMenu,wxID_ANY,name,wxEmptyString,wxITEM_NORMAL);
        wxStringClientData* data = new wxStringClientData(wxString(thisBackup.string()));

        backupRestoreMenu->Append(entry);
        backupRestoreMenu->Bind(wxEVT_MENU,&MainWindow::RestoreBackup,this,entry->GetId(),-1,(wxObject*)data);
    } else {
        wxLogWarning("Backup folder path specified in the settings does not exist. Backup Aborted");
    }
}

void MainWindow::RestoreBackup( wxCommandEvent& event){
    //std::cout << event.GetId() << std::endl;
    wxStringClientData* data = (wxStringClientData*)event.GetEventUserData();
    if(!tracklistingPath.empty() && !tracIDPath.empty() && !tracEPath.empty()){
        fs::path src(data->GetData().ToStdString());
        fs::copy_options copyOptions;
        copyOptions |= fs::copy_options::overwrite_existing;
        fs::copy(src / "tracklisting.xml", tracklistingPath,copyOptions);
        fs::copy(src / "TRACID.txt", tracIDPath,copyOptions);
        fs::copy(src / "TRACE.txt", tracEPath,copyOptions);

        //refresh extracted files and start again
        ParseExtracted(basePath);
    }
}

void MainWindow::UpdateTable(){
    mainTable->data.clear();
    XMLNode* track = tracklisting.RootElement()->FirstChild();

    while(track != nullptr){
        TableRow row;

        std::string id = "";
        std::string name1 = "";
        std::string name2 = "";
        std::string artist1 = "";
        std::string artist2 = "";
        std::string bpm = "";

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

        row.id = id;
        
        //if artist1 is empty -> ""
        //if artist1 is not empty
        //  if textData contains key -> textData[key]
        //  else "!MISSING!"

        if(artist1.empty()) row.artist1 = "";
        else {
            if(textData.count(artist1) == 1) row.artist1 = textData[artist1];
            else row.artist1 = "[MISSING]";
        }

        if(name1.empty()) row.song1 = "";
        else {
            if(textData.count(name1) == 1) row.song1 = textData[name1];
            else row.song1 = "[MISSING]";
        }

        if(artist2.empty()) row.artist2 = "";
        else {
            if(textData.count(artist2) == 1) row.artist2 = textData[artist2];
            else row.artist2 = "[MISSING]";
        }

        if(name2.empty()) row.song2 = "";
        else {
            if(textData.count(name2) == 1) row.song2 = textData[name2];
            else row.song2 = "[MISSING]";
        }
        
        row.bpm = std::stof(bpm);
        const char* name;
        name = track->ToElement()->Attribute("selectableinfem");

        if(name != 0){
            if(strcmp(name,"yes") == 0 || strcmp(name,"true"))
                row.enabled = true;
            //wxLogMessage(wxString() << id << " " << name); 
        }

        mainTable->data.push_back(row);

        track = track->NextSibling();
    }
    mainTable->SetItemCount(mainTable->data.size());
}

void MainWindow::OnSearch(wxCommandEvent& wxEvent){
    mainTable->Search(wxEvent.GetString().ToStdString());
}

//other windows and tools

void MainWindow::OpenTrackisting(wxCommandEvent& event){
    TracklistingWindow* twin = new TracklistingWindow(this);
    twin->Show();
}

void MainWindow::ToUpper(wxCommandEvent& event){
    if(!basePath.empty()){
        wxProgressDialog* dialog = new wxProgressDialog("Progress","Renaming the files. Please wait a few seconds",100,this);
        dialog->Show();
        dialog->Pulse();
        
        for(auto& item : fs::recursive_directory_iterator(basePath)){
            fs::path rel = fs::relative(item.path(),basePath);

            std::string upperPath = rel.generic_string();
            
            for(char& ch : upperPath){
                ch = std::toupper(ch);
            }

            fs::path destination = fs::path(upperPath);
            
            fs::rename(basePath / rel,basePath / destination);

            //show files to the user
            dialog->Pulse();
        }
        dialog->Destroy();
    } else {
        wxLogWarning("Please load the extracted files before renaming");
    }
}

void MainWindow::ApplyPatchFile( wxCommandEvent& event){
    if(basePath.empty()){
        wxLogWarning("Please load extracted files before applying patch files");
        return;
    }
    
    wxFileDialog dlg(this,"Select Patch File","","","XML Files (*.xml)|*.xml");
    if(dlg.ShowModal() == wxID_OK){
        CreateAutomaticBackup();
        //wxLogMessage(dlg.GetPath());
        
        XMLDocument doc;
        doc.LoadFile(dlg.GetPath());

        XMLElement* track = doc.RootElement()->FirstChildElement();
        while(track != nullptr){
            const char* idtag;
            idtag = track->ToElement()->Attribute("IDTag");
            wxLogMessage(idtag);

            //find custom in loaded tracks
            XMLElement* query = tracklisting.RootElement()->FirstChildElement();
            while(query != nullptr){
                const char* queryID = query->FirstChildElement("IDTag")->GetText();
                if(strcmp(idtag,queryID) == 0){
                    //we found the custom
                    wxLogMessage(wxString("WE FOUND THE CUSTOM WITH ID ") << idtag);
                    
                    //make tracklisting the parent of trackCopy, so that we can add it later
                    XMLNode* trackCopy = track->DeepClone(&tracklisting);

                    //see if <Leaderboard> is already present in the query
                    XMLNode* queryLeaderboard = query->FirstChildElement("LeaderboardID");
                    XMLNode* newLeaderboard = trackCopy->FirstChildElement("LeaderboardID");

                    if(newLeaderboard != nullptr){
                        //we must patch something
                        if(queryLeaderboard != nullptr){
                            query->DeleteChild(queryLeaderboard);
                        }
                        query->InsertEndChild(newLeaderboard);
                    }
                    break;
                }
                query = query->NextSiblingElement();
            }
            if(query == nullptr){
                wxLogMessage(wxString("Custom with ID ") << idtag << " was not found");
            }
            track = track->NextSiblingElement();
        }
        Export();
        wxLogMessage("Done Patching");
        //wxLogMessage(doc.RootElement()->FirstChild()->Value());
    }
}
