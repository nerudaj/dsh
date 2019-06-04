@echo off

set /p version=<VERSION

echo Making release folders
mkdir dshlibs-%version%\include
mkdir dshlibs-%version%\lib
# TODO: docs

echo Copying data
copy Logger\build\liblogger.a dshlibs-%version%\lib
copy Logger\vsbuild\Debug\logger-d.lib dshlibs-%version%\lib
copy Logger\vsbuild\Release\logger.lib dshlibs-%version%\lib
copy Logger\Logger.hpp dshlibs-%version%\include

copy Strings\build\libstrings.a dshlibs-%version%\lib
copy Strings\vsbuild\Debug\strings-d.lib dshlibs-%version%\lib
copy Strings\vsbuild\Release\strings.lib dshlibs-%version%\lib
copy Strings\Strings.hpp dshlibs-%version%\include

copy Config\build\libconfig.a dshlibs-%version%\lib
copy Config\vsbuild\Debug\config-d.lib dshlibs-%version%\lib
copy Config\vsbuild\Release\config.lib dshlibs-%version%\lib
robocopy Config dshlibs-%version%\include Config.hpp Args.hpp Item.hpp Csv.hpp Ini.hpp

copy LevelD\build\libleveld.a dshlibs-%version%\lib
copy LevelD\vsbuild\Debug\config-d.lib dshlibs-%version%\lib
copy LevelD\vsbuild\Release\config.lib dshlibs-%version%\lib
copy LevelD\LevelD.hpp dshlibs-%version%\include

@echo on