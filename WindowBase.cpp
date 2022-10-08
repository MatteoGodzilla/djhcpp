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

	m_searchCtrl2 = new wxSearchCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	m_searchCtrl2->ShowSearchButton( true );
	#endif
	m_searchCtrl2->ShowCancelButton( false );
	bSizer4->Add( m_searchCtrl2, 0, wxALL|wxEXPAND, 5 );


	topSizer->Add( bSizer4, 2, wxFIXED_MINSIZE, 5 );

	ExtractedFilesBTN = new wxButton( this, wxID_ANY, wxT("Open Extracted Files"), wxDefaultPosition, wxDefaultSize, 0 );
	topSizer->Add( ExtractedFilesBTN, 1, wxALL|wxEXPAND, 5 );


	rootSizer->Add( topSizer, 0, wxFIXED_MINSIZE|wxEXPAND, 5 );

	middleSizer = new wxBoxSizer( wxHORIZONTAL );


	rootSizer->Add( middleSizer, 5, wxEXPAND, 5 );

	wxBoxSizer* bottomSizer;
	bottomSizer = new wxBoxSizer( wxHORIZONTAL );

	addCustomBTN = new wxButton( this, wxID_ANY, wxT("Add Custom"), wxDefaultPosition, wxDefaultSize, 0 );
	addCustomBTN->SetFont( wxFont( 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bottomSizer->Add( addCustomBTN, 2, wxALL|wxEXPAND, 5 );


	rootSizer->Add( bottomSizer, 0, wxEXPAND, 5 );


	this->SetSizer( rootSizer );
	this->Layout();
	menuBar = new wxMenuBar( 0 );
	fileMenu = new wxMenu();
	wxMenuItem* openExtractedMI;
	openExtractedMI = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Open Extraced Files") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( openExtractedMI );

	wxMenuItem* addCustomMI;
	addCustomMI = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Add Custom") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( addCustomMI );

	wxMenuItem* updateManuallyMI;
	updateManuallyMI = new wxMenuItem( fileMenu, wxID_ANY, wxString( wxT("Update Manually") ) , wxEmptyString, wxITEM_NORMAL );
	fileMenu->Append( updateManuallyMI );

	menuBar->Append( fileMenu, wxT("File") );

	toolsMenu = new wxMenu();
	wxMenuItem* openTracklistingGeneratorMI;
	openTracklistingGeneratorMI = new wxMenuItem( toolsMenu, wxID_ANY, wxString( wxT("Open Tracklisting Generator") ) , wxEmptyString, wxITEM_NORMAL );
	toolsMenu->Append( openTracklistingGeneratorMI );

	wxMenuItem* applyPatchFileMI;
	applyPatchFileMI = new wxMenuItem( toolsMenu, wxID_ANY, wxString( wxT("Apply Patch File") ) , wxEmptyString, wxITEM_NORMAL );
	toolsMenu->Append( applyPatchFileMI );

	wxMenuItem* exportSelectedTracksMI;
	exportSelectedTracksMI = new wxMenuItem( toolsMenu, wxID_ANY, wxString( wxT("Export Selected Tracks As Customs") ) , wxEmptyString, wxITEM_NORMAL );
	toolsMenu->Append( exportSelectedTracksMI );

	toolsMenu->AppendSeparator();

	wxMenuItem* renameToUppercaseMI;
	renameToUppercaseMI = new wxMenuItem( toolsMenu, wxID_ANY, wxString( wxT("Rename to Uppercase (PS3/RPCS3 only)") ) , wxEmptyString, wxITEM_NORMAL );
	toolsMenu->Append( renameToUppercaseMI );

	automaticRenamingToggleMI = new wxMenuItem( toolsMenu, wxID_ANY, wxString( wxT("Automatic renaming when closing") ) , wxEmptyString, wxITEM_CHECK );
	#ifdef __WXMSW__
	automaticRenamingToggleMI->SetBitmaps( wxNullBitmap, wxNullBitmap );
	#endif
	toolsMenu->Append( automaticRenamingToggleMI );

	menuBar->Append( toolsMenu, wxT("Tools") );

	backupRestoreMenu = new wxMenu();
	wxMenuItem* BackupHeaderMI;
	BackupHeaderMI = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Backup") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( BackupHeaderMI );
	BackupHeaderMI->Enable( false );

	wxMenuItem* setBackupFolderMI;
	setBackupFolderMI = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Set Backup Folder ") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( setBackupFolderMI );

	wxMenuItem* manualBackupMI;
	manualBackupMI = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Manual Backup") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( manualBackupMI );

	backupRestoreMenu->AppendSeparator();

	wxMenuItem* restoreHeaderMI;
	restoreHeaderMI = new wxMenuItem( backupRestoreMenu, wxID_ANY, wxString( wxT("Restore") ) , wxEmptyString, wxITEM_NORMAL );
	backupRestoreMenu->Append( restoreHeaderMI );
	restoreHeaderMI->Enable( false );

	menuBar->Append( backupRestoreMenu, wxT("Backup/Restore") );

	this->SetMenuBar( menuBar );


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WindowBase::OnCloseEvent ) );
	m_searchCtrl2->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( WindowBase::OnSearch ), NULL, this );
	m_searchCtrl2->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( WindowBase::OnSearch ), NULL, this );
	ExtractedFilesBTN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );
	addCustomBTN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::AddCustom ), NULL, this );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), this, openExtractedMI->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::AddCustom ), this, addCustomMI->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ManualUpdate ), this, updateManuallyMI->GetId());
	toolsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::OpenTrackisting ), this, openTracklistingGeneratorMI->GetId());
	toolsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ApplyPatchFile ), this, applyPatchFileMI->GetId());
	toolsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::TracksToCustoms ), this, exportSelectedTracksMI->GetId());
	toolsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ToUpper ), this, renameToUppercaseMI->GetId());
	toolsMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ToggleAutomaticRenaming ), this, automaticRenamingToggleMI->GetId());
	backupRestoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::SetBackupFolder ), this, setBackupFolderMI->GetId());
	backupRestoreMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::ManualBackup ), this, manualBackupMI->GetId());
}

