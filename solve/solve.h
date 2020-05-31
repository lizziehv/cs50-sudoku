/* 
 * solve.h 
 * see solve.c for implementation
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Write code to solve a given sudoku puzzle
 */


#ifndef __SOLVE_H
#define __SOLVE_H

/* 
 * @param sudoku - an array of arrays(rows), where empty entries are set to 0
 * @param level - the level that the sudoku will be in
 * 
 * Given a sudoku with empty entries, complete Sudoku puzzle, following conventions 
 * (unique numbers in every row, column, and box)
 * 
 * Assumes that it is a valid sudoku (every number between 0 and 9)
 * 9*9 matrix with 9 boxes of 3*3
 * 
 * @return - true if sudoku has been correctly solved
 * @return - false if no solution found
 */
bool solve(int sudoku[9][9], int level);

/* 
 * @param sudoku - an array of arrays(rows), where empty entries are set to 0
 * @param level - the level that the sudoku will be in
 * 
 * Given a sudoku with empty entries, find the number of solutions without 
 * completing sudoku puzzle
 * 
 * Assumes that it is a valid sudoku (every number between 0 and 9)
 * 9*9 matrix with 9 boxes of 3*3
 * 
 * @return - number of solutions for given sudoku
 */
int sudoku_solutions(int sudoku[9][9], int level);

/******************* For extra credit *******************/

/*
 * @param samurai - an array of sudokus (a samurai sudoku)
 * 
 * Complete a samurai, a set of 5 overlapping sudoku puzzles, each with a unique solution
 * 
 * @return - true if the samurai has a solution
 *           false otherwise
 */
bool solve_samurai(int samurai[5][9][9])
#endif
