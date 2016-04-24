CC=gcc
CFLAGS= -O3 -fopenmp

all: prog_fast.out prog_2.out prog_4.out prog_5.out

debug: CFLAGS += -DDEBUG
debug: prog_fast.out prog_2.out prog_4.out prog_5.out

prog_fast.out: test_fast.c matrix_functions.c fast.c
	$(CC) -o prog_fast.out test_fast.c matrix_functions.c fast.c $(CFLAGS)

prog_2.out: Q2.c matrix_functions.c fast.c
	$(CC) -o prog_2.out Q2.c matrix_functions.c fast.c $(CFLAGS)

prog_4.out: Q4.c matrix_functions.c fast.c
	$(CC) -o prog_4.out Q4.c matrix_functions.c fast.c $(CFLAGS)

prog_5.out: Q5.c matrix_functions.c fast.c
	$(CC) -o prog_5.out Q5.c matrix_functions.c fast.c $(CFLAGS)
