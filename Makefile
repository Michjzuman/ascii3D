# ASCII3D

all = $(shell find src -name '*.*')
src = $(shell find src -name '*.c')
flags = -I src -l ncurses

ascii3D: $(all)
	clang $(src) $(flags) -o ascii3D -g -O0
