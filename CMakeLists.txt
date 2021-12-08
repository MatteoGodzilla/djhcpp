cmake_minimum_required(VERSION 3.0.0)
project(djhcpp VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(djhcp+ main.cpp MainWindowCallbacks.cpp MainWindow.cpp)

add_subdirectory(wxWidgets)
target_link_libraries(djhcp+ wx::core wx::base)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
