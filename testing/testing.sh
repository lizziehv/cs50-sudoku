# Testing script for sudoku.c
# Author: Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# Date: May 20, 2020
#
# usage: bash testing.sh

#####################################
# where the solutions will be saved
dir=testing/testdir


echo "#####################################"
echo "Testing incorrect parameters"

# Testing with too many parameters 
./sudoku solve create hello  

# Testing with too few parameters
./sudoku

#Testing with correct number, but incorrect parameter
./sudoku blahblah


### Testing the solver with a grids that have an incorrect format ###
echo
echo "#####################################"
echo "Testing solve on invalid puzzles (should fail)"

#Testing solver with grid with too few rows
echo
echo "Too few rows"
cat $dir/few_rows.txt | ./sudoku solve 

#Testing solver with grid with too few col
echo
echo "Too few columns"
cat $dir/few_col.txt | ./sudoku solve 

#Test the solver with a grid with non-unique horizontal rows
echo
echo "Non-unique horizontal rows"
cat $dir/horizontal.txt | ./sudoku solve

#Test the solver with a grid with non-unique vertical rows
echo
echo "Non-unique vertical rows"
cat $dir/vertical.txt | ./sudoku solve

#Test the solver with a grid with non-unique subsections 
echo
echo "Non-unique subsections (3x3 grids)"
cat $dir/section.txt | ./sudoku solve

echo
echo "#####################################"
echo "Testing solve on valid puzzles (should pass)"

#Test the solver with an empty grid
echo 
echo "Empty grid"
cat $dir/empty_grid.txt | ./sudoku solve

#Test the solver with a full grid
echo 
echo "Full grid"
cat $dir/full_grid.txt | ./sudoku solve

# With less than 40 missing numbers 
echo 
echo "Less than 40 missing numbers"
cat $dir/less_than_40.txt | ./sudoku solve 

# With 40 missing numbers
echo 
echo "40 missing numbers" 
./sudoku create | ./sudoku solve 

# With more than 40 missing numbers
echo 
echo "More than 40 missing numbers" 
cat $dir/more_than_40.txt | ./sudoku solve 

# A sudoku with a unique solution
echo 
echo "Unique solution"
cat $dir/uq_sol.txt | ./sudoku solve 

# A sudoku with multiple solutions
echo 
echo "Multiple solutions"
cat $dir/multi_sol.txt | ./sudoku solve 

# Testing known solutions
echo 
echo "#####################################"
echo "Testing for known solutions:"
cat $dir/example1.txt | ./sudoku solve > $dir/example-output-1.txt
echo "Comparing output to known solution..."
diff $dir/example-sol-1.txt $dir/example-output-1.txt

if [ $? -eq 0 ]; then
    echo "Solution is correct."
fi


### These tests for create should succeed ###
### These fuzztests for solve should succeed

echo 
echo "#####################################"
echo "Fuzzgenerator:"
echo "Testing create function: if any solution is incorrect, then the create is incorrect"
echo "(Check files fuzz and fuzz_solved)"

./testing/fuzzgenerator $dir/fuzz 20

# check if the creator and solver where correct
if [ $? -eq 4 ] || [ $? -eq 5 ]
    then 
        if [ $? -eq 4 ]
            then
                echo "ERROR: a sudoku has multiple solutions"
        elif [ $? -eq 5 ]
            then
                echo "ERROR: solver changes original grid"
        fi
else echo "CORRECT: no sudoku has multiple solutions and solver doesn't change original grid"
fi