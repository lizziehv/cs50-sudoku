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
- If the sudoku 

#### Sudoku creator

- For every character in the query
    - Go to next alpahbetic character
    - Insert that character pointer to array of words
    - Skip all alphabetic characters and go to the first space seen
    - Make the space a null character

Satisfy query runs as follows: 

- For every and sequence in the query
    - Initialize a counters structure to hold the intersection of the counters set in this sequence -> res_and
    - For every word in the and sequence
        - find the counters set in the index corresponding to the word
        - if the word's counters set exist
            - Find the intersection of the current res_and the words's counters set by ...
            - Iterating through the current res_and and adding every key, item pair to the word's counters with lesser values (0 if not contained in counters)
            - Iterate through the counter set and adding every key, item pair to res_and with lesser values (0 if not contained in res_and)
            - Now that res_and contains all the keys in both counters so that the value of a key is 0 if it is not in either of them, move all keys with a non-zero value to a new intersection and update res_and to point to this new intersection.
        - else, if the counters set does not exist
            - Since the intersection of the counters set in this sequence will empty, move to the next sequence and break from this
    - Clean up structure used (res_and)
    - Find union between current result and res_and and update result to be this nrw union

Print query runs as follows:

- Find the size of the result counters set by iterating through counters
- If size is 0, report documents found
- Else
    - Initialize an array of tuples of size
    - For every key, count pair in the result counter set
        - create a tuple holding (key, count) --> "current"
        - insert current at the end of the array
        - For every tuple already in the array --> "other"
            - If other has lower score
                - move lower to right and current to the left
    - For every tuple in the array
        - Find the url by accessing the document from the directory
        - Print score, document ID, and url





```c
/* @param char *line
 * 
 * Count the number of words in a line for size of word array
 * 
 * @return number of words in line
 */
int word_counter(char *line);

/* @param char *line - pointer to line to be divided
 * @param char *words[] - array of strings (empty)
 * @param int count - number of words in string array
 * 
 * Function to divide query line into an arrray of words
 * 
 * @return void
 */ 
void divide_query(char *line, char *words[], int count);

/* @param char *words[] - array of strings (empty)
 * @param int count - number of words in string array
 * 
 * Normalize each word in words
 * Output query
 * Check if the format is valid
 * <and sequence> or <and sequence> etc.
 * 
 * @return false if a word contains a non alphabetic character or
 *         format is invalid: consecutive ANDs, ORs, or query starts
 *         with AND, OR
 * @return true if success (valid format ans)
 */ 
bool parse_query(char *words[], int count);

/* @param result - empty counters set to insert query results
 * @param index - inverted-index structure
 * @param words - array of strings containing words
 * @param count - number of words
 * 
 * Find query results by merging and_sequences results
 * 
 * @return false if any error initializing structures
 * @return true if success
 */ 
bool query(counters_t* result, hashtable_t *index, char *words[], int count);

/* Helper function for query()
 * 
 * @param result - empty counters set to insert query results
 * @param index - inverted-index structure
 * @param words - array of strings containing words
 * @param count - number of words
 * @param current - index in words where current index was found
 * 
 * Function will find the intersection of all words in a sequence
 * Update current index to point to the beginning of the next sequence
 * 
 * @return pointer to counters containing intersection
 *         NULL for any error
 */ 
static counters_t * resolve_sequence(hashtable_t *index, char *words[], int count, int* current);

/* @param result - counters with results from query
 * @param page_dir - crawler produced directory where pages come from 
 * 
 * Print results to stdout. Pages ranked with format
 * score <score> doc <doc>: <url>
 * 
 */ 
void print_results(counters_t* result, char* page_dir);
```

See ../common/README.md for definition of functions in *pagedir.c* and *words.c*.

### Memory allocation in C and modules used

1. The cleanup is done by deleting the hashtable index and the counters inside it.

2. Note that there is no tuple_delete function because free(tuple) will work instead. 

3. A new counter set is initialized and deleted for every query.

### Error handling

* The querier will return a non zero exit status on any usage error or on any error allocating memory for structures.

* The querier will assume that if the directory given contains a crawler file, then it is a crawler produced directory, and that the index provided is a valid indexer produced index.

* The querier will ignore a query containing non-white-space or non-alphabetic characters


### Files required

The directory provided must be a crawler produced directory and must follow these conventions:
* File names are consecutive numbers starting from 1.
* Each file must have the following format : url + \n + depth + \n + html
The index provided must be an indexer produced index and follow the following conventions:
* One word per line with space-separated docID, occurrences 