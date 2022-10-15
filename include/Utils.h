#pragma once
#include <wx/event.h>
#include <filesystem>

//events
wxDECLARE_EVENT(DJHCPP_EVT_FORCE_LIST_UPDATE,wxCommandEvent);

//utility functions
std::filesystem::path FindCaseInsensitive(std::filesystem::path original);
