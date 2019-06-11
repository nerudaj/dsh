call /tools/doomsh.cmd

#@echo off

cd Logger
set rtn=logger
goto test-builddir
:logger
cd ../..

cd Strings
set rtn=strings
goto test-builddir
:strings
cd ../..

cd Config
set rtn=config
goto test-builddir
:config
cd ../..

cd LevelD
set rtn=leveld
goto test-builddir
:leveld
cd ../..

pause
goto build

:test-builddir
if not exist vsbuild (
	mkdir vsbuild
	cd vsbuild
	cmake.exe ..
) else (
	cd vsbuild
)
goto %rtn%

:build
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"

cd Logger/vsbuild
devenv logger.sln /Build Debug
devenv logger.sln /Build Release
cd ../..

cd Strings/vsbuild
devenv strings.sln /Build Debug
devenv strings.sln /Build Release
cd ../..

cd Config/vsbuild
devenv config.sln /Build Debug
devenv config.sln /Build Release
cd ../..

cd LevelD/vsbuild
devenv leveld.sln /Build Debug
devenv leveld.sln /Build Release
cd ../..

