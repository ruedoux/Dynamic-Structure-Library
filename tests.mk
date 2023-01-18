# ----------------------------------------------------
# Makefile builds unit tests executable
# Compatible with both Linux and Windows os
# ----------------------------------------------------

.ONESHELL: # Every line in one shell

# ----------------------------------------------------
# VARIABLES
# ----------------------------------------------------

CC=gcc
FLAGS=-Wall -Wextra -g3 -O -Werror
LINK=-lpsapi
SRC=*.c src/*.c test/*c
OUT_FILE=-o build/build.exe

# ----------------------------------------------------
# BUILD
# ----------------------------------------------------

all: main_build

# Build test
main_build: pre_build
	$(CC) $(FLAGS) $(SRC) $(OUT_FILE) $(LINK)


# Check if build folders exist before building
pre_build:
ifeq ($(OS), Windows_NT)
# Windows
	if not exist "build" mkdir "build"
else
# Linux
	if ! [ -d "build" ]; then mkdir build; fi
endif
