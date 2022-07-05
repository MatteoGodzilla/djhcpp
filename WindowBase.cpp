///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "WindowBase.h"

///////////////////////////////////////////////////////////////////////////

WindowBase::WindowBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 640,320 ), wxDefaultSize );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* rootSizer;
	rootSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* topSizer;
	topSizer = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	baseFolderLabel = new wxStaticText( this, wxID_ANY, wxT("Base Folder:"), wxDefaultPosition, wxDefaultSize, 0 );
	baseFolderLabel->Wrap( -1 );
	bSizer4->Add( baseFolderLabel, 0, wxALL, 5 );

	m_searchCtrl2 = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifndef __WXMAC__
	m_searchCtrl2->ShowSearchButton( true );
	#endif
	m_searchCtrl2->ShowCancelButton( false );
	bSizer4->Add( m_searchCtrl2, 0, wxALL|wxEXPAND, 5 );


	topSizer->Add( bSizer4, 2, wxFIXED_MINSIZE, 5 );

	ExtractedFilesBTN = new wxButton( this, wxID_ANY, wxT("Open Extracted Files"), wxDefaultPosition, wxDefaultSize, 0 );
	topSizer->Add( ExtractedFilesBTN, 1, wxALL|wxEXPAND, 5 );


	rootSizer->Add( topSizer, 0, wxFIXED_MINSIZE|wxEXPAND, 5 );

	wxBoxSizer* middleSizer;
	middleSizer = new wxBoxSizer( wxHORIZONTAL );

	mainTable = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	colID = mainTable->AppendTextColumn( wxT("ID"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	colArtist1 = mainTable->AppendTextColumn( wxT("Artist 1"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	colName1 = mainTable->AppendTextColumn( wxT("Name 1"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	colArtist2 = mainTable->AppendTextColumn( wxT("Artist 2"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	colName2 = mainTable->AppendTextColumn( wxT("Name 2"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	colBpm = mainTable->AppendTextColumn( wxT("BPM"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_LEFT), wxDATAVIEW_COL_RESIZABLE|wxDATAVIEW_COL_SORTABLE );
	middleSizer->Add( mainTable, 1, wxALL|wxEXPAND, 5 );


	rootSizer->Add( middleSizer, 5, wxEXPAND, 5 );

	wxBoxSizer* bottomSizer;
	bottomSizer = new wxBoxSizer( wxHORIZONTAL );

	addCustomBTN = new wxButton( this, wxID_ANY, wxT("Add Custom"), wxDefaultPosition, wxDefaultSize, 0 );
	addCustomBTN->SetFont( wxFont( 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bottomSizer->Add( addCustomBTN, 2, wxALL|wxEXPAND, 5 );


	rootSizer->Add( bottomSizer, 0, wxEXPAND, 5 );


	this->SetSizer( rootSizer );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* OpenExtractedMI;
	OpenExtractedMI = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Open Extraced Files") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( OpenExtractedMI );

	wxMenuItem* addCustomMI;
	addCustomMI = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Add Custom") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( addCustomMI );

	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Update Manually") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( m_menuItem3 );

	m_menubar1->Append( fileMenu, wxT("File") );

	toolsMenu = new wxMenu();
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( toolsMenu, wxID_ANY, wxString( wxT("Open Tracklisting Generator") ) , wxEmptyString, wxITEM_NORMAL );
	toolsMenu->Append( m_menuItem4 );

	m_menubar1->Append( toolsMenu, wxT("Tools") );

	backupRestoreMenu = new wxMenu();
	wxMenuItem* m_menuItem8;
	m_menuItem8 = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Backup") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( m_menuItem8 );
	m_menuItem8->Enable( false );

	wxMenuItem* m_menuItemSetBakFolder;
	m_menuItemSetBakFolder = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Set Backup Folder ") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( m_menuItemSetBakFolder );

	wxMenuItem* m_menuItemManualBak;
	m_menuItemManualBak = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Manual Backup") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( m_menuItemManualBak );

	backupRestoreMenu->AppendSeparator();

	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Restore") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( m_menuItem6 );
	m_menuItem6->Enable( false );

	m_menubar1->Append( backupRestoreMenu, wxT("Backup/Restore") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	ExtractedFilesBTN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );
	addCustomBTN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::AddCustom ), NULL, this );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), this, OpenExtractedMI->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::AddCustom ), this, addCustomMI->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ManualUpdate ), this, m_menuItem3->GetId());
	toolsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::OpenTrackisting ), this, m_menuItem4->GetId());
	backupRestoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::SetBackupFolder ), this, m_menuItemSetBakFolder->GetId());
	backupRestoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ManualBackup ), this, m_menuItemManualBak->GetId());
}

WindowBase::~WindowBase()
{
	// Disconnect Events
	ExtractedFilesBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );
	addCustomBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::AddCustom ), NULL, this );

}

