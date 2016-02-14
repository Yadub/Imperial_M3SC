CC=gcc
CFLAGS=-I.
DEPS= lin_root.h quad_roots.h rcubic_roots.h order_nums.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

prog_4: prog_4.c order_nums.c lin_root.c quad_roots.c rcubic_roots.c
	$(CC) -o prog_4 prog_4.c order_nums.c lin_root.c quad_roots.c rcubic_roots.c -I.

prog_2: prog_2.c order_nums.c lin_root.c quad_roots.c rcubic_roots.c
	$(CC) -o prog_2 prog_2.c order_nums.c lin_root.c quad_roots.c rcubic_roots.c -I.

prog_1: prog_1.c order_nums.c lin_root.c quad_roots.c
	$(CC) -o prog_1 prog_1.c order_nums.c lin_root.c quad_roots.c -I.
