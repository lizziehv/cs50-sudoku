# Testing script for querier.c
# Author: Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# Date: May 20, 2020
#
# usage: bash -v testing.sh
filename=create_output
direrct=solve/testdir
#####################################

### These tests for sudoku should fail ###
#Testing with too many parameters 
./sudoku solve create 

#Testing with too few parameters
./sudoku

#Testing with correct number, but incorrect parameter
./sudoku blahblah



### These tests for solve should fail ###

#Testing solver with grid with too few rows/cols
cat $direct/few_rows.txt | ./sudoku solve 

#Test the solver with grid with no solution 
cat $direct/no_sol.txt | ./sudoku solve

#Test the solver with an empty grid 
cat $direct/empty_grid.txt | ./sudoku solve



### These tests for solve should succeed ###

# With less than 40 missing numbers 
cat $direct/less_than_forty.txt | ./sudoku solve 

# With 40 missing numbers 
./sudoku create | ./sudoku solve 

# With more than 40 missing numbers 
cat $direct/example-2 | ./sudoku solve 

# A sudoku with a unique solution
cat $direct/uq_sol.txt | ./sudoku solve 

# A sudoku with multiple solutions
cat $direct/multi_sol.txt | ./sudoku solve 



### These tests for create should succeed ###

#Testing piping different create output into solve multiple times 
for i in 1 2 3 4 5 6 7 8 9 10
do
./sudoku create | ./sudoku solve 
done
#Testing piping create output 
./sudokou create > $filename

#Testing solve on that output multiple times - should be the same every time 
for i in 1 2 3 4 5
do
cat $filename | ./sudoku solve 
done


### These fuzztests for solve should succeed ###
#insert fuzztesting bash stuff here
