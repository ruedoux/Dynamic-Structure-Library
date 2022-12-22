@echo off
REM ----------------------------------------
REM BUILD BATCH FOR WINDOWS
REM ----------------------------------------

REM ----------------------------------------
REM BUILD
REM ----------------------------------------
if not exist "build" mkdir "build"

@echo on
gcc -Wall -Wextra -g3 -O -Werror *.c src/*.c -o build/build.exe
