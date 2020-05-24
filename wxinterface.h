/*********************************************************************
 * Name:      	wxInterface.h
 * Purpose:   	Declares simple wxWidgets application with GUI
 * 				created using wxFormBuilder.
 * Author:    
 * Created:   
 * Copyright: 
 * License:   	wxWidgets license (www.wxwidgets.org)
 * 
 * Notes:		Note that all GUI creation code is declared in
 * 				gui.h source file which is generated by wxFormBuilder.
 *********************************************************************/

#ifndef WXINTERFACE_H
#define WXINTERFACE_H

#include <memory>
#include <set>
#include <utility>
#include <vector>

// main wxWidgets header file
#include <wx/wx.h>
#include <wx/colour.h>

// gui classes generated by wxFormBuilder
#include "arena.h"
#include "gui.h"

////////////////////////////////////////////////////////////////////////////////
// application class declaration 
////////////////////////////////////////////////////////////////////////////////

class MainApp : public wxApp
{
	public:
		virtual bool OnInit();
};

// declare global static function wxGetApp()
DECLARE_APP(MainApp)

////////////////////////////////////////////////////////////////////////////////
// main application frame declaration 
////////////////////////////////////////////////////////////////////////////////

class MainFrame : public MainFrameBase
{
private:
        int max_row, max_column,        // Size of the arena 
            scale_row, scale_column;    // Size of each character
        std::unique_ptr<Arena> arena;   // The arena
        
public:
        /**
         * @brief Construct a new GUI
         * @param parent The wxWidgets framework.
         */ 
        MainFrame( wxWindow *parent );
        
        /**
         * @brief Close the GUI.
         */
        virtual ~MainFrame();
        
        /**
         * @brief Erase a monster.
         * @param x The column where the monster was.
         * @param y The row where the monster was.
         */
        void undraw_monster(int x, int y);
        
        /**
         * @brief Draw a monster.
         * @param monster The monster to draw.
         * @param x The column where the monster is.
         * @param y The row where the monster is.
         */
        void draw_monster(Monster &monster, int x, int y);

protected:
        // protected event handlers
        virtual void OnCloseFrame( wxCloseEvent& event );
        virtual void OnExitClick( wxCommandEvent& event );
        virtual void onPaint( wxPaintEvent& event );
        virtual void clock( wxTimerEvent& event );
};

#endif //WXINTERFACE_H
