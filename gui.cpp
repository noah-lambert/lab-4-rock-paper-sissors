///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 15 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	menubar = new wxMenuBar( 0 );
	filemenu = new wxMenu();
	wxMenuItem* exitmenuitem;
	exitmenuitem = new wxMenuItem( filemenu, wxID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt+X"), wxEmptyString, wxITEM_NORMAL );
	filemenu->Append( exitmenuitem );

	menubar->Append( filemenu, _("&File") );

	this->SetMenuBar( menubar );

	wxBoxSizer* mainsizer;
	mainsizer = new wxBoxSizer( wxVERTICAL );

	world = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	world->SetFont( wxFont( 18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Courier New") ) );

	mainsizer->Add( world, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( mainsizer );
	this->Layout();
	statusbar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	timer.SetOwner( this, wxID_ANY );
	timer.Start( 1000 );


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	filemenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ), this, exitmenuitem->GetId());
	world->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrameBase::onPaint ), NULL, this );
	this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainFrameBase::clock ) );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
	world->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrameBase::onPaint ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainFrameBase::clock ) );

}
