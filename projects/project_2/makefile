CC=gcc
CFLAGS=-fopenmp -O3

debug: CFLAGS += -DDEBUG -DCOUNT
debug: prog_1a prog_1b prog_2a prog_2b prog_poisson1d

all: prog_1a prog_1b prog_2a prog_2b prog_poisson1d

prog_1a: prog_1a.c gauss.c matrix_functions.c
	$(CC) -o prog_1a prog_1a.c gauss.c matrix_functions.c $(CFLAGS)

prog_1b: prog_1b.c gauss.c matrix_functions.c
	$(CC) -o prog_1b prog_1b.c gauss.c matrix_functions.c $(CFLAGS)

prog_2a: prog_2a.c bgauss.c matrix_functions.c
	$(CC) -o prog_2a prog_2a.c bgauss.c matrix_functions.c $(CFLAGS)

prog_2b: prog_2b.c bgauss.c matrix_functions.c
	$(CC) -o prog_2b prog_2b.c bgauss.c matrix_functions.c $(CFLAGS)

prog_poisson1d: poisson1d.c gauss.c bgauss.c matrix_functions.c
	$(CC) -o prog_poisson1d poisson1d.c gauss.c bgauss.c matrix_functions.c $(CFLAGS)
