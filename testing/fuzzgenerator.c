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
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>

#include "../create/create.h"
#include "../solve/solve.h"
#include "../common/common.h"

/* The random() and srandom() functions are provided by stdlib,
 * but for some reason not declared by stdlib.h, so declare here.
 */
long int random(void);
void srandom(unsigned int seed);
int level = 1; 

/**************** file-local global variables ****************/
static char *program;

/**************** local functions ****************/
static void parse_args(const int argc, char *argv[], char** filename, int *numSudoku);
bool check_solver(int sudoku[9][9], int solution[9][9]);

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

        sudoku_build(sudoku, level);
        create_puzzle(sudoku, 40, level);
        print_sudoku(puzzles, sudoku);
        fprintf(puzzles, "\n");  
        
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

    // loop through the sudokus again
    for (int i = 0; i < numSudoku; i++) {
      int solution[9][9];
      int sudoku[9][9]; // will not be changed by solver

      // parse them into the structure (need both to check if any item in the grid is changed)
      if (parse_sudoku(puzzles, sudoku, level)) {

        for (int i = 0; i < 9; i++) {
          for (int j = 0; j < 9; j++) {
            solution[i][j] = sudoku[i][j];
          }
        }
        
        // if it has a unique solution
        if (sudoku_solutions(solution, level) == 1) { 
          
          // solve it
          if (!efficient_solver(solution, level)) {
              fprintf(solutions, "Sudoku given has no solution.\n");
          }
          else if (check_solver(sudoku, solution)) {
              fprintf(solutions, "Solution #%d:\n", i+1);
              print_sudoku(solutions, solution);
          }
          else {
            fprintf(stderr, "Solver changes original grid\n");
            return 5;
          }
        }
        // there is no unique solution
        else {
          fprintf(stderr, "Sudoku does not have a unique solution.\n");
          return 4;
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

/**************** parse_args ****************/
// Checks if solver does not change already filled cells in the grids
bool check_solver(int sudoku[9][9], int solution[9][9]) {
  for (int i = 0; i < 9; i++) {       // rows
    for (int j = 0; j < 9; j++) {     // columns
      // if the entry there is not 0 and the entries are not equal
      if (sudoku[i][j] != 0 && sudoku[i][j] != solution[i][j]) {
        return false;
      }
    }
  }
  return true; 
}