SHELL:=/bin/bash

CC= gcc
CFLAGS= -Wall -g -std=c11 -fopenmp -lm
SRC = ./src
BIN = ./bin
OBJS = l_list_test lf_list_test l_queue_test lf_queue_test

./bin/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

l_list_test: $(BIN)/l_list_test.o $(BIN)/l_list.o
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS)

lf_list_test: $(BIN)/lf_list_test.o $(BIN)/lf_list.o
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS)

l_queue_test: $(BIN)/l_queue_test.o $(BIN)/l_queue.o
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS)

lf_queue_test: $(BIN)/lf_queue_test.o $(BIN)/lf_queue.o
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS)

all: $(OBJS) clean

clean:
	rm -f $(BIN)/*.o *~
