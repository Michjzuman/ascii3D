# ASCII3D

src = $(shell find src -name '*.c')
flags = -I src -l ncurses

ascii3D: $(src)
	clang $(src) $(flags) -o ascii3D -g -O0
