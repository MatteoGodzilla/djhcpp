cmake_minimum_required(VERSION 3.0.0)
project(djhcpp VERSION 0.2.4)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
# set(BUILD_SHARED_LIBS OFF)
# set(CMAKE_EXE_LINKER_FLAGS "-static")
# set(wxBUILD_SHARED OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(CTest)
enable_testing()

configure_file(${PROJECT_SOURCE_DIR}/include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_executable(djhcpp
    "include/config.h"
    "include/CustomTable.h"
    "include/DirectoryDropTarget.h"
    "include/MainWindow.h"
    "include/TrackInfoViewer.h"
    "include/TracklistingWindow.h"
    "include/Utils.h"
    "WindowBase.h"
    src/CustomTable.cpp
    src/DirectoryDropTarget.cpp
    src/main.cpp
    src/MainWindow.cpp
    src/TracklistingWindow.cpp
    src/TrackInfoViewer.cpp
    src/Utils.cpp
    WindowBase.cpp
    )

add_subdirectory(tinyxml2)
if(MINGW OR MSYS)
    add_subdirectory(wxWidgets)
    set(wxWidgets_LIBRARIES wx::core wx::base wx::xml)
elseif(UNIX)
    find_package(wxWidgets REQUIRED COMPONENTS core base )
    include(${wxWidgets_USE_FILE})
endif()

target_include_directories(djhcpp PRIVATE include)

target_include_directories(djhcpp PUBLIC "mINI/src")

target_link_libraries(djhcpp ${wxWidgets_LIBRARIES} tinyxml2 stdc++fs curl crypto ssl)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "djhcpp-debug")
    message("Set Debug Mode")
endif()
