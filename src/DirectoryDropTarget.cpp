#include "DirectoryDropTarget.h"

#include "MainWindow.h"

namespace fs = std::filesystem;

DirectoryDropTarget::DirectoryDropTarget( MainWindow* parent ) {
    mainWindow = parent;
}

bool DirectoryDropTarget::OnDropFiles( wxCoord x, wxCoord y, const wxArrayString& filenames ) {
    wxLogMessage( "RECEIVED DROP!" );
    for ( auto& file : filenames ) {
        fs::path p = fs::path( file.ToStdString() );
        if ( fs::is_directory( p ) ) {
            wxLogMessage( wxString( "Found directory to import:" ) << file );
            if ( fs::exists( p / "DJH2" ) )
                p /= "DJH2";
            mainWindow->ProcessCustom( p );
        }
    }
    return false;
}