cmake_minimum_required(VERSION 3.0.0)
project(djhcpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(wxBUILD_SHARED OFF)

include(CTest)
enable_testing()

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

add_executable(djhcpp 
    main.cpp 
    MainWindow.cpp 
    WindowBase.cpp
)

add_subdirectory(tinyxml2)
add_subdirectory(wxWidgets)

target_link_libraries(djhcpp wx::core wx::base wx::xml tinyxml2 stdc++fs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
