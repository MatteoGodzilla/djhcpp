#include "MainWindow.h"

namespace fs = std::filesystem;

//copied from stack overflow: https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c
size_t downloadPatchFile(void* buffer, size_t size, size_t nmemb, FILE* userp){
    size_t written = fwrite(buffer, size, nmemb, userp);
    //wxLogMessage(wxString()<<nmemb);
    return written;
}

//this would probably fail if the packet size is not 64 chars, but less
size_t checkSHA(void* buffer, size_t size, size_t nmemb, void* userp){
    std::string remoteSHA;
    //0xff is a byte, but it has 2 chars written in it
    remoteSHA.resize(SHA256_DIGEST_LENGTH*2);
    memcpy(remoteSHA.data(),buffer,SHA256_DIGEST_LENGTH*2);

    //wxLogMessage(wxString() << nmemb);

    //open patch file
    std::ifstream patchFile(PATCH_FILE_NAME,std::ios::binary);
    if(patchFile.is_open()){
        std::stringstream sstr;
        sstr << patchFile.rdbuf();
        std::string data = sstr.str();

        std::cout << data.length() << std::endl;

        unsigned char dataSHABuffer[SHA256_DIGEST_LENGTH];
        SHA256_CTX context;
        SHA256_Init(&context);
        SHA256_Update(&context,data.data(),data.length());
        SHA256_Final(dataSHABuffer,&context);

        std::stringstream dataSHAstream;
        dataSHAstream << std::hex;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
            dataSHAstream << std::setw(2) << std::setfill('0') << (int)dataSHABuffer[i];
        }

        std::string dataSHA = dataSHAstream.str();

        if(remoteSHA == dataSHA){
            //wxLogMessage("SHA256 is Valid! Yay!");
            return nmemb;
        } else {
            wxLogError("There was a conflict between the SHA256 codes of the remote and local patch files.");
            wxLogMessage("Remote");
            wxLogMessage(wxString(remoteSHA));
            wxLogMessage("Downloaded File");
            wxLogMessage(wxString(dataSHAstream.str()));
        }
        return 1;
    }

    return 0;
}

