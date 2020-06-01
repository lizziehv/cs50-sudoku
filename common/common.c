/* 
 * common.c 
 * see common.c for details
 *
 * Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
 * May 2020
 * Purpose: Write common functions used for both solver and creator of Sudoku puzzle
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"

/****************** Local functions ******************/
static bool check_valid(int sudoku[9][9], int level);

/****************** Local functions (extra credit) ******************/
static void samurai_print_two(FILE *fp_out, int sudoku[5][9][9], bool top);
static void samurai_print_three(FILE *fp_out, int sudoku[5][9][9], bool top);
static bool samurai_parse_two(FILE *file, int sudoku[5][9][9], bool top);
static bool samurai_parse_three(FILE *file, int sudoku[5][9][9], bool top);
static bool samurai_scan_assign(FILE *file, int sudoku[5][9][9], int puzzle, int i, int j);
static bool samurai_scan_assign_twice(FILE *file, int sudoku[5][9][9], int puzzle1, int i, int j, int puzzle2, int k, int l);

/****************** Global functions ******************/

/***********  print_sudoku()  ***********/
/******  See common.h for details  ******/
void print_sudoku(FILE *fp_out, int sudoku[9][9]) {  
    // for every row
    for (int i = 0; i < 9; i++) {
        // for every column
        for (int j = 0; j < 8; j++) {
            fprintf(fp_out, "%d ", sudoku[i][j]);
        }
        fprintf(fp_out, "%d", sudoku[i][8]);
        fprintf(fp_out, "\n");
    }
}

/***********  check_entry()  ************/
/******  See common.h for details  ******/
bool check_entry(int sudoku[9][9], int row, int column, int entry, int level) {
    // Loop through the rows to check column
    for (int r = 0; r < 9; r++) {
        if (sudoku[r][column] == entry && r != row) {
            return false;
        } 
    }

    // Loop through the columns to check row 
    for (int c = 0; c < 9; c++){
        if (sudoku[row][c] == entry && c != column) {
            return false;
        }
    }

    // Check box
    int rbox = row/3;
    int cbox = column/3;
    for (int i = rbox*3; i < (rbox*3)+3; i++) {
        for (int j = cbox*3; j < (cbox*3)+3; j++) {
            if (sudoku[i][j] == entry && i != row && j != column) {
                return false;
            }
        }
    }

    // diagonal sudoku
    if (level == 2) {
        // the negative sloped diagonal
        if (row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the entry
                if (i != row && sudoku[i][i] == entry) {
                    return false;
                }
            }
        }
        // the positive sloped diagonal
        if (8-row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the entry
                if (8-i != row && column != i && sudoku[8-i][i] == entry) {
                    return false;
                }
            }
        }
    }
    return true;
}

/***********  check_box()  ************/
/******  See common.h for details  ******/
bool check_box(int sudoku[9][9], int diag, int row, int column, int entry, int level) {
    // check if that box is not already filled
    if (sudoku[row][column] != 0) {
        return false; 
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // if the entry is already in the 3x3 box 
            if (sudoku[diag+i][diag+j] == entry) {
                return false;
            }
        } 
    }
    // diagonal sudoku
    if (level == 2) {
        // the negative sloped diagonal
        if (row == column) {
            for (int i = 0; i < 9; i++) {
                // check if it's in the entry
                if (i != row && sudoku[i][i] == entry) {
                    return false;
                }
            }
        }
    }
    // if it was not in the box
    return true; 
}


/***********  parse_sudoku()  ***********/
/******  See common.h for details  ******/
bool parse_sudoku(FILE* file, int sudoku[9][9], int level) {
    // Some checks
    if (file == NULL) {
        return false;
    }
    if (sudoku == NULL) {
        return false;
    }

    // loop through entries
    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            int entry;
        
            int ret = fscanf(file, "%d", &entry);
            
            if(ret != 1){
                return false;
            }

            if(entry <= 9 && entry >= 0){
                sudoku[i][j] = entry;
            }
            else{
                return false;
            }
        }
        
        // Check valid format (9x9 matrix)
        char c;
        fscanf(file, "%c", &c);
        if (c != '\n' && i != 8) {
            return false;
        }
    }

    if (!check_valid(sudoku, level)) {
        return false;
    }

    return true; 
}

/**************** lines_in_file ****************/
int lines_in_file(FILE *fp){
  if (fp == NULL)
    return 0;

  rewind(fp);

  int nlines = 0;
  char c = '\0';
  while ( (c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      nlines++;
    }
  }

  rewind(fp);
  
  return nlines;
}

/**************  Global functions for extra credit  **************/

/***********  print_samurai()  ***********/
/******  See common.h for details  ******/
void print_samurai(FILE *fp_out, int sudoku[5][9][9]) {
    // Print the first 6 rows
    samurai_print_two(fp_out, sudoku, true);

    // Print the next 3 rows
    samurai_print_three(fp_out, sudoku, true);

    // Print the next 3 lines. Only middle sudoku printed
    for (int r = 9; r < 12; r++) {
        for (int j = 0; j < 6; j++) {
            fprintf(fp_out, "  ");
        }
        // Print the middle sudoku
        for (int j = 0; j < 9; j++) {
            fprintf(fp_out, "%d ", sudoku[2][r-6][j]);
        }
        for (int j = 0; j < 6; j++) {
            fprintf(fp_out, "  ");
        }
        fprintf(fp_out, "\n");
    }

    // Print the next 3 lines. All 3 sudokus printed
    samurai_print_three(fp_out, sudoku, false);

    samurai_print_two(fp_out, sudoku, false);
}

