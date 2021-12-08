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
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	baseFolderLabel = new wxStaticText( this, wxID_ANY, wxT("Base Folder:"), wxDefaultPosition, wxDefaultSize, 0 );
	baseFolderLabel->Wrap( -1 );
	bSizer4->Add( baseFolderLabel, 0, wxALL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	searchLabel = new wxStaticText( this, wxID_ANY, wxT("Search:"), wxDefaultPosition, wxDefaultSize, 0 );
	searchLabel->Wrap( -1 );
	bSizer5->Add( searchLabel, 0, wxALL|wxEXPAND, 5 );

	searchBox = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( searchBox, 1, wxALL|wxEXPAND, 5 );


	bSizer4->Add( bSizer5, 3, wxEXPAND, 5 );


	bSizer3->Add( bSizer4, 3, wxEXPAND, 5 );

	ExtractedFilesBTN = new wxButton( this, wxID_ANY, wxT("Open Extracted Files"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( ExtractedFilesBTN, 1, wxALL|wxEXPAND, 5 );


	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	mainTable = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( mainTable, 1, wxALL|wxEXPAND, 5 );


	bSizer2->Add( bSizer6, 5, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	addCustomBTN = new wxButton( this, wxID_ANY, wxT("Add Custom"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( addCustomBTN, 2, wxALL|wxEXPAND, 5 );


	bSizer2->Add( bSizer8, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
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
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), this, OpenExtractedMI->GetId());
}

WindowBase::~WindowBase()
{
	// Disconnect Events
	ExtractedFilesBTN->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( WindowBase::OpenExtractedFiles ), NULL, this );

}
