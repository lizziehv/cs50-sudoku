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
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect number of parameters given.\n");
        return 1; 
    }

    // start the sudoku grod
    int sudoku[9][9];

    // check what the parameters given are
    if (strcmp(argv[1], "create") == 0 ) {
        if (sudoku_build(sudoku)) {
            create_puzzle(sudoku, 40);
            print_sudoku(stdout, sudoku);
        }
        else {
            fprintf(stderr, "Error: Problem filling in sudoku.\n"); 
            return 2; 
        }
    }

    else if (strcmp(argv[1], "solve") == 0 ) {
        /* Parse Sudoku */
        if (parse_sudoku(stdin, sudoku)) {
            
            int solution[9][9];
            if (!solve(sudoku, solution)) {
                printf("Sudoku given has no solution.\n");
            }
            else {
                printf("Solution:\n");
                print_sudoku(stdout, solution);
            }
        }
        else {
            fprintf(stderr, "Error: Sudoku given has incorrect format.\n"); 
            return 3; 
        }
    }
    
    return 0; 
}