MainWindow::MainWindow() : WindowBase(NULL) {
    SetLabel("DJHCPP v" + DJHCPP_VERSION + "    [" + DJHCPP_BUILD + "]");

    Bind(DJHCPP_EVT_FORCE_LIST_UPDATE,&MainWindow::ManualUpdate,this);

    mainTable = new CustomTable(this);
    middleSizer->Add(mainTable,1,wxALL|wxEXPAND,5);

    mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
    mINI::INIStructure ini;

    if(fs::exists(SETTINGS_FILE_NAME))
        settings.read(ini);

    //write the settings file
    if(!ini["Settings"].has("baseFolder")) {
        ini["Settings"]["baseFolder"] = "";
        basePath = "";
    } else {
        basePath = fs::path(ini["Settings"]["baseFolder"]);
    }

    if(!ini["Settings"].has("backupFolderPath")){
        backupFolderPath = fs::current_path() / "djhcpp_backups";
        fs::create_directory(backupFolderPath);
        ini["Settings"]["backupFolderPath"] = backupFolderPath.string();
    } else {
        backupFolderPath = fs::path(ini["Settings"]["backupFolderPath"]);
    }

    if(!ini["Settings"].has("automaticBackups")) {
        ini["Settings"]["automaticBackups"] = "true";
        automaticBackups = true;
    } else {
        automaticBackups = ini["Settings"]["automaticBackups"] == "true";
    }

    if(!ini["Settings"].has("patchFileSourceURL")) {
        ini["Settings"]["patchFileSourceURL"] = "";
        patchFileSourceURL = "";
    } else {
        patchFileSourceURL = ini["Settings"]["patchFileSourceURL"];
    }

    if(!ini["Settings"].has("patchFileCRCURL")) {
        ini["Settings"]["patchFileCRCURL"] = "";
        patchFileCRCURL = "";
    } else {
        patchFileCRCURL = ini["Settings"]["patchFileCRCURL"];
    }

    if(!ini["Settings"].has("automaticPatching")) {
        ini["Settings"]["automaticPatching"] = "false";
        automaticPatching = false;
    } else {
        automaticPatching = ini["Settings"]["automaticPatching"] == "true";
    }

    if(!ini["Settings"].has("automaticRenaming")) {
        ini["Settings"]["automaticRenaming"] = "false";
        automaticRenaming= false;
    } else {
        automaticRenaming = ini["Settings"]["automaticRenaming"] == "true";
    }

    settings.write(ini);

    //program start

    if(basePath.empty()) return;

    ParseExtracted(basePath);

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

    automaticRenamingToggleMI->Check(automaticRenaming);

    //patch file stuff
    if(patchFileSourceURL.empty() || patchFileCRCURL.empty()) return;

    //initialize curl
    curlSession = curl_easy_init();
    //wxLogMessage(wxString() << (uint64_t)curlSession);
    if(curlSession){
        FILE* fp = fopen(PATCH_FILE_NAME.c_str(),"wb");
        curl_easy_setopt(curlSession, CURLOPT_URL, patchFileSourceURL.c_str());
        curl_easy_setopt(curlSession, CURLOPT_WRITEFUNCTION, downloadPatchFile);
        curl_easy_setopt(curlSession,CURLOPT_WRITEDATA,fp);
        CURLcode success = curl_easy_perform(curlSession);
        fclose(fp);
        //check CRC
        curl_easy_setopt(curlSession, CURLOPT_URL, patchFileCRCURL.c_str());
        curl_easy_setopt(curlSession, CURLOPT_WRITEFUNCTION, checkSHA);
        success = curl_easy_perform(curlSession);
        //wxLogMessage(wxString() << success);
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

        //load tracklisting
        tracklisting.LoadFile(tracklistingPath.generic_string().c_str());
        //count how many songs were loaded
        size_t count = 0;
        tinyxml2::XMLElement* track = tracklisting.RootElement()->FirstChildElement();
        do {
            count++;
            track = track->NextSiblingElement();
        } while(track != nullptr);

        wxLogMessage(wxString("Successfully loaded ") << count << " songs from tracklisting.");

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

    tinyxml2::XMLError errorID = doc.LoadFile(customTracklisting.generic_string().c_str());
    if(errorID != tinyxml2::XML_SUCCESS){
        wxLogError(wxString("XML Error: ") << errorID);
        if(errorID == tinyxml2::XML_ERROR_FILE_NOT_FOUND){
            wxLogError("There was a problem loading 'Info for Tracklisting.xml'. Make sure that the path to the file contains only standard characters.");
        }
        return;
    }

    tinyxml2::XMLNode* track = doc.RootElement()->FirstChild();

    while(track != nullptr){
        //identical
        if(strcmp(track->Value(),"Track") == 0){
            std::string addingTag = track->FirstChildElement("IDTag")->GetText();

            tinyxml2::XMLElement* tracklistingRoot = tracklisting.RootElement();
            tinyxml2::XMLNode* tracklistingTrack = tracklistingRoot->FirstChild();
            tinyxml2::XMLNode* possibleRemove = nullptr;

            while(tracklistingTrack != nullptr){
                tinyxml2::XMLElement* IDTag = tracklistingTrack->FirstChildElement("IDTag");
                if(IDTag != nullptr){
                    std::string trackTestingID = IDTag->GetText();
                    if(trackTestingID == addingTag){
                        wxLogMessage(wxString("Replacing track node: ") << addingTag);
                        possibleRemove = tracklistingTrack;
                    }
                }
                tracklistingTrack = tracklistingTrack->NextSibling();
            }
            //to insert a node in tracklisting that node needs to be own already by tracklisting
            //with DeepClone we get a copy that is own by tracklisting
            //that is safe to add to the root;
            if(possibleRemove != nullptr) tracklistingRoot->DeleteChild(possibleRemove);

            tinyxml2::XMLNode* copy = track->DeepClone(&tracklisting);
            tracklistingRoot->InsertEndChild(copy);
            wxLogMessage(wxString("Added track node: ") << addingTag);
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
    UpdateTable();
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

void MainWindow::TracksToCustoms(wxCommandEvent& event){
    wxDirDialog* dialog = new wxDirDialog(this, "Select a folder to export the customs to", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST );
    if(dialog->ShowModal() == wxID_OK){
        //get all of the selected tracks in the table
        fs::path containingFolder = fs::path(dialog->GetPath().ToStdString());
        for(int row : mainTable->selectedRows){
            //for each one
            TableRow dataRow = mainTable->data[row];
            //  get the id from track
            std::string id = dataRow.id;
            //  create root id with that name
            fs::create_directory(containingFolder / id);
            //  create DJH2 folder inside it
            fs::path djh2Folder = containingFolder / id / "DJH2";
            fs::create_directory(djh2Folder);
            //  get folderLocation from track

            std::string folderLocation = dataRow.trackRef->FirstChildElement("FolderLocation")->GetText();
            fs::path customFullFolderLocation = basePath / fs::path(folderLocation);
            //std::cout << customFullFolderLocation << std::endl;
            //  copy that folder inside DJH2
            fs::copy(customFullFolderLocation,djh2Folder / id);

            //  print xml node into "Info for Tracklisting.xml"
            tinyxml2::XMLDocument infoForTracklisting = tinyxml2::XMLDocument();
            tinyxml2::XMLElement* tl = infoForTracklisting.NewElement("TrackList");
            infoForTracklisting.InsertEndChild(tl);
            auto clone = dataRow.trackRef->DeepClone(&infoForTracklisting);
            tl->InsertEndChild(clone);

            fs::path foo = djh2Folder / "Info for Tracklisting.xml";
            infoForTracklisting.SaveFile(foo.generic_string().c_str());

            //  handle TRAC strings
            fs::path bar = djh2Folder / "Info for TRAC.csv";
            std::ofstream csv = std::ofstream(bar.generic_string());

            tinyxml2::XMLElement* element;

            //MixName
            element = dataRow.trackRef->FirstChildElement("MixName");
            if(element != nullptr){
                csv << element->GetText() << "," << textData[element->GetText()] << std::endl;

                element = element->NextSiblingElement("MixName");
                if(element != nullptr){
                    csv << element->GetText() << "," << textData[element->GetText()] << std::endl;
                }
            }

            //MixArtist
            element = dataRow.trackRef->FirstChildElement("MixArtist");
            if(element != nullptr){
                csv << element->GetText() << "," << textData[element->GetText()] << std::endl;

                element = element->NextSiblingElement("MixArtist");
                if(element != nullptr){
                    csv << element->GetText() << "," << textData[element->GetText()] << std::endl;
                }
            }

            //MixHeadline
            element = dataRow.trackRef->FirstChildElement("MixHeadline");
            if(element != nullptr){
                csv << element->GetText() << "," << textData[element->GetText()] << std::endl;
            }

            //MixHeadlineDJName
            element = dataRow.trackRef->FirstChildElement("MixHeadlineDJName");
            if(element != nullptr){
                csv << element->GetText() << "," << textData[element->GetText()] << std::endl;
            }

            csv.close();
            wxLogMessage(wxString("Exported Track with id:") << id);
        }
    }
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
    tinyxml2::XMLElement* track = tracklisting.RootElement()->FirstChildElement();

    while(track != nullptr){
        TableRow row;

        std::string id = "";
        std::string name1 = "";
        std::string name2 = "";
        std::string artist1 = "";
        std::string artist2 = "";
        std::string bpm = "";

        tinyxml2::XMLElement* token = track->FirstChildElement("IDTag");
        if(token != nullptr) id = token->GetText();

        token = track->FirstChildElement("MixName");
        if(token != nullptr) {
            name1 = token->GetText();

            token = token->NextSiblingElement("MixName");
            if(token != nullptr) name2 = token->GetText();
        }

        token = track->FirstChildElement("MixArtist");
        if(token != nullptr){
            artist1 = token->GetText();

            token = token->NextSiblingElement("MixArtist");
            if(token != nullptr) artist2 = token->GetText();
        }

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

        //not shown in the table, but set anyway
        row.trackRef = track;

        mainTable->data.push_back(row);

        track = track->NextSiblingElement();
    }
    mainTable->SetItemCount(mainTable->data.size());
    mainTable->Refresh();
}

void MainWindow::OnSearch(wxCommandEvent& wxEvent){
    mainTable->Search(wxEvent.GetString().ToStdString());
}

void MainWindow::OnCloseEvent(wxCloseEvent& event){
    //check if the base folder ends with PS3
    if(!basePath.empty()){
        //wxLogMessage(wxString() << basePath.filename().generic_string());
        std::string a = basePath.filename().generic_string(); // in this case, last folder
        std::string b = "PS3";

        //make the path all caps for this comparison
        for (auto & c: a) c = toupper(c);

        if(a.compare(b) == 0){
            //they are equal
            if(!automaticRenaming){
                //then ask if the user wants to run to upper

                wxMessageDialog dialog = wxMessageDialog(this,"PS3 folder detected.\nDo you want to make all files uppercase before closing DJHCPP?",
                    "run to_upper?",wxYES_NO|wxCANCEL|wxICON_QUESTION);

                //original buttons
                //YES                       | NO    | CANCEL
                //renamed buttons
                //YES, don't ask me again   | YES   | NO
                dialog.SetYesNoCancelLabels("Yes, don't ask me again","Yes","No");

                int choice = dialog.ShowModal();

                if(choice == wxID_CANCEL) {
                    event.Skip();
                    return;
                }

                if(choice == wxID_YES){
                    //set automatic renaming to true in the settings

                    mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
                    mINI::INIStructure ini;
                    settings.read(ini);
                    ini["Settings"]["automaticRenaming"] = "true";
                    settings.write(ini);
                }
            }

            //run to upper
            wxCommandEvent fakeEvent = wxCommandEvent(wxEVT_MENU);
            ToUpper(fakeEvent);
        }
    }
    event.Skip();
}

void MainWindow::ToggleAutomaticRenaming(wxCommandEvent& event){
    automaticRenaming = !automaticRenaming;

    //update settings
    mINI::INIFile settings = mINI::INIFile(SETTINGS_FILE_NAME);
    mINI::INIStructure ini;
    settings.read(ini);
    ini["Settings"]["automaticRenaming"] = (automaticRenaming ? "true" : "false");
    settings.write(ini);

    //update menu entry
    automaticRenamingToggleMI->Check(automaticRenaming);
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

        tinyxml2::XMLDocument doc;
        doc.LoadFile(dlg.GetPath());

        tinyxml2::XMLElement* track = doc.RootElement()->FirstChildElement();
        while(track != nullptr){
            if(strcmp(track->Value(),"Track") == 0){

                const char* idtag = nullptr;
                idtag = track->ToElement()->Attribute("IDTag");
                //wxLogMessage(idtag);

                if(idtag != nullptr){
                    //find custom in loaded tracks
                    tinyxml2::XMLElement* query = tracklisting.RootElement()->FirstChildElement();
                    while(query != nullptr){
                        const char* queryID = query->FirstChildElement("IDTag")->GetText();
                        if(strcmp(idtag,queryID) == 0){
                            //we found the custom
                            wxLogMessage(wxString("Updated Track with id ") << idtag);

                            //make tracklisting the parent of trackCopy, so that we can add it later
                            tinyxml2::XMLNode* trackCopy = track->DeepClone(&tracklisting);

                            //see if <Leaderboard> is already present in the query
                            tinyxml2::XMLNode* queryLeaderboard = query->FirstChildElement("LeaderboardID");
                            tinyxml2::XMLNode* newLeaderboard = trackCopy->FirstChildElement("LeaderboardID");

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
                    /*
                    if(query == nullptr){
                        wxLogMessage(wxString("Custom with ID ") << idtag << " was not found");
                    }
                    */
                }
            }
            track = track->NextSiblingElement();
        }
        Export();
        wxLogMessage("Done Patching");
        //wxLogMessage(doc.RootElement()->FirstChild()->Value());
    }
}

MainWindow::~MainWindow(){
    curl_easy_cleanup(curlSession);
}