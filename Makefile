ascii3D: src/*.c
	clang $(shell find src -type f -name '*.c') -l ncurses -I src -o ascii3D -g -O0