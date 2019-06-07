@echo off

cd Logger
rd /s /q build
rd /s /q vsbuild
cd ..

cd Strings
rd /s /q build
rd /s /q vsbuild
cd ..

cd Config
rd /s /q build
rd /s /q vsbuild
cd ..

cd LevelD
rd /s /q build
rd /s /q vsbuild
cd ..