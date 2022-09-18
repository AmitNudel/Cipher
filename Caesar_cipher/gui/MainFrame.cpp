#include "MainFrame.hpp"


MainFrame::MainFrame(const wxString& title) 
: wxFrame(nullptr, wxID_ANY, title)
{
    wxPanel* panel = new wxPanel(this);
    wxButton* button = new wxButton(panel, wxID_ANY, "Go", wxPoint(650, 700), wxSize(100,35));
    wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "Enter here", wxPoint(500, 300), wxSize(200, -1));

    wxArrayString choices;
    choices.Add("Encode");
    choices.Add("Decode");

    wxRadioBox* radioBox = new wxRadioBox(panel, wxID_ANY, "", wxPoint(485, 475), wxDefaultSize, choices);
}