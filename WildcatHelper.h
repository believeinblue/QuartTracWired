#pragma once
#pragma once

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "WildcatPullingTeam.h"
//application definition of public and private aspects
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
//ID number enumeration for each aspect on the GUI
enum
{
    //ID numbers for menues and button IDS
    ID_Hello = 1,
    BUTTON_durability = wxID_HIGHEST + 1,
    BUTTON_pulling = wxID_HIGHEST + 2,
    BUTTON_maneuverability = wxID_HIGHEST + 3,
    BUTTON_diagnostics = wxID_HIGHEST + 4,
    BUTTON_start_recording = wxID_HIGHEST + 5,
    BUTTON_end_recording = wxID_HIGHEST + 6,

    //IDS for every gauge
    Gauge1 = wxID_HIGHEST + 7,
    Gauge2 = wxID_HIGHEST + 8,
    Gauge3 = wxID_HIGHEST + 9,
    Gauge4 = wxID_HIGHEST + 10,
    Gauge5 = wxID_HIGHEST + 11,
    Gauge6 = wxID_HIGHEST + 12,
    Gauge7 = wxID_HIGHEST + 13,
    Gauge8 = wxID_HIGHEST + 14,
    Gauge9 = wxID_HIGHEST + 15,
    Gauge10 = wxID_HIGHEST + 16,

    //IDS for the gauge 1 textboxes
    TEXT_G1MIN = wxID_HIGHEST + 17,
    TEXT_G1MAX = wxID_HIGHEST + 18,
    TEXT_G1CUR = wxID_HIGHEST + 19,
    TEXT_G1TITLE = wxID_HIGHEST + 20,

    //IDS for the gauge 2 textboxes
    TEXT_G2MIN = wxID_HIGHEST + 21,
    TEXT_G2MAX = wxID_HIGHEST + 22,
    TEXT_G2CUR = wxID_HIGHEST + 23,
    TEXT_G2TITLE = wxID_HIGHEST + 24,

    //IDS for the gauge 3 textboxes
    TEXT_G3MIN = wxID_HIGHEST + 25,
    TEXT_G3MAX = wxID_HIGHEST + 26,
    TEXT_G3CUR = wxID_HIGHEST + 27,
    TEXT_G3TITLE = wxID_HIGHEST + 28,

    //IDS for the gauge 4 textboxes
    TEXT_G4MIN = wxID_HIGHEST + 29,
    TEXT_G4MAX = wxID_HIGHEST + 30,
    TEXT_G4CUR = wxID_HIGHEST + 31,
    TEXT_G4TITLE = wxID_HIGHEST + 32,

    //IDS for the gauge 5 textboxes
    TEXT_G5MIN = wxID_HIGHEST + 33,
    TEXT_G5MAX = wxID_HIGHEST + 34,
    TEXT_G5CUR = wxID_HIGHEST + 35,
    TEXT_G5TITLE = wxID_HIGHEST + 36,
    
    //IDS for the gauge 6 textboxes
    TEXT_G6MIN = wxID_HIGHEST + 37,
    TEXT_G6MAX = wxID_HIGHEST + 38,
    TEXT_G6CUR = wxID_HIGHEST + 39,
    TEXT_G6TITLE = wxID_HIGHEST + 40,

    //IDS for the gauge 7 textboxes
    TEXT_G7MIN = wxID_HIGHEST + 41,
    TEXT_G7MAX = wxID_HIGHEST + 42,
    TEXT_G7CUR = wxID_HIGHEST + 43,
    TEXT_G7TITLE = wxID_HIGHEST + 44,

    //IDS for the gauge 8 textboxes
    TEXT_G8MIN = wxID_HIGHEST + 45,
    TEXT_G8MAX = wxID_HIGHEST + 46,
    TEXT_G8CUR = wxID_HIGHEST + 47,
    TEXT_G8TITLE = wxID_HIGHEST + 48,

    //IDS for the gauge 9 textboxes
    TEXT_G9MIN = wxID_HIGHEST + 49,
    TEXT_G9MAX = wxID_HIGHEST + 50,
    TEXT_G9CUR = wxID_HIGHEST + 51,
    TEXT_G9TITLE = wxID_HIGHEST + 52,

    //IDS for the gauge 10 textboxes
    TEXT_G10MIN = wxID_HIGHEST + 53,
    TEXT_G10MAX = wxID_HIGHEST + 54,
    TEXT_G10CUR = wxID_HIGHEST + 55,
    TEXT_G10TITLE = wxID_HIGHEST + 56,
};