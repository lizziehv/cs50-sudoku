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
static void add_constraint(int constraints[9][9][9], int entry, int row, int column, int level);
static void remove_constraint(int constraints[9][9][9], int entry, int row, int column, int level);

/**************** Global functions ****************/

/********  efficient_solver()  *********/
/******  See solve.h for details  ******/
bool efficient_solver(int sudoku[9][9], int level){
    int constraints[9][9][9];     // keeps track of constraints for each number
    
    // fill in 3d matrix with 0s
    for(int number = 0; number < 9; number++){
        for(int row = 0; row < 9; row++){
            for(int column = 0; column < 9; column++){
                constraints[number][row][column] = 0;
            }
        }
    }

    // Add constraints for filled in squares
    for(int row = 0; row < 9; row++){
        for(int column = 0; column < 9; column++){
            int entry = sudoku[row][column];
            if(entry != 0)
                add_constraint(constraints, entry - 1, row, column, level);
        }
    }
    
    // call recursive solver
    return efficient_solver_helper(sudoku, constraints, 0, 0, level);
} 

/**************  solve()  **************/
/******  See solve.h for details  ******/
/***  Original solver implementation  **/
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
 * @param constraints - 3d matrix to keep track of where entries can't go
 * @param row - row to start solving from (0 for the entire matrix)
 * @param column - column to start solving from (0 for the entire matrix)
 * @param level - 1 for easy or 2 for medium
 * 
 * Solve a sudoku and modify entries
 * 
 * @return - true if sudoku has been correctly solved
 * @return - false if no solution found
 */
static bool efficient_solver_helper(int sudoku[9][9], int constraints[9][9][9], int row, int column, int level){
    // check if all entries have been visited
    if (no_possibilities(possibilities)) {
        return true;
    }
    for (int i=row; i<9; i++) {
        int j = (i == row) ? column : 0;
        
        for ( ; j<9; j++) {
            int entry = sudoku[i][j];
            // if it is empty
            if( entry == 0){
                for(int number = 0; number < 9; number++){
                    // only test number if there are no constraints
                    if(constraints[number][i][j] == 0){
                        // insert
                        sudoku[i][j] = number + 1;

                        // add constraints with new inserted number
                        add_constraint(constraints, number, i, j, level);

                        // recurse with new sudoku -> move to next entry
                        bool ret;
                        if (j == 8) 
                            ret = efficient_solver_helper(sudoku, constraints, i+1, 0, level);
                        else
                            ret = efficient_solver_helper(sudoku, constraints, i, j+1, level);
                        
                        if(ret){        // found a solution that works
                            return true;
                        }
                        else{           // number did not work
                            sudoku[i][j] = 0;
                            remove_constraint(constraints, number, i, j, level);
                        }
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

/* 
 * @param constraints - 3d matrix to keep track of where entries can't go
 * @param row - row where entry was found
 * @param column - column where entry was found
 * @param level - 1 for easy or 2 for medium
 * 
 * Add row, column, and box constraints to constraints matrix
 * 
 */
static void add_constraint(int constraints[9][9][9], int entry, int row, int column, int level){
    // add constraints to row
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

    // for diagonal matrix
    if(level == 2){
        // add constraints to diagonal
        if(row == column){
            for(int i = 0; i < 9;i++){
                constraints[entry][i][i]+=1;
            }
        }
        else if(row == 8 - column){
            for(int i = 0; i < 9;i++){
                constraints[entry][i][8-i]+=1;
            }
        }
    }
}

/* 
 * @param constraints - 3d matrix to keep track of where entries can't go
 * @param row - row where entry was found
 * @param column - column where entry was found
 * @param level - 1 for easy or 2 for medium
 * 
 * Remove row, column, and box constraints to constraints matrix
 * 
 */
static void remove_constraint(int constraints[9][9][9], int entry, int row, int column, int level){
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
    // for diagonal matrix
    if(level == 2){
        // add constraints to diagonal
        if(row == column){
            for(int i = 0; i < 9;i++){
                constraints[entry][i][i]-=1;
            }
        }
        else if(row == 8 - column){
            for(int i = 0; i < 9;i++){
                constraints[entry][i][8-i]-=1;
            }
        }
    }
}

/* Original sudoku solver
 * @param sudoku - a sudoku matrix to complete entries onto
 * @param row - row to start solving from (0 for the entire matrix)
 * @param column - column to start solving from (0 for the entire matrix)
 * @param level - 1 for easy or 2 for medium
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

/**********  solve_samurai()  **********/
/******  See solve.h for details  ******/
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
