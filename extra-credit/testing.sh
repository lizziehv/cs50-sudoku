# Testing script for extra credit sudoku
# Author: Maria Paula Mora, Lizzie Hernandez, Ethan Trepka, and Kshitij Jain 
# Date: May 20, 2020
#
# usage: bash testing.sh

#####################################
# where the solutions will be saved
dir=testdir


echo "#####################################"
echo "Testing incorrect parameters"

# Testing with too many parameters 
../sudoku create bla bla 

#Testing with correct number, but incorrect parameter
../sudoku create bla 


### Testing the solver with a grids that have an incorrect format ###
echo
echo "#####################################"
echo "Testing solve on invalid puzzles (should fail)"

#Testing solver with grid with too few rows
echo
echo "Too few rows"
cat $dir/few_rows.txt | ../sudoku solve hard

#Testing solver with grid with too few col
echo
echo "Too few columns"
cat $dir/few_col.txt | ../sudoku solve hard

#Test the solver with a grid with non-unique horizontal rows
echo
echo "Non-unique horizontal rows"
cat $dir/horizontal.txt | ../sudoku solve hard

#Test the solver with a grid with non-unique vertical rows
echo
echo "Non-unique vertical rows"
cat $dir/vertical.txt | ../sudoku solve hard

#Test the solver with a grid with non-unique subsections 
echo
echo "Non-unique subsections (3x3 grids)"
cat $dir/section.txt | ../sudoku solve hard

echo
echo "#####################################"
echo "Testing solve on valid puzzles (should pass)"

#Test the solver with an empty grid
echo 
echo "Empty grid"
cat $dir/empty_grid.txt | ../sudoku solve hard

#Test the solver with a full grid
echo 
echo "Full grid"
cat $dir/full_grid.txt | ../sudoku solve hard

# Testing known solutions
echo 
echo "#####################################"
echo "Testing for known solutions:"
cat $dir/example1.txt | ../sudoku solve hard > $dir/example-output-1.txt
echo "Comparing output to known solution..."
diff $dir/example-sol-1.txt $dir/example-output-1.txt

if [ $? -eq 0 ]; then
    echo "Solution is correct."
fi