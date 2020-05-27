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

/******  check_unique_solution()  ******/
/* 
* Checks if the given sudoku has a unique solution
* RETURN: true if sudoku has unique solution
*         false otherwise
*/
bool check_unique_solution(int sudoku[9][9]);


/******  sudoku_build()  ******/
/* 
* Build a sudoku ny using random numbers
*/
void sudoku_build(int sudoku[9][9]);


/******  create_puzzle()  ******/
/* 
* Takes the sudoku and makes a puzzle by removing 40 numbers
* It deletes random numbers and makes sure that the sudoku has a unique solution
*/
void create_puzzle(int sudoku[9][9]);

#endif