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


	rootSizer->Add( topSizer, 1, wxEXPAND|wxFIXED_MINSIZE, 5 );

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
	bottomSizer->Add( addCustomBTN, 2, wxALL|wxEXPAND, 5 );


	rootSizer->Add( bottomSizer, 1, wxEXPAND, 5 );


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

	m_menubar1->Append( fileMenu, wxT("File") );

	toolsMenu = new wxMenu();
	m_menubar1->Append( toolsMenu, wxT("Tools") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	ExtractedFilesBTN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );
	addCustomBTN->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::AddCustom ), NULL, this );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), this, OpenExtractedMI->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::AddCustom ), this, addCustomMI->GetId());
}

WindowBase::~WindowBase()
{
	// Disconnect Events
	ExtractedFilesBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );
	addCustomBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::AddCustom ), NULL, this );

}
