/* 
 * fuzzgenerator - generate a series of random sudoku for testing create and solve
 * 
 * usage: 
 *   fuzzgenerator filename numSudoku
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../create/create.h"
#include "../solve/solve.h"
#include "../common/common.h"
#include <netdb.h>

/* The random() and srandom() functions are provided by stdlib,
 * but for some reason not declared by stdlib.h, so declare here.
 */
long int random(void);
void srandom(unsigned int seed);

/**************** file-local global variables ****************/
static char *program;

/**************** local functions ****************/
static void parse_args(const int argc, char *argv[], char** filename, int *numSudoku);
/**************** main ****************/
int main(const int argc, char *argv[]) {
    char* filename;
    int numSudoku;

    /*
    * parse the arguments
    * function exits if any errors in parsing
    */
    parse_args(argc, argv, &filename, &numSudoku);

    /* 
    * check to see if index file is a valid pathname
    * by opening the file to prep it for loading 
    */
    FILE *puzzles = fopen(filename, "w");
    if(puzzles == NULL) {
      fprintf(stderr, "Error opening files\n");
      return 3;
    }

    // generate several random sudokus and print them to an output file
    // load an array full of words from the given index file
    for (int i = 0; i < numSudoku; i++) {
        
        // start the sudoku grid
        int sudoku[9][9];
        srandom(5);

        // dont' print anything if there was a proble building the sudoku
        if (sudoku_build(sudoku)) {
            create_puzzle(sudoku, 40);
            print_sudoku(puzzles, sudoku);
            fprintf(puzzles, "\n");  
        }
        sleep(1); 
    }

    // close the files
    fclose(puzzles);
    FILE *read_puzzles = fopen(filename, "r");
    if(read_puzzles == NULL) {
      fprintf(stderr, "Error opening files\n");
      return 3;
    }

    // where the solutions will be written 
    char *solve_file = malloc(strlen(filename)+sizeof(char)+strlen("solved")+1);
    sprintf(solve_file, "%s_%s", filename, "solved");
    FILE *solutions = fopen(solve_file, "w");
    if(solutions == NULL) {
      fprintf(stderr, "Error opening files\n");
      return 3;
    }

    for (int i = 0; i < numSudoku; i++) {
        int sudoku[9][9];

        if (parse_sudoku(puzzles, sudoku)) {
            if (!solve(sudoku)) {
                fprintf(solutions, "Sudoku given has no solution.\n");
            }
            else {
                fprintf(solutions, "Solution #%d:\n", i+1);
                print_sudoku(solutions, sudoku);
            }
        }
    }
    fclose(read_puzzles);
    fclose(solutions);
    free(solve_file);
    return 0; 
}

/**************** parse_args ****************/
/* Parse the command-line arguments, filling in the parameters;
 * if any error, print to stderr and exit.
 */
static void parse_args(const int argc, char *argv[], char** filename, int *numSudoku) {
  char extra;

  /**** usage ****/
  program = argv[0];
  if (argc != 3) {
    fprintf(stderr, "Error incorrect number of parameters given\n");
    exit(1);
  }

   /**** indexFile ****/
  *filename = argv[1];

  /**** numSudoku ****/
  if (sscanf(argv[2], "%d%c", numSudoku, &extra) != 1 || *numSudoku < 0) {
    fprintf(stderr, "usage: %s: invalid numSudoku '%s'\n", program, argv[2]);
    exit (2);
  }
}