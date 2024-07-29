#pragma once

#include <map>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <thread>
//external libs
#include <curl/curl.h>
#include "tinyxml2.h"
#include "mini/ini.h"
#include <openssl/sha.h>
//wxWidgets
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/progdlg.h>
//DJHCPP includes
#include "../WindowBase.h"
#include "TracklistingWindow.h"
#include "StringsViewer.h"
#include "CustomTable.h"
#include "Utils.h"
#include "DirectoryDropTarget.h"
#include "config.h"

class MainWindow : public WindowBase{
public:
    MainWindow();
    ~MainWindow();
    //File Menu items
    void OpenExtractedFiles( wxCommandEvent& event ) override;
    void AddCustom(wxCommandEvent& event) override;
    void AddCustomZip(wxCommandEvent& event) override;
    void ManualUpdate(wxCommandEvent& event) override;

    //Tools Menu items
    void OpenTrackisting( wxCommandEvent& event ) override;
    void OpenTrackText( wxCommandEvent& event ) override;
    void ApplyPatchFile( wxCommandEvent& event) override;
    void TracksToCustoms(wxCommandEvent& event) override;
    void ToUpper(wxCommandEvent& event) override;
    void ToggleAutomaticRenaming(wxCommandEvent& event) override;

    //Backup Menu items
    void SetBackupFolder( wxCommandEvent& event ) override;
    void ManualBackup( wxCommandEvent& event ) override;
    void RestoreBackup( wxCommandEvent& event ); //this is binded programmatically

    //ui events
    void OnSearch( wxCommandEvent& event ) override;
    void OnCloseEvent(wxCloseEvent& event) override;

    void CreateBackup(std::filesystem::path baseFolder, std::wstring name );
    void CreateAutomaticBackup();
    void ParseExtracted(std::filesystem::path path);
    void UpdateTable();
    void ProcessCustom(std::filesystem::path dir);
    void Export();

    CURL* curlSession = NULL;
    bool dirty = false;
    std::map<std::wstring, std::wstring> textData;
private:
    CustomTable* mainTable;
    //wxXmlDocument tracklisting;
    tinyxml2::XMLDocument tracklisting;
    std::filesystem::path basePath;
    std::filesystem::path tracklistingPath;
    std::filesystem::path tracIDPath;
    static const int LANG_COUNT = 6;
    std::wstring tracLangFiles[LANG_COUNT] = {L"TRACE.txt", L"TRACF.txt", L"TRACSNA", L"TRACS.txt", L"TRACG.txt", L"TRACI.txt"};
    //std::filesystem::path tracEPath;
    //backups
    std::filesystem::path backupFolderPath;
    bool automaticBackups = true;
    //patch files
    std::string patchFileSourceURL;
    std::string patchFileCRCURL;
    bool automaticPatching = false;
    bool automaticRenaming = false;
};