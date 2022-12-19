if ! [ -d "build" ]; then
	mkdir build
fi

gcc -Wall -Wextra -g3 *.c src/*.c -o build/build.out
./build/build.out

