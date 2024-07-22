#include "Utils.h"

#if defined( __linux__ ) || defined( __gnu_linux__ ) || defined( unix ) || \
defined( __unix ) || defined( __unix__ ) ||                                \
( defined( __APPLE__ ) && defined( __MACH__ ) )
    #define COMPILE_UNIX
#elif defined( _WIN32 ) || defined( _WIN64 )
    #define COMPILE_WIN
    #include <fileapi.h>
    #include <libloaderapi.h>
#endif

wxDEFINE_EVENT( DJHCPP_EVT_FORCE_LIST_UPDATE, wxCommandEvent );

std::string ToLower( std::string s ) {
    std::string res;
    for ( char ch : s ) {
        res += std::tolower( ch );
    }
    return res;
}

/// @brief This function receives a path to a file
/// @param original case-insensitive path that you want to find in the
/// filesystem
/// @return path to file that has the same name as original, null otherwise
std::filesystem::path
FindFileCaseInsensitive( std::filesystem::path startDirectory, std::filesystem::path original ) {
#ifdef COMPILE_UNIX
    // FIXME
    // linux or mac os
    std::filesystem::path result( "" );

    // iterate over the parent directory of original
    std::string lowercaseOriginal = ToLower( original.generic_string() );

    for ( auto const& dir_entry :
          std::filesystem::recursive_directory_iterator( startDirectory ) ) {
        // wxLogMessage(wxString(dir_entry.path().filename().generic_string()));
        std::string lowercaseDirEntry =
        ToLower( dir_entry.path().generic_string() );
        if ( lowercaseDirEntry.compare( lowercaseOriginal ) == 0 ) {
            result = dir_entry.path();
            break;
        }
    }
    // if file name in lowercase matches original in lowercase, we found the
    // file
    return result;
#endif
#ifdef COMPILE_WIN
    // windows
    // the fs is already case insensitive, so we don't need to do anything
    return original;
#endif
}

// https://stackoverflow.com/questions/1528298/get-path-of-executable
std::filesystem::path GetRunningPathOfExecutable() {
#ifdef COMPILE_UNIX
    return std::filesystem::canonical( "/proc/self/exe" );
#endif
#ifdef COMPILE_WIN
    wchar_t buffer[256];
    GetModuleFileName( NULL, buffer, 256 );
    return std::filesystem::path( buffer );
#endif
}

std::wstring GetFileSystemTypeFromPath( std::filesystem::path path ) {
#ifdef COMPILE_UNIX
    //FIXME
    return "";
#endif
#ifdef COMPILE_WIN
    wchar_t buffer[256];
    bool result = GetVolumeInformationW( path.root_name().c_str(), NULL, 0, NULL, NULL, NULL, buffer, 256 );
    return std::wstring( buffer );
#endif
}