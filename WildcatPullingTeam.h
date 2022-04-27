#pragma once

#include "resource.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    wxButton* event_durability;
    wxButton* event_pulling;
    //adds maneuverability button
    wxButton* event_maneuverability;
    //adds diagnostics button
    wxButton* event_diagnostics;
    //add start recording button
    wxButton* event_start_recording;
    //adds end recording button
    wxButton* event_end_recording;

    //adds all 10 gauges
    wxGauge* gauge1;
    wxGauge* gauge2;
    wxGauge* gauge3;
    wxGauge* gauge4;
    wxGauge* gauge5;
    wxGauge* gauge6;
    wxGauge* gauge7;
    wxGauge* gauge8;
    wxGauge* gauge9;
    wxGauge* gauge10;
    wxGauge* gauge11;
    wxGauge* gauge12;
    wxGauge* gauge13;
    wxGauge* gauge14;
    wxGauge* gauge15;
    wxGauge* gauge16;
    wxGauge* gauge17;
    wxGauge* gauge18;

    //gauge 1 min label
    wxTextCtrl* gauge1MIN;
    wxTextCtrl* gauge1MAX;
    wxTextCtrl* gauge1CUR;
    wxTextCtrl* gauge1TITLE;

    //gauge 2 min label
    wxTextCtrl* gauge2MIN;
    wxTextCtrl* gauge2MAX;
    wxTextCtrl* gauge2CUR;
    wxTextCtrl* gauge2TITLE;

    //gauge 3 min label
    wxTextCtrl* gauge3MIN;
    wxTextCtrl* gauge3MAX;
    wxTextCtrl* gauge3CUR;
    wxTextCtrl* gauge3TITLE;

    //gauge 4 min label
    wxTextCtrl* gauge4MIN;
    wxTextCtrl* gauge4MAX;
    wxTextCtrl* gauge4CUR;
    wxTextCtrl* gauge4TITLE;

    //gauge 5 min label
    wxTextCtrl* gauge5MIN;
    wxTextCtrl* gauge5MAX;
    wxTextCtrl* gauge5CUR;
    wxTextCtrl* gauge5TITLE;

    //gauge 6 min label
    wxTextCtrl* gauge6MIN;
    wxTextCtrl* gauge6MAX;
    wxTextCtrl* gauge6CUR;
    wxTextCtrl* gauge6TITLE;

    //gauge 7 min label
    wxTextCtrl* gauge7MIN;
    wxTextCtrl* gauge7MAX;
    wxTextCtrl* gauge7CUR;
    wxTextCtrl* gauge7TITLE;

    //gauge 8 min label
    wxTextCtrl* gauge8MIN;
    wxTextCtrl* gauge8MAX;
    wxTextCtrl* gauge8CUR;
    wxTextCtrl* gauge8TITLE;

    //gauge 9 min label
    wxTextCtrl* gauge9MIN;
    wxTextCtrl* gauge9MAX;
    wxTextCtrl* gauge9CUR;
    wxTextCtrl* gauge9TITLE;

    //gauge 10 min label
    wxTextCtrl* gauge10MIN;
    wxTextCtrl* gauge10MAX;
    wxTextCtrl* gauge10CUR;
    wxTextCtrl* gauge10TITLE;

    //gauge 11 min label
    wxTextCtrl* gauge11MIN;
    wxTextCtrl* gauge11MAX;
    wxTextCtrl* gauge11CUR;
    wxTextCtrl* gauge11TITLE;

    //gauge 12 min label
    wxTextCtrl* gauge12MIN;
    wxTextCtrl* gauge12MAX;
    wxTextCtrl* gauge12CUR;
    wxTextCtrl* gauge12TITLE;

    //gauge 13 min label
    wxTextCtrl* gauge13MIN;
    wxTextCtrl* gauge13MAX;
    wxTextCtrl* gauge13CUR;
    wxTextCtrl* gauge13TITLE;

    //gauge 14 min label
    wxTextCtrl* gauge14MIN;
    wxTextCtrl* gauge14MAX;
    wxTextCtrl* gauge14CUR;
    wxTextCtrl* gauge14TITLE;

    //gauge 15 min label
    wxTextCtrl* gauge15MIN;
    wxTextCtrl* gauge15MAX;
    wxTextCtrl* gauge15CUR;
    wxTextCtrl* gauge15TITLE;

    //gauge 16 min label
    wxTextCtrl* gauge16MIN;
    wxTextCtrl* gauge16MAX;
    wxTextCtrl* gauge16CUR;
    wxTextCtrl* gauge16TITLE;

    //gauge17 min label
    wxTextCtrl* gauge17MIN;
    wxTextCtrl* gauge17MAX;
    wxTextCtrl* gauge17CUR;
    wxTextCtrl* gauge17TITLE;

    //gauge 18 min label
    wxTextCtrl* gauge18MIN;
    wxTextCtrl* gauge18MAX;
    wxTextCtrl* gauge18CUR;
    wxTextCtrl* gauge18TITLE;

    wxTimer* updateTimer;

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void Event_durability(wxCommandEvent& event);
    void Event_pulling(wxCommandEvent& event);
    void Event_maneuverability(wxCommandEvent& event);
    void Event_diagnostics(wxCommandEvent& event);
    void Event_start_recording(wxCommandEvent& event);
    void Event_end_recording(wxCommandEvent& event);
    void Update(wxTimerEvent& event);

    wxDECLARE_EVENT_TABLE();
};
