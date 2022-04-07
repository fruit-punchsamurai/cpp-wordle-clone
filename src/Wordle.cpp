
#include "Wordle.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetIcon(wxIcon(wxT(PATH_TO_ICON), wxBITMAP_TYPE_ICO));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));

	MenuBar = new wxMenuBar(0);
	MenuBar->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	FileMenu = new wxMenu();
	wxMenuItem *StartNewMenuItem;
	StartNewMenuItem = new wxMenuItem(FileMenu, ID_StartNewGame, wxString(wxT("Start New Game")), wxT("Start a new game"), wxITEM_NORMAL);
	FileMenu->Append(StartNewMenuItem);

	FileMenu->AppendSeparator();

	wxMenuItem *QuitMenuItem;
	QuitMenuItem = new wxMenuItem(FileMenu, wxID_EXIT, wxString(wxT("Quit")), wxT("Exit the game"), wxITEM_NORMAL);
	FileMenu->Append(QuitMenuItem);

	MenuBar->Append(FileMenu, wxT("New"));

	AboutMenu = new wxMenu();
	wxMenuItem *AuthorsMenuItem;
	AuthorsMenuItem = new wxMenuItem(AboutMenu, ID_Authors, wxString(wxT("Authors")), wxT("Shows info of authors"), wxITEM_NORMAL);
	AboutMenu->Append(AuthorsMenuItem);

	MenuBar->Append(AboutMenu, wxT("About"));

	this->SetMenuBar(MenuBar);

	StatusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
	wxGridBagSizer *BagSizer;
	BagSizer = new wxGridBagSizer(0, 0);
	BagSizer->SetFlexibleDirection(wxBOTH);
	BagSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	WordleTitlename = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT(PATH_TO_HEADER), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxDefaultSize, 0);
	BagSizer->Add(WordleTitlename, wxGBPosition(0, 5), wxGBSpan(2, 3), wxALL, 5);

	StatusStaticText = new wxStaticText(this, wxID_ANY, wxT("Please Start a New Game from New Menu!"), wxDefaultPosition, wxDefaultSize, 0);
	StatusStaticText->Wrap(-1);
	StatusStaticText->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	StatusStaticText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));

	BagSizer->Add(StatusStaticText, wxGBPosition(3, 8), wxGBSpan(1, 5), wxALL, 5);

	TimerStaticText = new wxStaticText(this, wxID_ANY, wxT("Timer: 00:00:00"), wxDefaultPosition, wxDefaultSize, 0);
	TimerStaticText->Wrap(-1);
	TimerStaticText->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	TimerStaticText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));

	BagSizer->Add(TimerStaticText, wxGBPosition(4, 10), wxGBSpan(1, 1), wxALL, 5);

	EnterWordText = new wxStaticText(this, wxID_ANY, wxT("Enter the word:"), wxDefaultPosition, wxDefaultSize, 0);
	EnterWordText->Wrap(-1);
	EnterWordText->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	EnterWordText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));

	BagSizer->Add(EnterWordText, wxGBPosition(3, 4), wxGBSpan(1, 2), wxALL, 5);

	TextBox = new wxTextCtrl(this, wxID_ANY, wxT("GameNotStarted"), wxDefaultPosition, wxDefaultSize, wxTE_CAPITALIZE | wxTE_PROCESS_ENTER);
#ifdef __WXGTK__
	if (!TextBox->HasFlag(wxTE_MULTILINE))
	{
		TextBox->SetMaxLength(5);
	}
#else
	TextBox->SetMaxLength(5);
