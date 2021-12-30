#pragma once

#include <map>
#include <filesystem>
#include <fstream>
#include "wx/dirdlg.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "tinyxml2/tinyxml2.h"
#include "WindowBase.h"
#include "config.h"

class MainWindow : public WindowBase{
public:
    MainWindow();
    void OpenExtractedFiles( wxCommandEvent& event ) override;
    void AddCustom(wxCommandEvent& event) override;
    void ManualUpdate(wxCommandEvent& event) override;
    void UpdateTable();
    //bool CheckDuplicateID(std::string path);
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
};