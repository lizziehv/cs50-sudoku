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
static bool solve_recursively(int sudoku[9][9], int row, int column, int level);
static int solutions_recurse(int sudoku[9][9], int row, int column, int num_solutions, int level);


/**************** Global functions ****************/

/**************  solve()  **************/
/******  See solve.h for details  ******/
bool solve(int sudoku[9][9], int level) {    
    return solve_recursively(sudoku, 0, 0, level);
}

/********  sudoku_solutions()  *********/
/******  See solve.h for details  ******/
int sudoku_solutions(int sudoku[9][9], int level){
    return solutions_recurse(sudoku, 0, 0, 0, level);
}

/**************** Local functions ****************/

/* 
 * @param sudoku - a sudoku matrix to complete entries onto
 * @param row - row to start solving from (0 for the entire matrix)
 * @param column - column to start solving from (0 for the entire matrix)
 * 
 * Solve a sudoku and modify entries
 * 
 * @return - true if sudoku has been correctly solved
 * @return - false if no solution found
 */
static bool solve_recursively(int sudoku[9][9], int row, int column, int level){
    // check if all entries have been visited
    if (row == 9 && column == 0) {
        return true;
    }
    // Visit squares that have not yet been visited, from left to right
    for (int i=row; i<9; i++) {
        int j = (i == row) ? column : 0;
        
        for ( ; j<9; j++) {
            // check if entry is empty
            if (sudoku[i][j] == 0) {
                
                // Try every valid number for this entry
                int array[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
                int count = 0; 

                while (count < 9) {
                    int rand_num = (rand() % 9) + 1; 
                    if (array[rand_num - 1] != 0 ) {
                        if (check_entry(sudoku, i, j, rand_num, level)) {
                            sudoku[i][j] = rand_num;

                            // recurse with new sudoku -> move to next entry
                            bool ret;
                            if (j == 8) {
                                ret = solve_recursively(sudoku, i+1, 0, level);
                            }
                            else {
                                ret = solve_recursively(sudoku, i, j+1, level);
                            }

                            if (ret) {              // found a solution that works
                                return true;
                            }
                            else {                  // solution didn't work
                                sudoku[i][j]=0;
                            }
                        }
                        array[rand_num - 1] = 0; 
                        count ++; 
                    }
                }
                // Some entry did not work, so this is unsolvable
                return false;
            }
        }
    }
    return true;
}

/* 
 * @param sudoku - a sudoku matrix to find number of solutions for (does not modify them)
 * @param row - row to start recursing from (0 for the entire matrix)
 * @param column - column to start recursing from (0 for the entire matrix)
 * 
 * Find the number of solutions a sudoku has without completing the sudoku
 * 
 * @return - number of solutions
 */
static int solutions_recurse(int sudoku[9][9], int row, int column, int num_solutions, int level){
    // check if all entries have been visited
    if (row == 9 && column == 0) {
        return num_solutions+1;
    }
    // Visit squares that have not yet been visited, from left to right
    for (int i=row; i<9; i++) {
        int j = (i == row) ? column : 0;

        for ( ; j<9; j++) {
            // check if entry is empty in original
            if (sudoku[i][j] == 0) {

                // Try every valid number for this entry
                for (int entry=1; entry<=9; entry++) {
                    if (check_entry(sudoku, i, j, entry, level)) {
                        sudoku[i][j] = entry;

                        // recurse with new sudoku -> move to next entry
                        if (j == 8) {
                            num_solutions = solutions_recurse(sudoku, i+1, 0, num_solutions, level);
                        }
                        else {
                            num_solutions = solutions_recurse(sudoku, i, j+1, num_solutions, level);
                        }

                        sudoku[i][j]=0;
                    }
                }
                // Some entry did not work, so this is unsolvable
                return num_solutions;
            }
        }
    }
    return num_solutions + 1;
}

/**************** Extra credit functions ****************/
bool solve_samurai(int samurai[5][9][9]){
    for(int puzzle = 0; puzzle < 5; puzzle++){
        if(!solve(samurai[puzzle], 1)){
            
            return false;
        }
    }
    return true;
}
