cmake_minimum_required(VERSION 3.0.0)
project(djhcpp VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(djhcpp main.cpp MainWindow.cpp WindowBase.cpp)

add_subdirectory(wxWidgets)
target_link_libraries(djhcpp wx::core wx::base)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
