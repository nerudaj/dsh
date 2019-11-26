@echo off

echo Purge
rd /s /q build
rd /s /q vsbuild

echo Build GNU
call /tools/doomsh.cmd
mkdir build
cd build
    cmake.exe -G "MinGW Makefiles" ..
    mingw32-make -j4
    cpack
cd ..

echo Build VS
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
mkdir vsbuild
cd vsbuild
    cmake.exe ..
    devenv dshlibs.sln /Build Debug
    devenv dshlibs.sln /Build Release
    cpack
cd ..

@echo on