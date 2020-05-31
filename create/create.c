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
static bool check_multiple_samurai(int delete_i, int delete_j, int delete_puzzle, int sudoku[5][9][9]); 

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

/************  samurai_build()  ************/
/*******  See create.h for details  *******/
bool samurai_build(int sudoku[5][9][9]) {
    srand (time(NULL));
    int random_num; 

    // build the middle array normally
    if (!sudoku_build(sudoku[2], 1)) {
        return false; 
    }

    // fill in with zeroes, except the overlap
    for (int i = 0; i < 9; i++) {       // rows
        for (int j = 0; j < 9; j++) {   // columns 
            sudoku[0][i][j] = 0;
            sudoku[1][i][j] = 0;

            // if it overlaps with the middle one
            // for the two top sudokus
            if (j > 5) {
                if (i > 5) {
                    sudoku[0][i][j] = sudoku[2][i][j];
                }
                if (i < 3) {
                    sudoku[1][i][j] = sudoku[2][i][j];
                }
            }
            // for the two buttom sudokus
            if (j > 3) {
                if (i > 5) {
                    sudoku[3][i][j] = sudoku[2][i][j];
                }
                if (i < 3) {
                    sudoku[4][i][j] = sudoku[2][i][j];
                }
            }
        } 
    } 
 
    // the diagonal 3x3 boxes are independent of each other, fill them first
    // two top sudokus
    for (int puzzle = 0; puzzle < 2; puzzle ++) {
        for (int diag = 0; diag < 9; diag += 3) {
        
            for (int i = 0; i < 3; i++) {       // rows
                for (int j = 0; j < 3; j++) {   // columns 
                    do { 
                        
                        random_num = (rand() % 9) + 1; //from (1-9)
                    } 
                    // while you can't add that value in, change the number
                    // since it's not different from the original sudoku give it a level 1
                    while (!check_box(sudoku[puzzle], diag, diag + i, diag + j, random_num, 1));

                    // add the value to the grid
                    sudoku[puzzle][diag + i][diag + j] = random_num;
                } 
            } 
        }
    }
    // two bottom sudokus
    for (int puzzle = 3; puzzle < 5; puzzle ++) {
        for (int diag = 6; diag >= 0; diag -= 3) {
        
            for (int i = 0; i < 3; i++) {       // rows
                for (int j = 0; j < 3; j++) {   // columns 
                    do { 
                        
                        random_num = (rand() % 9) + 1; //from (1-9)
                    } 
                    // while you can't add that value in, change the number
                    // since it's not different from the original sudoku give it a level 1
                    while (!check_box(sudoku[puzzle], diag, diag + i, diag + j, random_num, 1));

                    // add the value to the grid
                    sudoku[puzzle][diag + i][diag - 6 + j] = random_num;
                } 
            } 
        }
    }

    /* fill the rest, starting at row 0 and column 3
     * since the diagonal has already been filled 
     */
    if (!solve_samurai(sudoku)) {
        return false;
    }
    return true;
}

/***********  create_puzzle_samurai()  ************/
/*******  See create.h for details  *******/
void create_puzzle_samurai(int sudoku[5][9][9], int num_removed){
    srand (time(NULL));

    for (int delete_puzzle = 0; delete_puzzle < 5; delete_puzzle++) {
        // delete 40 numbers
        for (int i = 0; i < num_removed; i++) {
            bool isUnique = true; // is there a unique solution if that number is deleted
            int delete_i;         // row where deleted number will be
            int delete_j;         // column where deleted number will be

            do {
                // choose a random number to delete (from 0-8) that had not been deleted
                // and a random sudoku to delete it from
                do {
                    delete_i = rand() % 9;
                    delete_j = rand() % 9;
                    delete_puzzle = rand() % 5;
                } while (sudoku[delete_puzzle][delete_i][delete_j] == 0);

                // store the value that will be deleted
                int deleted_value = sudoku[delete_puzzle][delete_i][delete_j];

                /* 
                * delete value and check to see if the new sudoku would have a unique
                * solution
                */
                sudoku[delete_puzzle][delete_i][delete_j] = 0;

                // check if the middle is not causing multiple solutions
                isUnique = check_multiple_samurai(delete_i, delete_j, delete_puzzle, sudoku); 

                // if it's not unique, then return the value that was deleted
                if(!isUnique){
                    sudoku[delete_puzzle][delete_i][delete_j] = deleted_value;
                }
                else{
                    isUnique = true;
                }

            } while (!isUnique);
        }
    }
}

// check to see if the value we are deleting is not causing multiple solutions
static bool check_multiple_samurai(int delete_i, int delete_j, int delete_puzzle, int sudoku[5][9][9]) {
    bool isUnique = true; 

    // check if the middle is not causing multiple solutions
    if (delete_j > 5 && delete_i > 5) {
        if (delete_puzzle == 0) {
            isUnique = (sudoku_solutions(sudoku[0], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
        if (delete_puzzle == 2) {
            isUnique = (sudoku_solutions(sudoku[4], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
    }
    else if (delete_j > 5 && delete_i < 3) {
        if (delete_puzzle == 1) {
            isUnique = (sudoku_solutions(sudoku[1], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
        if (delete_puzzle == 2) {
            isUnique = (sudoku_solutions(sudoku[2], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
    }
    else if (delete_j < 3 && delete_i > 5) {
        if (delete_puzzle == 3) {
            isUnique = (sudoku_solutions(sudoku[3], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
        if (delete_puzzle == 2) {
            isUnique = (sudoku_solutions(sudoku[3], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
    }
    else if (delete_j < 3 && delete_i < 3) {
        if (delete_puzzle == 4) {
            isUnique = (sudoku_solutions(sudoku[4], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
        if (delete_puzzle == 2) {
            isUnique = (sudoku_solutions(sudoku[0], 1) == 1 && sudoku_solutions(sudoku[2], 1) == 1);
        }
    }
    // return if deleting this value would cause multiple solutions on any of the functions
    return isUnique; 
}
