@echo off
REM ----------------------------------------
REM BUILD BATCH FOR WINDOWS
REM ----------------------------------------

REM ----------------------------------------
REM BUILD
REM ----------------------------------------
if not exist "build" mkdir "build"

@echo on
gcc -Wall *.c src/*.c -o build/build.exe
