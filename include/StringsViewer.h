#pragma once
#include "../WindowBase.h"
#include <map>

class MainWindow;

class StringsViewer : public TrackTextViewer {
public:
    StringsViewer(MainWindow* parent);

    virtual void OnTextChange( wxCommandEvent& event ) override;
    virtual void OnEditingDone( wxDataViewEvent& event ) override;
    virtual void onFinalize( wxCommandEvent& event ) override;
private:
    void RebuildTable(std::string query);
    std::map<std::string, std::string> localTextData;
    MainWindow* mainWindowRef;
};