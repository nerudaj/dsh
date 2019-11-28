@echo off

echo Creating folder root
mkdir C:\tools
mkdir C:\tools\bin


echo Copying runtime libraries and binaries
cd ..
robocopy include C:\tools\include
robocopy lib C:\tools\lib
rem TODO robocopy bin C:\tools\bin


echo Installing environment
cd install
copy /y dsh.bat C:\tools
copy /y doomsh.cmd C:\tools


echo Copying auxiliary install scripts
copy /y unzip.vbs C:\tools\bin
copy /y wget.js C:\tools\bin


echo Downloading MinGW
cd /tools/bin
mkdir mingw
cd mingw
cscript C:\tools\bin\wget.js "http://apps.wz.cz/debug/mingw.zip" mingw.zip
cscript C:\tools\bin\unzip.vbs mingw.zip
del mingw.zip


echo Installing GCC, G++, Make, GDB, ZLib, libmingwex
cd bin
mingw-get install mingw32-gcc-g++ mingw32-make mingw32-gdb mingw32-zlib libmingwex


echo Installing CMake 3.14
cd /tools/bin
cscript C:\tools\bin\wget.js "https://github.com/Kitware/CMake/releases/download/v3.14.1/cmake-3.14.1-win64-x64.zip" cmake.zip
cscript C:\tools\bin\unzip.vbs cmake.zip
del cmake.zip
move cmake-3.14.1-win64-x64 cmake


echo Installing Python 3.7.3
cd /tools/bin
mkdir python
cd python
cscript C:\tools\bin\wget.js "https://www.python.org/ftp/python/3.7.3/python-3.7.3-embed-amd64.zip" python.zip
cscript C:\tools\bin\unzip.vbs python.zip
del python.zip


echo Installing Putty suite
cd /tools/bin
mkdir putty
cd putty
cscript C:\tools\bin\wget.js "https://the.earth.li/~sgtatham/putty/latest/w64/putty.zip" putty.zip
cscript C:\tools\bin\unzip.vbs putty.zip
del putty.zip


echo Installing Doxygen 1.8.15
cd /tools/bin
mkdir doxygen
cd doxygen
cscript C:\tools\bin\wget.js "http://doxygen.nl/files/doxygen-1.8.15.windows.x64.bin.zip" doxygen.zip
cscript C:\tools\bin\unzip.vbs doxygen.zip
del doxygen.zip


echo Verification
call /tools/doomsh.cmd || goto error
mingw32-make --version || goto error
gcc --version || goto error
g++ --version || goto error
cmake --version || goto error
doxygen --version || goto error
python --version || goto error


:succ
@echo on
exit /b 0

:error
@echo on
exit /b 1
