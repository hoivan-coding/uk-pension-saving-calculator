#include <wx/wx.h>
#include "MainFrame.cpp"
class MainApp : public wxApp
{
public:
    virtual bool OnInit();
};
wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}
