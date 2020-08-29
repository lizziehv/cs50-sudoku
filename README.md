# CS50 Final Project
## Sudoku Puzzle Creator and Solver
This is the repository for the final project for Computer Science 50-- a sudoku puzzle creator and solver.

<img src="assets/img.png" alt="graphics" width="25%" />

### Contributors (Github username)
* Ethan Trepka (et22)
* Kshitij Jain (jkshitij77)
* Lizzie Hernandez (lizziehv)
* Maria Paula Mora (mpmora00)

### Final Video 
https://drive.google.com/file/d/1WL7K_2MHqExW_gd8VInaS9QMjAj8pFGk/view?usp=sharing

### Compiling
To build, run `make`.
To clean up, run `make clean`.

### Sudoku 
A *sudoku* is a well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. In a valid Sudoku grid every number from 1 to 9 must appear:
- Only once in every row
- Only once in every column
- Only once in every 3x3 squared region

#### Extra credit
There are several functions that will not be explained in this README file since they do not belong with the original assingment. These are extra credit functions and are all explained in [README](extra-credit/README.md).

This involve: graphics, levels, and even different sudoku types

### Usage
`sudoku.c` simply contains only a main function but it utilizes functions from `common.c`, `create.c` and `solve,c` as helpers. These are explained below and you can see [common.h](./common/common.h), [create.h](./create/create.h), and [solve.h][./solve/solve.h] for definitions of functions and paramters. This program works with the user through command lines:

``` bash
# creates a 9x9 grid with a unique solution 
# outputs the grid into the stdout
./sudoku create

# takes in a grid from stdin or through piping
# solves the sudoku
./sudoku solve

# OTHER COMMAND LINES ARE AVAILABLE, this are explained in the extra-credit file
```

#### Functionalities
The functionalities we implemented in this program are the following:
- `create.c` creates a 9x9 grid following the sudoku rules stated above with one unique solution and outputs to stdout.
- `solve.c` solves any sudoku given through stdin.
- `common.c` has helper methods which help print the sudoku, find if entry can be inserted into the sudoku and more. 

#### 'Sudoku Create' description
The documents `create.h` and `create.c` are called by `sudoku.c` when the following command line is asked to execute:
``` bash
./sudoku create
```
```
This command line, calls the program `create.c` which will:
1. Create a 2D array and fill it with the correct specifications (unique in row, column, subgrid)
2. For 40 iterations
    3. While there would be a unique solution
    4. Randomly choose one value to delete from the board 
    5. Check to see if this value has already been erased before
    6. Attempt to delete it
        8. If it would have a unique solution, then change the number to zero
        9. Else, put back the original number
10. Print the final puzzle to stdout
11. Exit with zero status
```

This is done with two main functions:
```c
// Builds a sudoku using random numbers
// where for the original, the level is 1
void sudoku_build(int sudoku[9][9], int level);

// Takes the sudoku and makes a puzzle by removing 40 numbers
// It deletes random numbers and makes sure that the sudoku has a unique solution
// where for the original, the level is 1
void create_puzzle(int sudoku[9][9], int level);
```

##### Output:
- It will print a randomized sudoku with 40 empty spaces that need to be solved
    - Every time it is called, there will be a unique, random sudoku
    - The grid is represented as 9 lines of text
    - Each line contains 9 integers that range from 0 to 9, separated by a whitespace
    - 0 represents a missing number in the grid

For example:

``` bash
0 0 9 1 4 0 8 0 2
8 0 0 0 5 9 0 0 0
6 4 2 0 0 0 0 9 0
0 8 0 9 7 0 4 1 0
9 6 0 0 8 1 2 5 0
0 7 0 6 0 0 3 8 9
0 3 0 0 1 0 9 0 8
5 0 4 8 0 0 1 0 0
0 0 8 3 6 2 0 0 5
```

#### 'Sudoku Solve' description
The documents `solve.h` and `solve.c` are called by `sudoku.c` when the following command line is asked to execute:
``` bash
./sudoku solve
```
This command line, calls the program `solve()` in `solve.c` which will:
```
1. Take a parsed sudoku matrix and 
2. Call a recursive sudoku solver on solution to complete the grid, where current square is set to the first one
3. If all squares have been visited 
    4. Return false
5. Else for every square that has not been visited starting from current square
    6. For every number in range [1, 9]
        7. If the number is a valid entry at current square
            8. Call recursive sudoke solver, where current square is set to the next square after current
            9. If it returns true
                10. return true (found a solution that works)
            11. Else 
                12. Set current entry to empty again
    13. Since no number could complete the sudoku, return false.
```

This is done with two main functions:
```c
/* 
 * Given a sudoku puzzle, copy solution onto solution sudoku, initially with empty   
 * entries, following conventions 
 * where for the original, the level is 1
 */
bool solve(int sudoku[9][9], int solution[9][9], int level);
```

##### Standard Input 
Sudoku solve prompts the user for a puzzle to solve which has certain specifications 
- No repeated numbers in every row
- No repeated numbers in every column
- No repeated numbers in every 3x3 squared region
- A 9x9 grid size

