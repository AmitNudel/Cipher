#include "App.hpp"
#include "MainFrame.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Caesar");
    mainFrame->SetClientSize(600,800);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}