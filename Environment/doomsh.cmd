@echo off

title Doom Shell

doskey ll=dir $*
doskey cat=type $*
doskey rm=del $*
doskey make=mingw32-make $*
doskey mv=move $*
doskey cp=copy $*
doskey diff=fc $*
doskey gmake=cmake.exe -G "MinGW Makefiles" $*

doskey ssh="/tools/various/putty.exe" -ssh $*
doskey scp="/tools/various/pscp.exe" $*

set PATH=%PATH%;/tools/utils/bin;/tools/utils/lib;/tools/utils/include
set PATH=%PATH%;/tools/bin/mingw/bin
set PATH=%PATH%;/tools/bin/doxygen
set PATH=%PATH%;/tools/bin/python3
set PATH=%PATH%;/tools/bin/putty/tools/python3
set PATH=%PATH%;/tools/bin/miktex/miktex/bin/x64/
set PATH=%PATH%;/tools/bin/cmake/bin

@echo on