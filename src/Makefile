CC=gcc
CFLAGS=-lm

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,../bin/%,$(SRCS))

all: $(PROGS)

../bin/%: %.c
		$(CC) $< $(CFLAGS) -o $@ 
clean: 
		rm -f $(PROGS)