#endif
	BagSizer->Add(TextBox, wxGBPosition(3, 6), wxGBSpan(1, 2), wxALL, 5);

	GameGrid = new wxGrid(this, ID_GameGrid, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	GameGrid->CreateGrid(6, 5);
	GameGrid->EnableEditing(false);
	GameGrid->EnableGridLines(true);
	GameGrid->EnableDragGridSize(false);
	GameGrid->SetMargins(0, 0);

	//make grid unselectable to be done
	GameGrid->SetSelectionBackground(wxColour(255, 255, 255, 0));
	GameGrid->SetSelectionForeground(wxColour(255, 255, 255, 0));
	GameGrid->SetCellHighlightColour(wxTransparentColour);

	// Columns
	GameGrid->SetColSize(0, 70);
	GameGrid->SetColSize(1, 70);
	GameGrid->SetColSize(2, 70);
	GameGrid->SetColSize(3, 70);
	GameGrid->SetColSize(4, 70);
	GameGrid->EnableDragColMove(false);
	GameGrid->EnableDragColSize(false);
	GameGrid->SetColLabelSize(0);
	GameGrid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	GameGrid->SetRowSize(0, 50);
	GameGrid->SetRowSize(1, 50);
	GameGrid->SetRowSize(2, 50);
	GameGrid->SetRowSize(3, 50);
	GameGrid->SetRowSize(4, 50);
	GameGrid->SetRowSize(5, 50);
	GameGrid->EnableDragRowSize(false);
	GameGrid->SetRowLabelSize(0);
	GameGrid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	GameGrid->SetDefaultCellBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
	GameGrid->SetDefaultCellTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	GameGrid->SetDefaultCellFont(wxFont(17, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Calibri")));
	GameGrid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	GameGrid->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	BagSizer->Add(GameGrid, wxGBPosition(4, 3), wxGBSpan(6, 7), wxALL, 5);

	LettersUsedText = new wxStaticText(this, wxID_ANY, wxT("LettersUsed:"), wxDefaultPosition, wxDefaultSize, 0);
	LettersUsedText->Wrap(-1);
	LettersUsedText->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	LettersUsedText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));

	BagSizer->Add(LettersUsedText, wxGBPosition(5, 10), wxGBSpan(1, 2), wxALL, 5);

	LettersUsedGrid = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	LettersUsedGrid->CreateGrid(3, 7);
	LettersUsedGrid->EnableEditing(false);
	LettersUsedGrid->EnableGridLines(false);
	LettersUsedGrid->EnableDragGridSize(false);
	LettersUsedGrid->SetMargins(0, 0);

	// Columns
	LettersUsedGrid->SetColSize(0, 30);
	LettersUsedGrid->SetColSize(1, 30);
	LettersUsedGrid->SetColSize(2, 30);
	LettersUsedGrid->SetColSize(3, 30);
	LettersUsedGrid->SetColSize(4, 30);
	LettersUsedGrid->SetColSize(5, 30);
	LettersUsedGrid->SetColSize(6, 30);
	LettersUsedGrid->EnableDragColMove(false);
	LettersUsedGrid->EnableDragColSize(false);
	LettersUsedGrid->SetColLabelSize(0);
	LettersUsedGrid->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	LettersUsedGrid->SetRowSize(0, 20);
	LettersUsedGrid->EnableDragRowSize(true);
	LettersUsedGrid->SetRowLabelSize(0);
	LettersUsedGrid->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	LettersUsedGrid->SetDefaultCellBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INFOTEXT));
	LettersUsedGrid->SetDefaultCellTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	LettersUsedGrid->SetDefaultCellAlignment(wxALIGN_CENTER, wxALIGN_CENTER);
	BagSizer->Add(LettersUsedGrid, wxGBPosition(6, 10), wxGBSpan(6, 4), wxALL, 5);

	this->SetSizer(BagSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	FileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::QuitMenuItemOnMenuSelection), this, QuitMenuItem->GetId());
	FileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnStartNewGame), this, StartNewMenuItem->GetId()); 
	AboutMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::AuthorsOnMenuSelection), this, AuthorsMenuItem->GetId());
	TextBox->Bind(wxEVT_TEXT_ENTER, wxCommandEventHandler(MainFrame::OnTextEnter), this, TextBox->GetId());
	m_timer.Bind(wxEVT_TIMER, wxTimerEventHandler(MainFrame::OnUpdateDisplayedTime), this, m_timer.GetId());
}

MainFrame::~MainFrame()
{
	// Disconnect Events
}

void MainFrame::OnStartNewGame(wxCommandEvent &event)
{
	GameGrid->ClearGrid();
	for (int i = 0; i < 6;i++)
		for (int j = 0; j < 5;j++)
			GameGrid->SetCellBackgroundColour(i, j, GameGrid->GetDefaultCellBackgroundColour());
	LettersUsedGrid->ClearGrid();
	for (int i = 0; i < 3;i++)
		for (int j = 0; j < 7;j++)
			LettersUsedGrid->SetCellBackgroundColour(i, j, LettersUsedGrid->GetDefaultCellBackgroundColour());
	TextBox->Clear();
	StatusStaticText->SetLabel("Timer will start after entering first guess.");
	Timer::OnStopTimer(&m_timer, TimerStaticText);
	TimerStaticText->SetLabel("Timer: 00:00:00");
	Game_mec::no_of_guesses = 0;
	Game_mec::gethidword();
}

