# Makefile for sudoku.c
#
# Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# May 2020

SOLVE_DIR = ./solve/
CREATE_DIR = ./create/
COMMON_DIR = ./common/
TESTING_DIR = ./testing/

PROG = sudoku
OBJS = $(COMMON_DIR)common.o $(CREATE_DIR)create.o $(SOLVE_DIR)solve.o sudoku.o

PROG1 = $(TESTING_DIR)fuzzgenerator
OBJS1 = $(COMMON_DIR)common.o $(CREATE_DIR)create.o $(SOLVE_DIR)solve.o $(TESTING_DIR)fuzzgenerator.o

SCRIPT = $(TESTING_DIR)testing.sh
FLAGS =
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I $(COMMON_DIR) -I $(SOLVE_DIR) -I $(CREATE_DIR)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ -o $@

# Dependencies: object files depend on header files
common.o: $(COMMON_DIR)common.h 
solve.o: $(SOLVE_DIR)solve.h
create.o: $(CREATE_DIR)create.h 


.PHONY:  clean test all test

test: $(PROG)
	bash $(SCRIPT)

all:
	$(MAKE) $(PROG)
	$(MAKE) $(PROG1)

clean:
	rm -f core
	rm -f *~ *.o
	rm -f stocks
	rm -f $(PROG) $(PROG1)
	rm -f $(COMMON_DIR)common.o  $(SOLVE_DIR)solve.o $(CREATE_DIR)create.o 
	rm -f $(TESTING_DIR)/testdir/fuzz $(TESTING_DIR)/testdir/fuzz_solved 
