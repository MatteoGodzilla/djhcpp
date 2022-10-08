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
    std::string id;
    std::string artist1;
    std::string song1;
    std::string artist2;
    std::string song2;
    float bpm;
    //not shown
    bool enabled = false;
    tinyxml2::XMLElement* trackRef;
};

class CustomTable : public wxListCtrl{
public:
    CustomTable(wxWindow *parent);
    wxString OnGetItemText(long item, long column) const override;
    int OnGetItemColumnImage(long item, long column) const override;
    void Search(std::string query);
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
};