#include "MainWindow.h"

namespace fs = std::filesystem;

// copied from stack overflow:
// https://stackoverflow.com/questions/1636333/download-file-using-libcurl-in-c-c
size_t downloadPatchFile( void* buffer, size_t size, size_t nmemb, FILE* userp ) {
    size_t written = fwrite( buffer, size, nmemb, userp );
    // wxLogMessage(wxString()<<nmemb);
    return written;
}

// this would probably fail if the packet size is not 64 chars, but less
size_t checkSHA( void* buffer, size_t size, size_t nmemb, void* userp ) {
    std::string remoteSHA;
    // 0xff is a byte, but it has 2 chars written in it
    remoteSHA.resize( SHA256_DIGEST_LENGTH * 2 );
    memcpy( remoteSHA.data(), buffer, SHA256_DIGEST_LENGTH * 2 );

    // wxLogMessage(wxString() << nmemb);

    // open patch file
    std::ifstream patchFile( PATCH_FILE_NAME, std::ios::binary );
    if ( patchFile.is_open() ) {
        std::stringstream sstr;
        sstr << patchFile.rdbuf();
        std::string data = sstr.str();

        std::cout << data.length() << std::endl;

        unsigned char dataSHABuffer[SHA256_DIGEST_LENGTH];
        SHA256_CTX context;
        SHA256_Init( &context );
        SHA256_Update( &context, data.data(), data.length() );
        SHA256_Final( dataSHABuffer, &context );

        std::stringstream dataSHAstream;
        dataSHAstream << std::hex;
        for ( int i = 0; i < SHA256_DIGEST_LENGTH; i++ ) {
            dataSHAstream << std::setw( 2 ) << std::setfill( '0' )
                          << (int)dataSHABuffer[i];
        }

        std::string dataSHA = dataSHAstream.str();

        if ( remoteSHA == dataSHA ) {
            // wxLogMessage("SHA256 is Valid! Yay!");
            return nmemb;
        } else {
            wxLogError(
            "There was a conflict between the SHA256 codes of the remote "
            "and local patch files." );
            wxLogMessage( "Remote" );
            wxLogMessage( wxString( remoteSHA ) );
            wxLogMessage( "Downloaded File" );
            wxLogMessage( wxString( dataSHAstream.str() ) );
        }
        return 1;
    }

    return 0;
}

