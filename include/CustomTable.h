#pragma once

#include <wx/listctrl.h>
#include <wx/bmpbndl.h>
#include <wx/dcmemory.h>
#include <wx/renderer.h>
#include <wx/log.h>
#include <vector>
#include <string>
#include <list>
#include "tinyxml2.h"
#include "TrackInfoViewer.h"

struct TableRow{
    std::wstring id;
    std::wstring artist1;
    std::wstring song1;
    std::wstring artist2;
    std::wstring song2;
    float bpm;
    //not shown
    bool enabled = false;
    tinyxml2::XMLElement* trackRef;
};

class MainWindow;

class CustomTable : public wxListCtrl{
public:
    CustomTable(MainWindow *parent);
    wxString OnGetItemText(long item, long column) const override;
    int OnGetItemColumnImage(long item, long column) const override;
    void Search(std::wstring query);
    void OnColumnClick(wxListEvent& event);
    void OnKeyDown(wxListEvent& event);
    void OnActivate(wxListEvent& event);

    void SelectRow(wxListEvent& event);
    void DeselectRow(wxListEvent& event);
    static bool CompareRows(const TableRow& a, const TableRow& b, int col, int dir);

    std::vector<TableRow> data;
    std::list<long> selectedRows;
private:
    int lastSortingColumn = -1;
    //true -> a to z (increasing for bpm)
    int sortingDirection = 1;
    MainWindow* mainWindow;
};