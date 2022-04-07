#include "timer.h"
//#include <iostream>

wxDateTime Timer::m_startTime;

void Timer::OnTimerStart(wxTimer *variable, wxStaticText *Text) // change parameters
{
    m_startTime = wxDateTime::Now();
    variable->Start(1000);  // every second
    //std::cout << "Timer Started" << std::endl;              
    UpdateDisplayedTime(variable, Text); // update immediatelly do not wait a second
}
void Timer::OnStopTimer(wxTimer *variable, wxStaticText *Text)
{
    variable->Stop();
    //std::cout << "Timer stopped" << std::endl;
    UpdateDisplayedTime(variable, Text);
}
void Timer::UpdateDisplayedTime(wxTimer *variable, wxStaticText *Text)
{
    if (variable->IsRunning())
    {

        wxDateTime currentTime = wxDateTime::Now();
        const wxTimeSpan ellapsedTime = currentTime - m_startTime;
        //std::cout << "current time:  "<<  ellapsedTime.Format("%H:%M:%S%l") << std::endl;
        Text->SetLabel(wxString("Time Elapsed: ") + ellapsedTime.Format("%H:%M:%S"));
    }
    else
    {
        ;
    }
}