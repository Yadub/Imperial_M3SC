CC=gcc
CFLAGS=

debug: CFLAGS += -DDEBUG -g
debug: prog_1a prog_1b

all: prog_1a prog_1b

prog_1a: prog_1a.c gauss.c
	$(CC) -o prog_1a prog_1a.c gauss.c $(CFLAGS)

prog_1b: prog_1b.c gauss.c
	$(CC) -o prog_1b prog_1b.c gauss.c $(CFLAGS)
