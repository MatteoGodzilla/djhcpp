
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

Then follow the instructions below depending on what OS you want to build for.

### MSYS2 (Windows) prerequisites 
* Install [MSYS2](https://www.msys2.org/) by following the instruction on their site (make sure to update as well)
* Open `MSYS2 MSYS` and install cmake: `pacman -S mingw-w64-x86_64-cmake`
* Close `MSYS2 MSYS` and open `MSYS2 MinGW x64` (Any other terminal different from MinGW x64 won't see cmake).
* Continue to [Actually building the code](#actually-building-the-code)

### Gnu/Linux prerequisites
* Change directory to "wxWidgets": `cd wxWidgets`
* Follow the [Official Instructions](https://wiki.wxwidgets.org/Compiling_and_getting_started) to configure and make the library using the folder inside djhcpp.
* Continue to [Actually building the code](#actually-building-the-code)

### Actually building the code 
DJHCPP is a cmake project, so if you already know how to build using cmake this section is irrelevant.

If otherwise you don't know how to build, there are two utility sh scripts in the root of the project.
`build-release.sh` and `build-debug.sh` will build using standard unix makefiles. 

These scripts are meant to be run in the root of the project with a build folder already present (if you followed this readme you already made that folder).