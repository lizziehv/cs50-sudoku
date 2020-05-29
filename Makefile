# Makefile for sudoku.c
#
# Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# May 2020

SOLVE_DIR = ./solve/
CREATE_DIR = ./create/
COMMON_DIR = ./common/

PROG = sudoku
OBJS = $(COMMON_DIR)common.o $(CREATE_DIR)create.o $(SOLVE_DIR)solve.o sudoku.o

SCRIPT = testing.sh
FLAGS =
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I $(COMMON_DIR) -I $(SOLVE_DIR) -I $(CREATE_DIR)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies: object files depend on header files
common.o: $(COMMON_DIR)common.h 
solve.o: $(SOLVE_DIR)solve.h
create.o: $(CREATE_DIR)create.h 


.PHONY:  clean test all test

test: $(PROG)
	bash -v $(SCRIPT)

all:
	$(MAKE) $(PROG)

clean:
	rm -f core
	rm -f *~ *.o
	rm -f stocks
	rm -f $(PROG)
	rm -f $(COMMON_DIR)common.o  $(SOLVE_DIR)solve.o $(CREATE_DIR)create.o
