#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <filesystem>
#include <wx/log.h>
#include <wx/dirdlg.h>
#include "WindowBase.h"
#include "tinyxml2.h"

class TracklistingWindow : public TracklistingGen{
public:
    TracklistingWindow(wxWindow* parent);
    void GenTracklisting( wxCommandEvent& event ) override;
    void GenBaseFolder( wxCommandEvent& event ) override;

    void ErrRequiredParameter(wxString parameter);
    void ErrInvalidParameter(wxString parameter, wxString type);

    wxString GenerateID(wxString source);

private:
    bool notEnoughParameters = false;
    bool invalidFormatParameters = false;
    bool generatedOnce = false;
};