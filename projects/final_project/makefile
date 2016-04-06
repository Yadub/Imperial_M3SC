CC=gcc
CFLAGS= -O3

all: prog_testing prog_fast prog_2 prog_4 prog_5

debug: CFLAGS += -DDEBUG
debug: prog_testing prog_fast prog_2 prog_4 prog_5

prog_testing: testing_program.c matrix_functions.c
	$(CC) -o prog_testing.out testing_program.c matrix_functions.c $(CFLAGS)

prog_fast: test_fast.c matrix_functions.c fast.c
	$(CC) -o prog_fast.out test_fast.c matrix_functions.c fast.c $(CFLAGS)

prog_2: Q2.c matrix_functions.c fast.c
	$(CC) -o prog_2.out Q2.c matrix_functions.c fast.c $(CFLAGS)

prog_4: Q4.c matrix_functions.c fast.c
	$(CC) -o prog_4.out Q4.c matrix_functions.c fast.c $(CFLAGS)

prog_5: Q5.c matrix_functions.c fast.c
	$(CC) -o prog_5.out Q5.c matrix_functions.c fast.c $(CFLAGS)
