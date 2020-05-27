/* 
 * solve.c 
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: solve a given sudoku
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**************** Global functions ****************/

/* solves a given sudoku
* if there is no solution, returns NULL */
int** solve(int** sudoku) {

}

bool checkValid(int** sudoku){
    // Check for every number if it occurs only once in a row
    // Check for every number if it occurs only once in a column
    // Check if every number is in the square box only once
}