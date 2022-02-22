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
    wxButton* event_durability = NULL;
    wxButton* event_pulling = NULL;
    wxButton* event_maneuverability = NULL;
    wxButton* event_diagnostics = NULL;
    wxButton* event_start_recording = NULL;
    wxButton* event_end_recording = NULL;

    wxGauge* gauge1 = NULL;
    wxGauge* gauge2 = NULL;
    wxGauge* gauge3 = NULL;
    wxGauge* gauge4 = NULL;
    wxGauge* gauge5 = NULL;
    wxGauge* gauge6 = NULL;
    wxGauge* gauge7 = NULL;
    wxGauge* gauge8 = NULL;
    wxGauge* gauge9 = NULL;
    wxGauge* gauge10 = NULL;

    wxTextCtrl* gauge1MIN;
    wxTextCtrl* gauge1MAX;
    wxTextCtrl* gauge1CUR;
    wxTextCtrl* gauge1TITLE;

    wxTextCtrl* gauge2MIN;
    wxTextCtrl* gauge2MAX;
    wxTextCtrl* gauge2CUR;
    wxTextCtrl* gauge2TITLE;

    wxTextCtrl* gauge3MIN;
    wxTextCtrl* gauge3MAX;
    wxTextCtrl* gauge3CUR;
    wxTextCtrl* gauge3TITLE;

    wxTextCtrl* gauge4MIN;
    wxTextCtrl* gauge4MAX;
    wxTextCtrl* gauge4CUR;
    wxTextCtrl* gauge4TITLE;

    wxTextCtrl* gauge5MIN;
    wxTextCtrl* gauge5MAX;
    wxTextCtrl* gauge5CUR;
    wxTextCtrl* gauge5TITLE;

    wxTextCtrl* gauge6MIN;
    wxTextCtrl* gauge6MAX;
    wxTextCtrl* gauge6CUR;
    wxTextCtrl* gauge6TITLE;

    wxTextCtrl* gauge7MIN;
    wxTextCtrl* gauge7MAX;
    wxTextCtrl* gauge7CUR;
    wxTextCtrl* gauge7TITLE;

    wxTextCtrl* gauge8MIN;
    wxTextCtrl* gauge8MAX;
    wxTextCtrl* gauge8CUR;
    wxTextCtrl* gauge8TITLE;

    wxTextCtrl* gauge9MIN;
    wxTextCtrl* gauge9MAX;
    wxTextCtrl* gauge9CUR;
    wxTextCtrl* gauge9TITLE;

    wxTextCtrl* gauge10MIN;
    wxTextCtrl* gauge10MAX;
    wxTextCtrl* gauge10CUR;
    wxTextCtrl* gauge10TITLE;


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


    wxDECLARE_EVENT_TABLE();
};
