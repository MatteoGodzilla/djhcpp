#!/bin/sh
cd build
cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE="Release"
make -j$(nproc)
