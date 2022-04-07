
#pragma once
#include <wx/datetime.h>
#include <wx/timer.h>
#include <wx/stattext.h>

class Timer
{
public:
    static wxDateTime m_startTime;
    //starts Timer
    static void OnTimerStart(wxTimer *variable, wxStaticText* Text);
    //stops Timer
    static void OnStopTimer(wxTimer *variable, wxStaticText* Text);
    //Updates the Time in Display
    static void UpdateDisplayedTime(wxTimer *variable, wxStaticText* Text);
};
