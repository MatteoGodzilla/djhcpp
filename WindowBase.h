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
#include <wx/textctrl.h>
#include <wx/checkbox.h>

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
		virtual void ManualUpdate( wxCommandEvent& event ) = 0;


	public:

		WindowBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("DJHCPP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,480 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~WindowBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TracklistingGen
///////////////////////////////////////////////////////////////////////////////
class TracklistingGen : public wxFrame
{
	private:

	protected:
		wxStaticText* Tag1;
		wxStaticText* spacer1;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrl3;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrl4;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textCtrl5;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl6;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textCtrl7;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_textCtrl8;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textCtrl9;
		wxStaticText* m_staticText9;
		wxTextCtrl* m_textCtrl10;
		wxStaticText* tag2;
		wxStaticText* spacer2;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textCtrl11;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textCtrl12;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_textCtrl13;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textCtrl14;
		wxStaticText* tag3;
		wxStaticText* spacer3;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textCtrl17;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textCtrl18;
		wxStaticText* m_staticText23;
		wxCheckBox* m_checkBox1;
		wxStaticText* m_staticText24;
		wxCheckBox* m_checkBox2;
		wxTextCtrl* xmlOutput;
		wxTextCtrl* csvOutput;
		wxButton* GenerateTracklisting;
		wxButton* CreateBaseFolder;

	public:

		TracklistingGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Tracklisting Generator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 766,693 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~TracklistingGen();

};

