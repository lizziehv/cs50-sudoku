/* 
 * common.h
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Header file for common
 */

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/******  print_sudoku()  ******/
/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * 
 * Prints out the sudoku in a 9 by 9 grid format
 */
void print_sudoku(int sudoku[9][9]);

/******  check_entry()  ******/
/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * @param row - number of row of an entry
 * @param column - number of column of an entry
 * @param entry - number in range 1-9 to check
 * 
 * Checks if the entry can be put into the given row and column without making it invalid
 * It would be invalid if the row or column or the 3 by 3 square box contains the entry
 * 
 * @return true if the entry is valid
 *         false otherwise
 */
bool check_entry(int sudoku[9][9], int row, int column, int entry);

/******  check_box()  ******/
/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * @param row - number of row of an entry
 * @param column - number of column of an entry
 * @param entry - number in range 1-9 to check
 * 
 * Checks if the entry can be put into a given 3 by 3 square box 
 * 
 * @return true if the entry is valid
 *         false otherwise
 */
bool check_box(int sudoku[9][9], int diag, int row, int column, int entry); 

/******  parse_sudoku()  ******/
/* 
 * @param file - File from which to read sudoku puzzle
 * @param sudoku - an array of arrays which are the rows
 * 
 * Read a sudoku from a file and add the entries to sudoku matrix
 * 
 * @return false - on any argument or format errors
 *         true - otherwise
 */ 
bool parse_sudoku(FILE* fp, int sudoku[9][9]);

#endif