MainWindow::MainWindow() :
    WindowBase( NULL ) {
    SetLabel( "DJHCPP v" + DJHCPP_VERSION + "    [" + DJHCPP_BUILD + "]" );

    Bind( DJHCPP_EVT_FORCE_LIST_UPDATE, &MainWindow::ManualUpdate, this );

    mainTable = new CustomTable( this );
    middleSizer->Add( mainTable, 1, wxALL | wxEXPAND, 5 );

    DirectoryDropTarget* dropTarget = new DirectoryDropTarget( this );
    SetDropTarget( dropTarget );

    // get absolute path of where the exe is running
    fs::path exePath = GetRunningPathOfExecutable();

    // set icon
    fs::path imageFile = exePath.parent_path() / "icon.png";
    if ( fs::exists( imageFile ) ) {
        wxImage::AddHandler( new wxPNGHandler() );
        // icon.LoadFile("icon.png");
        SetIcon( wxIcon( imageFile.c_str(), wxBitmapType::wxBITMAP_TYPE_PNG ) );
    }

    // wxLogMessage(exePath.c_str());
    fs::path settingsFile = exePath.parent_path() / SETTINGS_FILE_NAME;

    mINI::INIFile settings = mINI::INIFile( settingsFile.generic_string() );
    mINI::INIStructure ini;

    if ( fs::exists( settingsFile ) )
        settings.read( ini );

    // write the settings file
    if ( !ini["Settings"].has( "baseFolder" ) ) {
        ini["Settings"]["baseFolder"] = "";
        basePath = "";
    } else {
        basePath = fs::path( ini["Settings"]["baseFolder"] );
    }

    if ( !ini["Settings"].has( "backupFolderPath" ) ) {
        backupFolderPath = fs::current_path() / "djhcpp_backups";
        fs::create_directory( backupFolderPath );
        ini["Settings"]["backupFolderPath"] = backupFolderPath.string();
    } else {
        backupFolderPath = fs::path( ini["Settings"]["backupFolderPath"] );
    }

    if ( !ini["Settings"].has( "automaticBackups" ) ) {
        ini["Settings"]["automaticBackups"] = "true";
        automaticBackups = true;
    } else {
        automaticBackups = ini["Settings"]["automaticBackups"] == "true";
    }

    if ( !ini["Settings"].has( "patchFileSourceURL" ) ) {
        ini["Settings"]["patchFileSourceURL"] = "";
        patchFileSourceURL = "";
    } else {
        patchFileSourceURL = ini["Settings"]["patchFileSourceURL"];
    }

    if ( !ini["Settings"].has( "patchFileCRCURL" ) ) {
        ini["Settings"]["patchFileCRCURL"] = "";
        patchFileCRCURL = "";
    } else {
        patchFileCRCURL = ini["Settings"]["patchFileCRCURL"];
    }

    if ( !ini["Settings"].has( "automaticPatching" ) ) {
        ini["Settings"]["automaticPatching"] = "false";
        automaticPatching = false;
    } else {
        automaticPatching = ini["Settings"]["automaticPatching"] == "true";
    }

    if ( !ini["Settings"].has( "automaticRenaming" ) ) {
        ini["Settings"]["automaticRenaming"] = "false";
        automaticRenaming = false;
    } else {
        automaticRenaming = ini["Settings"]["automaticRenaming"] == "true";
    }

    settings.write( ini );

    // program start

    if ( basePath.empty() )
        return;

    ParseExtracted( basePath );

    for ( auto& dirEntry : fs::directory_iterator( backupFolderPath ) ) {
        if ( dirEntry.is_directory() ) {
            std::wstring text = dirEntry.path().filename().wstring();
            wxMenuItem* entry =
            new wxMenuItem( backupRestoreMenu, wxID_ANY, text, wxEmptyString, wxITEM_NORMAL );
            wxStringClientData* data =
            new wxStringClientData( wxString( dirEntry.path().string() ) );

            backupRestoreMenu->Append( entry );
            // i spent 2 hours trying to figure out how bind works. Rip me
            backupRestoreMenu->Bind( wxEVT_MENU, &MainWindow::RestoreBackup, this, entry->GetId(), -1, (wxObject*)data );
        }
    }

    automaticRenamingToggleMI->Check( automaticRenaming );

    // patch file stuff
    if ( patchFileSourceURL.empty() || patchFileCRCURL.empty() )
        return;

    // initialize curl
    curlSession = curl_easy_init();
    // wxLogMessage(wxString() << (uint64_t)curlSession);
    if ( curlSession ) {
        FILE* fp = fopen( PATCH_FILE_NAME.c_str(), "wb" );
        curl_easy_setopt( curlSession, CURLOPT_URL, patchFileSourceURL.c_str() );
        curl_easy_setopt( curlSession, CURLOPT_WRITEFUNCTION, downloadPatchFile );
        curl_easy_setopt( curlSession, CURLOPT_WRITEDATA, fp );
        CURLcode success = curl_easy_perform( curlSession );
        fclose( fp );
        // check CRC
        curl_easy_setopt( curlSession, CURLOPT_URL, patchFileCRCURL.c_str() );
        curl_easy_setopt( curlSession, CURLOPT_WRITEFUNCTION, checkSHA );
        success = curl_easy_perform( curlSession );
        // wxLogMessage(wxString() << success);
    }
}

