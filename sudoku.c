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
#include "./create/create.c"

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
        sudoku_build(sudoku);
        create_puzzle(sudoku);
    }

    else if (strcmp(argv[1], "solve") == 0 ) {
        int solution[9][9];

        if (!solve(sudoku, solution)) {
            printf("Sudoku given has no solution.\n");
        }
        else {
            print_sudoku(solution);
        }
    }
    
    return 0; 
}