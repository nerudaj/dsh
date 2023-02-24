@echo off

set src=%~1
set dst=%~2

if not defined src (
	echo ERROR: URL to file must be specified!
	exit /b 1
)

if "%src%"=="/?" (
	echo USAGE:
	echo wget url target_file
	exit /b 0
)

if not defined dst (
	echo ERROR: Target file name must be specified!
	exit /b 1
)

cscript //nologo wget.js "%src%" "%dst%"
echo Downloaded!

@echo on
