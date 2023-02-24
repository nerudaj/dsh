@echo off

set fname=%~1

if not defined fname (
	echo ERROR: You need to provide path to file that should be extracted
	exit /b 1
)

cscript //nologo unzip.vbs %fname%

@echo on
