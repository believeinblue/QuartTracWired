#include "WildcatPullingTeam.h"
#include "WildcatHelper.h"
//begin list of events in the GUI
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
//button event for durability
EVT_BUTTON(BUTTON_durability, MyFrame::Event_durability)
//button event for pulling
EVT_BUTTON(BUTTON_pulling, MyFrame::Event_pulling)
//button event for maneuverability
EVT_BUTTON(BUTTON_maneuverability, MyFrame::Event_maneuverability)
//button event for diagnostics
EVT_BUTTON(BUTTON_diagnostics, MyFrame::Event_diagnostics)
//button event for start recording
EVT_BUTTON(BUTTON_start_recording, MyFrame::Event_start_recording)
//button event for end recording
EVT_BUTTON(BUTTON_end_recording, MyFrame::Event_end_recording)
//end event list
EVT_TIMER(Timer, Update)

wxEND_EVENT_TABLE()
//application definition
wxIMPLEMENT_APP(MyApp);
//on initialization of the application
bool MyApp::OnInit()
{
    //crate the frame of the GUI and then 
    MyFrame* frame = new MyFrame("Hello World", wxPoint(50, 50), wxSize(1900, 1200));
    //show the frame, set as top option and return true
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}