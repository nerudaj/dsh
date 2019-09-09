@echo off

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