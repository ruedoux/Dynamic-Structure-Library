@echo off
REM ----------------------------------------
REM BUILD BATCH FOR WINDOWS
REM ----------------------------------------

REM ----------------------------------------
REM BUILD
REM ----------------------------------------
if not exist "build" mkdir "build"

set FLAGS=-Wall -Wextra -g3 -O -Werror -c
set LINK=-lpsapi
set SRC=../*.c ../src/*.c ../test/*c


cd build
@echo on
gcc %FLAGS% %SRC% %LINK%
ar rcs libout.a *.o
@echo off
del *.o
cd ..

REM ----------------------------------------
REM COPY HEADERS TO INCLUDE
REM ----------------------------------------
if not exist "build\include" mkdir "build\include"

@echo on
xcopy /s src\*h build\include
@echo off