TracklistingGen::TracklistingGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,500 ), wxDefaultSize );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* data;
	data = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	wxGridSizer* inputData;
	inputData = new wxGridSizer( 0, 2, 0, 0 );

	Tag1 = new wxStaticText( this, wxID_ANY, wxT("General Info"), wxDefaultPosition, wxDefaultSize, 0 );
	Tag1->Wrap( -1 );
	inputData->Add( Tag1, 0, wxALL, 5 );

	spacer1 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	spacer1->Wrap( -1 );
	inputData->Add( spacer1, 0, wxALL, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("ID (string) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	inputData->Add( m_staticText2, 1, wxALL, 5 );

	m_textID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textID, 1, wxALL|wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("BPM (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	inputData->Add( m_staticText3, 0, wxALL, 5 );

	m_textBPM = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textBPM, 0, wxALL|wxEXPAND, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Artist 1 (string) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	inputData->Add( m_staticText4, 0, wxALL, 5 );

	m_textArtist1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textArtist1, 0, wxALL|wxEXPAND, 5 );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Song 1 (string) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	inputData->Add( m_staticText5, 0, wxALL, 5 );

	m_textSong1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textSong1, 0, wxALL|wxEXPAND, 5 );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Artist 2 (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	inputData->Add( m_staticText6, 0, wxALL, 5 );

	m_textArtist2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textArtist2, 0, wxALL|wxEXPAND, 5 );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Song 2 (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	inputData->Add( m_staticText7, 0, wxALL, 5 );

	m_textSong2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textSong2, 0, wxALL|wxEXPAND, 5 );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Mixed By (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	inputData->Add( m_staticText8, 0, wxALL, 5 );

	m_textMixedBy = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textMixedBy, 0, wxALL|wxEXPAND, 5 );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Mixer Presents (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	inputData->Add( m_staticText9, 0, wxALL, 5 );

	m_textMixerPresents = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textMixerPresents, 0, wxALL|wxEXPAND, 5 );

	tag2 = new wxStaticText( this, wxID_ANY, wxT("Difficulties"), wxDefaultPosition, wxDefaultSize, 0 );
	tag2->Wrap( -1 );
	inputData->Add( tag2, 1, wxALL, 5 );

	spacer2 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	spacer2->Wrap( -1 );
	inputData->Add( spacer2, 0, wxALL, 5 );

	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("General Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	inputData->Add( m_staticText10, 0, wxALL, 5 );

	m_textDiffGeneral = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffGeneral, 0, wxALL|wxEXPAND, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Tap Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	inputData->Add( m_staticText11, 0, wxALL, 5 );

	m_textDiffTap = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffTap, 0, wxALL|wxEXPAND, 5 );

	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Scratch Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	inputData->Add( m_staticText17, 0, wxALL, 5 );

	m_textDiffScratch = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffScratch, 0, wxALL|wxEXPAND, 5 );

	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Crossfade Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	inputData->Add( m_staticText18, 0, wxALL, 5 );

	m_textDiffCrossfade = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffCrossfade, 0, wxALL|wxEXPAND, 5 );

	tag3 = new wxStaticText( this, wxID_ANY, wxT("Extra"), wxDefaultPosition, wxDefaultSize, 0 );
	tag3->Wrap( -1 );
	inputData->Add( tag3, 0, wxALL, 5 );

	spacer3 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	spacer3->Wrap( -1 );
	inputData->Add( spacer3, 0, wxALL, 5 );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Deck Speed (number) (absolute)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	inputData->Add( m_staticText21, 0, wxALL, 5 );

	m_textSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textSpeed->HasFlag( wxTE_MULTILINE ) )
	{
	m_textSpeed->SetMaxLength( 20 );
	}
	#else
	m_textSpeed->SetMaxLength( 20 );
	#endif
	inputData->Add( m_textSpeed, 0, wxALL|wxEXPAND, 5 );

	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Song Duration (number)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	inputData->Add( m_staticText22, 0, wxALL, 5 );

	m_textDuration = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textDuration->HasFlag( wxTE_MULTILINE ) )
	{
	m_textDuration->SetMaxLength( 20 );
	}
	#else
	m_textDuration->SetMaxLength( 20 );
	#endif
	inputData->Add( m_textDuration, 0, wxALL|wxEXPAND, 5 );

	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("Is Vocal Mix ?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	inputData->Add( m_staticText23, 0, wxALL, 5 );

	m_checkBoxIsVocal = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_checkBoxIsVocal, 0, wxALL, 5 );

	m_staticText24 = new wxStaticText( this, wxID_ANY, wxT("Include Music in Menu?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	inputData->Add( m_staticText24, 0, wxALL, 5 );

	m_checkBoxIsMenuMusic = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_checkBoxIsMenuMusic, 0, wxALL, 5 );


	bSizer7->Add( inputData, 1, 0, 5 );

	wxBoxSizer* outputData;
	outputData = new wxBoxSizer( wxVERTICAL );

	xmlOutput = new wxTextCtrl( this, wxID_ANY, wxT("XML here"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	outputData->Add( xmlOutput, 1, wxALL|wxEXPAND, 5 );

	csvOutput = new wxTextCtrl( this, wxID_ANY, wxT("CSV Here"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	outputData->Add( csvOutput, 1, wxALL|wxEXPAND, 5 );


	bSizer7->Add( outputData, 1, wxEXPAND, 5 );


	data->Add( bSizer7, 1, wxEXPAND, 5 );


	bSizer6->Add( data, 6, wxEXPAND, 5 );

	wxBoxSizer* buttons;
	buttons = new wxBoxSizer( wxHORIZONTAL );

	GenerateTracklisting = new wxButton( this, wxID_ANY, wxT("Generate Tracklisting"), wxDefaultPosition, wxDefaultSize, 0 );
	buttons->Add( GenerateTracklisting, 1, wxALL|wxEXPAND, 5 );

	CreateBaseFolder = new wxButton( this, wxID_ANY, wxT("Create Base Folder"), wxDefaultPosition, wxDefaultSize, 0 );
	buttons->Add( CreateBaseFolder, 1, wxALL|wxEXPAND, 5 );


	bSizer6->Add( buttons, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	GenerateTracklisting->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TracklistingGen::GenTracklisting ), NULL, this );
	CreateBaseFolder->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TracklistingGen::GenBaseFolder ), NULL, this );
}

TracklistingGen::~TracklistingGen()
{
	// Disconnect Events
	GenerateTracklisting->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TracklistingGen::GenTracklisting ), NULL, this );
	CreateBaseFolder->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TracklistingGen::GenBaseFolder ), NULL, this );

}
