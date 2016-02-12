CC=gcc
CFLAGS=-I.
DEPS= lin_root.h quad_roots.h order_by_size.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prog_1: prog_1.c order_by_size.c lin_root.c quad_roots.c
	$(CC) -o prog_1 prog_1.c order_by_size.c lin_root.c quad_roots.c -I.
