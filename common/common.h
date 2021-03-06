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

/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * @param fp_out - a file to write the output in 
 * 
 * Prints out the sudoku in a 9 by 9 grid format
 */
void print_sudoku(FILE *fp_out, int sudoku[9][9]);

/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * @param fp_out - a file to write the output in 
 * 
 * Prints out a samurai sudoku in a 9 by 9 grid format
 */
void print_samurai(FILE *fp_out, int sudoku[5][9][9]);

/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * @param row - number of row of an entry
 * @param column - number of column of an entry
 * @param entry - number in range 1-9 to check
 * @param level - the level that the sudoku will be in 
 * 
 * Checks if the entry can be put into the given row and column without making it invalid
 * It would be invalid if the row or column or the 3 by 3 square box contains the entry
 * 
 * @return true if the entry is valid
 *         false otherwise
 */
bool check_entry(int sudoku[9][9], int row, int column, int entry, int level);

/******  check_box()  ******/
/* 
 * @param sudoku - an array of arrays (9*9 matrix)
 * @param row - number of row of an entry
 * @param column - number of column of an entry
 * @param entry - number in range 1-9 to check
 * @param level - the level that the sudoku will be in
 * 
 * Checks if the entry can be put into a given 3 by 3 square box 
 * 
 * @return true if the entry is valid
 *         false otherwise
 */
bool check_box(int sudoku[9][9], int diag, int row, int column, int entry, int level); 

/******  parse_sudoku()  ******/
/* 
 * @param file - File from which to read sudoku puzzle
 * @param sudoku - an array of arrays which are the rows
 * @param level - the level that the sudoku will be in 
 * 
 * Read a sudoku from a file and add the entries to sudoku matrix
 * 
 * @return false - on any argument or format errors
 *         true - otherwise
 */ 
bool parse_sudoku(FILE* fp, int sudoku[9][9], int level);

/******  parse_sudoku()  ******/
/* 
 * @param file - File from which to read sudoku puzzle
 * @param sudoku - a 3d array (first is the sudoku puzzle, second is the rows, third is the columns) 
 * 
 * Read a samurai sudoku from a file and add the entries to sudoku matrix
 * 
 * @return false - on any argument or format errors
 *         true - otherwise
 */ 
bool parse_samurai(FILE* fp, int sudoku[5][9][9]);

/******  lines_in_file()  ******/
/* @param fp - file
 * 
 * Reads the number of new line characters 
 *
 * @return - number of lines in file
 */
int lines_in_file(FILE *fp);

#endif
