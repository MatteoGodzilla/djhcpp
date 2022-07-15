#pragma once

#include <wx/listctrl.h>
#include <vector>

struct TableRow{
    wxString id;
    wxString artist1;
    wxString song1;
    wxString artist2;
    wxString song2;
    float bpm;
};

class CustomTable : public wxListCtrl{
public:
    CustomTable(wxWindow *parent);
    wxString OnGetItemText(long item, long column) const override;
    std::vector<TableRow> data;
    void Search(wxString query);
};