WindowBase::~WindowBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( WindowBase::OnCloseEvent ) );
	m_searchCtrl2->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( WindowBase::OnSearch ), NULL, this );
	m_searchCtrl2->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( WindowBase::OnSearch ), NULL, this );
	ExtractedFilesBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );
	addCustomBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::AddCustom ), NULL, this );

}

TracklistingGen::TracklistingGen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,500 ), wxDefaultSize );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* rootSizer;
	rootSizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* data;
	data = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* columns;
	columns = new wxBoxSizer( wxHORIZONTAL );

	songInfoPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* inputData;
	inputData = new wxGridSizer( 0, 2, 0, 0 );

	GeneralInfoTag = new wxStaticText( songInfoPanel, wxID_ANY, wxT("General Info"), wxDefaultPosition, wxDefaultSize, 0 );
	GeneralInfoTag->Wrap( -1 );
	inputData->Add( GeneralInfoTag, 0, wxALL, 5 );

	spacer1 = new wxStaticText( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	spacer1->Wrap( -1 );
	inputData->Add( spacer1, 0, wxALL, 5 );

	idLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("ID (string) *"), wxDefaultPosition, wxDefaultSize, 0 );
	idLabel->Wrap( -1 );
	inputData->Add( idLabel, 1, wxALL, 5 );

	m_textID = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textID, 1, wxALL|wxEXPAND, 5 );

	bpmLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("BPM (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	bpmLabel->Wrap( -1 );
	inputData->Add( bpmLabel, 0, wxALL, 5 );

	m_textBPM = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textBPM, 0, wxALL|wxEXPAND, 5 );

	artist1Label = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Artist 1 (string) *"), wxDefaultPosition, wxDefaultSize, 0 );
	artist1Label->Wrap( -1 );
	inputData->Add( artist1Label, 0, wxALL, 5 );

	m_textArtist1 = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textArtist1, 0, wxALL|wxEXPAND, 5 );

	song1Label = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Song 1 (string) *"), wxDefaultPosition, wxDefaultSize, 0 );
	song1Label->Wrap( -1 );
	inputData->Add( song1Label, 0, wxALL, 5 );

	m_textSong1 = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textSong1, 0, wxALL|wxEXPAND, 5 );

	artist2Label = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Artist 2 (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	artist2Label->Wrap( -1 );
	inputData->Add( artist2Label, 0, wxALL, 5 );

	m_textArtist2 = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textArtist2, 0, wxALL|wxEXPAND, 5 );

	song2Label = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Song 2 (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	song2Label->Wrap( -1 );
	inputData->Add( song2Label, 0, wxALL, 5 );

	m_textSong2 = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textSong2, 0, wxALL|wxEXPAND, 5 );

	mixedByLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Mixed By (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	mixedByLabel->Wrap( -1 );
	inputData->Add( mixedByLabel, 0, wxALL, 5 );

	m_textMixedBy = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textMixedBy, 0, wxALL|wxEXPAND, 5 );

	mixerPresentsLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Mixer Presents (string)"), wxDefaultPosition, wxDefaultSize, 0 );
	mixerPresentsLabel->Wrap( -1 );
	inputData->Add( mixerPresentsLabel, 0, wxALL, 5 );

	m_textMixerPresents = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textMixerPresents, 0, wxALL|wxEXPAND, 5 );

	DifficultiesTag = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Difficulties"), wxDefaultPosition, wxDefaultSize, 0 );
	DifficultiesTag->Wrap( -1 );
	inputData->Add( DifficultiesTag, 1, wxALL, 5 );

	spacer2 = new wxStaticText( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	spacer2->Wrap( -1 );
	inputData->Add( spacer2, 0, wxALL, 5 );

	generalDiffLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("General Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	generalDiffLabel->Wrap( -1 );
	inputData->Add( generalDiffLabel, 0, wxALL, 5 );

	m_textDiffGeneral = new wxTextCtrl( songInfoPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffGeneral, 0, wxALL|wxEXPAND, 5 );

	tapDifficultyLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Tap Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	tapDifficultyLabel->Wrap( -1 );
	inputData->Add( tapDifficultyLabel, 0, wxALL, 5 );

	m_textDiffTap = new wxTextCtrl( songInfoPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffTap, 0, wxALL|wxEXPAND, 5 );

	scratchDifficultyLAbel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Scratch Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	scratchDifficultyLAbel->Wrap( -1 );
	inputData->Add( scratchDifficultyLAbel, 0, wxALL, 5 );

	m_textDiffScratch = new wxTextCtrl( songInfoPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffScratch, 0, wxALL|wxEXPAND, 5 );

	crossfadeDifficultyLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Crossfade Difficulty (number) *"), wxDefaultPosition, wxDefaultSize, 0 );
	crossfadeDifficultyLabel->Wrap( -1 );
	inputData->Add( crossfadeDifficultyLabel, 0, wxALL, 5 );

	m_textDiffCrossfade = new wxTextCtrl( songInfoPanel, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_textDiffCrossfade, 0, wxALL|wxEXPAND, 5 );

	ExtraTag = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Extra"), wxDefaultPosition, wxDefaultSize, 0 );
	ExtraTag->Wrap( -1 );
	inputData->Add( ExtraTag, 0, wxALL, 5 );

	spacer3 = new wxStaticText( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	spacer3->Wrap( -1 );
	inputData->Add( spacer3, 0, wxALL, 5 );

	deckSpeedLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Deck Speed (number) (absolute)"), wxDefaultPosition, wxDefaultSize, 0 );
	deckSpeedLabel->Wrap( -1 );
	inputData->Add( deckSpeedLabel, 0, wxALL, 5 );

	m_textSpeed = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textSpeed->HasFlag( wxTE_MULTILINE ) )
	{
	m_textSpeed->SetMaxLength( 20 );
	}
	#else
	m_textSpeed->SetMaxLength( 20 );
	#endif
	inputData->Add( m_textSpeed, 0, wxALL|wxEXPAND, 5 );

	songDurationLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Song Duration (number)"), wxDefaultPosition, wxDefaultSize, 0 );
	songDurationLabel->Wrap( -1 );
	inputData->Add( songDurationLabel, 0, wxALL, 5 );

	m_textDuration = new wxTextCtrl( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !m_textDuration->HasFlag( wxTE_MULTILINE ) )
	{
	m_textDuration->SetMaxLength( 20 );
	}
	#else
	m_textDuration->SetMaxLength( 20 );
	#endif
	inputData->Add( m_textDuration, 0, wxALL|wxEXPAND, 5 );

	isVocalMixLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Is Vocal Mix ?"), wxDefaultPosition, wxDefaultSize, 0 );
	isVocalMixLabel->Wrap( -1 );
	inputData->Add( isVocalMixLabel, 0, wxALL, 5 );

	m_checkBoxIsVocal = new wxCheckBox( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_checkBoxIsVocal, 0, wxALL, 5 );

	includeMixInMenuLabel = new wxStaticText( songInfoPanel, wxID_ANY, wxT("Include Music in Menu?"), wxDefaultPosition, wxDefaultSize, 0 );
	includeMixInMenuLabel->Wrap( -1 );
	inputData->Add( includeMixInMenuLabel, 0, wxALL, 5 );

	m_checkBoxIsMenuMusic = new wxCheckBox( songInfoPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	inputData->Add( m_checkBoxIsMenuMusic, 0, wxALL, 5 );


	songInfoPanel->SetSizer( inputData );
	songInfoPanel->Layout();
	inputData->Fit( songInfoPanel );
	columns->Add( songInfoPanel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* outputData;
	outputData = new wxBoxSizer( wxVERTICAL );

	xmlOutput = new wxTextCtrl( this, wxID_ANY, wxT("XML here"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	outputData->Add( xmlOutput, 1, wxALL|wxEXPAND, 5 );

	csvOutput = new wxTextCtrl( this, wxID_ANY, wxT("CSV Here"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP );
	outputData->Add( csvOutput, 1, wxALL|wxEXPAND, 5 );


	columns->Add( outputData, 1, wxEXPAND, 5 );


	data->Add( columns, 1, wxEXPAND, 5 );


	rootSizer->Add( data, 6, wxEXPAND, 5 );

	wxBoxSizer* buttons;
	buttons = new wxBoxSizer( wxHORIZONTAL );

	GenerateTracklisting = new wxButton( this, wxID_ANY, wxT("Generate Tracklisting"), wxDefaultPosition, wxDefaultSize, 0 );
	buttons->Add( GenerateTracklisting, 1, wxALL|wxEXPAND, 5 );

	CreateBaseFolder = new wxButton( this, wxID_ANY, wxT("Create Base Folder"), wxDefaultPosition, wxDefaultSize, 0 );
	buttons->Add( CreateBaseFolder, 1, wxALL|wxEXPAND, 5 );


	rootSizer->Add( buttons, 1, wxEXPAND, 5 );


	this->SetSizer( rootSizer );
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

TrackInfoBase::TrackInfoBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* rootSizer;
	rootSizer = new wxBoxSizer( wxVERTICAL );

	label = new wxStaticText( this, wxID_ANY, wxT("Track XML Info"), wxDefaultPosition, wxDefaultSize, 0 );
	label->Wrap( -1 );
	rootSizer->Add( label, 0, wxALL, 5 );

	xmlInfo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB );
	rootSizer->Add( xmlInfo, 10, wxALL|wxEXPAND, 5 );

	wxBoxSizer* buttons;
	buttons = new wxBoxSizer( wxHORIZONTAL );

	deleteButton = new wxButton( this, wxID_ANY, wxT("Delete Track"), wxDefaultPosition, wxDefaultSize, 0 );
	buttons->Add( deleteButton, 1, wxALL, 5 );

	updateTrackButton = new wxButton( this, wxID_ANY, wxT("Update Track"), wxDefaultPosition, wxDefaultSize, 0 );
	buttons->Add( updateTrackButton, 1, wxALL, 5 );


	rootSizer->Add( buttons, 0, wxEXPAND, 5 );


	this->SetSizer( rootSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	deleteButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrackInfoBase::onDeleteTrack ), NULL, this );
	updateTrackButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrackInfoBase::onUpdateTrack ), NULL, this );
}

TrackInfoBase::~TrackInfoBase()
{
	// Disconnect Events
	deleteButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrackInfoBase::onDeleteTrack ), NULL, this );
	updateTrackButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TrackInfoBase::onUpdateTrack ), NULL, this );

}
