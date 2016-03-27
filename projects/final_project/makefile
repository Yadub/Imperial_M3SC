CC=gcc
CFLAGS= -O3 -fopenmp

all: prog_test_factors

debug: CFLAGS += -DDEBUG
debug: prog_1a prog_1b prog_2a prog_2b prog_poisson1d prog_poisson2d prog_poisson3d

prog_test_factors: test_factors.c sfactors.c matrix_functions.c
	$(CC) -o prog_test_factors test_factors.c sfactors.c matrix_functions.c $(CFLAGS)
