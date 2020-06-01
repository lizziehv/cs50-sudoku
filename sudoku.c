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
#include <time.h>
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

    int level = 1; // keeps track of level (easy, medium, hard)
    char *levels[3] = {"easy", "medium", "hard"};

    if (argc == 3) {
        bool correct = false;
        for(int i = 1; i <= 3; i++){
            if(strcmp(argv[2], levels[i - 1]) == 0){
                level = i;
                correct = true;
                break;
            }
        }
        if(!correct){
            fprintf(stderr, "Error: Incorrect level given.\n");
            return 1;
        }
    }

    // check what the parameters given are
    if (strcmp(argv[1], "create") == 0 ) {
        if (level < 3) {
            int sudoku[9][9];

            // We are creating sudoku here
            sudoku_build(sudoku, level);
            create_puzzle(sudoku, 40, level);
            print_sudoku(stdout, sudoku);
        }
        else {
            int sudoku[5][9][9];
            samurai_build(sudoku);
            create_puzzle_samurai(sudoku, 40);
            print_samurai(stdout, sudoku);
        }
    }

    else if (strcmp(argv[1], "solve") == 0 ) {
        // Parse Sudoku
        if (level != 3) {
            int sudoku[9][9];
            int other[9][9];
            for (int i = 0; i < 9; i++) {
                for (int j=0; j < 9; j++) {
                    other[i][j] = sudoku[i][j]; 
                }            
            }
            if (parse_sudoku(stdin, sudoku, level)) {
                
                clock_t tic = clock();
                if (!efficient_solver(sudoku, level)) {
                    printf("Sudoku given has no solution.\n");
                }
                else {
                    printf("Solution:\n");
                }
                clock_t toc = clock();
                printf("Elapsed efficient: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

                clock_t ticky = clock();
                if (!solve(other, level)) {
                    printf("Sudoku given has no solution.\n");
                }
                else {
                    printf("Solution:\n");
                }
                clock_t tocky = clock();
                printf("Elapsed solve: %f seconds\n", (double)(tocky - ticky) / CLOCKS_PER_SEC);
            }
            else {
                fprintf(stderr, "Error: Sudoku given has incorrect format.\n"); 
                return 2; 
            }
            
        }
        else {
            int sudoku[5][9][9];
            if (parse_samurai(stdin, sudoku)) {
                
                clock_t tic = clock();
                if (!solve_samurai(sudoku)) {
                    printf("Sudoku given has no solution.\n");
                }
                else {
                    printf("Solution:\n");
                    print_samurai(stdout, sudoku); 
                }
                clock_t toc = clock();
                printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
            }
            else {
                fprintf(stderr, "Error: Sudoku given has incorrect format.\n"); 
                return 2; 
            }
        }
    }
    else {
        fprintf(stderr, "Error: Incorrect argument given.\n"); 
        return 1; 
    }
    
    return 0; 
}
