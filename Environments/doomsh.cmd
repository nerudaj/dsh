@echo off

title Doom Shell

doskey colorize=color 4B
doskey ll=dir $*
doskey cat=type $*
doskey rm=del $*
doskey make=mingw32-make $*
doskey mv=move $*
doskey cp=copy $*
doskey diff=fc $*

doskey ssh="/tools/various/putty.exe" -ssh $*
doskey scp="/tools/various/pscp.exe" $*


set PATH=%PATH%;/tools/mingw/bin;/tools/doxygen;/tools/various;/tools/python3;/tools/miktex/miktex/bin/x64/;/tools/utils

@echo on