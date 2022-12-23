if ! [ -d "build" ]; then
	mkdir build
fi

FLAGS="-Wall -Wextra -g3 -O -Werror"
LINK=""
SRC="*.c src/*.c test/*c"
OUT_FILE="-o build/build.out"

gcc $FLAGS $SRC $OUT_FILE $LINK
./build/build.out

