# CS50 Final Project
## Kshitij Jain, Maria Mora, Ethan Trepka, Lizzie Hernandez Videa
## CS50 Spring 2020

### Testing 'sudoku'

To test our *sudoku* module, we need to test both create.c and solve.c

All these can be tested by running testing.sh by doing ```make test```

Testing.sh makes use of fuzzquery.c





### Test create

Run it using 
```
./sudoku create
```

This should print a sudoku puzzle with a unique solution

Each time, this should give us different sudoku puzzles

Giving more or less parameters gives an error

We can also check if sudoku puzzle created has a unique solution by calling solve on it as done below




### Test solve

Run it using 
```
./sudoku create | ./sudoku solve
cat valid_sudoku_puzzle | ./sudoku solve
```

This should print a solved sudoku puzzle

This will also work if the given sudoku has multiple solutions but will give only one solution

Will give an error for an unsolvable sudoku or an invalid sudoku

Giving more or less parameters gives an error
