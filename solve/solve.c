/* 
 * solve.c 
 * see solve.h for details
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Write code to solve a given sudoku puzzle
 */

#include <stdbool.h>
#include "solve.h"
#include "../common/common.h"

/**************** Local functions ****************/
/************ (Not visible outside) **************/
bool solve_recursively(int sudoku[9][9], int row, int column);

// solve, which calls a recursive function
bool solve(int sudoku[9][9], int solution[9][9]) {

    // Copy grid into a solution matrix
    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            solution[i][j] = sudoku[i][j];
        }
    }
    
    return solve_recursively(solution, 0, 0);
}

/**************** Global functions ****************/

/* 
 * recursive function to solve part of a sudoku 
 */
bool solve_recursively(int sudoku[9][9], int row, int column){
    // check if all entries have been visited
    if (row == 9 && column == 0) {
        return true;
    }
    // Visit squares that have not yet been visited, from left to right
    for (int i=row; i<9; i++) {
        int j;
        if (i == row) {
            j = column;
        }
        else {
            j = 0;
        }
        for ( ; j<9; j++) {

            // check if entry is empty
            if (sudoku[i][j] == 0) {

                // Try every valid number for this entry
                for (int entry=1; entry<=9; entry++) {
                    if (check_entry(sudoku, i, j, entry)) {
                        sudoku[i][j] = entry;

                        // recurse with new sudoku -> move to next entry
                        bool ret;
                        if (j == 8) {
                            ret = solve_recursively(sudoku, i+1, 0);
                        }
                        else {
                            ret = solve_recursively(sudoku, i, j+1);
                        }

                        if (ret) {              // found a solution that works
                            return true;
                        }
                        else {                  // solution didn't work
                            sudoku[i][j]=0;
                        }
                    }
                }
                // Some entry did not work, so this is unsolvable
                return false;
            }
        }
    }
    return true;
}