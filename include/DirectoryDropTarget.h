#pragma once
#include <wx/dnd.h>
#include <wx/log.h>
#include <filesystem>

class MainWindow;

class DirectoryDropTarget : public wxFileDropTarget {
public:
    DirectoryDropTarget(MainWindow* parent);
    bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames) override;
private:
    MainWindow* mainWindow;
};