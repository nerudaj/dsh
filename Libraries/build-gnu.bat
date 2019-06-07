call /tools/doomsh.cmd

@echo off

echo Building liblogger
cd Logger
set rtn=logger
goto test-builddir
:logger
mingw32-make
mingw32-make install
cd ../..

echo Building libstrings
cd Strings
set rtn=strings
goto test-builddir
:strings
mingw32-make
mingw32-make install
cd ../..

echo Building libconfig
cd Config
set rtn=config
goto test-builddir
:config
mingw32-make
mingw32-make install
cd ../..

echo Building libleveld
cd LevelD
set rtn=leveld
goto test-builddir
:leveld
mingw32-make
mingw32-make install
cd ../..

echo Exiting
goto:eof

:test-builddir
if not exist build (
	mkdir build
	cd build
	cmake.exe -G "MinGW Makefiles" ..
) else (
	cd build
)
goto %rtn%
