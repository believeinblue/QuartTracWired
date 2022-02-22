//---------------------------------------
//SharpClean
//Authors: David Pippen and Tyler Dishman
//---------------------------------------
#include "WildcatPullingTeam.h"
#include "WildcatHelper.h"
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstdlib>
#include "wx/progdlg.h"

using namespace std;

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, "Sharp Clean")
{
    //create menue
    wxMenu* menuFile = new wxMenu;
    //adds Hello to the menue
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    //adds a seperator
    menuFile->AppendSeparator();
    //adds an exit button to the menue
    menuFile->Append(wxID_EXIT);
    //makes the help menue
    wxMenu* menuHelp = new wxMenu;
    //adds an about to the help menue
    menuHelp->Append(wxID_ABOUT);
    //adds menue bar
    wxMenuBar* menuBar = new wxMenuBar;
    //adds hello menue and the help menue
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    //adds the menue bar to the top of the GUI
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome Wildcat PullingTeam GO CATS!");
    //adds durability button
    event_durability = new wxButton(this, BUTTON_durability, "Durability", wxPoint(10, 10), wxSize(150, 50));
    //adds pulling team button
    event_pulling = new wxButton(this, BUTTON_pulling, "Pulling", wxPoint(10, 110), wxSize(150, 50));
    //adds maneuverability button
    event_maneuverability = new wxButton(this, BUTTON_maneuverability, "Maneuverability", wxPoint(10, 210), wxSize(150, 50));
    //adds diagnostics button
    event_diagnostics = new wxButton(this, BUTTON_diagnostics, "Diagnostics", wxPoint(10, 310), wxSize(150, 50));
    //add start recording button
    event_start_recording = new wxButton(this, BUTTON_start_recording, "Start Recording", wxPoint(10, 410), wxSize(150, 50));
    //adds end recording button
    event_end_recording = new wxButton(this, BUTTON_end_recording, "End Recording", wxPoint(10, 510), wxSize(150, 50));

    //adds all 10 gauges
    gauge1 = new wxGauge(this, Gauge1, 100, wxPoint(225, 60), wxSize(500, 20));
    gauge2 = new wxGauge(this, Gauge2, 100, wxPoint(825, 60), wxSize(500, 20));
    gauge3 = new wxGauge(this, Gauge3, 100, wxPoint(225, 210), wxSize(500, 20));
    gauge4 = new wxGauge(this, Gauge4, 100, wxPoint(825, 210), wxSize(500, 20));
    gauge5 = new wxGauge(this, Gauge5, 100, wxPoint(225, 360), wxSize(500, 20));
    gauge6 = new wxGauge(this, Gauge6, 100, wxPoint(825, 360), wxSize(500, 20));
    gauge7 = new wxGauge(this, Gauge7, 100, wxPoint(225, 510), wxSize(500, 20));
    gauge8 = new wxGauge(this, Gauge8, 100, wxPoint(825, 510), wxSize(500, 20));
    gauge9 = new wxGauge(this, Gauge9, 100, wxPoint(225, 660), wxSize(500, 20));
    gauge10 = new wxGauge(this, Gauge10, 100, wxPoint(825, 660), wxSize(500, 20));

    //gauge 1 min label
    gauge1MIN = new wxTextCtrl(this, TEXT_G1MIN, "MIN", wxPoint(225, 80), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    wxFont font = gauge1MIN->GetFont();
    font.SetPointSize(15);
    gauge1MIN->SetFont(font);

    //gauge 1 max label
    gauge1MAX = new wxTextCtrl(this, TEXT_G1MAX, "MAX", wxPoint(675, 80), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge1MAX->GetFont();
    font.SetPointSize(15);
    gauge1MAX->SetFont(font);

    //gauge 1 current value label
    gauge1CUR = new wxTextCtrl(this, TEXT_G1CUR, "CUR", wxPoint(450, 80), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge1CUR->GetFont();
    font.SetPointSize(15);
    gauge1CUR->SetFont(font);
    gauge1CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge1CUR->SetValue("");
    gauge1CUR->AppendText("CUR");

    //gauge 1 title label
    gauge1TITLE = new wxTextCtrl(this, TEXT_G1TITLE, "Title of Sensor", wxPoint(350, 10), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge1TITLE->GetFont();
    font.SetPointSize(15);
    gauge1TITLE->SetFont(font);

    //gauge 2
    //gauge 2 min label
    gauge2MIN = new wxTextCtrl(this, TEXT_G2MIN, "MIN", wxPoint(835, 80), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge2MIN->GetFont();
    font.SetPointSize(15);
    gauge2MIN->SetFont(font);

    //gauge 2 max label
    gauge2MAX = new wxTextCtrl(this, TEXT_G2MAX, "MAX", wxPoint(1275, 80), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge2MAX->GetFont();
    font.SetPointSize(15);
    gauge2MAX->SetFont(font);

    //gauge 2 current value label
    gauge2CUR = new wxTextCtrl(this, TEXT_G2CUR, "CUR", wxPoint(1050, 80), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge2CUR->GetFont();
    font.SetPointSize(15);
    gauge2CUR->SetFont(font);
    gauge2CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge2CUR->SetValue("");
    gauge2CUR->AppendText("CUR");

    //gauge 2 title label
    gauge2TITLE = new wxTextCtrl(this, TEXT_G2TITLE, "Title of Sensor", wxPoint(950, 10), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge2TITLE->GetFont();
    font.SetPointSize(15);
    gauge2TITLE->SetFont(font);

    //gauge 3
    //gauge 3 min label
    gauge3MIN = new wxTextCtrl(this, TEXT_G3MIN, "MIN", wxPoint(225, 230), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge3MIN->GetFont();
    font.SetPointSize(15);
    gauge3MIN->SetFont(font);

    //gauge 3 max label
    gauge3MAX = new wxTextCtrl(this, TEXT_G3MAX, "MAX", wxPoint(675, 230), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge3MAX->GetFont();
    font.SetPointSize(15);
    gauge3MAX->SetFont(font);

    //gauge 3 current value label
    gauge3CUR = new wxTextCtrl(this, TEXT_G3CUR, "CUR", wxPoint(450, 230), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge3CUR->GetFont();
    font.SetPointSize(15);
    gauge3CUR->SetFont(font);
    gauge3CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge3CUR->SetValue("");
    gauge3CUR->AppendText("CUR");

    //gauge 3 title label
    gauge3TITLE = new wxTextCtrl(this, TEXT_G3TITLE, "Title of Sensor", wxPoint(350, 160), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge3TITLE->GetFont();
    font.SetPointSize(15);
    gauge3TITLE->SetFont(font);

    //gauge 4
    //gauge 4 min label
    gauge4MIN = new wxTextCtrl(this, TEXT_G4MIN, "MIN", wxPoint(825, 230), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge4MIN->GetFont();
    font.SetPointSize(15);
    gauge4MIN->SetFont(font);

    //gauge 4 max label
    gauge4MAX = new wxTextCtrl(this, TEXT_G4MAX, "MAX", wxPoint(1275, 230), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge4MAX->GetFont();
    font.SetPointSize(15);
    gauge4MAX->SetFont(font);

    //gauge 4 current value label
    gauge4CUR = new wxTextCtrl(this, TEXT_G4CUR, "CUR", wxPoint(1050, 230), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge4CUR->GetFont();
    font.SetPointSize(15);
    gauge4CUR->SetFont(font);
    gauge4CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge4CUR->SetValue("");
    gauge4CUR->AppendText("CUR");

    //gauge 4 title label
    gauge4TITLE = new wxTextCtrl(this, TEXT_G4TITLE, "Title of Sensor", wxPoint(950, 160), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge4TITLE->GetFont();
    font.SetPointSize(15);
    gauge4TITLE->SetFont(font);

    //gauge 5
    //gauge 5 min label
    gauge5MIN = new wxTextCtrl(this, TEXT_G5MIN, "MIN", wxPoint(225, 380), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge5MIN->GetFont();
    font.SetPointSize(15);
    gauge5MIN->SetFont(font);

    //gauge 5 max label
    gauge5MAX = new wxTextCtrl(this, TEXT_G5MAX, "MAX", wxPoint(675, 380), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge5MAX->GetFont();
    font.SetPointSize(15);
    gauge5MAX->SetFont(font);

    //gauge 5 current value label
    gauge5CUR = new wxTextCtrl(this, TEXT_G5CUR, "CUR", wxPoint(450, 380), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge5CUR->GetFont();
    font.SetPointSize(15);
    gauge5CUR->SetFont(font);
    gauge5CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge5CUR->SetValue("");
    gauge5CUR->AppendText("CUR");

    //gauge 5 title label
    gauge5TITLE = new wxTextCtrl(this, TEXT_G5TITLE, "Title of Sensor", wxPoint(350, 310), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge5TITLE->GetFont();
    font.SetPointSize(15);
    gauge5TITLE->SetFont(font);

    //gauge 6
    //gauge 6 min label
    gauge6MIN = new wxTextCtrl(this, TEXT_G6MIN, "MIN", wxPoint(825, 380), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge6MIN->GetFont();
    font.SetPointSize(15);
    gauge6MIN->SetFont(font);

    //gauge 6 max label
    gauge6MAX = new wxTextCtrl(this, TEXT_G6MAX, "MAX", wxPoint(1275, 380), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge6MAX->GetFont();
    font.SetPointSize(15);
    gauge6MAX->SetFont(font);

    //gauge 6 current value label
    gauge6CUR = new wxTextCtrl(this, TEXT_G6CUR, "CUR", wxPoint(1050, 380), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge6CUR->GetFont();
    font.SetPointSize(15);
    gauge6CUR->SetFont(font);
    gauge6CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge6CUR->SetValue("");
    gauge6CUR->AppendText("CUR");

    //gauge 6 title label
    gauge6TITLE = new wxTextCtrl(this, TEXT_G6TITLE, "Title of Sensor", wxPoint(950, 310), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge6TITLE->GetFont();
    font.SetPointSize(15);
    gauge6TITLE->SetFont(font);

    //gauge 7
    //gauge 7 min label
    gauge7MIN = new wxTextCtrl(this, TEXT_G7MIN, "MIN", wxPoint(225, 530), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge7MIN->GetFont();
    font.SetPointSize(15);
    gauge7MIN->SetFont(font);

    //gauge 7 max label
    gauge7MAX = new wxTextCtrl(this, TEXT_G7MAX, "MAX", wxPoint(675, 530), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge7MAX->GetFont();
    font.SetPointSize(15);
    gauge7MAX->SetFont(font);

    //gauge 7 current value label
    gauge7CUR = new wxTextCtrl(this, TEXT_G7CUR, "CUR", wxPoint(450, 530), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge7CUR->GetFont();
    font.SetPointSize(15);
    gauge7CUR->SetFont(font);
    gauge7CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge7CUR->SetValue("");
    gauge7CUR->AppendText("CUR");

    //gauge 7 title label
    gauge7TITLE = new wxTextCtrl(this, TEXT_G7TITLE, "Title of Sensor", wxPoint(350, 460), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge7TITLE->GetFont();
    font.SetPointSize(15);
    gauge7TITLE->SetFont(font);

    //gauge 8
    //gauge 8 min label
    gauge8MIN = new wxTextCtrl(this, TEXT_G8MIN, "MIN", wxPoint(825, 530), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge8MIN->GetFont();
    font.SetPointSize(15);
    gauge8MIN->SetFont(font);

    //gauge 8 max label
    gauge8MAX = new wxTextCtrl(this, TEXT_G8MAX, "MAX", wxPoint(1275, 530), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge8MAX->GetFont();
    font.SetPointSize(15);
    gauge8MAX->SetFont(font);

    //gauge 8 current value label
    gauge8CUR = new wxTextCtrl(this, TEXT_G8CUR, "CUR", wxPoint(1050, 530), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge8CUR->GetFont();
    font.SetPointSize(15);
    gauge8CUR->SetFont(font);
    gauge8CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge8CUR->SetValue("");
    gauge8CUR->AppendText("CUR");

    //gauge 8 title label
    gauge8TITLE = new wxTextCtrl(this, TEXT_G8TITLE, "Title of Sensor", wxPoint(950, 460), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge8TITLE->GetFont();
    font.SetPointSize(15);
    gauge8TITLE->SetFont(font);

    //gauge 9
    //gauge 9 min label
    gauge9MIN = new wxTextCtrl(this, TEXT_G9MIN, "MIN", wxPoint(225, 680), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge9MIN->GetFont();
    font.SetPointSize(15);
    gauge9MIN->SetFont(font);

    //gauge 9 max label
    gauge9MAX = new wxTextCtrl(this, TEXT_G9MAX, "MAX", wxPoint(675, 680), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge9MAX->GetFont();
    font.SetPointSize(15);
    gauge9MAX->SetFont(font);

    //gauge 9 current value label
    gauge9CUR = new wxTextCtrl(this, TEXT_G9CUR, "CUR", wxPoint(450, 680), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge9CUR->GetFont();
    font.SetPointSize(15);
    gauge9CUR->SetFont(font);
    gauge9CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge9CUR->SetValue("");
    gauge9CUR->AppendText("CUR");

    //gauge 9 title label
    gauge9TITLE = new wxTextCtrl(this, TEXT_G9TITLE, "Title of Sensor", wxPoint(350, 610), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge9TITLE->GetFont();
    font.SetPointSize(15);
    gauge9TITLE->SetFont(font);

    //gauge 10
    //gauge 10 min label
    gauge10MIN = new wxTextCtrl(this, TEXT_G10MIN, "MIN", wxPoint(825, 680), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge10MIN->GetFont();
    font.SetPointSize(15);
    gauge10MIN->SetFont(font);

    //gauge 10 max label
    gauge10MAX = new wxTextCtrl(this, TEXT_G10MAX, "MAX", wxPoint(1275, 680), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge10MAX->GetFont();
    font.SetPointSize(15);
    gauge10MAX->SetFont(font);

    //gauge 10 current value label
    gauge10CUR = new wxTextCtrl(this, TEXT_G10CUR, "CUR", wxPoint(1050, 680), wxSize(50, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge10CUR->GetFont();
    font.SetPointSize(15);
    gauge10CUR->SetFont(font);
    gauge10CUR->SetDefaultStyle(wxTextAttr(*wxRED, *wxGREEN));
    gauge10CUR->SetValue("");
    gauge10CUR->AppendText("CUR");

    //gauge 10 title label
    gauge10TITLE = new wxTextCtrl(this, TEXT_G10TITLE, "Title of Sensor", wxPoint(950, 610), wxSize(250, 50), wxTE_READONLY | wxTE_RICH);
    font = gauge10TITLE->GetFont();
    font.SetPointSize(15);
    gauge10TITLE->SetFont(font);

}
//The exit function
void MyFrame::OnExit(wxCommandEvent& event)
{
    //clean close
    Close(true);
}
//The about function
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}
//The hello function
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
//The function called when the durability button is pushed
void MyFrame::Event_durability(wxCommandEvent& event)
{
    wxLogMessage("Durability in action!!");
    gauge1CUR->SetValue("");
    gauge1CUR->AppendText("TEST");
    gauge1TITLE->SetValue("");
    gauge1TITLE->AppendText("VALIDATION OF WORKING");
    gauge1MAX->SetValue("");
    gauge1MAX->AppendText("100");
    gauge1MIN->SetValue("");
    gauge1MIN->AppendText("0");
    gauge1->SetValue(50);
}
//the function called when the pulling button is pressed
void MyFrame::Event_pulling(wxCommandEvent& event)
{
    wxLogMessage("Pulling in action!!");
}
//the function called when the maneuverability button is bpushed
void MyFrame::Event_maneuverability(wxCommandEvent& event)
{
    wxLogMessage("Maneuverability in action!!");
}
//The function called when the diagnostics button is pressed
void MyFrame::Event_diagnostics(wxCommandEvent& event)
{
    wxLogMessage("Diagnostics in action!!");
}
//The function called when the start recording button is pressed
void MyFrame::Event_start_recording(wxCommandEvent& event)
{
    wxLogMessage("Recording in action!");
}
//The function called when the stop recording button is pressed
void MyFrame::Event_end_recording(wxCommandEvent& event)
{
    wxLogMessage("Recording stoping!");
}
