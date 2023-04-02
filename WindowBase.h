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
#include <wx/dataview.h>

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
		wxMenuBar* menuBar;
		wxMenu* fileMenu;
		wxMenu* windowsMenu;
		wxMenu* toolsMenu;
		wxMenuItem* automaticRenamingToggleMI;
		wxMenu* backupRestoreMenu;

		// Virtual event handlers, override them in your derived class
		virtual void OnCloseEvent( wxCloseEvent& event ) = 0;
		virtual void OnSearch( wxCommandEvent& event ) = 0;
		virtual void OpenExtractedFiles( wxCommandEvent& event ) = 0;
		virtual void AddCustom( wxCommandEvent& event ) = 0;
		virtual void ManualUpdate( wxCommandEvent& event ) = 0;
		virtual void OpenTrackisting( wxCommandEvent& event ) = 0;
		virtual void OpenTrackText( wxCommandEvent& event ) = 0;
		virtual void ApplyPatchFile( wxCommandEvent& event ) = 0;
		virtual void TracksToCustoms( wxCommandEvent& event ) = 0;
		virtual void ToUpper( wxCommandEvent& event ) = 0;
		virtual void ToggleAutomaticRenaming( wxCommandEvent& event ) = 0;
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
		wxPanel* songInfoPanel;
		wxStaticText* GeneralInfoTag;
		wxStaticText* spacer1;
		wxStaticText* idLabel;
		wxTextCtrl* m_textID;
		wxStaticText* bpmLabel;
		wxTextCtrl* m_textBPM;
		wxStaticText* artist1Label;
		wxTextCtrl* m_textArtist1;
		wxStaticText* song1Label;
		wxTextCtrl* m_textSong1;
		wxStaticText* artist2Label;
		wxTextCtrl* m_textArtist2;
		wxStaticText* song2Label;
		wxTextCtrl* m_textSong2;
		wxStaticText* mixedByLabel;
		wxTextCtrl* m_textMixedBy;
		wxStaticText* mixerPresentsLabel;
		wxTextCtrl* m_textMixerPresents;
		wxStaticText* DifficultiesTag;
		wxStaticText* spacer2;
		wxStaticText* generalDiffLabel;
		wxTextCtrl* m_textDiffGeneral;
		wxStaticText* tapDifficultyLabel;
		wxTextCtrl* m_textDiffTap;
		wxStaticText* scratchDifficultyLAbel;
		wxTextCtrl* m_textDiffScratch;
		wxStaticText* crossfadeDifficultyLabel;
		wxTextCtrl* m_textDiffCrossfade;
		wxStaticText* ExtraTag;
		wxStaticText* spacer3;
		wxStaticText* deckSpeedLabel;
		wxTextCtrl* m_textSpeed;
		wxStaticText* songDurationLabel;
		wxTextCtrl* m_textDuration;
		wxStaticText* isVocalMixLabel;
		wxCheckBox* m_checkBoxIsVocal;
		wxStaticText* includeMixInMenuLabel;
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
		wxStaticText* label;
		wxTextCtrl* xmlInfo;
		wxButton* deleteButton;
		wxButton* updateTrackButton;

		// Virtual event handlers, override them in your derived class
		virtual void onDeleteTrack( wxCommandEvent& event ) = 0;
		virtual void onUpdateTrack( wxCommandEvent& event ) = 0;


	public:

		TrackInfoBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Track Info Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~TrackInfoBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TrackTextViewer
///////////////////////////////////////////////////////////////////////////////
class TrackTextViewer : public wxFrame
{
	private:

	protected:
		wxSearchCtrl* m_searchCtrl2;
		wxDataViewListCtrl* table;
		wxDataViewColumn* m_dataViewListColumn1;
		wxDataViewColumn* m_dataViewListColumn2;

		// Virtual event handlers, override them in your derived class
		virtual void OnTextChange( wxCommandEvent& event ) { event.Skip(); }


	public:

		TrackTextViewer( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Track Text Viewer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~TrackTextViewer();

};

