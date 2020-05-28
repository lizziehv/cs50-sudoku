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

/******  sudoku_build()  ******/
/* 
 * @param sudoku - an array of arrays(rows), where empty entries
 *                 are set to 0
 * 
 * Given an empty sudoku, builds a sudoku using random numbers
 * (unique numbers in every row, column, and box)
 * 
 * @return - true if sudoku has been correctly create
 * @return - false if there was an error encountered
 */
bool sudoku_build(int sudoku[9][9]);


/******  create_puzzle()  ******/
/* 
 * @param sudoku - an array of arrays(rows), where empty entries
 *                 are set to 0
 * 
 * Given a full sudoku, makes a puzzle by removing 40 numbers
 * It deletes random numbers and makes sure that the sudoku has a unique solution
 * 
 * @return - nothing
 * */
void create_puzzle(int sudoku[9][9]);

#endif