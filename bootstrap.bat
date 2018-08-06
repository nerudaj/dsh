@echo off

echo Creating folders
mkdir C:\tools
mkdir C:\tools\coding
mkdir C:\tools\utils

cd Environments

echo Copying environment scripts
copy /y dsh.bat C:\tools
copy /y doomsh.cmd C:\tools

@echo on