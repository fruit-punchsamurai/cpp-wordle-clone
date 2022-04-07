#include "Wordle.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MainFrame *frame = new MainFrame(NULL);
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);