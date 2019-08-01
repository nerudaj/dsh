call /tools/doomsh.cmd
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"

@echo off

cd Strings
set rtn=strings
goto test-builddir
:strings
cd ../..

cd Strings/vsbuild
devenv strings.sln /Build Debug
copy Debug\strings-d.lib C:\tools\lib
devenv strings.sln /Build Release
copy Release\strings.lib C:\tools\lib
cd ../..

cd Config
set rtn=config
goto test-builddir
:config
cd ../..

cd Config/vsbuild
devenv config.sln /Build Debug
copy Debug\config-d.lib C:\tools\lib
devenv config.sln /Build Release
copy Release\config.lib C:\tools\lib
cd ../..


cd LevelD
set rtn=leveld
goto test-builddir
:leveld
cd ../..

cd LevelD/vsbuild
devenv leveld.sln /Build Debug
copy Debug\leveld-d.lib C:\tools\lib
devenv leveld.sln /Build Release
copy Release\leveld.lib C:\tools\lib
cd ../..

pause

exit 0

:test-builddir
if not exist vsbuild (
	mkdir vsbuild
	cd vsbuild
	cmake.exe ..
) else (
	cd vsbuild
	cmake.exe ..
)
goto %rtn%