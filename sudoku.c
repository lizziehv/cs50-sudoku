/* 
 * sudoku.c 
 * see IMPLEMENTATION.md and DESIGN.md for more information.
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: call create and solver to handle any puzzle 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./common/common.h"
#include "./create/create.h"
#include "./solve/solve.h"

/**************** Main function ****************/
int main(int argc, char *argv[]) {
    
    // if the wrong number of parameters is given
    if (argc > 3 || argc < 2) {
        fprintf(stderr, "Error: Incorrect number of parameters given.\n");
        return 1; 
    }

    int level;

    if (argc == 2) {
        // If difficulty not explicitly mentioned, we want an easy level sudoku
        level = 1;
    }
    else if (argc==3) {
        if (strcmp(argv[2], "easy")==0) {
            // Level 1 is easy
            level = 1;
        }
        else if (strcmp(argv[2], "medium")==0) {
            // Level 3 is medium
            level = 2;
        }
        else if (strcmp(argv[2], "hard")==0) {
            // Level 3 is hard
            level = 3;
        }
        else {
            fprintf(stderr, "Error: Incorrect level given.\n");
            return 1;
        }
    }

    // start the sudoku grod
    int sudoku[9][9];

    // check what the parameters given are
    if (strcmp(argv[1], "create") == 0 ) {
        // We are creating sudoku here
        if (sudoku_build(sudoku, level)) {
            create_puzzle(sudoku, 40);
            print_sudoku(stdout, sudoku, level);
        }
        else {
            fprintf(stderr, "Error: Problem filling in sudoku.\n"); 
            return 2; 
        }
    }

    else if (strcmp(argv[1], "solve") == 0 ) {
        // Parse Sudoku
        if (parse_sudoku(stdin, sudoku, level)) {

            if (!solve(sudoku, level)) {
                printf("Sudoku given has no solution.\n");
            }
            else {
                printf("Solution:\n");
                print_sudoku(stdout, sudoku, level);
            }
        }
        else {
            fprintf(stderr, "Error: Sudoku given has incorrect format.\n"); 
            return 3; 
        }
    }
    else {
        fprintf(stderr, "Error: Incorrect argument given.\n"); 
        return 1; 
    }
    
    return 0; 
}
