CC=gcc
CFLAGS=-I.
DEPS= lin_root.h quad_roots.h rcubic_roots.h order_nums.h print_statements.h quad_roots_complex.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: prog_1 prog_2 prog_3 prog_4 prog_5 prog_mastery prog_m

prog_1: prog_1.c order_nums.c lin_root.c quad_roots.c print_statements.c
	$(CC) -o prog_1 prog_1.c order_nums.c lin_root.c quad_roots.c print_statements.c -I.

prog_2: prog_2.c order_nums.c lin_root.c quad_roots.c rcubic_roots.c print_statements.c
	$(CC) -o prog_2 prog_2.c order_nums.c lin_root.c quad_roots.c rcubic_roots.c print_statements.c -I.

prog_3: prog_3.c order_nums.c lin_root.c quad_roots.c rcubic_roots_optimized.c print_statements.c
	$(CC) -o prog_3 prog_3.c order_nums.c lin_root.c quad_roots.c rcubic_roots_optimized.c print_statements.c -I.

prog_4: prog_4.c order_nums.c lin_root.c quad_roots.c rcubic_roots_optimized.c print_statements.c
	$(CC) -o prog_4 prog_4.c order_nums.c lin_root.c quad_roots.c rcubic_roots_optimized.c print_statements.c -I.

prog_5: prog_5.c
	$(CC) -o prog_5 prog_5.c

prog_mastery: prog_mastery.c quad_roots_complex.c rcubic_complex.c print_statements.c
	$(CC) -o prog_mastery prog_mastery.c quad_roots_complex.c rcubic_complex.c print_statements.c -I.

prog_m: prog_m.c quad_roots_complex.c rcubic_complex.c
	$(CC) -o prog_m prog_m.c quad_roots_complex.c rcubic_complex.c -I.
