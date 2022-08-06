
# DJHCPP
Dj Hero Control Panel Plus, a better version of [DJHCP](https://github.com/MatteoGodzilla/DJHCP) written in C++/CMake

## Release
If you want to download the latest release, [Click Here](https://github.com/MatteoGodzilla/djhcpp/releases/latest)

## Build instructions
First of all, download the repo with all of the submodules
```
git clone --recurse-submodules https://github.com/MatteoGodzilla/djhcpp.git
cd djhcpp
mkdir build
```
Then follow the instructions below depending on what OS you want to build for

### MSYS2 (Windows)
* Install [MSYS2](https://www.msys2.org/) by following the instruction on their site (make sure to update as well)
* Install cmake: `pacman -S mingw-w64-x86_64-cmake`
* Run either `build-release.sh` or `build-debug.sh` depending on what configuration you want to use

### Gnu/Linux
* Change directory to "wxWidgets": `cd wxWidgets`
* Follow the [Official Instructions](https://wiki.wxwidgets.org/Compiling_and_getting_started) to configure and make the library using the folder inside djhcpp.
* Run either `build-release.sh` or `build-debug.sh` depending on what configuration you want to use

