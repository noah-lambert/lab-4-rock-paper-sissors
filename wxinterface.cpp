/*********************************************************************
 * Name:      	wxInterface.cpp
 * Purpose:   	Implements simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is implemented in
 * 				gui.cpp source file which is generated by wxFormBuilder.
 *********************************************************************/

#include <ctime>
#include <map>
#include <random>
#include <iostream>
#include <string>
#include <sstream>

#include "arena.h"
#include "wxinterface.h"

static const int icon_len=5;
static wxString icon[icon_len+1]={wxT(" "), wxT("O"), wxT("@"), wxT("X"), wxT("A"), wxT("B")};

static const int colors_len=5;
static wxColor colors[colors_len+2]=
    {   
        wxColor(0x808080),  // Rock, grey
        *wxWHITE,           // Paper, white
        wxColor(255,215,0), // Scissors, gold
        wxColor(0xffa500),  // A, orange
        wxColor(0xb666d2),  // B, lilac
        wxColor(0xf0f0f0),  // Dead, background
        *wxRED              // Winner, red
    };

// initialize the application
IMPLEMENT_APP(MainApp)

////////////////////////////////////////////////////////////////////////////////
// application class implementation 
////////////////////////////////////////////////////////////////////////////////

bool MainApp::OnInit()
{
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	
	// true = enter the main loop
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// main application frame implementation 
////////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{   wxClientDC draw(world);
    wxFontMetrics scale=draw.GetFontMetrics();
    
    scale_row=scale.height;
    scale_column=scale.averageWidth;
    
    world->GetSize(&max_column, &max_row);
    max_column/=scale_column;
    max_row/=scale_row;
    max_row--; // Reserve last row for status.
    arena.reset(new Arena(max_row, max_column));
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnCloseFrame(wxCloseEvent& UNUSED(event))
{
	Destroy();
}

void MainFrame::OnExitClick(wxCommandEvent& UNUSED(event))
{
	Destroy();
}

wxString &get_icon(Monster &monster)
{
    if(!monster) return icon[0];
    int a=monster.get_appearance();
    a%=icon_len;
    if(a<0) a+=icon_len;
    return icon[a+1];
}

wxColor &get_color(Monster &monster)
{
    if(!monster) return colors[colors_len];
    if(monster.won()) return colors[colors_len+1];
    int mt=monster.get_monster_type();
    mt%=colors_len;
    if(mt<0) mt+=colors_len;
    return colors[mt];
}

void MainFrame::undraw_monster(int ox, int oy)
{
    wxPaintDC draw(world);
    draw.SetBackgroundMode(wxSOLID);
    draw.SetTextBackground(colors[colors_len]);
    draw.DrawText(icon[0], ox*scale_column, oy*scale_row); 
}

void MainFrame::draw_monster(Monster &monster, int x, int y)
{
    wxPaintDC draw(world);
    draw.SetBackgroundMode(wxSOLID);
    draw.SetTextBackground(get_color(monster));
    draw.DrawText(get_icon(monster), x*scale_column, y*scale_row);
}

void MainFrame::onPaint( wxPaintEvent& UNUSED(event)) 
{   
    std::string status=arena->onPaint<MainFrame>(this);
    wxPaintDC draw(world);
    int sizex, sizey;
    
    world->GetSize(&sizex, &sizey);
    draw.SetBackgroundMode(wxSOLID);
    draw.SetTextBackground(wxColor(0xfff0f0));
    draw.DrawText(status, scale_column, sizey-scale_row);
}

void MainFrame::clock( wxTimerEvent& UNUSED(event) ) 
{   
    if(arena->clock())
        world->Refresh(false);
}