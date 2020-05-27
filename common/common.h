/* 
 * common.h
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Header file for common
 */

#ifndef __COMMON
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/******  print_sudoku()  ******/
/* 
* Prints out the sudoku in a 9 by 9 grid format
*/
void print_sudoku(int Sudoku[9][9]);


/******  check_entry()  ******/
/* 
* Takes the sudoku and a row and column and an entry
* Checks if the entry can be put into the given row and column without making it invalid
* It would be invalid if the row or column or the 3 by 3 square box contains the entry
* 
* RETURN: true if the entry is valid
*         false otherwise
*/
bool check_entry(int sudoku[9][9], int row, int column, int entry);


/******  parse_sudoku()  ******/
/* 
* Reads the sudoku from the file using the ginven file pointer
* Stores it into the given integer array of arrays
* 
* RETURN: true if successfully read
*         false if sudoku cna not be read properly 
*/
bool parse_sudoku(FILE* fp, int sudoku[9][9]);

#endif