void MainWindow::OpenExtractedFiles( wxCommandEvent& event ) {
    wxDirDialog* dialog =
    new wxDirDialog( this, "Open WII/PS3/X360 folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST );

    if ( dialog->ShowModal() == wxID_OK ) {
        // std::filesystem::path p = std::filesystem::path(dialog->GetPath());
        basePath = fs::path( dialog->GetPath().ToStdWstring() );
        wxLogMessage( wxString( basePath ) );
        ParseExtracted( basePath );
    }
}

void MainWindow::ParseExtracted( fs::path path ) {
    tracklistingPath = path / "AUDIO" / "Audiotracks" / "tracklisting.xml";
    tracIDPath = path / "Text" / "TRAC" / "TRACID.txt";
    fs::path tracEPath = path / "Text" / "TRAC" / "TRACE.txt";
    // fix these paths if it's under linux
    tracklistingPath = FindFileCaseInsensitive( path, tracklistingPath );
    tracIDPath = FindFileCaseInsensitive( path, tracIDPath );
    tracEPath = FindFileCaseInsensitive( path, tracEPath );

    // std::cout << tracklistingPath << " : " << tracIDPath << ": " << tracEPath
    // << std::endl;

    if ( fs::exists( tracklistingPath ) && fs::exists( tracIDPath ) && fs::exists( tracEPath ) ) {
        // wxLogMessage("Extracted Files found");
        // load text string
        std::wifstream tracIDStream = std::wifstream( tracIDPath );
        std::wifstream tracEStream = std::wifstream( tracEPath );

        textData.clear();
        textData.insert(
        std::make_pair( std::wstring( L"" ),
                        std::wstring( L"" ) ) ); // default when string is empty

        while ( !tracIDStream.eof() ) {
            std::wstring id;
            std::wstring value;
            std::getline( tracIDStream, id );
            std::getline( tracEStream, value, L'\0' );
            if ( id.back() == L'\r' )
                id = id.substr( 0, id.size() - 1 );
            if ( value.back() == L'\r' )
                value = value.substr( 0, value.size() - 1 );

            textData.insert( std::make_pair( id, value ) );
        }

        // load tracklisting
        tracklisting.LoadFile( tracklistingPath.generic_string().c_str() );
        // count how many songs were loaded
        size_t count = 0;
        tinyxml2::XMLElement* track =
        tracklisting.RootElement()->FirstChildElement();
        do {
            count++;
            track = track->NextSiblingElement();
        } while ( track != nullptr );

        wxLogMessage( wxString( "Successfully loaded " ) << count << " songs from tracklisting." );

        addCustomBTN->Enable( true );
        addCustomMI->Enable(true);
        addCustomZipBTN->Enable( true );
        addCustomZipMI->Enable(true);
        updateManuallyMI->Enable(true);
        // ApplyPatchFile->Enable(true);
        exportSelectedTracksMI->Enable(true);
        openTrackTextViewer->Enable(true);
        renameToUppercaseMI->Enable(true);

        UpdateTable();
        // add backup
        CreateAutomaticBackup();
        baseFolderLabel->SetLabelText( wxString( "Base Folder:  " ) << path.c_str() );

        // set in the settings
        mINI::INIFile settings = mINI::INIFile( SETTINGS_FILE_NAME );
        mINI::INIStructure ini;
        settings.read( ini );
        ini["Settings"]["baseFolder"] = path.string();
        settings.write( ini );
    } else {
        wxLogError( "Tracklisting file not found (error 0x1)" );
    }
}

void MainWindow::CreateAutomaticBackup() {
    if ( !automaticBackups )
        return;
    time_t t = time( NULL );
    tm* now = localtime( &t );
    wchar_t dateFolder[31];
    // format table is present here:
    // https://cplusplus.com/reference/ctime/strftime/
    std::wcsftime( dateFolder, 30, L"%Y-%m-%d_%H-%M-%S", now );
    CreateBackup( backupFolderPath, dateFolder );
}

void MainWindow::AddCustomZip( wxCommandEvent& event){
    wxFileDialog* dialog = new wxFileDialog(this, "Open zip file", "", "", "Zip files (*.zip)|*.zip",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    if(dialog->ShowModal() == wxID_OK){
        wxArrayString paths;
        dialog->GetPaths(paths);

        bit7z::Bit7zLibrary lib("7z.dll");
        bit7z::BitFileExtractor extractor(lib, bit7z::BitFormat::Zip);
        extractor.setOverwriteMode(bit7z::OverwriteMode::Overwrite);

        for(size_t i = 0; i < paths.GetCount(); i++){
            fs::path outputPath = fs::temp_directory_path() / "djhcpp" / std::to_string(i);
            //library does not support wide strings
            std::string filePath = paths[i].ToStdString();
            extractor.extract(filePath, outputPath.generic_string());
            bit7z::BitArchiveReader archiveReader(lib, filePath, bit7z::BitFormat::Zip);
            //find the DJH2 folder
            for ( auto& item : archiveReader.items() ) {
                if(item.name() == "DJH2" && item.isDir()){
                    fs::path filesToImport = outputPath / item.path();
                    ProcessCustom(filesToImport);
                }
            }
        }
    }
}

void MainWindow::AddCustom( wxCommandEvent& event ) {
    wxDirDialog* dialog = new wxDirDialog( this, "Open Custom's folder", "",
        wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST | wxDD_MULTIPLE );
    if ( dialog->ShowModal() == wxID_OK ) {
        wxArrayString paths;
        dialog->GetPaths( paths );

        bool showOverwriteDialog = true; //???
        for ( size_t i = 0; i < paths.GetCount(); i++ ) {
            fs::path dir = fs::path( paths[i].ToStdWstring() );
            if ( fs::exists( dir / "DJH2" ) )
                dir /= "DJH2";

            ProcessCustom( dir );
        }
    }
}

void MainWindow::ProcessCustom( fs::path dir ) {
    // importing tracklisting info
    fs::path customTracklisting = dir / "Info for Tracklisting.xml";
    fs::path customTextData = dir / "Info for TRAC.csv";
    customTracklisting = FindFileCaseInsensitive( dir, customTracklisting );
    customTextData = FindFileCaseInsensitive( dir, customTextData );

    tinyxml2::XMLDocument doc;
    if ( !fs::exists( customTracklisting ) ) {
        wxLogError( "'Info for Tracklisting.xml' file not found" );
        return;
    }

    tinyxml2::XMLError errorID =
    doc.LoadFile( customTracklisting.generic_string().c_str() );
    if ( errorID != tinyxml2::XML_SUCCESS ) {
        wxLogError( wxString( "XML Error: " ) << errorID );
        if ( errorID == tinyxml2::XML_ERROR_FILE_NOT_FOUND ) {
            wxLogError(
            "There was a problem loading 'Info for Tracklisting.xml'. Make "
            "sure "
            "that the path to the file contains only standard "
            "characters." );
        }
        return;
    }

    tinyxml2::XMLNode* track = doc.RootElement()->FirstChild();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    while ( track != nullptr ) {
        // identical
        if ( strcmp( track->Value(), "Track" ) == 0 ) {
            std::wstring addingTag = converter.from_bytes( track->FirstChildElement( "IDTag" )->GetText() );

            tinyxml2::XMLElement* tracklistingRoot = tracklisting.RootElement();
            tinyxml2::XMLNode* tracklistingTrack =
            tracklistingRoot->FirstChild();
            tinyxml2::XMLNode* possibleRemove = nullptr;

            while ( tracklistingTrack != nullptr ) {
                tinyxml2::XMLElement* IDTag =
                tracklistingTrack->FirstChildElement( "IDTag" );
                if ( IDTag != nullptr ) {
                    std::wstring trackTestingID = converter.from_bytes( IDTag->GetText() );
                    if ( trackTestingID == addingTag ) {
                        wxLogMessage( wxString( "Replacing track node: " ) << addingTag );
                        possibleRemove = tracklistingTrack;
                    }
                }
                tracklistingTrack = tracklistingTrack->NextSibling();
            }
            // to insert a node in tracklisting that node needs to be own
            // already by tracklisting with DeepClone we get a copy that is own
            // by tracklisting that is safe to add to the root;
            if ( possibleRemove != nullptr )
                tracklistingRoot->DeleteChild( possibleRemove );

            tinyxml2::XMLNode* copy = track->DeepClone( &tracklisting );
            tracklistingRoot->InsertEndChild( copy );
            wxLogMessage( wxString( "Added track node: " ) << addingTag );
        }
        track = track->NextSibling();
    }

    // importing text data
    std::ifstream textDataStream = std::ifstream( customTextData.generic_string() );
    std::string line;
    while ( std::getline( textDataStream, line ) ) {
        if ( line.find( "//" ) != std::string::npos )
            continue;
        if ( line.length() == 0 )
            continue;

        bool insideQuotes = false;
        std::vector<std::wstring> tokens;
        tokens.emplace_back( L"" );
        char previousChar = '\0';

        for ( size_t i = 0; i < line.length(); i++ ) {
            char c = line[i];
            if ( c == '"' ) {
                insideQuotes = !insideQuotes;
                if ( previousChar == '"' ) {
                    // in the csv standard, if there are two "" that is
                    // considered as the " literal
                    tokens.back() += '"';
                    previousChar = '\0';
                } else
                    previousChar = c;
            } else if ( c == ',' && !insideQuotes ) {
                // we found the comma separator and we're not in something in
                // quotes, so we're good to go to parse the next token (by
                // pushing an empty string)
                tokens.emplace_back( L"" );
                previousChar = c;
            } else {
                tokens.back() += c;
                previousChar = c;
            }
        }
        if ( tokens.size() > 1 ) {
            textData.insert_or_assign( tokens[0], tokens[1] );
        }
    }

    // copy files to location
    fs::path rootAudiotracks = basePath / "AUDIO" / "Audiotracks";
    rootAudiotracks = FindFileCaseInsensitive( basePath, rootAudiotracks );

    for ( auto& path : fs::directory_iterator( dir ) ) {
        if ( fs::is_directory( path ) ) {
            // only copy inner subfolders and skip "info for ..." files
            fs::path destination = rootAudiotracks;
            destination /= path.path().filename().generic_string();
            // wxLogMessage(destination.generic_string().c_str());
            fs::copy( path, destination, fs::copy_options::recursive | fs::copy_options::overwrite_existing );
        }
    }
    dirty = true;
    UpdateTable();
    Export();
}

void MainWindow::ManualUpdate( wxCommandEvent& e ) {
    UpdateTable();
    Export();
}

void MainWindow::Export() {
    tracklisting.SaveFile( tracklistingPath.generic_string().c_str() );

    std::wofstream trackIDStream( tracIDPath );
    if ( trackIDStream.is_open() ) {
        for ( auto& pair : textData ) {
            if ( pair.first != std::wstring( L"" ) ) {
                trackIDStream << pair.first << L"\n";
            }
        }
        trackIDStream.close();

        for ( int i = 0; i < LANG_COUNT; i++ ) {
            std::filesystem::path p =
            basePath / "Text" / "TRAC" / tracLangFiles[i];

            if ( !fs::exists( p ) )
                continue;

            std::ofstream trackLangStream( p, std::ios::binary);
            if ( trackLangStream.is_open() ) {
                for ( auto& pair : textData ) {
                    if ( pair.first != std::wstring( L"" ) ) {
                        trackLangStream << pair.second << '\0';
                    }
                }

                trackLangStream.close();
            }
        }
    }
    wxLogMessage( "Successfully updated the game's files" );
}

void MainWindow::TracksToCustoms( wxCommandEvent& event ) {
    wxDirDialog* dialog =
    new wxDirDialog( this, "Select a folder to export the customs to", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST );
    if ( dialog->ShowModal() == wxID_OK ) {
        // get all of the selected tracks in the table
        fs::path containingFolder = fs::path( dialog->GetPath().ToStdWstring() );
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        for ( int row : mainTable->selectedRows ) {
            // for each one
            TableRow dataRow = mainTable->data[row];
            //  get the id from track
            std::wstring id = dataRow.id;
            //  create root id with that name
            fs::create_directory( containingFolder / id );
            //  create DJH2 folder inside it
            fs::path djh2Folder = containingFolder / id / "DJH2";
            fs::create_directory( djh2Folder );
            //  get folderLocation from track

            std::wstring folderLocation = converter.from_bytes( dataRow.trackRef->FirstChildElement( "FolderLocation" )->GetText() );
            fs::path customFullFolderLocation =
            basePath / fs::path( folderLocation );
            // std::cout << customFullFolderLocation << std::endl;
            //   copy that folder inside DJH2
            fs::copy( customFullFolderLocation, djh2Folder / id );

            //  print xml node into "Info for Tracklisting.xml"
            tinyxml2::XMLDocument infoForTracklisting = tinyxml2::XMLDocument();
            tinyxml2::XMLElement* tl =
            infoForTracklisting.NewElement( "TrackList" );
            infoForTracklisting.InsertEndChild( tl );
            auto clone = dataRow.trackRef->DeepClone( &infoForTracklisting );
            tl->InsertEndChild( clone );

            fs::path foo = djh2Folder / "Info for Tracklisting.xml";
            infoForTracklisting.SaveFile( foo.generic_string().c_str() );

            //  handle TRAC strings
            fs::path bar = djh2Folder / "Info for TRAC.csv";
            std::wofstream csv = std::wofstream( bar.generic_string() );

            tinyxml2::XMLElement* element;

            // MixName
            element = dataRow.trackRef->FirstChildElement( "MixName" );
            if ( element != nullptr ) {
                std::wstring elmText = converter.from_bytes( element->GetText() );
                csv << elmText << "," << textData[elmText] << std::endl;

                element = element->NextSiblingElement( "MixName" );
                elmText = converter.from_bytes( element->GetText() );
                if ( element != nullptr ) {
                    csv << elmText << "," << textData[elmText] << std::endl;
                }
            }

            // MixArtist
            element = dataRow.trackRef->FirstChildElement( "MixArtist" );
            if ( element != nullptr ) {
                std::wstring elmText = converter.from_bytes( element->GetText() );
                csv << elmText << "," << textData[elmText] << std::endl;

                element = element->NextSiblingElement( "MixArtist" );
                elmText = converter.from_bytes( element->GetText() );
                if ( element != nullptr ) {
                    csv << elmText << "," << textData[elmText] << std::endl;
                }
            }

            // MixHeadline
            element = dataRow.trackRef->FirstChildElement( "MixHeadline" );
            if ( element != nullptr ) {
                std::wstring elmText = converter.from_bytes( element->GetText() );
                csv << elmText << "," << textData[elmText] << std::endl;
            }

            // MixHeadlineDJName
            element = dataRow.trackRef->FirstChildElement( "MixHeadlineDJName" );
            if ( element != nullptr ) {
                std::wstring elmText = converter.from_bytes( element->GetText() );
                csv << elmText << "," << textData[elmText] << std::endl;
            }

            csv.close();
            wxLogMessage( wxString( "Exported Track with id:" ) << id );
        }
    }
}

void MainWindow::SetBackupFolder( wxCommandEvent& event ) {
    wxDirDialog* dialog =
    new wxDirDialog( this, "Open Custom's folder", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST );
    if ( dialog->ShowModal() == wxID_OK ) {
        fs::path path = fs::path( dialog->GetPath().ToStdWstring() );
        mINI::INIFile settings = mINI::INIFile( SETTINGS_FILE_NAME );
        mINI::INIStructure ini;
        settings.read( ini );
        ini["Settings"]["backupFolderPath"] = path.string();
        settings.write( ini );
    }
}

void MainWindow::ManualBackup( wxCommandEvent& event ) {
    std::wstring text =
    wxGetTextFromUser( "Please enter the name of the backup:", "Caption", wxEmptyString, this )
    .ToStdWstring();
    CreateBackup( backupFolderPath, text );
}

void MainWindow::CreateBackup( std::filesystem::path baseFolder, std::wstring name ) {
    if ( fs::exists( baseFolder ) ) {
        fs::path thisBackup = baseFolder / name;
        fs::create_directory( thisBackup );

        fs::copy_file( tracklistingPath, thisBackup / "tracklisting.xml" );
        fs::copy_file( tracIDPath, thisBackup / "TRACID.txt" );
        for ( int i = 0; i < LANG_COUNT; i++ ) {
            std::filesystem::path p =
            basePath / "Text" / "TRAC" / tracLangFiles[i];

            if ( fs::exists( p ) )
                fs::copy_file( p, thisBackup / tracLangFiles[i] );
        }

        // add another entry to the menu
        wxMenuItem* entry = new wxMenuItem( backupRestoreMenu, wxID_ANY, name, wxEmptyString, wxITEM_NORMAL );
        wxStringClientData* data =
        new wxStringClientData( wxString( thisBackup.string() ) );

        backupRestoreMenu->Append( entry );
        backupRestoreMenu->Bind( wxEVT_MENU, &MainWindow::RestoreBackup, this, entry->GetId(), -1, (wxObject*)data );
    } else {
        wxLogWarning(
        "Backup folder path specified in the settings does not exist. "
        "Backup Aborted" );
    }
}

void MainWindow::RestoreBackup( wxCommandEvent& event ) {
    // std::cout << event.GetId() << std::endl;
    wxStringClientData* data = (wxStringClientData*)event.GetEventUserData();
    if ( !tracklistingPath.empty() && !tracIDPath.empty() ) {
        fs::path src( data->GetData().ToStdWstring() );
        fs::copy_options copyOptions;
        copyOptions |= fs::copy_options::overwrite_existing;
        fs::path backupTracklisting = src / "tracklisting.xml";
        fs::path backupTrackID = src / "TRACID.txt";
        // fix file names if necessary (probably overkill)
        backupTracklisting = FindFileCaseInsensitive( src, backupTracklisting );
        backupTrackID = FindFileCaseInsensitive( src, backupTrackID );

        fs::copy( backupTracklisting, tracklistingPath, copyOptions );
        fs::copy( backupTrackID, tracIDPath, copyOptions );

        for ( int i = 0; i < LANG_COUNT; i++ ) {
            fs::path backupTrackLang = src / tracLangFiles[i];
            backupTrackLang = FindFileCaseInsensitive( src, backupTrackLang );
            std::filesystem::path p =
            basePath / "Text" / "TRAC" / tracLangFiles[i];

            if ( fs::exists( p ) )
                fs::copy( backupTrackLang, p, copyOptions );
        }

        // refresh extracted files and start again
        ParseExtracted( basePath );
    }
}

void MainWindow::UpdateTable() {
    mainTable->data.clear();
    tinyxml2::XMLElement* track =
    tracklisting.RootElement()->FirstChildElement();

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    while ( track != nullptr ) {
        TableRow row;

        std::wstring id = L"";
        std::wstring name1 = L"";
        std::wstring name2 = L"";
        std::wstring artist1 = L"";
        std::wstring artist2 = L"";
        std::wstring bpm = L"";

        tinyxml2::XMLElement* token = track->FirstChildElement( "IDTag" );
        if ( token != nullptr )
            id = converter.from_bytes( token->GetText() );

        token = track->FirstChildElement( "MixName" );
        if ( token != nullptr ) {
            name1 = converter.from_bytes( token->GetText() );

            token = token->NextSiblingElement( "MixName" );
            if ( token != nullptr )
                name2 = converter.from_bytes( token->GetText() );
        }

        token = track->FirstChildElement( "MixArtist" );
        if ( token != nullptr ) {
            artist1 = converter.from_bytes( token->GetText() );

            token = token->NextSiblingElement( "MixArtist" );
            if ( token != nullptr )
                artist2 = converter.from_bytes( token->GetText() );
        }

        token = track->FirstChildElement( "BPM" );
        if ( token != nullptr )
            bpm = converter.from_bytes( token->GetText() );

        row.id = id;

        // if artist1 is empty -> ""
        // if artist1 is not empty
        //   if textData contains key -> textData[key]
        //   else "[key]"

        if ( artist1.empty() )
            row.artist1 = L"";
        else {
            if ( textData.count( artist1 ) == 1 )
                row.artist1 = textData[artist1];
            else
                row.artist1 = "[" + artist1 + "]";
        }

        if ( name1.empty() )
            row.song1 = L"";
        else {
            if ( textData.count( name1 ) == 1 )
                row.song1 = textData[name1];
            else
                row.song1 = "[" + name1 + "]";
        }

        if ( artist2.empty() )
            row.artist2 = L"";
        else {
            if ( textData.count( artist2 ) == 1 )
                row.artist2 = textData[artist2];
            else
                row.artist2 = "[" + artist2 + "]";
        }

        if ( name2.empty() )
            row.song2 = L"";
        else {
            if ( textData.count( name2 ) == 1 )
                row.song2 = textData[name2];
            else
                row.song2 = "[" + name2 + "]";
        }

        row.bpm = std::stof( bpm );
        const char* name;
        name = track->ToElement()->Attribute( "selectableinfem" );

        if ( name != 0 ) {
            if ( strcmp( name, "yes" ) == 0 || strcmp( name, "true" ) == 0 )
                row.enabled = true;
            // wxLogMessage(wxString() << id << " " << name);
        }

        // not shown in the table, but set anyway
        row.trackRef = track;

        mainTable->data.push_back( row );

        track = track->NextSiblingElement();
    }
    mainTable->SetItemCount( mainTable->data.size() );
    mainTable->Refresh();
}

void MainWindow::OnSearch( wxCommandEvent& wxEvent ) {
    mainTable->Search( wxEvent.GetString().ToStdWstring() );
}

void MainWindow::OnCloseEvent( wxCloseEvent& event ) {
    // check if the base folder ends with PS3
    if ( !basePath.empty() && dirty ) {
        // wxLogMessage(wxString() << basePath.filename().generic_string());
        std::wstring a = basePath.filename().generic_wstring();
        // in this case, last folder
        std::wstring b = L"PS3";

        // make the path all caps for this comparison
        for ( auto& c : a )
            c = toupper( c );

        if ( a.compare( b ) == 0 ) {
            // they are equal
            if ( !automaticRenaming ) {
                // then ask if the user wants to run to upper

                wxMessageDialog dialog = wxMessageDialog(
                this,
                "PS3 folder detected.\nDo you want to make all files "
                "uppercase "
                "before closing DJHCPP?",
                "run to_upper?", wxYES_NO | wxCANCEL | wxICON_QUESTION );

                // original buttons
                // YES                       | NO    | CANCEL
                // renamed buttons
                // YES, don't ask me again   | YES   | NO
                dialog.SetYesNoCancelLabels( "Yes, don't ask me again", "Yes", "No" );

                int choice = dialog.ShowModal();

                if ( choice == wxID_CANCEL ) {
                    event.Skip();
                    return;
                }

                if ( choice == wxID_YES ) {
                    // set automatic renaming to true in the settings

                    mINI::INIFile settings = mINI::INIFile( SETTINGS_FILE_NAME );
                    mINI::INIStructure ini;
                    settings.read( ini );
                    ini["Settings"]["automaticRenaming"] = "true";
                    settings.write( ini );
                }
            }

            // run to upper
            wxCommandEvent fakeEvent = wxCommandEvent( wxEVT_MENU );
            ToUpper( fakeEvent );
        }
    }
    event.Skip();
}

void MainWindow::ToggleAutomaticRenaming( wxCommandEvent& event ) {
    automaticRenaming = !automaticRenaming;

    // update settings
    mINI::INIFile settings = mINI::INIFile( SETTINGS_FILE_NAME );
    mINI::INIStructure ini;
    settings.read( ini );
    ini["Settings"]["automaticRenaming"] = ( automaticRenaming ? "true" : "false" );
    settings.write( ini );

    // update menu entry
    automaticRenamingToggleMI->Check( automaticRenaming );
}

// other windows and tools

void MainWindow::OpenTrackisting( wxCommandEvent& event ) {
    TracklistingWindow* twin = new TracklistingWindow( this );
    twin->Show();
}

void MainWindow::OpenTrackText( wxCommandEvent& event ) {
    StringsViewer* text = new StringsViewer( this );
    text->Show();
};

void MainWindow::ToUpper( wxCommandEvent& event ) {
    if ( !basePath.empty() ) {
        // check if the files are in a FAT file system
        std::wstring filesystem = GetFileSystemTypeFromPath( basePath );
        if ( filesystem.find( L"FAT", 0 ) != std::wstring::npos ) {
            std::wstring message = L"Unsupported Filesystem detected: " + filesystem + L"\n";
            message += L"Renaming a file to the same name in uppercase does not work on FAT filesystems.\n";
            message += L"Please move the files so they are inside a disk formatted differently.\n";
            wxMessageDialog* confirm = new wxMessageDialog( this, message, "Invalid file system format found", wxOK );
            if ( confirm->ShowModal() )
                return;
        }

        wxProgressDialog* dialog = new wxProgressDialog( "Progress", "Renaming the files. Please wait a few seconds", 100, this );
        dialog->Show();
        dialog->Pulse();

        for ( auto& item : fs::recursive_directory_iterator( basePath ) ) {
            fs::path rel = fs::relative( item.path(), basePath );
            std::wstring upperPath = rel.generic_wstring();

            for ( wchar_t& ch : upperPath ) {
                ch = std::toupper( ch );
            }

            fs::path destination = fs::path( upperPath );
            fs::rename( basePath / rel, basePath / destination );

            // show files to the user
            dialog->Pulse();
        }
        dialog->Destroy();
    } else {
        wxLogWarning( "Please load the extracted files before renaming" );
    }
}

void MainWindow::ApplyPatchFile( wxCommandEvent& event ) {
    if ( basePath.empty() ) {
        wxLogWarning( "Please load extracted files before applying patch files" );
        return;
    }

    wxFileDialog dlg( this, "Select Patch File", "", "", "XML Files (*.xml)|*.xml" );
    if ( dlg.ShowModal() == wxID_OK ) {
        CreateAutomaticBackup();

        tinyxml2::XMLDocument doc;
        doc.LoadFile( dlg.GetPath() );

        tinyxml2::XMLElement* track = doc.RootElement()->FirstChildElement();
        while ( track != nullptr ) {
            if ( strcmp( track->Value(), "Track" ) == 0 ) {
                const char* idtag = nullptr;
                idtag = track->ToElement()->Attribute( "IDTag" );
                // wxLogMessage(idtag);

                if ( idtag != nullptr ) {
                    // find custom in loaded tracks
                    tinyxml2::XMLElement* query =
                    tracklisting.RootElement()->FirstChildElement();
                    while ( query != nullptr ) {
                        const char* queryID =
                        query->FirstChildElement( "IDTag" )->GetText();
                        if ( strcmp( idtag, queryID ) == 0 ) {
                            // we found the custom
                            wxLogMessage( wxString( "Updated Track with id " ) << idtag );

                            // make tracklisting the parent of trackCopy, so
                            // that we can add it later
                            tinyxml2::XMLNode* trackCopy =
                            track->DeepClone( &tracklisting );

                            // see if <Leaderboard> is already present in the
                            // query
                            tinyxml2::XMLNode* queryLeaderboard =
                            query->FirstChildElement( "LeaderboardID" );
                            tinyxml2::XMLNode* newLeaderboard =
                            trackCopy->FirstChildElement( "LeaderboardID" );

                            if ( newLeaderboard != nullptr ) {
                                // we must patch something
                                if ( queryLeaderboard != nullptr ) {
                                    query->DeleteChild( queryLeaderboard );
                                }
                                query->InsertEndChild( newLeaderboard );
                            }
                            break;
                        }
                        query = query->NextSiblingElement();
                    }
                }
            }
            track = track->NextSiblingElement();
        }
        Export();
        wxLogMessage( "Done Patching" );
    }
}

MainWindow::~MainWindow() {
    if ( curlSession )
        curl_easy_cleanup( curlSession );
}