#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp{
public:
    virtual bool OnInit(){
        MainWindow* mainwindow = new MainWindow();
        mainwindow->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);