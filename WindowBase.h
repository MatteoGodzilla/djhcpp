///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/srchctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/dataview.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class WindowBase
///////////////////////////////////////////////////////////////////////////////
class WindowBase : public wxFrame
{
	private:

	protected:
		wxStaticText* baseFolderLabel;
		wxSearchCtrl* m_searchCtrl2;
		wxButton* ExtractedFilesBTN;
		wxDataViewListCtrl* mainTable;
		wxDataViewColumn* colID;
		wxDataViewColumn* colArtist1;
		wxDataViewColumn* colName1;
		wxDataViewColumn* colArtist2;
		wxDataViewColumn* colName2;
		wxDataViewColumn* colBpm;
		wxButton* addCustomBTN;
		wxMenuBar* m_menubar1;
		wxMenu* fileMenu;
		wxMenu* toolsMenu;

		// Virtual event handlers, override them in your derived class
		virtual void OpenExtractedFiles( wxCommandEvent& event ) = 0;
		virtual void AddCustom( wxCommandEvent& event ) = 0;


	public:

		WindowBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("DJHCPP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~WindowBase();

};