A correct input would look like the following :
``` 
8 0 0 0 1 3 5 0 4 
2 9 0 0 5 7 0 0 0 
0 0 5 0 0 0 7 1 0 
1 2 3 0 0 9 0 5 0 
0 0 4 0 0 0 9 2 1 
5 0 9 1 0 8 6 0 0 
0 0 6 9 0 2 1 8 5 
7 1 0 5 0 4 2 0 9 
0 0 2 3 0 0 4 0 0 
```

After you have finished writting the puzzle and want to solve it, use Control + D. 

##### Output:
- If the stdin is empty or an incorrect puzzle is given, it will print "Error: Sudoku given has incorrect format."
- Otherwise, it will print the solved sudoku into stdout

For example:
``` bash
Solution:
2 5 7 9 3 6 1 4 8
1 9 3 2 8 4 7 6 5
6 4 8 7 5 1 9 2 3
3 6 1 5 7 9 2 8 4
4 8 9 6 2 3 5 7 1
7 2 5 4 1 8 6 3 9
5 1 2 8 4 7 3 9 6
8 3 6 1 9 2 4 5 7
9 7 4 3 6 5 8 1 2
```

#### Common description
The documents `common.h` and `common.c` define the following helper functions

``` c
// Prints out the sudoku in a 9 by 9 grid format
void print_sudoku(int sudoku[9][9]);

// Checks if the entry can be put into the given row and column without making it invalid
// It would be invalid if the row or column or the 3 by 3 square box contains the entry
// where for the original, the level is 1
bool check_entry(int sudoku[9][9], int row, int column, int entry, int level);

// Checks if the entry can be put into a given 3 by 3 square box 
// where for the original, the level is 1
bool check_box(int sudoku[9][9], int diag, int row, int column, int entry, int level); 

// Read a sudoku from a file and add the entries to sudoku matrix
// where for the original, the level is 1
bool parse_sudoku(FILE* fp, int sudoku[9][9], int level);
```

These are used by both `create.c` and `solve.c` to perform all sudoku functions.

### Fuzzgenerator
Only works on the original sudoku puzzle. This function is automatically run by the `make test` in `testing.sh`. However, we thought it would be important to define how it works 

After making an executable, this function can be run by moving into the testing directory and using the following command line:

```bash
./fuzzgenerator filename numSudoku
```

Parameters:
- `filename` where the the sudokus will be saved (if the file already exists, it will be overwritten)
- `numSudoku` how many random sudokus you want generated

This function will iterate over the number of times given (`numSudoku`) and create random sudokus, then afterwards, it will loop over this file and solve all of the sudokus saved.
- Before solving each sudoku, the fuzzgenerator will check if the sudoku created has a unique solution (making sure `create` works correctly)
- After solving each sudoku, the fuzz generatory will check if the solver changed any of the original values (making sure the solution was valid)
- Since we want all of the puzzles to be random, we needed it to sleep for each solution to be different (because of the rand function), causing it to take a little long to run since it sleeps for a second for every iteration

Output:
- print out several random puzzles to `filename` and then will solve all of these puzzles and print them into a file called`filename_solve`. 

Exit values:
- 0 Executed the function succesfully
- 1 Incorrect number of parameters given
- 2 Incorrect numSudoku given 
- 3 Error opening files
- 4 Sudoku created by `create()` does not have a unique solution
- 5 Solver changes an item from the original grid

### Extra credit 
The extra-credit is tested separately to not confuse the original testing. The samurai sudokus (or the hard level) is tested with the same descriptions as the original sudoku, except for the fuzzgenerator. For more imformation, see [testing](extra-credit/testing.sh).

### Output
All errors are logged into standard error.

### Exit Status (for querier)
0: Success, no errors <br/>
1: Wrong arguments/parameters given <br/>
2: Error - sudoku given has incorrect format  <br/>

### Implementation

For more imformation, see [IMPLEMENTATION](IMPLEMENTATION.md)

Our sudoku create, fills an entire 9x9 grid and then erases 40 numbers, constantly checking if it's a unique solution to create a puzzle. 
Our sudoku solver, waits for a stdin sudoku and checks to see if it's valid. If it is, it proceeds to solve it and completes a solution grid. 

The functions use a 2D array, `sudoku[9][9]` where the first index is the row, and the second index is the column. 

### Assumptions
- When given a grid with a zero, the solver assumes it's empty
- `solve` assumes that the sudoku given is valid (you have to parse the sudoku beforehand)
- `create_puzzle` function assumes that the sudoku given is valid (since `sudoku_build` only builds valid sudokus)

### Compilation

To begin the compilation, write `make`. 

### Testing
One of the test, is a fuzzgenerator, which generates several random sudoku and tests them on solve. For this reason, before running the test, make sure to call `make all`. 
    - The function `fuzzgenerator` and its usage is explained in more depth in [TESTING](TESTING.md).

To test, simply `make test`.
For this testing method, the file `testing.sh` is required since it provides the bash script that requires what will be run. 

See `testing.out` for a test that has already been run. 

See [TESTING](TESTING.md) for details of testing and an example test run.
