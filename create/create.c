/* 
 * create.c 
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: create a Sudoku with a unique solution
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../solve/solve.c"
#include "../common/common.c"

// checks to see if there is a solution to the given sudoku
bool check_unique_solution(int sudoku[9][9]);

/**************** Global functions ****************/

/* fills in the grid with random numbers from 1-9 
* follows the guidelines necessary for a Sudoku grid */
void sudoku_build(int sudoku[9][9]) {
    int random_num; 

    for (int i = 0; i < 9; i++) {   // rows
        for (int j = 0; j < 9; j++) {   // columns 
            do { 
                random_num = (rand() % 9) + 1; //from (1-9)
            } 
            // while you can't add that value in, change the number
            while (!check_entry(sudoku, i, j, random_num));

            // add the value to the grid
            sudoku[i][j] = random_num;
        } 
    } 
}

// creates the puzzle by erasing some of the values added above
void create_puzzle(int sudoku[9][9]){
    // delete 40 numbers
    for (int i = 0; i < 40; i++)
    {
        bool isUnique = true; // is there a unique solution if that number is deleted
        int delete_i;         // row where deleted number will be
        int delete_j;         // column where deleted number will be

        do
        {
            // choose a random number to delete (from 0-8)
            delete_i = rand() % 9;
            delete_j = rand() % 9;

            // while the number that will be deleted has not been deleted before
            while (sudoku[delete_i][delete_j] == 0)
            {
                delete_i = rand() % 9;
                delete_j = rand() % 9;
            }

            // store the value that will be deleted
            int deleted_value = sudoku[delete_i][delete_j];

            /* check to see if any other value could be placed ther
            * if it can be placed, then it means the grid has more than 
            * one solution */
            for (int j = 1; j <= 9; j++)
            {

                /* if the value we are checking is not the same as the one we had before
                * and if the value can validly be put in */
                if (j != deleted_value && check_entry(sudoku, delete_i, delete_j, j))
                {

                    sudoku[delete_i][delete_j] = j;
                    isUnique = check_unique_solution(sudoku);

                    // if it was not a unique solution
                    if (!isUnique)
                    {
                        // return the value to where it was
                        sudoku[delete_i][delete_j] = deleted_value;
                        break;
                    }
                }
            }
        } while (!isUnique);

        // once you have found a value that gives you a unique solution, make it 0
        sudoku[delete_i][delete_j] = 0;
    }
}

// checks to see if there is a solution to the given sudoku
<<<<<<< HEAD
bool check_unique_solution(int sudoku[9][9]) {
    int solution[9][9];

    //The solver returns false when there's no solution
    if (!solve(sudoku, solution)) {
=======
bool check_unique_solution(int **sudoku)
{
    //The solver returns false when there's no solution
    if (!solve(sudoku))
    {
>>>>>>> 36bc3c301c4f22cafe383f449b48cc5fd0607aa9
        return false;
    }
    return true;
}
