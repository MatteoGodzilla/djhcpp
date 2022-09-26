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
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>

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
		wxBoxSizer* middleSizer;
		wxButton* addCustomBTN;
		wxMenuBar* m_menubar1;
		wxMenu* fileMenu;
		wxMenu* toolsMenu;
		wxMenu* backupRestoreMenu;

		// Virtual event handlers, override them in your derived class
		virtual void OnSearch( wxCommandEvent& event ) = 0;
		virtual void OpenExtractedFiles( wxCommandEvent& event ) = 0;
		virtual void AddCustom( wxCommandEvent& event ) = 0;
		virtual void ManualUpdate( wxCommandEvent& event ) = 0;
		virtual void OpenTrackisting( wxCommandEvent& event ) = 0;
		virtual void ToUpper( wxCommandEvent& event ) = 0;
		virtual void ApplyPatchFile( wxCommandEvent& event ) = 0;
		virtual void SetBackupFolder( wxCommandEvent& event ) = 0;
		virtual void ManualBackup( wxCommandEvent& event ) = 0;


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
		wxPanel* m_panel2;
		wxStaticText* Tag1;
		wxStaticText* spacer1;
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textID;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textBPM;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textArtist1;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textSong1;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textArtist2;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_textSong2;
		wxStaticText* m_staticText8;
		wxTextCtrl* m_textMixedBy;
		wxStaticText* m_staticText9;
		wxTextCtrl* m_textMixerPresents;
		wxStaticText* tag2;
		wxStaticText* spacer2;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textDiffGeneral;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textDiffTap;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_textDiffScratch;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textDiffCrossfade;
		wxStaticText* tag3;
		wxStaticText* spacer3;
		wxStaticText* m_staticText21;
		wxTextCtrl* m_textSpeed;
		wxStaticText* m_staticText22;
		wxTextCtrl* m_textDuration;
		wxStaticText* m_staticText23;
		wxCheckBox* m_checkBoxIsVocal;
		wxStaticText* m_staticText24;
		wxCheckBox* m_checkBoxIsMenuMusic;
		wxTextCtrl* xmlOutput;
		wxTextCtrl* csvOutput;
		wxButton* GenerateTracklisting;
		wxButton* CreateBaseFolder;

		// Virtual event handlers, override them in your derived class
		virtual void GenTracklisting( wxCommandEvent& event ) = 0;
		virtual void GenBaseFolder( wxCommandEvent& event ) = 0;


	public:

		TracklistingGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Tracklisting Generator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 766,723 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~TracklistingGen();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TrackInfoBase
///////////////////////////////////////////////////////////////////////////////
class TrackInfoBase : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText24;
		wxTextCtrl* xmlInfo;
		wxButton* deleteButton;
		wxButton* updateTrack;

		// Virtual event handlers, override them in your derived class
		virtual void onDeleteTrack( wxCommandEvent& event ) = 0;
		virtual void onUpdateTrack( wxCommandEvent& event ) = 0;


	public:

		TrackInfoBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Track Info Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~TrackInfoBase();

};

