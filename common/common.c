/* 
 * common.c 
 * see common.c for details
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Write common functions used for both solver and creator of Sudoku puzzle
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"

/****************** Local functions ******************/
bool check_valid(int sudoku[9][9]);

/****************** Global functions ******************/

/***********  print_sudoku()  ***********/
/******  See common.h for details  ******/
void print_sudoku(FILE *fp_out, int sudoku[9][9]) {  
    // for every row
    for (int i = 0; i < 9; i++) {
        // for every column
        for (int j = 0; j < 8; j++) {
            fprintf(fp_out, "%d ", sudoku[i][j]);
        }
        fprintf(fp_out, "%d", sudoku[i][8]);
        fprintf(fp_out, "\n");
    }
}

/***********  check_entry()  ************/
/******  See common.h for details  ******/
bool check_entry(int sudoku[9][9], int row, int column, int entry) {
    // Loop through the rows to check column
    for (int r = 0; r < 9; r++) {
        if (sudoku[r][column] == entry && r != row) {
            return false;
        } 
    }

    // Loop through the columns to check row 
    for (int c = 0; c < 9; c++){
        if (sudoku[row][c] == entry && c != column) {
            return false;
        }
    }

    // Check box
    int rbox = row/3;
    int cbox = column/3;
    for (int i = rbox*3; i < (rbox*3)+3; i++) {
        for (int j = cbox*3; j < (cbox*3)+3; j++) {
            if (sudoku[i][j] == entry && i != row && j != column) {
                return false;
            }
        }
    }
    return true;
}

/***********  check_box()  ************/
/******  See common.h for details  ******/
bool check_box(int sudoku[9][9], int diag, int row, int column, int entry) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j<3; j++) {
            // if the entry is already in the 3x3 box 
            if (sudoku[diag+i][diag+j] == entry) {
                return false;
            }
        } 
    }
    // if it was not in the box
    return true; 
}

/***********  parse_sudoku()  ***********/
/******  See common.h for details  ******/
bool parse_sudoku(FILE* file, int sudoku[9][9]) {
    // Some checks
    if (file == NULL) {
        return false;
    }
    if (sudoku == NULL) {
        return false;
    }

    // loop through entries
    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            int entry;

            int ret = fscanf(file, "%d", &entry);
            if(ret == 0){
                return false;
            }

            if(entry <= 9 && entry >= 0){
                sudoku[i][j] = entry;
            }
            else{
                return false;
            }
        }
        
        // Check valid format (9x9 matrix)
        char c;
        fscanf(file, "%c", &c);
        if (c != '\n' && i != 8) {
            return false;
        }
    }

    if (!check_valid(sudoku)) {
        return false;
    }

    return true; 
}

/****************** Local functions ******************/

/* 
 * @param sudoku - an array of arrays which are the rows
 * 
 * Check if parsing produces a valid sudoku puzzle
 * 
 * @return true if sudoku is valid (can have 0 entries)
 *         false otherwise
 */
bool check_valid(int sudoku[9][9]){
    if (sudoku == NULL)
        return false;

    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            int entry = sudoku[i][j];
            if (entry != 0 && !check_entry(sudoku, i, j, entry)) {
                return false;
            }
        }
    }
    return true;
}
