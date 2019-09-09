@echo off

echo Creating folder structure
mkdir C:\tools
mkdir C:\tools\bin
mkdir C:\tools\utils\bin
mkdir C:\tools\utils\include
mkdir C:\tools\utils\lib
mkdir C:\tools\opt

cd Environments

echo Copying environment scripts
copy /y dsh.bat C:\tools
copy /y doomsh.cmd C:\tools

cd Scripts

echo Copying scripts
copy /y * C:\tools\bin
cd ../../Utilities/wget
copy /y wget.js C:\tools\bin

cd /tools/bin

echo Installing mingw
mkdir mingw && cd mingw
cscript C:\tools\bin\wget.js "http://apps.wz.cz/debug/mingw.zip" mingw.zip
cscript C:\tools\bin\unzip.vbs mingw.zip

del mingw.zip
cd bin
mingw-get install mingw32-gcc-g++ mingw32-make mingw32-gdb mingw32-zlib libmingwex

echo Installing cmake
cd /tools/bin
cscript C:\tools\bin\wget.js "https://github.com/Kitware/CMake/releases/download/v3.14.1/cmake-3.14.1-win64-x64.zip" cmake.zip
cscript C:\tools\bin\unzip.vbs cmake.zip
del cmake.zip
move cmake-3.14.1-win64-x64 cmake

Installing python
cd /tools/bin
mkdir python && cd python
cscript C:\tools\bin\wget.js "https://www.python.org/ftp/python/3.7.3/python-3.7.3-embed-amd64.zip" python.zip
cscript C:\tools\bin\unzip.vbs python.zip
del python.zip

echo Installing putty suite
cd /tools/bin
mkdir putty && cd putty
cscript C:\tools\bin\wget.js "https://the.earth.li/~sgtatham/putty/latest/w64/putty.zip" putty.zip
cscript C:\tools\bin\unzip.vbs putty.zip
del putty.zip

echo Installing doxygen suite
cd /tools/bin
mkdir doxygen && cd doxygen
cscript C:\tools\bin\wget.js "http://doxygen.nl/files/doxygen-1.8.15.windows.x64.bin.zip" doxygen.zip
cscript C:\tools\bin\unzip.vbs doxygen.zip
del doxygen.zip

echo Installing dsh runtime libraries
echo TODO

@echo on