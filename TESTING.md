# CS50 Final Project
## Kshitij Jain, Maria Mora, Ethan Trepka, Lizzie Hernandez Videa
## CS50 Spring 2020

### Testing 'sudoku'
All necessary testing files are inside a directory called testing 
To test our *sudoku* module, we need to test both `create.c` and `solve.c`

### Testing the create function
This function can be run using 
``` bash
./sudoku create
```

This should print a sudoku puzzle with a unique solution
- Each time, this should give us different sudoku puzzles
- Giving more or less parameters to the command line gives an error
- We can also check if sudoku puzzle created has a unique solution by calling solve on it as done below

### Testing the solve create function
This function can be run using 
``` bash
# asks for a sudoku on the stdin
./sudoku solve

# will create a sudoku and pipe it to solve it
./sudoku create | ./sudoku solve

# giving it a valid file name that contains a sudoku puzzle
cat valid_sudoku_puzzle | ./sudoku solve
```

This should print a solved sudoku puzzle
- This will also work if the given sudoku has multiple solutions but will print out only one solution
- Will give an error for an unsolvable sudoku or an invalid sudoku
- Giving more or less parameters gives an error

### Fuzzgenerator
This function is automatically run by the `make test` in `testing.sh`. However, we thought it would be important to defin how it works 

After making an executable, this function can be run by moving into the testing directory and using the following command line:

```bash
./fuzzgenerator filename numSudoku
```

This function will print out several random puzzles to `filename` and then will solve all of these puzzles and print them into a file called`filename_solve`. 

A more in depth description is found in 

### Test file explanation
`testing.sh` was written to be able to see the progress of `sudoku.c`. In order to cover all basis, we split this test in four parts:
1. Testing incorrect parameters 
    - Less or more than 4 arguments are given 
	- Incorrect parameters (a word that is not "create" or "solve")

2. Testing the solver with a grid that has an incorrect format
	- Incomplete grid (less number of rows/less number of columns)
	- Horizontal row is not unique
	- Vertical row is not unique
	- 3x3 subsections are not unique

3. Testing correct formats on solver to see it's reaction
    - A grid with no missing numbers
    - Test the solver with an empty grid
    - A grid with multiple solutions
    - A grid with one solution
	- With less than 40 missing numbers 
	- With 40 missing numbers 
	- With more than 40 missing numbers 

4. Fuzzgenerator to test the solver on several random sudokus
    - Will generate any given number of sudokus and solve them 
	- Before solving each sudoku, the fuzzgenerator will check if the sudoku created has a unique solution (making sure `create` works correctly)
	- After solving each sudoku, the fuzz generatory will check if the solver changed any of the original values (making sure the solution was valid)

### Test run
To test, write `make all` (not make because `fuzzgenerator` is needed to be able to run the test). After the sudoku and fuzzgenerator executable files are made, then you can run the test options. 

An example test run is in `testing.out`, built with

	make test &> testing.out

In that file one can see the results of all of the explanations mentioned above. 

### Limitations
For `sudoku.c`, the code assumes that the sudoku given has numbers 1-9 and that any zero is a missing value. For this reason, if given a different type of sudoku where 0 are numbers, it will proceed to solve them instead of considering them as numbers