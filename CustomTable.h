#pragma once

#include <wx/listctrl.h>
#include <wx/bmpbndl.h>
#include <wx/dcmemory.h>
#include <wx/renderer.h>
#include <vector>
#include <string>

struct TableRow{
    std::string id;
    std::string artist1;
    std::string song1;
    std::string artist2;
    std::string song2;
    float bpm;
    bool enabled = false;
    //TODO: add reference to actual xml entry
};

class CustomTable : public wxListCtrl{
public:
    CustomTable(wxWindow *parent);
    wxString OnGetItemText(long item, long column) const override;
    int OnGetItemColumnImage(long item, long column) const override;
    std::vector<TableRow> data;
    void Search(std::string query);
    void OnColumnClick(wxListEvent& event);
    static bool CompareRows(const TableRow& a, const TableRow& b, int col, int dir);
private:
    int lastSortingColumn = -1;
    //true -> a to z (increasing for bpm)
    int sortingDirection = 1; 
};