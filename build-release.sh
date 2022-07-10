#!/bin/sh
cd build
cmake .. -G"Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -j16
