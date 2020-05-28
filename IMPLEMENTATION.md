# CS50 Final Project
## Sudoke Puzzle Creator and Solver Implementation

### Data structures used

* 2D Array: A Sudoku is implemented as 2D array, or array of arrays (or array of rows), of size 9x9. Therefore, the element `sudoku[i][j]` is the element positioned at the ith row and jth column

### Resource management

The program `sudoku.c` has two modules, create and solve, implemented in [create.c](./create/create.c) and [solve.c][./solve/solve.c] and detailed in [create.h](./create/create.h) and [solve.h][./solve/solve.h]. Common functions used by both modules are found in the common directory and implemented in [common.c](./common/common.c). See header file [common.h](./common/common.h) for definitions of functions and arguments

### Definition of functions and parameters used 

#### Sudoku solver
```c
/* 
 * Given a sudoku puzzle, copy solution onto solution sudoku with empty entries, following conventions 
 * (unique numbers in every row, column, and box). Return true if there is a solution, false otherwise
 * 
 * Assumes that sudoku is valid sudoku (every number between 0 and 9)
 * 9*9 matrix with 9 boxes of 3*3
 */
bool solve(int sudoku[9][9], int solution[9][9]);

/* 
 * Given any sudoku, complete its 0 entries following sudoku conventions
 * (unique numbers in every row, column, and box). Return true if there is a solution, false otherwise)
 */
bool solve_recursively(int sudoku[9][9], int row, int column);
```

#### Sudoku creator
```c
/*
 * Populate a sudoku grid by using random numbers
 */
bool sudoku_build(int sudoku[9][9]);


/* 
 * Takes a completed sudoku and makes a puzzle by removing num_removed numbers
 * It deletes random numbers and makes sure that the sudoku has a unique solution
 * 
 */
void create_puzzle(int sudoku[9][9], int num_removed);

```

### Pseudocode for each object/components/functions

#### Sudoku
The sudoku runs as follows:
- Execute from a command line and validate parameters
- Initialize data structure to hold sudoku
- If sudoku solver was called
    - Call `parse_sudoku` reading from stdin
    - Initialize a solution sudoku (initially empty)
    - Call `solve` on sudoku and solution
    - If solve is false
        - Output "No solution"
    - Otherwise, call `print_sudoku` on solved sudoku
- Else if sudoku create was called
    - Call `sudoku_build` and `sudoku_ouzzle` on sudoku
    - call `print_sudoku` on sudoku

Some functions that are important for the solve and create function are found in `common.h` These are:

#### print_sudoku
- Loop through every row and column
    - Print the digit in that space of the grid, followed by a space
    - If it's the last column, don't add the space
    - Instead add an end of line

#### check_entry

#### check_box
- Loop through every row and column in the given diagonal (0-3)
    - if the number in (diag + the loop, diag + the loop) is equal to the entry
        - return false; this means that it would not be valid to add a number here
- return true; it would be valid to add a number here

#### parse_sudoku

However, the two most important functions are found in `solve.h` and `create.h`. These are:

#### Sudoku solver
The solver runs as follows:
- Given a sudoku structure and a solution sudoku, structure ...
- Copy all entries from sudoku onto solution
- Call recursive solver on solution and starting with the entry at the first position (0, 0)

The recursive solver runs as follows:
- If the solver is being called on entry (9, 0)
    - Since this entry is not existent, all squares have been visited so return true
- Otherwise
    - For all squares starting at the current square and moving to the right and bottom rows
        - If the entry is empty ( if it is 0)
            - for every number in range [1, 9]
                - If the number would be valid at this entry
                    - Call recursive solver on the entry that comes after it
                    - if the recursive solver returns true
                        - return true (found a solution that works)
                    - else
                        - reset current entry to empty
            - Since every number was tried and none worked, return false (backtrace steps)
    - Return true


#### Sudoku creator
- Fill the entire grid given with zeroes (to avoid any confusion)
- Fill the diagonal 3x3 squares since they are independent of each other, this is more efficient since we only call `check_box` rather than `check_entry`
    - To do this, loop through the beginning of the three diagonals 0,3,6
        - In each diagonal, loop over the 3 rows and 3 columns
            - Do:
                - Find a random number 
            - Do, while `check_box` of that number if false
            - Once it's true input the random number into the sudoky
- Fill in the rest of the sudoku
    - Call `solve_recursively` which fills in the rest of the sudoku in a valid matter 

- After the sudoku has been filled, loop through 40 times (to delete 40 numbers)
    - Do:
        - randomly select a location (row and column) to delete
        - while this location has already been deleted
            - randomly select another a location (row and column) to delete
        - store the value that will be deleted
        - loop through 1-9 
            - if it's not the stored value and this integer could be placed into the sudoku validly
                - insert the index into the sudoky
                - attempt to solve the sudoku to see if there would be a valid solution with a different integer
                - If it was not unique
                    - Return the original deleted value
                    - Finish the for loop and return to select another location to delete
        - If none of these values ever found another solution, then it is unique
    - Do, while the answer is not unique
    - now that the answer is clearly unique, make the location zero
       
### Memory allocation in C and modules used
No memory has been allocated or freed in the heap.

### Error handling

- Sudoku will check the number of parameters and valid arguments, "solve" or "create".
- Sudoku parser will check that the sudoku is valid. It can have 0 entries, but every nonzero entry must be unique in each column, row, and box.
- Sudoku build will return false on any error populating grid, which technically should not occur.
