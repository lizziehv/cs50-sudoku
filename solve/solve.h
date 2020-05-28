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

/* @param sudoku - an array of arrays(rows), where empty entries
 *                 are set to 0
 * @param solution - an empty array to copy solution onto
 * 
 * Given a sudoku with empty entries, complete Sudoku puzzle, following conventions 
 * (unique numbers in every row, column, and box)
 * 
 * Assumes that it is a valid sudoku (every number between 0 and 9)
 * 9*9 matrix with 9 boxes of 3*3
 * 
 * @return - true if sudoku has been correctly solved and copied onto solution
 * @return - false if no solution found
 */
bool solve(int sudoku[9][9], int solution[9][9]);

/* @param sudoku - a sudoku matrix to complete entries onto
 * @param row - row to start solving from (0 for the entire matrix)
 * @param column - column to start solving from (0 for the entire matrix)
 * 
 * Solve a sudoku and modify entries
 * 
 * @return - true if sudoku has been correctly solved
 * @return - false if no solution found
 */
bool solve_recursively(int sudoku[9][9], int row, int column);

#endif