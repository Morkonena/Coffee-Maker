@echo off

cd Cappuccino
start Rebuild.bat

set /p O="Continue (y/n): "
if "%O%"=="n" goto exit

cd ../Affogato
start Rebuild.bat

cd ../Espresso
start Rebuild.bat

cd ../Mocha
start Rebuild.bat

set /p O="Continue (y/n): "
if "%O%"=="n" goto exit

cd ../Altra
start /wait Rebuild.bat

:exit
cd ../