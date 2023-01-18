# ----------------------------------------------------
# Makefile builds static library
# Compatible with both Linux and Windows os
# ----------------------------------------------------

.ONESHELL: # Every line in one shell

# ----------------------------------------------------
# VARIABLES
# ----------------------------------------------------

FLAGS=-Wall -Wextra -g3 -O -Werror -c
LINK=-lpsapi
SRC=../*.c ../src/*.c ../test/*c

# ----------------------------------------------------
# BUILD
# ----------------------------------------------------

all: main_build


# Build static library
main_build: pre_build
ifeq ($(OS), Windows_NT)
# Windows
	cd build 
	gcc $(FLAGS) $(SRC) $(LINK)
	ar rcs libout.a *.o
	del *.o
else
# Linux
	cd build
	gcc $(FLAGS) $(SRC)
	ar rcs libout.a *.o
	rm *.o
endif


# Check if build folders exist before building
pre_build:
ifeq ($(OS), Windows_NT)
# Windows
	if not exist "build" mkdir "build"
	if not exist "build\include" mkdir "build\include"
	xcopy /s src\\*h build\\include
else
# Linux
	if ! [ -d "build" ]; then mkdir build; fi
	if ! [ -d "build\include" ]; then mkdir build\include; fi
endif
