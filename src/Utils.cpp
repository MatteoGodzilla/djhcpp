#include "Utils.h"

wxDEFINE_EVENT(DJHCPP_EVT_FORCE_LIST_UPDATE,wxCommandEvent);

/// @brief This function receives a path to a file
/// @param original case-insensitive path that you want to find in the filesystem
/// @return path to file that has the same name as original, null otherwise
std::filesystem::path FindCaseInsensitive(std::filesystem::path original){
#if defined(__linux__) || defined(__gnu_linux__) || defined(unix) || defined(__unix) || defined(__unix__) || ( defined(__APPLE__) && defined(__MACH__) )
    //linux or mac os
    std::filesystem::path result;
    
    return NULL;
#elif defined(_WIN32) || defined(_WIN64)
    //windows
    return original;
#endif
}