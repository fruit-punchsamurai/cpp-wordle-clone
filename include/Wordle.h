
#pragma once
#include <wx/app.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>
// #include <wx/timer.h>
#include <fstream>
#include "gamemechanics.h"
// #include "timer.h"

#define PATH_TO_HEADER "../../img/wordlename.bmp"
#define PATH_TO_ICON "../../img/Wordle.ico"


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////


class MainFrame : public wxFrame
{
	private:

	protected:
		enum
		{
			ID_Authors = 1000,
			ID_TextBox = 1001,
			ID_StartNewGame = 1002,
			ID_GameGrid = 1003,
			ID_LettersUsedGrid = 1004,
			ID_Timer = 1005
		};

		wxMenuBar* MenuBar;
		wxMenu* FileMenu;
		wxMenu* AboutMenu;
		wxStatusBar* StatusBar;
		wxStaticBitmap* WordleTitlename;
		wxStaticText* StatusStaticText;
		wxStaticText* TimerStaticText;
		wxStaticText *EnterWordText;
		wxTextCtrl* TextBox;
		wxGrid* GameGrid;
		wxStaticText* LettersUsedText;
		wxGrid* LettersUsedGrid;

		//Timer functions remainging 
		// Time_data *timervar;
		// wxTimer timer;

		// event handlers
		void OnStartNewGame(wxCommandEvent &event);
		void QuitMenuItemOnMenuSelection(wxCommandEvent &event) { Close(true); }
		void AuthorsOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }

		//to do things after user enters the text
		void OnTextEnter(wxCommandEvent &event);
		void UpdateLettersUsedGrid();

		//for timer
		// void OnTimer(wxTimerEvent &event);

		//To check if letter is in used grid
		wxGridCellCoords LetterInGrid(wxString character);

		//to deselct grid cells


	public:

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Wordle"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 624,549 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU );

		~MainFrame();

};

// wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
//     EVT_TIMER(ID_Timer, MainFrame::OnTimer)
// wxEND_EVENT_TABLE()
