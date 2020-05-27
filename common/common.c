/* 
 * common.c 
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: print a sudoku into stdout
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// prints the sudoku grid
void print_sudoku(int** Sudoku) {
    
    // for every row
    for (int i = 0; i < 9; i++) {
        // for every column
        for (int j = 0; j < 9; j++) {
            printf("%d ", Sudoku[i][j]);
        }
        printf("\n");
    }
}

// checks to see if you can add a specific entry and still have a valid grid
bool check_entry(int** Sudoku, int row, int column, int entry) {
    // NEEDS TO BE FILLED
    return true;
}

// Parse the sudoku from the command line
int ** parseSudoku(){
    int ** sudoku;
    return sudoku;
}