/***********  parse_samurai()  ***********/
/******  See common.h for details  ******/
bool parse_samurai(FILE* file, int sudoku[5][9][9]) {
    if(! samurai_parse_two(file, sudoku, true))
        return false;
    if(! samurai_parse_three(file, sudoku, true))   
        return false;
    
    // parse middle rows
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 9; j++){
            if(!samurai_scan_assign(file, sudoku, 2, i, j))
                return false;
        }
    }

    if(! samurai_parse_three(file, sudoku, false))
        return false;

    if(! samurai_parse_two(file, sudoku, false))   
        return false;
    
    return true;
}


/****************** Local functions ******************/

/* 
 * @param sudoku - an array of arrays which are the rows
 * 
 * Check if parsing produces a valid sudoku puzzle
 * 
 * @return true if sudoku is valid (can have 0 entries)
 *         false otherwise
 */
static bool check_valid(int sudoku[9][9], int level) {
    if (sudoku == NULL)
        return false;

    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            int entry = sudoku[i][j];
            if (entry != 0 && !check_entry(sudoku, i, j, entry, level)) {
                return false;
            }
        }
    }
    return true;
}

static void samurai_print_two(FILE *fp_out, int sudoku[5][9][9], bool top){
    int first = top ? 0 : 3;  // first samurai to print
    int second = top ? 1 : 4 ; // second samurai to print
    
    int first_row = top ? 0 : 3;
    for (int r = first_row; r < first_row + 6; r++) {
        // Print the row of the first sudoku
        for (int j = 0; j < 9; j++) {
            fprintf(fp_out, "%d ", sudoku[first][r][j]);
        }
        // Print spaces betweent the first and second sudoku
        for (int j = 0; j < 3; j++) {
            fprintf(fp_out, "  ");
        }
        // Print the row of the second sudoku
        for (int j = 0; j < 9; j++) {
            fprintf(fp_out, "%d ", sudoku[second][r][j]);
        }
        fprintf(fp_out, "\n");
    }
}

static void samurai_print_three(FILE *fp_out, int sudoku[5][9][9], bool top){
    int first = top ? 0 : 3;  // first samurai to print
    int second = top ? 1 : 4 ; // second samurai to print
    
    int first_row = top ? 6 : 0;

    for (int r = first_row; r < first_row + 3; r++) {
        // Print the row of the first sudoku
        for (int j = 0; j < 9; j++) {
            fprintf(fp_out, "%d ", sudoku[first][r][j]);
        }
        // Print spaces between the first and second sudoku
        for (int j = 3; j < 6; j++) {
            fprintf(fp_out, "%d ", sudoku[2][6-2*first_row + r][j]);
        }
        
        // Print the row of the second sudoku
        for (int j = 0; j < 9; j++) {
            fprintf(fp_out, "%d ", sudoku[second][r][j]);
        }
        fprintf(fp_out, "\n");
    }
}

static bool samurai_parse_two(FILE *file, int sudoku[5][9][9], bool top){
    int first = top ? 0 : 3;  // first samurai to parse
    int second = top ? 1 : 4 ; // second samurai to parse
    
    int first_row = top ? 0 : 3;
    for (int r = first_row; r < first_row + 6; r++) {
        for(int puzzle = first; puzzle <= second; puzzle++){
            // Parse line and enter into sudoku
            for (int j = 0; j < 9; j++) {
                if(!samurai_scan_assign(file, sudoku, puzzle, r, j)){
                    return false;
                }
            }
        }
    }
    return true;
}

static bool samurai_parse_three(FILE *file, int sudoku[5][9][9], bool top){
    int first = top ? 0 : 3;  // first samurai to print
    int second = top ? 1 : 4 ; // second samurai to print
    
    int first_row = top ? 6 : 0;

    for (int r = first_row; r < first_row + 3; r++) {
        
        // first six numbers, only first sudoku
        for(int c = 0; c < 6; c++){
            if(!samurai_scan_assign(file, sudoku, first, r, c))
                return false;
        }

        // intersection
        for(int c = 6; c < 9; c++){
            if(!samurai_scan_assign_twice(file, sudoku, first, r, c, 2, 6-2*first_row + r, c-6))
                return false;
        }

        // assign only to middle one
        for(int c = 3; c < 6; c++){
            if(!samurai_scan_assign(file, sudoku, 2, 6-2*first_row + r, c))
                return false;
        }

        //intersection
        for(int c = 6; c < 9; c++){
            if(!samurai_scan_assign_twice(file, sudoku, second, r, c - 6, 2, 6-2*first_row + r, c))
                return false;
        }

        // last six number -> only second sudoku
        for(int c = 3; c < 9; c++){
            if(!samurai_scan_assign(file, sudoku, second, r, c))
                return false;
        }
    }
    return true;
}

static bool samurai_scan_assign(FILE *file, int sudoku[5][9][9], int puzzle, int i, int j){
    int entry;
    int ret = fscanf(file, "%d", &entry);

    if(ret != 1 || ! (entry <= 9 && entry >= 0))
        return false;
    
    sudoku[puzzle][i][j] = entry;
    return true;
}

static bool samurai_scan_assign_twice(FILE *file, int sudoku[5][9][9], int puzzle1, int i, int j, int puzzle2, int k, int l){
    int entry;
    int ret = fscanf(file, "%d", &entry);

    if(ret != 1 || ! (entry <= 9 && entry >= 0))
        return false;
    
    sudoku[puzzle1][i][j] = entry;
    sudoku[puzzle2][k][l] = entry;
    return true;
}
