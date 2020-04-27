SHELL:=/bin/bash

CC= gcc
CFLAGS= -Wall -g -std=c11 -fopenmp -lm
SRC = main.c lfqueue.c
OBJ = $(SRC:.c=.o)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
