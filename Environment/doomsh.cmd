@echo off

title DSH

doskey ll=dir $*
doskey cat=type $*
doskey rm=del $*
doskey mv=move $*
doskey cp=copy $*
doskey diff=fc $*
doskey mc=md $1$tcd $1

doskey make=mingw32-make $*
doskey gmake=cmake.exe -G "MinGW Makefiles" $*

set PATH=%PATH%;/tools/bin;/tools/utils/lib;/tools/utils/include
set PATH=%PATH%;/tools/bin/mingw/bin
set PATH=%PATH%;/tools/bin/doxygen
set PATH=%PATH%;/tools/bin/python3
set PATH=%PATH%;/tools/bin/miktex/miktex/bin/x64/
set PATH=%PATH%;/tools/bin/cmake/bin

rem help
echo DSH cheatsheet
echo.
echo Basic commands
echo   ll ^<path1 [...]^>
echo   cat ^<file1 [...]^>
echo   rm ^<file^> - Delete file
echo   mv ^<file1 file2^> - Move files
echo   cp ^<file1 file2^> - Copy files
echo   diff ^<file1 file2^> - Diff two files
echo   mc ^<name^> - Create folder and cd into it
echo.
echo Build commands:
echo   make - Make using mingw32-make (requires Makefile in current dir)
echo   gmake ^<path^> - Configure cmake project to use mingw gcc (there is CMakeLists.txt at given path)
echo Tip of the day:
echo forfiles /C "cmd /c echo @file"
echo findstr /N /P dummy ^<filename^>
echo.

@echo on