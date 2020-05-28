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

/*** solve, which calls a recursive function ***/
bool solve(int sudoku[9][9]) {
    return solve_recursively(sudoku, 0, 0);
}

/*** recursive function to solve part of a sudoku ***/
bool solve_recursively(int sudoku[9][9], int row, int column){
    /* check if all entries have been visited */
    if(row == 9 && column == 0){
        return true;
    }
    /* Visit squares that have not yet been visited */
    for(int i=row; i<9; i++){
        for(int j=column; j<9; j++){

            /* check if entry is empty */
            if(sudoku[i][j] == 0){

                /* Try every valid number for this entry */
                for(int entry=1; entry<=9; entry++){
                    if(check_entry(sudoku, i, j, entry)){
                        sudoku[i][j] = entry;

                         /* recurse with new sudoku -> move to next entry */
                        bool ret;
                        if(j == 8)
                            ret = solve_recursively(sudoku, i+1, 0);
                        else
                            ret = solve_recursively(sudoku, i, j+1);

                        if(ret)             // found a solution that works
                            return true;
                        else                // solution didn't work
                            sudoku[i][j]=0;
                    }
                }
                /* Some entry did not work, so this is unsolvable */
                return false;
            }
        }
    }
    return true;
}