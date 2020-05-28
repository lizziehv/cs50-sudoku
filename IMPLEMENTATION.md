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

### Pseudocode for each component

#### Sudoku
The sudoku runs as follows:
- Execute from a command line and validate parameters
- Initialize data structure to hold sudoku
- If sudoku solver was called
    - Parse sudoku from stdin
    - Initialize a solution sudoku (initially empty)
    - Call solver on sudoku and solution
    - If solver is false
        - Output "No solution"
    - Otherwise, output solved sudoku
- Else if sudoku create was called
    - Call sudoku creator
    - Output sudoku

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

### Memory allocation in C and modules used
No memory has been allocated or freed in the heap.

### Error handling

- Sudoku will check the number of parameters and valid arguments, "solve" or "create".
- Sudoku parser will check that the sudoku is valid. It can have 0 entries, but every nonzero entry must be unique in each column, row, and box.
- Sudoku build will return false on any error populating grid, which technically should not occur.
