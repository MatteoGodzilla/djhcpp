#include <map>
#include <filesystem>
#include <fstream>
#include "wx/dirdlg.h"
#include "wx/log.h"
#include "wx/xml/xml.h"
#include "WindowBase.h"

class MainWindow : public WindowBase{
public:
    MainWindow();
    void OpenExtractedFiles( wxCommandEvent& event ) override;
    void UpdateTable();

private:
    std::map<std::string, std::string> textData;
    wxXmlDocument tracklisting;
};