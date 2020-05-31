/* 
 * create.h
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Header file for create
 */

#ifndef CREATE
#define CREATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 
 * @param sudoku - an array of arrays(rows), where empty entries
 *                 are set to 0
 * @param level - the level that the sudoku will be in
 * 
 * Given an empty sudoku, builds a sudoku using random numbers
 * (unique numbers in every row, column, and box)
 * 
 * @return - true if sudoku has been correctly create
 * @return - false if there was an error encountered
 */
bool sudoku_build(int sudoku[9][9], int level);


/* @param sudoku - populated grid 
 * @param num_removed - number of entries to remove from grid
 * @param level - the level that the sudoku will be in
 * 
 * Takes a completed sudoku and makes a puzzle by removing num_removed numbers
 * It deletes random numbers and makes sure that the sudoku has a unique solution
 * 
 * @return - nothing
 */
void create_puzzle(int sudoku[9][9], int num_removed, int level);

#endif
