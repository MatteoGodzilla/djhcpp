#pragma once
#include <wx/event.h>
#include <wx/log.h>
#include <filesystem>

//events
wxDECLARE_EVENT(DJHCPP_EVT_FORCE_LIST_UPDATE,wxCommandEvent);

//utility functions
std::filesystem::path FindFileCaseInsensitive(std::filesystem::path startDirectory, std::filesystem::path file);
