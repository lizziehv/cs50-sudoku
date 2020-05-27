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
void print_sudoku(int Sudoku[9][9]) {
    
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
bool check_entry(int sudoku[9][9], int row, int column, int entry) {
    for (int r = 0; r <9; r++){
        // Loop through the rows and check the column
        if (sudoku[r][column]==entry && r!=row){
            return false;
        } 
    }

    for (int c = 0; c<9; c++){
        // Loop through the columns in the given row
        if (sudoku[row][c]==entry && c!=column){
            return false;
        }
    }

    // Check in square box
    int rbox = row/3;
    int cbox = column/3;
    for (int i = rbox*3; i < (rbox*3)+3; i++){
        for (int j = cbox*3; j < (cbox*3)+3; j++){
            if (sudoku[i][j]==entry && i!=row && j!= column){
                return false;
            }
        }
    }
    return true;
}

// Parse the sudoku from the command line
int ** parseSudoku(){
    int ** sudoku;
    return sudoku;
// reads a sudoku from a file (could be stdout)
}
bool parse_sudoku(char* filename, int sudoku[9][9]){
    // NEEDS TO BE FILLED
    return false; 
}