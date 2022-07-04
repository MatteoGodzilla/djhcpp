#!/bin/sh
cd build
cmake .. -G"Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
make -j16 && ./djhcpp.exe
