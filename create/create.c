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
#include "create.h"
#include "../solve/solve.h"
#include "../common/common.h"
#include <time.h>

/**************** Local functions ****************/


/**************** Global functions ****************/

/************  sudoku_build()  ************/
/*******  See create.h for details  *******/
bool sudoku_build(int sudoku[9][9], int level) {
    srand (time(NULL));
    int random_num; 

    for (int i = 0; i < 9; i++) {       // rows
        for (int j = 0; j < 9; j++) {   // columns 
            sudoku[i][j] = 0;
        } 
    } 
 
    // the diagonal 3x3 boxes are independent of each other, fill them first
    for (int diag = 0; diag < 9; diag += 3) {
    
        for (int i = 0; i < 3; i++) {       // rows
            for (int j = 0; j < 3; j++) {   // columns 
                do { 
                    
                    random_num = (rand() % 9) + 1; //from (1-9)
                } 
                // while you can't add that value in, change the number
                while (!check_box(sudoku, diag, diag + i, diag + j, random_num, level));

                // add the value to the grid
                sudoku[diag + i][diag + j] = random_num;
            } 
        } 
    }

    /* fill the rest, starting at row 0 and column 3
     * since the diagonal has already been filled 
     */
    if (!solve(sudoku, level)) {
        return false;
    }
    return true;
}


/***********  create_puzzle()  ************/
/*******  See create.h for details  *******/
void create_puzzle(int sudoku[9][9], int num_removed, int level){
    srand (time(NULL));

    // delete 40 numbers
    for (int i = 0; i < num_removed; i++) {
        bool isUnique = true; // is there a unique solution if that number is deleted
        int delete_i;         // row where deleted number will be
        int delete_j;         // column where deleted number will be

        do {
            // choose a random number to delete (from 0-8) that had not been deleted
            do {
                delete_i = rand() % 9;
                delete_j = rand() % 9;
            } while (sudoku[delete_i][delete_j] == 0);

            // store the value that will be deleted
            int deleted_value = sudoku[delete_i][delete_j];

            /* 
             * delete value and check to see if the new sudoku would have a unique
             * solution
             */
            sudoku[delete_i][delete_j] = 0;

            isUnique = (sudoku_solutions(sudoku, level) == 1);

            if(!isUnique){
                sudoku[delete_i][delete_j] = deleted_value;
            }
            else{
                isUnique = true;
            }

        } while (!isUnique);
    }
}
