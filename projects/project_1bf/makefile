CC=gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: prog_1 prog_2 prog_3 prog_4 prog_5 prog_m prog_mastery

prog_1: prog_1.c lin_root.c quad_roots.c
	$(CC) -o prog_1 prog_1.c lin_root.c quad_roots.c

prog_2: prog_2.c lin_root.c quad_roots.c rcubic_roots.c
	$(CC) -o prog_2 prog_2.c lin_root.c quad_roots.c rcubic_roots.c

prog_3: prog_3.c lin_root.c quad_roots.c rcubic_roots_optimized.c
	$(CC) -o prog_3 prog_3.c lin_root.c quad_roots.c rcubic_roots_optimized.c

prog_4: prog_4.c lin_root.c quad_roots.c rcubic_roots_optimized.c
	$(CC) -o prog_4 prog_4.c lin_root.c quad_roots.c rcubic_roots_optimized.c

prog_5: prog_5.c
	$(CC) -o prog_5 prog_5.c

prog_m: prog_m.c quad_roots_complex.c rcubic_complex.c
	$(CC) -o prog_m prog_m.c quad_roots_complex.c rcubic_complex.c

prog_mastery: prog_mastery.c quad_roots_complex.c rcubic_complex.c
	$(CC) -o prog_mastery prog_mastery.c quad_roots_complex.c rcubic_complex.c
