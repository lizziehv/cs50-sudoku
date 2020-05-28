---
written by: Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain
layout: page
title: Sudoku Design Spec
---

# Sudoku Design Spec
Following the Sudoku Requirements spec Instructions in the webpage https://www.cs.dartmouth.edu/~cs50/Project, the **create** directory should take care a Sudoku puzzle with a unique solution, while the **solve** directory should take care of solving any Sudoku puzzle given to it..

### User interface

The Sudoku modules’ only interface with the user is on the command-line; the ** create** directory will run with the command:
```
$ ./sudoku create
```
Similarly, the **solve** directory will run with the following command:
```
$ ./sudoku solve
```

### Inputs and outputs

#### Input:   

`./sudoku create` requires no inputs

`./sudoku solve` takes a sudoku grid as a `board`

A board is defined as:
* The grid is represented as 9 lines of text
* Each line contains 9 integers that range from 0 to 9, separated by a whitespace
* 0 represents a missing number in the grid

#### Output: 

`./sudoku create` outputs an unsolved sudoku `board` (same structure as the one mentioned above) that is missing at least 40 elements (meaning there are forty ‘0’ present in the grid.

`./sudoku solve` outputs a solved sudoku `board` 

### Functional decomposition into modules

We anticipate the following modules or functions:

#### Create module
 1. *sudoku_build(sudoku)* builds a sudoku with the specifications mentioned above
 2. *create_puzzle(sudoku)* edits the sudoku by adding the zeros in to create a puzzle, calls *check_unique_solution(sudoku)* to see if the zeros added are correct
 3. *check_unique_solution(sudoku)* checks to see if the sudoku that was build has a unique solution

#### Solve module
 1. *solve(sudoku)*, given a struct with the loaded puzzle, it solves and returns the solved struct
 2. *check_valid(sudoku)*, checks if the given puzzle is valid

#### Common library
 1. *sudoku_print(sudoku)*, which prints a given sudoku puzzle to the command line with 0s for empty squares
 2. *parse_sudoku(file)*, which reads a puzzle from a file and creates a data structure for the 9x9 grid
 3. *check_entry(sudoku, row, column, entry)* checks to see if a given entry is added in that specific row or column is valid (row, column, and square)

And some helper modules that provide data structures:
 1. *set* maps from a sudoku squares specified by (i,j) pairs to possible numbers that could go in those squares

### Pseudocode for logic/algorithmic flow
#### create pseudocode
1. Create a 9x9 sudoku board with random (unique in row, column, subgrid) numbers and store it in a 2D array
2. For 40 iterations
	3. Do the following
		4. On each iteration, randomly choose one value to delete from the board 
		5. Create a set to hold the number of possible elements that could go in that square that is not the value we deleted
		6. For each element in the set 
			7. Put the element in the sudoku board at our current square
			8. Solve the sudoku board and set a boolean to true if there is a solution
		9. if boolean from line 7 is true 
			10. put the original number back into our current square
		11. else
			12. put zero into our current square 
	13. while (boolean from line 7 is true)

#### solve pseudocode 
1. If all squares have been visited, return true
2. Else, for every square in the puzzle that has not been visited yet
	3. If the square has not been filled
		4. for every value from 1-9
			5. if adding the value at this square would be valid (unique in row, square, column)
				6. return value = recurse with a new sudoku (skipping squares that have already been checked) with the value at this square
				7. if return value is true, return true
		8. return false

### Dataflow through modules
create.c
 1. *main*, parses parameters (uses common library) 
 3. *sudoku_build(sudoku)* builds a sudoku with the specifications mentioned above, calls `create puzzle`
 4. *create_puzzle(sudoku)* edits the sudoku by adding the zeros in to create a puzzle, calls *check_unique_solution(sudoku)* to see if the zeros added are correct
 5. *check_unique_solution(sudoku)* checks to see if the sudoku that was build has a unique solution
 6. *sudoku_print(sudoku, file)*, which prints the puzzle to the command line with 0s for empty squares

solve.c
1. *main* Loads the sudoku puzzle into a struct, checks if the puzzle is valid, calls ```solve``` to solve the puzzle and then prints the solved puzzle
2. *solve(sudoku)*, given a struct with the loaded puzzle, it solves and returns the solved struct
3. *check_valid(sudoku)*, Given the struct with the puzzle, it checks if the puzzle is valid
4. *sudoku_print(sudoku, file)*, which prints the solution to the command line with 0s for empty squares

### Major data structures

We use an array of array of integers to hold the numbers for our sudoku puzzle.

### Testing plan

*Unit testing*.  A small test program in `testing.sh` to test each module to make sure it does what it's supposed to do.

*Integration testing*.  Assemble the sudoku and test it as a whole using `testing.sh`.
In each case, examine the output files carefully to be sure they have the correct representation of the index data structure. 

*Fuzz testing*. Utilize fuzz testing to test several random grids on the solver to see if they are solved correctly (meaning unique vertical/horizontal rows and 3x3 grids)

#### Incorrect Inputs
- Test the solver with a grid that has the an incorrect format
	- Incomplete grid (less number of rows/less number of columns)
	- Horizontal row is not unique
	- Vertical row is not unique
	- 3x3 subsections are not unique
- Test the solver with a grid that has no solution
- Test the solver with an empty grid

#### Correct Inputs
- Test the solver with a correct grid
	- With less than 40 missing numbers 
	- With 40 missing numbers 
	- With more than 40 missing numbers 
	- A sudoku with a unique solution
	- A sudoku with multiple solutions
