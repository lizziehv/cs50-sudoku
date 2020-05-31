# Makefile for sudoku.c
#
# Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# May 2020

SOLVE_DIR = ../solve/
CREATE_DIR = ../create/
COMMON_DIR = ../common/

PROG = game
OBJS = $(COMMON_DIR)common.o $(CREATE_DIR)create.o $(SOLVE_DIR)solve.o button.o game.o

FLAGS = -lSDL2 -lSDL2_ttf
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@


# Dependencies: object files depend on header files
common.o: $(COMMON_DIR)common.h 
solve.o: $(SOLVE_DIR)solve.h
create.o: $(CREATE_DIR)create.h 
button.o: button.h


.PHONY:  clean test all test

all:
	$(MAKE) $(PROG)

clean:
	rm -f $(PROG)
	rm -f core
	rm -f *~ *.o
	rm -f stocks
	rm -rf *.dSYM
