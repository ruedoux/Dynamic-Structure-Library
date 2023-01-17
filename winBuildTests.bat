@echo off
REM ----------------------------------------
REM BUILD BATCH FOR WINDOWS
REM ----------------------------------------

REM ----------------------------------------
REM BUILD
REM ----------------------------------------
if not exist "build" mkdir "build"

set FLAGS=-Wall -Wextra -g3 -O -Werror
set LINK=-lpsapi
set SRC=*.c src/*.c test/*c
set OUT_FILE=-o build/build.exe

@echo on
gcc %FLAGS% %SRC% %OUT_FILE% %LINK%
