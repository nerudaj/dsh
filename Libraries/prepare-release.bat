@echo off

set /p version=<VERSION

echo Purge
rd /s /q build
rd /s /q vsbuild

echo Build GNU
call /tools/doomsh.cmd
mkdir build
cd build
    cmake.exe -G "MinGW Makefiles" ..
    mingw32-make
cd ..

echo Build VS
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
mkdir vsbuild
cd vsbuild
    cmake.exe ..
    devenv dshlibs.sln /Build Debug
    devenv dshlibs.sln /Build Release
cd ..

echo Making release folders
mkdir RELEASE
mkdir RELEASE\dshlibs-%version%-mingw8\include
mkdir RELEASE\dshlibs-%version%-mingw8\lib
mkdir RELEASE\dshlibs-%version%-mingw8\docs
mkdir RELEASE\dshlibs-%version%-vs2019-x64\include
mkdir RELEASE\dshlibs-%version%-vs2019-x64\lib
mkdir RELEASE\dshlibs-%version%-vs2019-x64\docs

echo Copying data

copy build\Strings\libstrings.a RELEASE\dshlibs-%version%-mingw8\lib
copy vsbuild\Strings\Debug\strings-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy vsbuild\Strings\Release\strings.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy Strings\Strings.hpp RELEASE\dshlibs-%version%-mingw8\include
copy Strings\Strings.hpp RELEASE\dshlibs-%version%-vs2019-x64\include

copy build\Config\libconfig.a RELEASE\dshlibs-%version%-mingw8\lib
copy vsbuild\Config\Debug\config-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy vsbuild\Config\Release\config.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
robocopy Config RELEASE\dshlibs-%version%-mingw8\include Config.hpp Args.hpp Item.hpp Csv.hpp Ini.hpp
robocopy Config RELEASE\dshlibs-%version%-vs2019-x64\include Config.hpp Args.hpp Item.hpp Csv.hpp Ini.hpp

copy build\LevelD\libleveld.a RELEASE\dshlibs-%version%-mingw8\lib
copy vsbuild\LevelD\Debug\leveld-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy vsbuild\LevelD\Release\leveld.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy LevelD\LevelD.hpp RELEASE\dshlibs-%version%-mingw8\include
copy LevelD\LevelD.hpp RELEASE\dshlibs-%version%-vs2019-x64\include

copy build\Bitmap\libbitmap.a RELEASE\dshlibs-%version%-mingw8\lib
copy vsbuild\Bitmap\Debug\bitmap-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy vsbuild\Bitmap\Release\bitmap.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy Bitmap\Bitmap.hpp RELEASE\dshlibs-%version%-mingw8\include
copy Bitmap\Bitmap.hpp RELEASE\dshlibs-%version%-vs2019-x64\include

rem Copy LevelD docs
copy LevelD\LevelD.md RELEASE\dshlibs-%version%-mingw8\docs
copy LevelD\LevelD.md RELEASE\dshlibs-%version%-vs2019-x64\docs

copy changelog.txt RELEASE\dshlibs-%version%-mingw8
copy changelog.txt RELEASE\dshlibs-%version%-vs2019-x64

@echo on