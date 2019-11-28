# dsh

## Purpose

This repository contains a bunch of simple and useful C++ libraries usable in everyday development.

## Building

To build and package contents of this repository on the UNIX machine, do the following:

```sh
mkdir build
cd build
cmake ..
make -j4
cpack
```

To build the project on Windows machine with MinGW, one has to configure cmake with MinGW generator: `cmake -G "MinGW Makefiles" ..`. You can also build the project for Visual Studio. Please refer to `prepare-release.sh` for more details on the subject.

## Installation

If you obtained the release package (provided only for Windows machines), you have two options when installing dsh project.

### Locally for each project

This approach is recommended if you only develop in Visual Studio. Simply configure your CMakeLists.txt to automatically fetch fixed release of `dsh`, unzip it and link against its `libs` and include `folders`.

### Globally for whole machine

If you prefer UNIX way of installing and sharing libraries and you develop your apps in g++, you can install dsh as an enviroment. After unzipping release package to any folder, navigate to its `install` folder and run `bootstrap.bat`.

Before you'll do it, you probably wonder: "What it'll do?". Well, here's the list:

 * Creates UNIX-like folder structure under `C:\tools`
 * Downloads and installs
    * Cmake 3
    * MinGW with G++ 6.x
    * Doxygen
    * Putty, pscp
    * Install Python 3.7.3
 * Installs `doomsh.cmd` and `dsh.bat`

Everything will be installed under `C:\tools` and will not interfere with your normal environment. Nothing will be added in `PATH`. In fact, updating `PATH` is a last part of installation: Do add `C:\tools` to your `PATH`. This will unlock the command `dsh` which will start a dedicated command line, which can interact with tools installed in previous step. Plus, it has a few handy aliases and thus the following commands will work:
 * `make`
 * `ssh`
 * `scp`
 * `ll`
 * `gmake`

The last command: `gmake` is an alias to `cmake -G "MinGW Makefiles`` and is important if you have Visual Studio installed on your machine. In that case, calling `cmake` will generate solution for Visual Studio. If you need Makefile for G++, you can call `gmake` and everything will work.

#### Sharing libraries

As mentioned above, installing dsh globally on your system will give you advantage of sharing libraries. If you set your cmake in such way that library install folder is `/tools/lib` and header install folder is `/tools/include`, it will then be able to find installed libraries from dsh and link against them.
