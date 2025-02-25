#!/bin/sh
#./build-release.sh

mkdir -p gh-release
dlls=`cat dlls.txt`

# copy library dlls installed in msys2
for file in $dlls
do
    cp "/mingw64/bin/${file}" ./gh-release
done

# copy dlls built with djhcpp
cp ./build/lib/gcc_x64_dll/wxbase316u_gcc_custom.dll ./gh-release
cp ./build/lib/gcc_x64_dll/wxmsw316u_core_gcc_custom.dll ./gh-release

# copy the actual executable
cp ./build/djhcpp.exe ./gh-release

# make zip
cd ./gh-release
rm ../djhcpp-win.zip
zip ../djhcpp-win.zip *