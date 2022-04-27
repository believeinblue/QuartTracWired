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
#include "SimpleSerial.cpp"
#include <fstream>

#include <signal.h>

using namespace std;

int eventSelect = -1;
int const SPEED_MAX = 5;

string filename = "C:\\Users\\David\\OneDrive\\Desktop\\output.txt";

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
    //event_start_recording = new wxButton(this, BUTTON_start_recording, "Start Recording", wxPoint(10, 410), wxSize(150, 50));
    //adds end recording button
    //event_end_recording = new wxButton(this, BUTTON_end_recording, "End Recording", wxPoint(10, 510), wxSize(150, 50));
    //adds Timer
    updateTimer = new wxTimer(this, Timer);
    updateTimer->Start(1000, TRUE);

    //adds all 18 gauges
    gauge1 = new wxGauge(this, Gauge1, 100, wxPoint(225, 30), wxSize(500, 10));
    gauge2 = new wxGauge(this, Gauge2, 100, wxPoint(825, 30), wxSize(500, 10));
    gauge3 = new wxGauge(this, Gauge3, 100, wxPoint(225, 110), wxSize(500, 10));
    gauge4 = new wxGauge(this, Gauge4, 100, wxPoint(825, 110), wxSize(500, 10));
    gauge5 = new wxGauge(this, Gauge5, 100, wxPoint(225, 190), wxSize(500, 10));
    gauge6 = new wxGauge(this, Gauge6, 100, wxPoint(825, 190), wxSize(500, 10));
    gauge7 = new wxGauge(this, Gauge7, 100, wxPoint(225, 270), wxSize(500, 10));
    gauge8 = new wxGauge(this, Gauge8, 100, wxPoint(825, 270), wxSize(500, 10));
    gauge9 = new wxGauge(this, Gauge9, 100, wxPoint(225, 350), wxSize(500, 10));
    gauge10 = new wxGauge(this, Gauge10, 100, wxPoint(825, 350), wxSize(500, 10));
    gauge11 = new wxGauge(this, Gauge1, 100, wxPoint(225, 430), wxSize(500, 10));
    gauge12 = new wxGauge(this, Gauge2, 100, wxPoint(825,430), wxSize(500, 10));
    gauge13 = new wxGauge(this, Gauge3, 100, wxPoint(225, 510), wxSize(500, 10));
    gauge14 = new wxGauge(this, Gauge4, 100, wxPoint(825, 510), wxSize(500, 10));
    gauge15 = new wxGauge(this, Gauge5, 100, wxPoint(225, 590), wxSize(500, 10));
    gauge16 = new wxGauge(this, Gauge6, 100, wxPoint(825, 590), wxSize(500, 10));
    gauge17 = new wxGauge(this, Gauge7, 100, wxPoint(225, 670), wxSize(500, 10));
    gauge18 = new wxGauge(this, Gauge8, 100, wxPoint(825, 670), wxSize(500, 10));

    //gauge 1 min label
    gauge1MIN = new wxTextCtrl(this, TEXT_G1MIN, "MIN", wxPoint(225, 40), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    wxFont font = gauge1MIN->GetFont();
    font.SetPointSize(15);
    gauge1MIN->SetFont(font);

    //gauge 1 max label
    gauge1MAX = new wxTextCtrl(this, TEXT_G1MAX, "MAX", wxPoint(675, 40), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge1MAX->GetFont();
    font.SetPointSize(15);
    gauge1MAX->SetFont(font);

    //gauge 1 current value label
    gauge1CUR = new wxTextCtrl(this, TEXT_G1CUR, "CUR", wxPoint(450, 40), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge1CUR->GetFont();
    font.SetPointSize(15);
    gauge1CUR->SetFont(font);
    gauge1CUR->SetValue("");
    gauge1CUR->AppendText("CUR");

    //gauge 1 title label
    gauge1TITLE = new wxTextCtrl(this, TEXT_G1TITLE, "Title of Sensor", wxPoint(350, 00), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge1TITLE->GetFont();
    font.SetPointSize(15);
    gauge1TITLE->SetFont(font);

    //gauge 2
    //gauge 2 min label
    gauge2MIN = new wxTextCtrl(this, TEXT_G2MIN, "MIN", wxPoint(835, 40), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge2MIN->GetFont();
    font.SetPointSize(15);
    gauge2MIN->SetFont(font);

    //gauge 2 max label
    gauge2MAX = new wxTextCtrl(this, TEXT_G2MAX, "MAX", wxPoint(1275, 40), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge2MAX->GetFont();
    font.SetPointSize(15);
    gauge2MAX->SetFont(font);

    //gauge 2 current value label
    gauge2CUR = new wxTextCtrl(this, TEXT_G2CUR, "CUR", wxPoint(1050, 40), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge2CUR->GetFont();
    font.SetPointSize(15);
    gauge2CUR->SetFont(font);
    gauge2CUR->SetValue("");
    gauge2CUR->AppendText("CUR");

    //gauge 2 title label
    gauge2TITLE = new wxTextCtrl(this, TEXT_G2TITLE, "Title of Sensor", wxPoint(950, 00), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge2TITLE->GetFont();
    font.SetPointSize(15);
    gauge2TITLE->SetFont(font);

    //gauge 3
    //gauge 3 min label
    gauge3MIN = new wxTextCtrl(this, TEXT_G3MIN, "MIN", wxPoint(225, 120), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge3MIN->GetFont();
    font.SetPointSize(15);
    gauge3MIN->SetFont(font);

    //gauge 3 max label
    gauge3MAX = new wxTextCtrl(this, TEXT_G3MAX, "MAX", wxPoint(675, 120), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge3MAX->GetFont();
    font.SetPointSize(15);
    gauge3MAX->SetFont(font);

    //gauge 3 current value label
    gauge3CUR = new wxTextCtrl(this, TEXT_G3CUR, "CUR", wxPoint(450, 120), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge3CUR->GetFont();
    font.SetPointSize(15);
    gauge3CUR->SetFont(font);
    gauge3CUR->SetValue("");
    gauge3CUR->AppendText("CUR");

    //gauge 3 title label
    gauge3TITLE = new wxTextCtrl(this, TEXT_G3TITLE, "Title of Sensor", wxPoint(350, 80), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge3TITLE->GetFont();
    font.SetPointSize(15);
    gauge3TITLE->SetFont(font);

    //gauge 4
    //gauge 4 min label
    gauge4MIN = new wxTextCtrl(this, TEXT_G4MIN, "MIN", wxPoint(825, 120), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge4MIN->GetFont();
    font.SetPointSize(15);
    gauge4MIN->SetFont(font);

    //gauge 4 max label
    gauge4MAX = new wxTextCtrl(this, TEXT_G4MAX, "MAX", wxPoint(1275, 120), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge4MAX->GetFont();
    font.SetPointSize(15);
    gauge4MAX->SetFont(font);

    //gauge 4 current value label
    gauge4CUR = new wxTextCtrl(this, TEXT_G4CUR, "CUR", wxPoint(1050, 120), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge4CUR->GetFont();
    font.SetPointSize(15);
    gauge4CUR->SetFont(font);
    gauge4CUR->SetValue("");
    gauge4CUR->AppendText("CUR");

    //gauge 4 title label
    gauge4TITLE = new wxTextCtrl(this, TEXT_G4TITLE, "Title of Sensor", wxPoint(950, 80), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge4TITLE->GetFont();
    font.SetPointSize(15);
    gauge4TITLE->SetFont(font);

    //gauge 5
    //gauge 5 min label
    gauge5MIN = new wxTextCtrl(this, TEXT_G5MIN, "MIN", wxPoint(225, 200), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge5MIN->GetFont();
    font.SetPointSize(15);
    gauge5MIN->SetFont(font);

    //gauge 5 max label
    gauge5MAX = new wxTextCtrl(this, TEXT_G5MAX, "MAX", wxPoint(675, 200), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge5MAX->GetFont();
    font.SetPointSize(15);
    gauge5MAX->SetFont(font);

    //gauge 5 current value label
    gauge5CUR = new wxTextCtrl(this, TEXT_G5CUR, "CUR", wxPoint(450, 200), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge5CUR->GetFont();
    font.SetPointSize(15);
    gauge5CUR->SetFont(font);
    gauge5CUR->SetValue("");
    gauge5CUR->AppendText("CUR");

    //gauge 5 title label
    gauge5TITLE = new wxTextCtrl(this, TEXT_G5TITLE, "Title of Sensor", wxPoint(350, 160), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge5TITLE->GetFont();
    font.SetPointSize(15);
    gauge5TITLE->SetFont(font);

    //gauge 6
    //gauge 6 min label
    gauge6MIN = new wxTextCtrl(this, TEXT_G6MIN, "MIN", wxPoint(825, 200), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge6MIN->GetFont();
    font.SetPointSize(15);
    gauge6MIN->SetFont(font);

    //gauge 6 max label
    gauge6MAX = new wxTextCtrl(this, TEXT_G6MAX, "MAX", wxPoint(1275, 200), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge6MAX->GetFont();
    font.SetPointSize(15);
    gauge6MAX->SetFont(font);

    //gauge 6 current value label
    gauge6CUR = new wxTextCtrl(this, TEXT_G6CUR, "CUR", wxPoint(1050, 200), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge6CUR->GetFont();
    font.SetPointSize(15);
    gauge6CUR->SetFont(font);
    gauge6CUR->SetValue("");
    gauge6CUR->AppendText("CUR");

    //gauge 6 title label
    gauge6TITLE = new wxTextCtrl(this, TEXT_G6TITLE, "Title of Sensor", wxPoint(950, 160), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge6TITLE->GetFont();
    font.SetPointSize(15);
    gauge6TITLE->SetFont(font);

    //gauge 7
    //gauge 7 min label
    gauge7MIN = new wxTextCtrl(this, TEXT_G7MIN, "MIN", wxPoint(225, 280), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge7MIN->GetFont();
    font.SetPointSize(15);
    gauge7MIN->SetFont(font);

    //gauge 7 max label
    gauge7MAX = new wxTextCtrl(this, TEXT_G7MAX, "MAX", wxPoint(675, 280), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge7MAX->GetFont();
    font.SetPointSize(15);
    gauge7MAX->SetFont(font);

    //gauge 7 current value label
    gauge7CUR = new wxTextCtrl(this, TEXT_G7CUR, "CUR", wxPoint(450, 280), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge7CUR->GetFont();
    font.SetPointSize(15);
    gauge7CUR->SetFont(font);
    gauge7CUR->SetValue("");
    gauge7CUR->AppendText("CUR");

    //gauge 7 title label
    gauge7TITLE = new wxTextCtrl(this, TEXT_G7TITLE, "Title of Sensor", wxPoint(350, 240), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge7TITLE->GetFont();
    font.SetPointSize(15);
    gauge7TITLE->SetFont(font);

    //gauge 8
    //gauge 8 min label
    gauge8MIN = new wxTextCtrl(this, TEXT_G8MIN, "MIN", wxPoint(825, 280), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge8MIN->GetFont();
    font.SetPointSize(15);
    gauge8MIN->SetFont(font);

    //gauge 8 max label
    gauge8MAX = new wxTextCtrl(this, TEXT_G8MAX, "MAX", wxPoint(1275, 280), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge8MAX->GetFont();
    font.SetPointSize(15);
    gauge8MAX->SetFont(font);

    //gauge 8 current value label
    gauge8CUR = new wxTextCtrl(this, TEXT_G8CUR, "CUR", wxPoint(1050, 280), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge8CUR->GetFont();
    font.SetPointSize(15);
    gauge8CUR->SetFont(font);
    gauge8CUR->SetValue("");
    gauge8CUR->AppendText("CUR");

    //gauge 8 title label
    gauge8TITLE = new wxTextCtrl(this, TEXT_G8TITLE, "Title of Sensor", wxPoint(950, 240), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge8TITLE->GetFont();
    font.SetPointSize(15);
    gauge8TITLE->SetFont(font);

    //gauge 9
    //gauge 9 min label
    gauge9MIN = new wxTextCtrl(this, TEXT_G9MIN, "MIN", wxPoint(225, 360), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge9MIN->GetFont();
    font.SetPointSize(15);
    gauge9MIN->SetFont(font);

    //gauge 9 max label
    gauge9MAX = new wxTextCtrl(this, TEXT_G9MAX, "MAX", wxPoint(675, 360), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge9MAX->GetFont();
    font.SetPointSize(15);
    gauge9MAX->SetFont(font);

    //gauge 9 current value label
    gauge9CUR = new wxTextCtrl(this, TEXT_G9CUR, "CUR", wxPoint(450, 360), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge9CUR->GetFont();
    font.SetPointSize(15);
    gauge9CUR->SetFont(font);
    gauge9CUR->SetValue("");
    gauge9CUR->AppendText("CUR");

    //gauge 9 title label
    gauge9TITLE = new wxTextCtrl(this, TEXT_G9TITLE, "Title of Sensor", wxPoint(350, 320), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge9TITLE->GetFont();
    font.SetPointSize(15);
    gauge9TITLE->SetFont(font);

    //gauge 10
    //gauge 10 min label
    gauge10MIN = new wxTextCtrl(this, TEXT_G10MIN, "MIN", wxPoint(825, 360), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge10MIN->GetFont();
    font.SetPointSize(15);
    gauge10MIN->SetFont(font);

    //gauge 10 max label
    gauge10MAX = new wxTextCtrl(this, TEXT_G10MAX, "MAX", wxPoint(1275, 360), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge10MAX->GetFont();
    font.SetPointSize(15);
    gauge10MAX->SetFont(font);

    //gauge 10 current value label
    gauge10CUR = new wxTextCtrl(this, TEXT_G10CUR, "CUR", wxPoint(1050, 360), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge10CUR->GetFont();
    font.SetPointSize(15);
    gauge10CUR->SetFont(font);
    gauge10CUR->SetValue("");
    gauge10CUR->AppendText("CUR");

    //gauge 10 title label
    gauge10TITLE = new wxTextCtrl(this, TEXT_G10TITLE, "Title of Sensor", wxPoint(950, 320), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge10TITLE->GetFont();
    font.SetPointSize(15);
    gauge10TITLE->SetFont(font);

    //gauge 11
    //gauge 11 min label
    gauge11MIN = new wxTextCtrl(this, TEXT_G11MIN, "MIN", wxPoint(225, 440), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge11MIN->GetFont();
    font.SetPointSize(15);
    gauge11MIN->SetFont(font);

    //gauge 11 max label
    gauge11MAX = new wxTextCtrl(this, TEXT_G11MAX, "MAX", wxPoint(675, 440), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge11MAX->GetFont();
    font.SetPointSize(15);
    gauge11MAX->SetFont(font);

    //gauge 11 current value label
    gauge11CUR = new wxTextCtrl(this, TEXT_G11CUR, "CUR", wxPoint(450, 440), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge11CUR->GetFont();
    font.SetPointSize(15);
    gauge11CUR->SetFont(font);
    gauge11CUR->SetValue("");
    gauge11CUR->AppendText("CUR");

    //gauge 11 title label
    gauge11TITLE = new wxTextCtrl(this, TEXT_G11TITLE, "Title of Sensor", wxPoint(350, 400), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge11TITLE->GetFont();
    font.SetPointSize(15);
    gauge11TITLE->SetFont(font);

    //gauge 12
    //gauge 12 min label
    gauge12MIN = new wxTextCtrl(this, TEXT_G12MIN, "MIN", wxPoint(825, 440), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge12MIN->GetFont();
    font.SetPointSize(15);
    gauge12MIN->SetFont(font);

    //gauge 12 max label
    gauge12MAX = new wxTextCtrl(this, TEXT_G12MAX, "MAX", wxPoint(1275, 440), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge12MAX->GetFont();
    font.SetPointSize(15);
    gauge12MAX->SetFont(font);

    //gauge 12 current value label
    gauge12CUR = new wxTextCtrl(this, TEXT_G12CUR, "CUR", wxPoint(1050, 440), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge12CUR->GetFont();
    font.SetPointSize(15);
    gauge12CUR->SetFont(font);
    gauge12CUR->SetValue("");
    gauge12CUR->AppendText("CUR");

    //gauge 12 title label
    gauge12TITLE = new wxTextCtrl(this, TEXT_G12TITLE, "Title of Sensor", wxPoint(950, 400), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge12TITLE->GetFont();
    font.SetPointSize(15);
    gauge12TITLE->SetFont(font);

    //gauge 13
    //gauge 13 min label
    gauge13MIN = new wxTextCtrl(this, TEXT_G13MIN, "MIN", wxPoint(225, 520), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge13MIN->GetFont();
    font.SetPointSize(15);
    gauge13MIN->SetFont(font);

    //gauge 13 max label
    gauge13MAX = new wxTextCtrl(this, TEXT_G13MAX, "MAX", wxPoint(675, 520), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge13MAX->GetFont();
    font.SetPointSize(15);
    gauge13MAX->SetFont(font);

    //gauge 13 current value label
    gauge13CUR = new wxTextCtrl(this, TEXT_G13CUR, "CUR", wxPoint(450, 520), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge13CUR->GetFont();
    font.SetPointSize(15);
    gauge13CUR->SetFont(font);
    gauge13CUR->SetValue("");
    gauge13CUR->AppendText("CUR");

    //gauge 13 title label
    gauge13TITLE = new wxTextCtrl(this, TEXT_G13TITLE, "Title of Sensor", wxPoint(350, 480), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge13TITLE->GetFont();
    font.SetPointSize(15);
    gauge13TITLE->SetFont(font);

    //gauge 14
    //gauge 14 min label
    gauge14MIN = new wxTextCtrl(this, TEXT_G14MIN, "MIN", wxPoint(825, 520), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge14MIN->GetFont();
    font.SetPointSize(15);
    gauge14MIN->SetFont(font);

    //gauge 14 max label
    gauge14MAX = new wxTextCtrl(this, TEXT_G14MAX, "MAX", wxPoint(1275, 520), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge14MAX->GetFont();
    font.SetPointSize(15);
    gauge14MAX->SetFont(font);

    //gauge 14 current value label
    gauge14CUR = new wxTextCtrl(this, TEXT_G14CUR, "CUR", wxPoint(1050, 520), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge14CUR->GetFont();
    font.SetPointSize(15);
    gauge14CUR->SetFont(font);
    gauge14CUR->SetValue("");
    gauge14CUR->AppendText("CUR");

    //gauge 14 title label
    gauge14TITLE = new wxTextCtrl(this, TEXT_G14TITLE, "Title of Sensor", wxPoint(950, 480), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge14TITLE->GetFont();
    font.SetPointSize(15);
    gauge14TITLE->SetFont(font);

    //gauge 15
    //gauge 15 min label
    gauge15MIN = new wxTextCtrl(this, TEXT_G15MIN, "MIN", wxPoint(225, 600), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge15MIN->GetFont();
    font.SetPointSize(15);
    gauge15MIN->SetFont(font);

    //gauge 15 max label
    gauge15MAX = new wxTextCtrl(this, TEXT_G15MAX, "MAX", wxPoint(675, 600), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge15MAX->GetFont();
    font.SetPointSize(15);
    gauge15MAX->SetFont(font);

    //gauge 15 current value label
    gauge15CUR = new wxTextCtrl(this, TEXT_G15CUR, "CUR", wxPoint(450, 600), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge15CUR->GetFont();
    font.SetPointSize(15);
    gauge15CUR->SetFont(font);
    gauge15CUR->SetValue("");
    gauge15CUR->AppendText("CUR");

    //gauge 15 title label
    gauge15TITLE = new wxTextCtrl(this, TEXT_G15TITLE, "Title of Sensor", wxPoint(350, 560), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge15TITLE->GetFont();
    font.SetPointSize(15);
    gauge15TITLE->SetFont(font);

    //gauge 16
    //gauge 16 min label
    gauge16MIN = new wxTextCtrl(this, TEXT_G16MIN, "MIN", wxPoint(825, 600), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge16MIN->GetFont();
    font.SetPointSize(15);
    gauge16MIN->SetFont(font);

    //gauge 16 max label
    gauge16MAX = new wxTextCtrl(this, TEXT_G16MAX, "MAX", wxPoint(1275, 600), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge16MAX->GetFont();
    font.SetPointSize(15);
    gauge16MAX->SetFont(font);

    //gauge 16 current value label
    gauge16CUR = new wxTextCtrl(this, TEXT_G16CUR, "CUR", wxPoint(1050, 600), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge16CUR->GetFont();
    font.SetPointSize(15);
    gauge16CUR->SetFont(font);
    gauge16CUR->SetValue("");
    gauge16CUR->AppendText("CUR");

    //gauge 16 title label
    gauge16TITLE = new wxTextCtrl(this, TEXT_G8TITLE, "Title of Sensor", wxPoint(950, 560), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge16TITLE->GetFont();
    font.SetPointSize(15);
    gauge16TITLE->SetFont(font);

    //gauge 17
    //gauge 17 min label
    gauge17MIN = new wxTextCtrl(this, TEXT_G17MIN, "MIN", wxPoint(225, 680), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge17MIN->GetFont();
    font.SetPointSize(15);
    gauge17MIN->SetFont(font);

    //gauge 17 max label
    gauge17MAX = new wxTextCtrl(this, TEXT_G17MAX, "MAX", wxPoint(675, 680), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge17MAX->GetFont();
    font.SetPointSize(15);
    gauge17MAX->SetFont(font);

    //gauge 17 current value label
    gauge17CUR = new wxTextCtrl(this, TEXT_G17CUR, "CUR", wxPoint(450, 680), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge17CUR->GetFont();
    font.SetPointSize(15);
    gauge17CUR->SetFont(font);
    gauge17CUR->SetValue("");
    gauge17CUR->AppendText("CUR");

    //gauge 17 title label
    gauge17TITLE = new wxTextCtrl(this, TEXT_G17TITLE, "Title of Sensor", wxPoint(350, 640), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge17TITLE->GetFont();
    font.SetPointSize(15);
    gauge17TITLE->SetFont(font);

    //gauge 18
    //gauge 18 min label
    gauge18MIN = new wxTextCtrl(this, TEXT_G18MIN, "MIN", wxPoint(825, 680), wxSize(50, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge18MIN->GetFont();
    font.SetPointSize(15);
    gauge18MIN->SetFont(font);

    //gauge 18 max label
    gauge18MAX = new wxTextCtrl(this, TEXT_G18MAX, "MAX", wxPoint(1275, 680), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge18MAX->GetFont();
    font.SetPointSize(15);
    gauge18MAX->SetFont(font);

    //gauge 18 current value label
    gauge18CUR = new wxTextCtrl(this, TEXT_G18CUR, "CUR", wxPoint(1050, 680), wxSize(60, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge18CUR->GetFont();
    font.SetPointSize(15);
    gauge18CUR->SetFont(font);
    gauge18CUR->SetValue("");
    gauge18CUR->AppendText("CUR");

    //gauge 18 title label
    gauge18TITLE = new wxTextCtrl(this, TEXT_G10TITLE, "Title of Sensor", wxPoint(950, 640), wxSize(250, 30), wxTE_READONLY | wxTE_RICH);
    font = gauge18TITLE->GetFont();
    font.SetPointSize(15);
    gauge18TITLE->SetFont(font);

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
    //wxLogMessage("Durability in action!!");
    eventSelect = 1;
    //Gauge 1
    gauge1CUR->SetValue("");
    gauge1TITLE->SetValue("Left Front Wheel");
    gauge1MAX->SetValue("5");
    gauge1MIN->SetValue("0");
    gauge1->SetValue(0);
    //Gauge 2
    gauge2CUR->SetValue("");
    gauge2TITLE->SetValue("Right Front Wheel");
    gauge2MAX->SetValue("5");
    gauge2MIN->SetValue("0");
    gauge2->SetValue(0);
    //Gauge 3
    gauge3CUR->SetValue("");
    gauge3TITLE->SetValue("Left Back Wheel");
    gauge3MAX->SetValue("5");
    gauge3MIN->SetValue("0");
    gauge3->SetValue(0);
    //Gauge 4
    gauge4CUR->SetValue("");
    gauge4TITLE->SetValue("Right Back Wheel");
    gauge4MAX->SetValue("5");
    gauge4MIN->SetValue("0");
    gauge4->SetValue(0);
    //Gauge 5
    gauge5CUR->SetValue("");
    gauge5TITLE->SetValue("Hitch Load");
    gauge5MAX->SetValue("5000");
    gauge5MIN->SetValue("0");
    gauge5->SetValue(0);
    //Gauge 6
    gauge6CUR->SetValue("");
    gauge6TITLE->SetValue("");
    gauge6MAX->SetValue("");
    gauge6MIN->SetValue("");
    gauge6->SetValue(0);
    //Gauge 7
    gauge7CUR->SetValue("");
    gauge7TITLE->SetValue("");
    gauge7MAX->SetValue("");
    gauge7MIN->SetValue("");
    gauge7->SetValue(0);
    //Gauge 8
    gauge8CUR->SetValue("");
    gauge8TITLE->SetValue("");
    gauge8MAX->SetValue("");
    gauge8MIN->SetValue("");
    gauge8->SetValue(0);
    //Gauge 9
    gauge9CUR->SetValue("");
    gauge9TITLE->SetValue("");
    gauge9MAX->SetValue("");
    gauge9MIN->SetValue("");
    gauge9->SetValue(0);
    //Gauge 10
    gauge10CUR->SetValue("");
    gauge10TITLE->SetValue("");
    gauge10MAX->SetValue("");
    gauge10MIN->SetValue("");
    gauge10->SetValue(0);
    //Gauge 11
    gauge11CUR->SetValue("");
    gauge11TITLE->SetValue("");
    gauge11MAX->SetValue("");
    gauge11MIN->SetValue("");
    gauge11->SetValue(0);
    //Gauge 12
    gauge12CUR->SetValue("");
    gauge12TITLE->SetValue("");
    gauge12MAX->SetValue("");
    gauge12MIN->SetValue("");
    gauge12->SetValue(0);
    //Gauge 13
    gauge13CUR->SetValue("");
    gauge13TITLE->SetValue("");
    gauge13MAX->SetValue("");
    gauge13MIN->SetValue("");
    gauge13->SetValue(0);
    //Gauge 14
    gauge14CUR->SetValue("");
    gauge14TITLE->SetValue("");
    gauge14MAX->SetValue("");
    gauge14MIN->SetValue("");
    gauge14->SetValue(0);
    //Gauge 15
    gauge15CUR->SetValue("");
    gauge15TITLE->SetValue("");
    gauge15MAX->SetValue("");
    gauge15MIN->SetValue("");
    gauge15->SetValue(0);
    //Gauge 16
    gauge16CUR->SetValue("");
    gauge16TITLE->SetValue("");
    gauge16MAX->SetValue("");
    gauge16MIN->SetValue("");
    gauge16->SetValue(0);
    //Gauge 17
    gauge17CUR->SetValue("");
    gauge17TITLE->SetValue("");
    gauge17MAX->SetValue("");
    gauge17MIN->SetValue("");
    gauge17->SetValue(0);
    //Gauge 18
    gauge18CUR->SetValue("");
    gauge18TITLE->SetValue("");
    gauge18MAX->SetValue("");
    gauge18MIN->SetValue("");
    gauge18->SetValue(0);
}
//the function called when the pulling button is pressed
void MyFrame::Event_pulling(wxCommandEvent& event)
{
    //wxLogMessage("Pulling in action!!");
    eventSelect = 2;
    //Gauge 1
    gauge1CUR->SetValue("");
    gauge1TITLE->SetValue("Left Front Wheel");
    gauge1MAX->SetValue("50");
    gauge1MIN->SetValue("0");
    gauge1->SetValue(0);
    //Gauge 2
    gauge2CUR->SetValue("");
    gauge2TITLE->SetValue("Right Front Wheel");
    gauge2MAX->SetValue("50");
    gauge2MIN->SetValue("0");
    gauge2->SetValue(0);
    //Gauge 3
    gauge3CUR->SetValue("");
    gauge3TITLE->SetValue("Left Back Wheel");
    gauge3MAX->SetValue("50");
    gauge3MIN->SetValue("0");
    gauge3->SetValue(0);
    //Gauge 4
    gauge4CUR->SetValue("");
    gauge4TITLE->SetValue("Right Back Wheel");
    gauge4MAX->SetValue("50");
    gauge4MIN->SetValue("0");
    gauge4->SetValue(0);
    //Gauge 5
    gauge5CUR->SetValue("");
    gauge5TITLE->SetValue("Front Load");
    gauge5MAX->SetValue("5000");
    gauge5MIN->SetValue("0");
    gauge5->SetValue(0);
    //Gauge 6
    gauge6CUR->SetValue("");
    gauge6TITLE->SetValue("Hitch Load");
    gauge6MAX->SetValue("5000");
    gauge6MIN->SetValue("0");
    gauge6->SetValue(0);
    //Gauge 7
    gauge7CUR->SetValue("");
    gauge7TITLE->SetValue("Engine Speed");
    gauge7MAX->SetValue("9999");
    gauge7MIN->SetValue("0");
    gauge7->SetValue(0);
    //Gauge 8
    gauge8CUR->SetValue("");
    gauge8TITLE->SetValue("");
    gauge8MAX->SetValue("");
    gauge8MIN->SetValue("");
    gauge8->SetValue(0);
    //Gauge 9
    gauge9CUR->SetValue("");
    gauge9TITLE->SetValue("");
    gauge9MAX->SetValue("");
    gauge9MIN->SetValue("");
    gauge9->SetValue(0);
    //Gauge 10
    gauge10CUR->SetValue("");
    gauge10TITLE->SetValue("");
    gauge10MAX->SetValue("");
    gauge10MIN->SetValue("");
    gauge10->SetValue(0);
    //Gauge 11
    gauge11CUR->SetValue("");
    gauge11TITLE->SetValue("");
    gauge11MAX->SetValue("");
    gauge11MIN->SetValue("");
    gauge11->SetValue(0);
    //Gauge 12
    gauge12CUR->SetValue("");
    gauge12TITLE->SetValue("");
    gauge12MAX->SetValue("");
    gauge12MIN->SetValue("");
    gauge12->SetValue(0);
    //Gauge 13
    gauge13CUR->SetValue("");
    gauge13TITLE->SetValue("");
    gauge13MAX->SetValue("");
    gauge13MIN->SetValue("");
    gauge13->SetValue(0);
    //Gauge 14
    gauge14CUR->SetValue("");
    gauge14TITLE->SetValue("");
    gauge14MAX->SetValue("");
    gauge14MIN->SetValue("");
    gauge14->SetValue(0);
    //Gauge 15
    gauge15CUR->SetValue("");
    gauge15TITLE->SetValue("");
    gauge15MAX->SetValue("");
    gauge15MIN->SetValue("");
    gauge15->SetValue(0);
    //Gauge 16
    gauge16CUR->SetValue("");
    gauge16TITLE->SetValue("");
    gauge16MAX->SetValue("");
    gauge16MIN->SetValue("");
    gauge16->SetValue(0);
    //Gauge 17
    gauge17CUR->SetValue("");
    gauge17TITLE->SetValue("");
    gauge17MAX->SetValue("");
    gauge17MIN->SetValue("");
    gauge17->SetValue(0);
    //Gauge 18
    gauge18CUR->SetValue("");
    gauge18TITLE->SetValue("");
    gauge18MAX->SetValue("");
    gauge18MIN->SetValue("");
    gauge18->SetValue(0);
}
//the function called when the maneuverability button is bpushed
void MyFrame::Event_maneuverability(wxCommandEvent& event)
{
    //wxLogMessage("Maneuverability in action!!");
    eventSelect = 3;
    //Gauge 1
    gauge1CUR->SetValue("");
    gauge1TITLE->SetValue("Engine Speed");
    gauge1MAX->SetValue("9999");
    gauge1MIN->SetValue("0");
    gauge1->SetValue(0);
    //Gauge 2
    gauge2CUR->SetValue("");
    gauge2TITLE->SetValue("Steering velocity");
    gauge2MAX->SetValue("36000");
    gauge2MIN->SetValue("0");
    gauge2->SetValue(0);
    //Gauge 3
    gauge3CUR->SetValue("");
    gauge3TITLE->SetValue("Voltage");
    gauge3MAX->SetValue("60");
    gauge3MIN->SetValue("0");
    gauge3->SetValue(0);
    //Gauge 4
    gauge4CUR->SetValue("");
    gauge4TITLE->SetValue("");
    gauge4MAX->SetValue("");
    gauge4MIN->SetValue("");
    gauge4->SetValue(0);
    //Gauge 5
    gauge5CUR->SetValue("");
    gauge5TITLE->SetValue("");
    gauge5MAX->SetValue("");
    gauge5MIN->SetValue("");
    gauge5->SetValue(0);
    //Gauge 6
    gauge6CUR->SetValue("");
    gauge6TITLE->SetValue("");
    gauge6MAX->SetValue("");
    gauge6MIN->SetValue("");
    gauge6->SetValue(0);
    //Gauge 7
    gauge7CUR->SetValue("");
    gauge7TITLE->SetValue("");
    gauge7MAX->SetValue("");
    gauge7MIN->SetValue("");
    gauge7->SetValue(0);
    //Gauge 8
    gauge8CUR->SetValue("");
    gauge8TITLE->SetValue("");
    gauge8MAX->SetValue("");
    gauge8MIN->SetValue("");
    gauge8->SetValue(0);
    //Gauge 9
    gauge9CUR->SetValue("");
    gauge9TITLE->SetValue("");
    gauge9MAX->SetValue("");
    gauge9MIN->SetValue("");
    gauge9->SetValue(0);
    //Gauge 10
    gauge10CUR->SetValue("");
    gauge10TITLE->SetValue("");
    gauge10MAX->SetValue("");
    gauge10MIN->SetValue("");
    gauge10->SetValue(0);
    //Gauge 11
    gauge11CUR->SetValue("");
    gauge11TITLE->SetValue("");
    gauge11MAX->SetValue("");
    gauge11MIN->SetValue("");
    gauge11->SetValue(0);
    //Gauge 12
    gauge12CUR->SetValue("");
    gauge12TITLE->SetValue("");
    gauge12MAX->SetValue("");
    gauge12MIN->SetValue("");
    gauge12->SetValue(0);
    //Gauge 13
    gauge13CUR->SetValue("");
    gauge13TITLE->SetValue("");
    gauge13MAX->SetValue("");
    gauge13MIN->SetValue("");
    gauge13->SetValue(0);
    //Gauge 14
    gauge14CUR->SetValue("");
    gauge14TITLE->SetValue("");
    gauge14MAX->SetValue("");
    gauge14MIN->SetValue("");
    gauge14->SetValue(0);
    //Gauge 15
    gauge15CUR->SetValue("");
    gauge15TITLE->SetValue("");
    gauge15MAX->SetValue("");
    gauge15MIN->SetValue("");
    gauge15->SetValue(0);
    //Gauge 16
    gauge16CUR->SetValue("");
    gauge16TITLE->SetValue("");
    gauge16MAX->SetValue("");
    gauge16MIN->SetValue("");
    gauge16->SetValue(0);
    //Gauge 17
    gauge17CUR->SetValue("");
    gauge17TITLE->SetValue("");
    gauge17MAX->SetValue("");
    gauge17MIN->SetValue("");
    gauge17->SetValue(0);
    //Gauge 18
    gauge18CUR->SetValue("");
    gauge18TITLE->SetValue("");
    gauge18MAX->SetValue("");
    gauge18MIN->SetValue("");
    gauge18->SetValue(0);
}
//The function called when the diagnostics button is pressed
void MyFrame::Event_diagnostics(wxCommandEvent& event)
{
    //wxLogMessage("Diagnostics in action!!");
    eventSelect = 4;
    //Gauge 1
    gauge1CUR->SetValue("");
    gauge1TITLE->SetValue("Left Front Wheel");
    gauge1MAX->SetValue("50");
    gauge1MIN->SetValue("0");
    gauge1->SetValue(0);
    //Gauge 2
    gauge2CUR->SetValue("");
    gauge2TITLE->SetValue("Right Front Wheel");
    gauge2MAX->SetValue("50");
    gauge2MIN->SetValue("0");
    gauge2->SetValue(0);
    //Gauge 3
    gauge3CUR->SetValue("");
    gauge3TITLE->SetValue("Left Back Wheel");
    gauge3MAX->SetValue("50");
    gauge3MIN->SetValue("0");
    gauge3->SetValue(0);
    //Gauge 4
    gauge4CUR->SetValue("");
    gauge4TITLE->SetValue("Right Back Wheel");
    gauge4MAX->SetValue("50");
    gauge4MIN->SetValue("0");
    gauge4->SetValue(0);
    //Gauge 5
    gauge5CUR->SetValue("");
    gauge5TITLE->SetValue("Front Hitch Load");
    gauge5MAX->SetValue("5000");
    gauge5MIN->SetValue("0");
    gauge5->SetValue(0);
    //Gauge 6
    gauge6CUR->SetValue("");
    gauge6TITLE->SetValue("Back Hitch Load");
    gauge6MAX->SetValue("5000");
    gauge6MIN->SetValue("0");
    gauge6->SetValue(0);
    //Gauge 7
    gauge7CUR->SetValue("");
    gauge7TITLE->SetValue("Engine Speed");
    gauge7MAX->SetValue("9999");
    gauge7MIN->SetValue("0");
    gauge7->SetValue(0);
    //Gauge 8
    gauge8CUR->SetValue("");
    gauge8TITLE->SetValue("Drive Shaft Speed");
    gauge8MAX->SetValue("9999");
    gauge8MIN->SetValue("0");
    gauge8->SetValue(0);
    //Gauge 9
    gauge9CUR->SetValue("");
    gauge9TITLE->SetValue("Steering angle");
    gauge9MAX->SetValue("360");
    gauge9MIN->SetValue("0");
    gauge9->SetValue(0);
    //Gauge 10
    gauge10CUR->SetValue("");
    gauge10TITLE->SetValue("Steering velocity");
    gauge10MAX->SetValue("360");
    gauge10MIN->SetValue("0");
    gauge10->SetValue(0);
    //Gauge 11
    gauge11CUR->SetValue("");
    gauge11TITLE->SetValue("Gear");
    gauge11MAX->SetValue("");
    gauge11MIN->SetValue("");
    gauge11->SetValue(0);
    //Gauge 12
    gauge12CUR->SetValue("");
    gauge12TITLE->SetValue("Voltage");
    gauge12MAX->SetValue("60");
    gauge12MIN->SetValue("0");
    gauge12->SetValue(0);
    //Gauge 13
    gauge13CUR->SetValue("");
    gauge13TITLE->SetValue("");
    gauge13MAX->SetValue("");
    gauge13MIN->SetValue("");
    gauge13->SetValue(0);
    //Gauge 14
    gauge14CUR->SetValue("");
    gauge14TITLE->SetValue("");
    gauge14MAX->SetValue("");
    gauge14MIN->SetValue(""); 
    gauge14->SetValue(0);
    //Gauge 15
    gauge15CUR->SetValue("");
    gauge15TITLE->SetValue("");
    gauge15MAX->SetValue("");
    gauge15MIN->SetValue("");
    gauge15->SetValue(0);
    //Gauge 16
    gauge16CUR->SetValue("");
    gauge16TITLE->SetValue("");
    gauge16MAX->SetValue("");
    gauge16MIN->SetValue("");
    gauge16->SetValue(0);
    //Gauge 17
    gauge17CUR->SetValue("");
    gauge17TITLE->SetValue("");
    gauge17MAX->SetValue("");
    gauge17MIN->SetValue(""); 
    gauge17->SetValue(0);
    //Gauge 18
    gauge18CUR->SetValue("");
    gauge18TITLE->SetValue("");
    gauge18MAX->SetValue("");
    gauge18MIN->SetValue("");
    gauge18->SetValue(0);
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

void MyFrame::Update(wxTimerEvent& event)
{
    string trash, input;
    ifstream file1(filename);
    if (!file1.is_open())
    {
        return;
    }
    while (getline(file1, trash) )
    {
        if (trash.length()>=143)
            input = trash;
    }
    int hitchF = stoi(input.substr(7, 4));
    int LWF = stoi(input.substr(26, 5));
    int RWF = stoi(input.substr(32, 5));
    int EngineSpeed = stoi(input.substr(45, 5));
    int driveShaft = stoi(input.substr(64, 5));
    int voltage = stoi(input.substr(76, 3));
    int hitchR = stoi(input.substr(83, 4));
    int LWR = stoi(input.substr(101, 5));
    int RWR = stoi(input.substr(107, 5));
    int steeringAngle = stoi(input.substr(121, 5));
    int steeringVelocity = stoi(input.substr(139, 5));

    file1.close();
    
    if (eventSelect == 1)
    {
        //Left FrontWheel
        if (LWF > SPEED_MAX)
            gauge1->SetValue(100);
        else
            gauge1->SetValue(int((LWF * 100)/5));
        do {
            wxStreamToTextRedirector redirect(gauge1CUR);
            gauge1CUR->SetValue("");
            cout << LWF;
        } while (1 == 2);
        //Right Front Wheel
        if (RWF > SPEED_MAX)
            gauge2->SetValue(100);
        else
            gauge2->SetValue(int((RWF * 100) / 5));
        do {
            wxStreamToTextRedirector redirect(gauge2CUR);
            gauge2CUR->SetValue("");
            cout << RWF;
        } while (1 == 2);

        //Left Rear Wheel
        if (LWR > SPEED_MAX)
            gauge3->SetValue(100);
        else
            gauge3->SetValue(int((LWR * 100) / 5));
        do {
            wxStreamToTextRedirector redirect(gauge3CUR);
            gauge3CUR->SetValue("");
            cout << LWR;
        } while (1 == 2);;

        //Right Rear Wheel
        if (RWR > SPEED_MAX)
            gauge4->SetValue(100);
        else
            gauge4->SetValue(int((RWR * 100) / 5));
        do {
            wxStreamToTextRedirector redirect(gauge4CUR);
            gauge4CUR->SetValue("");
            cout << RWR;
        } while (1 == 2);

        //hitch load
        if (hitchR > 5000)
            gauge5->SetValue(100);
        else
            gauge5->SetValue(int((hitchR * 100) / 5000));
        do {
            wxStreamToTextRedirector redirect(gauge5CUR);
            gauge5CUR->SetValue("");
            cout << hitchR;
        } while (1 == 2);
    }
    else if (eventSelect == 2)
    {
        //Left FrontWheel
        if (LWF > 100)
            gauge1->SetValue(100);
        else
            gauge1->SetValue(int((LWF * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge1CUR);
            gauge1CUR->SetValue("");
            cout << LWF;
        } while (1 == 2);
        //Right Front Wheel
        if (RWF > 100)
            gauge2->SetValue(100);
        else
            gauge2->SetValue(int((RWF * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge2CUR);
            gauge2CUR->SetValue("");
            cout << RWF;
        } while (1 == 2);

        //Left Rear Wheel
        if (LWR > 100)
            gauge3->SetValue(100);
        else
            gauge3->SetValue(int((LWR * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge3CUR);
            gauge3CUR->SetValue("");
            cout << LWR;
        } while (1 == 2);;

        //Right Rear Wheel
        if (RWR > 100)
            gauge4->SetValue(100);
        else
            gauge4->SetValue(int((RWR * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge4CUR);
            gauge4CUR->SetValue("");
            cout << RWR;
        } while (1 == 2);

        //front load
        if (hitchF > 5000)
            gauge5->SetValue(100);
        else
            gauge5->SetValue(int((hitchF * 100) / 5000));
        do {
            wxStreamToTextRedirector redirect(gauge5CUR);
            gauge5CUR->SetValue("");
            cout << hitchF;
        } while (1 == 2);

        //hitch load
        if (hitchR > 5000)
            gauge6->SetValue(100);
        else
            gauge6->SetValue(int((hitchR * 100) / 5000));
        do {
            wxStreamToTextRedirector redirect(gauge6CUR);
            gauge6CUR->SetValue("");
            cout << hitchR;
        } while (1 == 2);

        gauge7->SetValue(int((EngineSpeed * 100) / 9999));
        do {
            wxStreamToTextRedirector redirect(gauge7CUR);
            gauge7CUR->SetValue("");
            cout << EngineSpeed;
        } while (1 == 2);
    }
    else if (eventSelect == 3)
    {
        gauge1->SetValue(int((EngineSpeed * 100) / 9999));
        do {
            wxStreamToTextRedirector redirect(gauge1CUR);
            gauge1CUR->SetValue("");
            cout << EngineSpeed;
        } while (1 == 2);

        //steeringVelocity
        if (steeringVelocity > 36000)
            gauge2->SetValue(100);
        else
            gauge2->SetValue(int((steeringVelocity * 100) / 36000));
        do {
            wxStreamToTextRedirector redirect(gauge2CUR);
            gauge2CUR->SetValue("");
            cout << (steeringVelocity/100);
        } while (1 == 2);
 
        if (voltage > 60)
            gauge3->SetValue(100);
        else
            gauge3->SetValue(int((voltage * 100) / 60));
        do {
            wxStreamToTextRedirector redirect(gauge3CUR);
            gauge3CUR->SetValue("");
            cout << voltage;
        } while (1 == 2);
    }
    else if (eventSelect == 4)
    {
        //Left FrontWheel
        if (LWF > 50)
            gauge1->SetValue(100);
        else
            gauge1->SetValue(int((LWF * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge1CUR);
            gauge1CUR->SetValue("");
            cout << LWF;
        } while (1 == 2);
        //Right Front Wheel
        if (RWF > 50)
            gauge2->SetValue(100);
        else
            gauge2->SetValue(int((RWF * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge2CUR);
            gauge2CUR->SetValue("");
            cout << RWF;
        } while (1 == 2);

        //Left Rear Wheel
        if (LWR > 50)
            gauge3->SetValue(100);
        else
            gauge3->SetValue(int((LWR * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge3CUR);
            gauge3CUR->SetValue("");
            cout << LWR;
        } while (1 == 2);;

        //Right Rear Wheel
        if (RWR > 50)
            gauge4->SetValue(100);
        else
            gauge4->SetValue(int((RWR * 100) / 50));
        do {
            wxStreamToTextRedirector redirect(gauge4CUR);
            gauge4CUR->SetValue("");
            cout << RWR;
        } while (1 == 2);

        //front load
        if (hitchF > 5000)
            gauge5->SetValue(100);
        else
            gauge5->SetValue(int((hitchF * 100) / 5000));
        do {
            wxStreamToTextRedirector redirect(gauge5CUR);
            gauge5CUR->SetValue("");
            cout << hitchF;
        } while (1 == 2);

        //hitch load
        if (hitchR > 5000)
            gauge6->SetValue(100);
        else
            gauge6->SetValue(int((hitchR * 100) / 5000));
        do {
            wxStreamToTextRedirector redirect(gauge6CUR);
            gauge6CUR->SetValue("");
            cout << hitchR;
        } while (1 == 2);

        gauge7->SetValue(int((EngineSpeed * 100) / 9999));
        do {
            wxStreamToTextRedirector redirect(gauge7CUR);
            gauge7CUR->SetValue("");
            cout << EngineSpeed;
        } while (1 == 2);

        gauge8->SetValue(int((driveShaft * 100) / 9999));
        do {
            wxStreamToTextRedirector redirect(gauge8CUR);
            gauge8CUR->SetValue("");
            cout << driveShaft;
        } while (1 == 2);

        if (steeringAngle > 3600)
            gauge9->SetValue(100);
        else
            gauge9->SetValue(int((steeringAngle * 100) / 3600));
        do {
            wxStreamToTextRedirector redirect(gauge9CUR);
            gauge9CUR->SetValue("");
            cout << (steeringAngle/10);
        } while (1 == 2);

        //steeringVelocity
        if (steeringVelocity > 36000)
            gauge10->SetValue(100);
        else
            gauge10->SetValue(int((steeringVelocity * 100) / 36000));
        do {
            wxStreamToTextRedirector redirect(gauge10CUR);
            gauge10CUR->SetValue("");
            cout << (steeringVelocity / 100);
        } while (1 == 2);

        if (voltage > 60)
            gauge12->SetValue(100);
        else
            gauge12->SetValue(int((voltage * 100) / 60));
        do {
            wxStreamToTextRedirector redirect(gauge12CUR);
            gauge12CUR->SetValue("");
            cout << voltage;
        } while (1 == 2);
    }
    updateTimer->Start(-1, TRUE);
}