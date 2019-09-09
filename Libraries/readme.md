# Libraries

This folder contains libraries that are released under name dshlibs. Libraries that are currently part of the release process are the following:

 * liblogger - Simple logging library with formatted messages and configurable report level
 * libstrings - Simple string manipulation library
 * libconfig - Library for configuration use-cases. Provides API for CSV files, INI files and cmd argument parsing
 * libleveld - Library for loading/storing 2D game level data in a dedicated file format

## Building

You need cmake3 in order to configure the libraries for building. Libraries can be build for both mingw-g++ and VS2017.

## Script suite

There is currently script suite in development dedicated to automatic building of all served libraries. This suite currently consists of three scripts:

 * purge.bat - Deletes all `build` and `vsbuild` folders from served libraries
 * build-gnu.bat - Creates a `build` folder for all served libraries, configures it for mingw-g++ and builds and installs the library
 * build-vs.bat - Create a `vsbuild` folder for all server libraries, configures it for Visual Studio and builds it both release and debug mode. Install is also performed
 * prepare-release - Assumes that VS versions of libraries were build manually, creates a release folder with release file structure, copies changelog into it and also all needed headers and library files

## Testrunners

Each served library comes with a testrunner. To use it, you need to install header file from `Testrunner` folder. Currently, testrunners can only be succesfully build in release modes, Debug ones are not fixed yet (they are linking wrong libraries).