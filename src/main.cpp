#include "MainWindow.h"
#include "wx/wx.h"

#include <iostream>

class App : public wxApp {
public:
    virtual bool OnInit() {
        MainWindow* mainwindow = new MainWindow();
        mainwindow->Show();
        return true;
    }
    virtual bool OnExceptionInMainLoop() override {
        try {
            throw; //Rethrow the current Exception
        } catch ( std::exception& e ) {
            wxLogError( wxString( "EXCEPTION:" ) << e.what() );
        }
        return true;
    }
};

wxIMPLEMENT_APP( App );