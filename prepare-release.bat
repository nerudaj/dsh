@echo off

echo Purge
rd /s /q build
rd /s /q vsbuild

echo Build GNU
call /tools/doomsh.cmd
mkdir build
cd build
    cmake.exe -G "MinGW Makefiles" ..
    mingw32-make catch2
    mingw32-make -j4
    cpack
cd ..

echo Build VS
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
mkdir vsbuild
cd vsbuild
    cmake.exe ..
    devenv dsh.sln /Build Release /Project catch2
    devenv dsh.sln /Build Debug
    devenv dsh.sln /Build Release
    cpack
cd ..

mkdir RELEASE
copy build\*.zip RELEASE\
copy vsbuild\*.zip RELEASE\

@echo on