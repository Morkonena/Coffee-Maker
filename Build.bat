@echo off

cd Cappuccino
start Build.bat

set /p O="Continue (y/n): "
if "%O%"=="n" goto exit

cd ../Affogato
start Build.bat

cd ../Espresso
start Build.bat

cd ../Mocha
start Build.bat

set /p O="Continue (y/n): "
if "%O%"=="n" goto exit

cd ../Altra
start /wait Build.bat

:exit
cd ../