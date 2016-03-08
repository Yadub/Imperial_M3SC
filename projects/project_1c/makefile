CC=gcc
CFLAGS=

all: prog_quad prog_1 prog_2 prog_3 prog_3b

debug: CFLAGS += -DDEBUG -g
debug: prog_quad prog_1 prog_2 prog_3 prog_3b

prog_1: prog_1.c lin_root.c quad_roots.c rcubic_roots.c
	$(CC) -o prog_1 prog_1.c lin_root.c quad_roots.c rcubic_roots.c $(CFLAGS)

prog_2: prog_2.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_2 prog_2.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3: prog_3.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3 prog_3.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3b: prog_3b.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3b prog_3b.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_quad: prog_quad.c lin_root.c quad_roots.c
	$(CC) -o prog_quad prog_quad.c lin_root.c quad_roots.c $(CFLAGS)
