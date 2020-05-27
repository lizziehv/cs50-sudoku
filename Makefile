# Makefile for crawler.c
#
# Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# May 2020

PROG=sudoku
OBJS=sudoku.o

FLAGS =
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies: object files depend on header files
sudoku.o: ./common/common.c ./solve/solve.c ./create/create.c

.PHONY:  clean test all

all:
	$(MAKE) $(PROG)

clean:
	rm -f core
	rm -f *~ *.o
	rm -f stocks
	rm -f $(PROG)
