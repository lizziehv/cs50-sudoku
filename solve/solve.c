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

// for efficient solver
static bool efficient_solver_helper(int sudoku[9][9], int constraints[9][9][9], int row, int column, int level);
void find_smallest_location (int possibilities[9][9][9], int *min_row, int *min_col);
bool no_possibilities(int possibilities[9][9][9]); 
static void edit_posibilities(int sudoku[9][9], int possibilities[9][9][9], int entry, int row, int column); 
static void add_possibilities(int possibilities[9][9][9], int entry, int row, int column); 

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

bool efficient_solver(int sudoku[9][9], int level){
    int possibilities[9][9][9];
    
    
    for(int row = 0; row < 9; row++){
        for(int column = 0; column < 9; column++){
            for(int number = 0; number < 9; number++) {
                if (sudoku[row][column] == 0) {
                    if (check_entry(sudoku, row, column, number + 1, level)) {
                        possibilities[row][column][number] = 1;
                    }
                    else {
                        possibilities[row][column][number] = 0;
                    }
                }
                else {
                    possibilities[row][column][number] = 0;
                }
            }
        }
    }

    return efficient_solver_helper(sudoku, possibilities, 0, 0, level);
} 

static bool efficient_solver_helper(int sudoku[9][9], int possibilities[9][9][9], int min_row, int min_col, int level){
    // check if all entries have been visited
    if (no_possibilities(possibilities)) {
        return true;
    }
    
    find_smallest_location(possibilities, &min_row, &min_col);

    for (int num = 0; num < 9; num++) {
        if (possibilities[min_row][min_col][num] == 1) {
            sudoku[min_row][min_col] = num + 1;
            edit_posibilities(sudoku, possibilities, num, min_row, min_col);
            
            bool ret;
            if (min_col == 8) 
                ret = efficient_solver_helper(sudoku, possibilities, min_row+1, 0, level);
            else
                ret = efficient_solver_helper(sudoku, possibilities, min_row, min_col+1, level);
            
            if(ret){        // found a solution that works
                return true;
            }
            else{           // number did not work
                sudoku[min_row][min_col] = 0;
                add_possibilities(possibilities, num, min_row, min_col);
            }
        }
    }
    // no number worked
    return false;
  
} 


void find_smallest_location (int possibilities[9][9][9], int *min_row, int *min_col) {
    int min = 0;  
    int current = 0; 
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == *min_row && j == *min_col) {
                break;
            }
            else {
                for (int num = 0; num < 9; num++) {
                    if (possibilities[i][j][num] == 1) {
                        current ++; 
                    }
                }
                if (current <= min) {
                    min = current; 
                    *min_row = i; 
                    *min_col = j; 
                }
                current = 0; 
            }
        }
    }  
}

bool no_possibilities(int possibilities[9][9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int num = 0; num < 9; num++) {
                if (possibilities[i][j][num] == 1) {
                    return false; 
                }
            }
        }
    }  
    return true; 
}


static void edit_posibilities(int sudoku[9][9], int possibilities[9][9][9], int entry, int row, int column){
    // remove constraints from row
    for(int j = 0; j < 9; j++){
        possibilities[row][j][entry-1] = 0;
    }

    // remove constraint from column
    for(int i = 0; i < 9; i++){
        possibilities[i][column][entry-1] = 0;
    }

    // remove constraints from box
    int rbox = row/3;
    int cbox = column/3;
    for (int i = rbox*3; i < (rbox*3)+3; i++) {
        for (int j = cbox*3; j < (cbox*3)+3; j++) {
            possibilities[i][j][entry-1] = 0;
        }
    }
}

static void add_possibilities(int possibilities[9][9][9], int entry, int row, int column){
     // remove constraints from row
    for(int j = 0; j < 9; j++){
        possibilities[row][j][entry-1] = 1;
    }

    // remove constraint from column
    for(int i = 0; i < 9; i++){
        possibilities[i][column][entry-1] = 1;
    }

    // remove constraints from box
    int rbox = row/3;
    int cbox = column/3;
    for (int i = rbox*3; i < (rbox*3)+3; i++) {
        for (int j = cbox*3; j < (cbox*3)+3; j++) {
            possibilities[i][j][entry-1] = 1;
        }
    }

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
bool solve_samurai(int sudoku[5][9][9]){

    // Solve middle sudoku first
    if(!solve(sudoku[2], 1)){
        return false;
    }

    // Solve intersections
    for (int i = 0; i < 9; i++) {       // rows
        for (int j = 0; j < 9; j++) {   // columns 
            // if it overlaps with the middle one
            // for the two top sudokus
            if (j < 3) {
                if (i > 5) {
                    sudoku[3][i-6][6+j] = sudoku[2][i][j];
                }
                if (i < 3) {
                    sudoku[0][6+i][6+j] = sudoku[2][i][j];
                }
            }
            // for the two buttom sudokus
            if (j > 5) {
                if (i > 5) {
                    sudoku[4][i-6][j-6] = sudoku[2][i][j];

                }
                if (i < 3) {
                    sudoku[1][6+i][j-6] = sudoku[2][i][j];
                }
            }
        } 
    } 

    for(int puzzle = 0; puzzle < 5; puzzle++){
        if(puzzle != 2 && !solve(sudoku[puzzle], 1)){
            return false;
        }
    }
    return true;
}
