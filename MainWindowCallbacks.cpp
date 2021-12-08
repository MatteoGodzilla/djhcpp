#include "MainWindow.h"
#include "wx/dirdlg.h"
#include "wx/log.h"

void MainWindow::OpenExtractedFiles(wxCommandEvent& e){
    wxDirDialog* dlg = new wxDirDialog(this,
        "Open up the WII/PS3/X360 folder", "",
        wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if(dlg->ShowModal() == wxID_OK){
        wxLogMessage(dlg->GetPath());
    }
}