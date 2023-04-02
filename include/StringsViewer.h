#pragma once
#include "../WindowBase.h"

class MainWindow;

class StringsViewer : public TrackTextViewer {
public:
    StringsViewer(MainWindow* parent);

    virtual void OnTextChange( wxCommandEvent& event ) override;
private:
    void RebuildTable(std::string query);

    MainWindow* mainWindowRef;
};