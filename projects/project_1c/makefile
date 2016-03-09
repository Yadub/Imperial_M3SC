CC=gcc
CFLAGS=

all: prog_quad prog_1 prog_2 prog_3 prog_3b prog_3c prog_3d prog_3e prog_m

debug: CFLAGS += -DDEBUG -g
debug: prog_quad prog_1 prog_2 prog_3 prog_3b prog_3c prog_3d prog_3e prog_m

prog_1: prog_1.c lin_root.c quad_roots.c rcubic_roots.c
	$(CC) -o prog_1 prog_1.c lin_root.c quad_roots.c rcubic_roots.c $(CFLAGS)

prog_2: prog_2.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_2 prog_2.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3: prog_3.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3 prog_3.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3b: prog_3b.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3b prog_3b.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3c: prog_3c.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3c prog_3c.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3d: prog_3d.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3d prog_3d.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_3e: prog_3e.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c
	$(CC) -o prog_3e prog_3e.c lin_root.c quad_roots.c rcubic_roots.c rquartic_roots.c $(CFLAGS)

prog_m: prog_m.c quad_roots_complex.c rcubic_complex.c rquartic_complex.c
	$(CC) -o prog_m prog_m.c quad_roots_complex.c rcubic_complex.c rquartic_complex.c $(CFLAGS)

prog_quad: prog_quad.c lin_root.c quad_roots.c
	$(CC) -o prog_quad prog_quad.c lin_root.c quad_roots.c $(CFLAGS)
