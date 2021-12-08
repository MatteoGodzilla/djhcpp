#include "MainWindow.h"

MainWindow::MainWindow() : WindowBase(NULL) {}

void MainWindow::OpenExtractedFiles( wxCommandEvent& event ){
    wxDirDialog* dialog = new wxDirDialog(this,
    "Open WII/PS3/X360 folder", "",
    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if(dialog->ShowModal() == wxID_OK){
        wxLogMessage(dialog->GetPath());
    }
}