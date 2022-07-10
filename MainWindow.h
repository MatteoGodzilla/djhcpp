#pragma once

#include <map>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <thread>
#include "wx/dirdlg.h"
#include "wx/textdlg.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wx/progdlg.h"
#include "tinyxml2/tinyxml2.h"
#include "mini/ini.h"
#include "WindowBase.h"
#include "TracklistingWindow.h"
#include "config.h"

class MainWindow : public WindowBase{
public:
    MainWindow();
    void OpenExtractedFiles( wxCommandEvent& event ) override;
    void AddCustom(wxCommandEvent& event) override;
    void ManualUpdate(wxCommandEvent& event) override;
    void OpenTrackisting( wxCommandEvent& event ) override;
    void SetBackupFolder( wxCommandEvent& event ) override;
    void ManualBackup( wxCommandEvent& event ) override;
    void ToUpper(wxCommandEvent& event) override;
    void RestoreBackup( wxCommandEvent& event );

    void CreateBackup(std::filesystem::path baseFolder, wxString name );
    void ParseExtracted(std::filesystem::path path);
    void UpdateTable();
    void ProcessCustom(std::filesystem::path dir);
    void Export();

private:
    std::map<std::string, std::string> textData;
    //wxXmlDocument tracklisting;
    tinyxml2::XMLDocument tracklisting;
    std::filesystem::path basePath;
    std::filesystem::path tracklistingPath;
    std::filesystem::path tracIDPath;
    std::filesystem::path tracEPath;
    //backups
    std::filesystem::path backupFolderPath;
    bool automaticBackups = true;
};