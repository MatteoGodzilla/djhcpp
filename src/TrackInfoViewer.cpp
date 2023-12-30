#include "TrackInfoViewer.h"

using namespace tinyxml2;

TrackInfoViewer::TrackInfoViewer( wxWindow* parent, tinyxml2::XMLElement* track ) :
    TrackInfoBase( parent ) {
    trackRef = track;
    WriteTrackToTextbox();
}

void TrackInfoViewer::WriteTrackToTextbox() {
    XMLPrinter printer;
    XMLDocument doc;
    XMLNode* node = trackRef->DeepClone( &doc );
    doc.InsertEndChild( node );
    doc.Print( &printer );

    xmlInfo->Clear();
    xmlInfo->AppendText( printer.CStr() );
}

void TrackInfoViewer::onDeleteTrack( wxCommandEvent& event ) {
    wxMessageDialog* dialog = new wxMessageDialog( this, "THIS ACTION IS PERMANENT!\nDo you really want to delete this track?", "Confirm delete", wxYES_NO | wxCANCEL | wxICON_WARNING );
    if ( dialog->ShowModal() == wxID_YES ) {
        XMLDocument* realdocument = trackRef->GetDocument();
        realdocument->RootElement()->DeleteChild( trackRef );

        wxCommandEvent forceListUpdate( DJHCPP_EVT_FORCE_LIST_UPDATE );
        wxWindow* mw = GetParent()->GetParent();
        wxPostEvent( mw, forceListUpdate );

        Close();
    }
}

void TrackInfoViewer::onUpdateTrack( wxCommandEvent& event ) {
    XMLDocument doc;
    XMLError result = doc.Parse( xmlInfo->GetValue() );
    if ( result == XML_SUCCESS ) {
        XMLDocument* realdocument = trackRef->GetDocument();
        XMLNode* copy = doc.RootElement()->DeepClone( realdocument );

        //append the new one after the old one
        realdocument->RootElement()->InsertAfterChild( trackRef, copy );
        //then delete the old one
        realdocument->RootElement()->DeleteChild( trackRef );
        wxLogMessage( "Successfully updated the track information." );

        //force an update in MainWindow
        wxCommandEvent forceListUpdate( DJHCPP_EVT_FORCE_LIST_UPDATE );
        wxWindow* mw = GetParent()->GetParent();
        wxPostEvent( mw, forceListUpdate );

        Close();
    } else {
        wxLogError( wxString( "There was an error parsing the xml:\n" ) << doc.ErrorIDToName( result ) );
    }
}