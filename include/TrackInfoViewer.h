#pragma once
#include <wx/log.h>
#include <wx/msgdlg.h>
#include "../WindowBase.h"
#include "CustomEvents.h"
#include "tinyxml2.h"

class TrackInfoViewer : public TrackInfoBase{
public:
    TrackInfoViewer(wxWindow* parent,tinyxml2::XMLElement* track);
    void WriteTrackToTextbox();

    //events override
    virtual void onDeleteTrack( wxCommandEvent& event ) override;
    virtual void onUpdateTrack( wxCommandEvent& event ) override;
private:
    tinyxml2::XMLElement* trackRef;
};