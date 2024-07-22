#include "StringsViewer.h"

#include "MainWindow.h"

StringsViewer::StringsViewer( MainWindow* parent ) :
    TrackTextViewer( parent ) {
    mainWindowRef = parent;
    RebuildTable( std::wstring() );
}

void StringsViewer::OnTextChange( wxCommandEvent& event ) {
    //table->DeleteAllItems();
    RebuildTable( event.GetString().ToStdWstring() );
}

void StringsViewer::OnEditingDone( wxDataViewEvent& event ) {
    std::wstring update = event.GetValue().GetString().ToStdWstring();
    int row = table->GetSelectedRow();
    int col = event.GetColumn();

    wxVariant oldID;
    table->GetStore()->GetValueByRow( oldID, row, 0 );

    if ( col == 1 ) {
        // the value changed
        mainWindowRef->textData[oldID] = update;
    } else {
        //the id changed -> bit more complicated
        std::wstring oldValue = mainWindowRef->textData[oldID];
        mainWindowRef->textData.erase( oldID );
        mainWindowRef->textData[update] = oldValue;
    }
}

void StringsViewer::RebuildTable( std::wstring query ) {
    table->DeleteAllItems();
    for ( auto& pair : mainWindowRef->textData ) {
        bool allowed = false;

        // check if the query is somewhat inside the current string
        // the query must be shorter than the text

        allowed = pair.first.find( query ) != std::wstring::npos;
        allowed = allowed || pair.second.find( query ) != std::wstring::npos;

        int idCharIndex = 0;
        for ( size_t i = 0; i < pair.first.size(); i++ ) {
            if ( idCharIndex < query.size() ) {
                //check character
                if ( tolower( pair.first[i] ) == tolower( query[idCharIndex] ) )
                    idCharIndex++;
            } else {
                //we ran out of the query string
                allowed = true;
                break;
            }
        }

        if ( !allowed ) {
            //check for the value
            int valueCharIndex = 0;
            for ( size_t i = 0; i < pair.second.size(); i++ ) {
                if ( valueCharIndex < query.size() ) {
                    //check character
                    if ( tolower( pair.second[i] ) == tolower( query[valueCharIndex] ) )
                        valueCharIndex++;
                } else {
                    //we ran out of the query string
                    allowed = true;
                    break;
                }
            }
        }

        if ( allowed ) {
            wxVector<wxVariant> row = wxVector<wxVariant>();
            row.push_back( wxString() << pair.first );
            row.push_back( wxString() << pair.second );
            table->AppendItem( row );
        }
    }
}

void StringsViewer::OnClose( wxCloseEvent& event ) {
    mainWindowRef->CreateAutomaticBackup();
    mainWindowRef->Export();
    event.Skip();
}