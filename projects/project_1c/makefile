CC=gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: prog_1

prog_1: prog_1.c lin_root.c quad_roots.c rcubic_roots.c
	$(CC) -o prog_1 prog_1.c lin_root.c quad_roots.c rcubic_roots.c
