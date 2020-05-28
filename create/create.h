/* 
 * create.h
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Header file for create
 */

#ifndef CREATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* @param sudoku - initially empty sudoku to fill with random numbers

 * Build a sudoku by using random numbers
 * 
 * @return true - if sudoku was successfuly built
 *         false - otherwise (error handling) 
 */
bool sudoku_build(int sudoku[9][9]);


/* @param sudoku - populated grid 
 * @param num_removed - number of entries to remove from grid
 * 
 * Takes a completed sudoku and makes a puzzle by removing 40 numbers
 * It deletes random numbers and makes sure that the sudoku has a unique solution
 * 
 */
void create_puzzle(int sudoku[9][9], int num_removed);

#endif