void MainFrame::OnTextEnter(wxCommandEvent &event)
{
	if (Game_mec::game_started)
	{
		wxString text, temp;
		temp = TextBox->GetValue().MakeUpper();
		text = temp;
		if (text.Len() == 5)
		{
			// check if valid
			if (Game_mec::val_checker(temp.MakeLower().ToStdString()))
			{
				// start the timer
				if (Game_mec::no_of_guesses == 0)
				{
					Timer::OnTimerStart(&m_timer, TimerStaticText);
				}
				// check correct letters position and
				Game_mec::let_checker(temp.MakeLower().ToStdString());

				// clear status text
				StatusStaticText->SetLabel("");
				for (int i = 0; i < 6; i++)
				{
					if (GameGrid->GetCellValue(wxGridCellCoords(i, 0)) == "")
					{
						for (int j = 0; j < 5; j++)
						{
							GameGrid->SetCellValue(wxGridCellCoords(i, j), text.GetChar(j));
							switch (Game_mec::posn[j])
							{
							case 0: // case for wrong letter
								break;
							case 1: // case for right letter
								GameGrid->SetCellBackgroundColour(i, j, wxColour(45, 102, 4));
								break;
							case 2: // case for partially right letter
								GameGrid->SetCellBackgroundColour(i, j, wxColour(240, 158, 43));
								break;
							default:
								break;
							}
						}
						Game_mec::no_of_guesses++;
						if(Game_mec::no_of_guesses == 6){
							Timer::OnStopTimer(&m_timer, TimerStaticText);
							Game_mec::no_of_guesses = 0;
							Game_mec::game_started = false;
							temp = Game_mec::hidword;
							StatusStaticText->SetLabel("You Lost!, The word was " + temp.MakeUpper().ToStdString());
						}
						if (Game_mec::status == 1)
						{
							Timer::OnStopTimer(&m_timer, TimerStaticText);
							temp = Game_mec::hidword;
							StatusStaticText->SetLabel("You Won!, The word was " + temp.MakeUpper().ToStdString());
							Game_mec::game_started = false;
						}
						
						// call UpdateLettersUsedGrid function
						UpdateLettersUsedGrid();
						return;
					}
				}
			}
			else
				StatusStaticText->SetLabel("Invalid Word");
		}
	}
	GameGrid->ForceRefresh();
	LettersUsedGrid->ForceRefresh();
}
void MainFrame::UpdateLettersUsedGrid()
{
	wxString text = TextBox->GetValue().MakeUpper();
	for (int itr = 0; itr < 5; itr++)
	{
		wxGridCellCoords coords = LetterInGrid(text[itr]);
		if ((coords.GetRow()!=-1)&&(coords.GetCol()!=-1))
			switch (Game_mec::posn[itr])
			{
			case 0: // case for wrong letter
				break;
			case 1: // case for right letter
				LettersUsedGrid->SetCellBackgroundColour(coords.GetRow(), coords.GetCol(), wxColour(45, 102, 4));
				break;
			case 2: // case for partially right letter
				LettersUsedGrid->SetCellBackgroundColour(coords.GetRow(), coords.GetCol(), wxColour(240, 158, 43));
				break;
			default:
				break;
			}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (LettersUsedGrid->GetCellValue(wxGridCellCoords(i, j)) == "")
					{
						LettersUsedGrid->SetCellValue(wxGridCellCoords(i, j), text.GetChar(itr));
						switch (Game_mec::posn[itr])
						{
						case 0: // case for wrong letter
							break;
						case 1: // case for right letter
							LettersUsedGrid->SetCellBackgroundColour(i, j, wxColour(45, 102, 4));
							break;
						case 2: // case for partially right letter
							LettersUsedGrid->SetCellBackgroundColour(i, j, wxColour(240, 158, 43));
							break;
						default:
							break;
						}
						goto breakloop;
					}
				}
			}
		breakloop:;
		}
	}
	TextBox->SetValue("");
}

wxGridCellCoords MainFrame::LetterInGrid(wxString character)
{
	wxGridCellCoords result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (LettersUsedGrid->GetCellValue(i, j) != "" && LettersUsedGrid->GetCellValue(i, j) == character)
				return (result=wxGridCellCoords(i, j));
		}
	}
	return (result=wxGridCellCoords(-1, -1));
}

void MainFrame::OnUpdateDisplayedTime(wxTimerEvent& event)
{
	Timer::UpdateDisplayedTime(&m_timer, TimerStaticText);
}