#include "WindowBase.h"
#include "wx/dirdlg.h"
#include "wx/log.h"

class MainWindow : public WindowBase{
public:
    MainWindow();
    void OpenExtractedFiles( wxCommandEvent& event ) override;
};