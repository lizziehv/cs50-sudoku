# Makefile for sudoku.c
#
# Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# May 2020

SOLVE_DIR = ./solve/
CREATE_DIR = ./create/
COMMON_DIR = ./common/

PROG=sudoku
OBJS= common.o create.o solve.o sudoku.o

FLAGS =
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I $(COMMON_DIR) -I $(SOLVE_DIR) -I $(CREATE_DIR)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies: object files depend on header files
common.o: common.h 
solve.o: solve.h
create.o: create.h 


.PHONY:  clean test all

all:
	$(MAKE) $(PROG)

clean:
	rm -f core
	rm -f *~ *.o
	rm -f stocks
	rm -f $(PROG)
