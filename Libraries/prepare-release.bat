@echo off

set /p version=<VERSION

echo Making release folders
mkdir RELEASE
mkdir RELEASE\dshlibs-%version%-mingw8\include
mkdir RELEASE\dshlibs-%version%-mingw8\lib
mkdir RELEASE\dshlibs-%version%-vs2019-x64\include
mkdir RELEASE\dshlibs-%version%-vs2019-x64\lib

pause

echo Copying data

copy Strings\build\libstrings.a RELEASE\dshlibs-%version%-mingw8\lib
copy Strings\vsbuild\Debug\strings-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy Strings\vsbuild\Release\strings.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy Strings\Strings.hpp RELEASE\dshlibs-%version%-mingw8\include
copy Strings\Strings.hpp RELEASE\dshlibs-%version%-vs2019-x64\include

copy Config\build\libconfig.a RELEASE\dshlibs-%version%-mingw8\lib
copy Config\vsbuild\Debug\config-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy Config\vsbuild\Release\config.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
robocopy Config RELEASE\dshlibs-%version%-mingw8\include Config.hpp Args.hpp Item.hpp Csv.hpp Ini.hpp
robocopy Config RELEASE\dshlibs-%version%-vs2019-x64\include Config.hpp Args.hpp Item.hpp Csv.hpp Ini.hpp

copy LevelD\build\libleveld.a RELEASE\dshlibs-%version%-mingw8\lib
copy LevelD\vsbuild\Debug\leveld-d.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy LevelD\vsbuild\Release\leveld.lib RELEASE\dshlibs-%version%-vs2019-x64\lib
copy LevelD\LevelD.hpp RELEASE\dshlibs-%version%-mingw8\include
copy LevelD\LevelD.hpp RELEASE\dshlibs-%version%-vs2019-x64\include

copy changelog.txt RELEASE\dshlibs-%version%-mingw8
copy changelog.txt RELEASE\dshlibs-%version%-vs2019-x64

@echo on