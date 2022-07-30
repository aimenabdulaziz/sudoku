# Sudoku Design Spec

The Sudoku puzzle is presented as a 9x9 valid grid with some numbers missing. A person or program solving the Sudoku puzzle should fill in the missing numbers without violating the certain rules.

In a valid Sudoku grid every number from 1 to 9 must appear:
- Only once in every row
- Only once in every column
- Only once in every 3x3 squared region

The sudoku program offers two functions depending on its argument. If the argument is `create`, then it creates a valid sudoku with a unique solution with at least 40 missing numbers, and prints this to `stdout`. If the argument is `solve`, then it solves the sudoku puzzle inputed by the user and prints the solution to `stdin`.
 
### User interface

The sudoku's interface with the user is on the command line; it must always have one argument, which can be either "create" or "solve". If the argument is "solve", then the program reads the puzzle to be solved from `stdin`.

Create a sudoku
```
./sudoku create
```

Solve a sudoku
```
./sudoku solve
```
 
For example:

``` bash
$ ./sudoku create
```

and

``` bash
$ ./sudoku solve 
```

### Inputs and outputs

#### Representing a Sudoku
As both input in `stdin` for solving a sudoku and output for a created or solved sudoku, the sudoku is represented in this way:
1. The grid is represented as 9 lines of text
2. Each line contains 9 integers that range from 0 to 9, separated by a white space
3. 0 represents a missing number in the grid
 
#### Input
1. the command line argument
2. if the command line argument is "solve", the sudoku puzzle to be solved from `stdin`
 
#### Output:
1. If the command line argument is "create", then the newly created sudoku is printed to `stdout`
2. If the command line argument is "solve", then then the solution to the sudoku puzzle is printed to `stdout`
 
### Functional decomposition into modules
 
We anticipate the following modules or functions for sudoku:

1. *main* which validates and parses the command line argument, and calls *sudokuCreate* or *solveSudoku* depending on the argument parsed.
2. *loadSudoku* which reads input from `stdin` and creates a two dimensional 9 by 9 array where each position reflects the number on the board at that spot (if there is no number the value will be 0). This function will prompt the user to input the sudoku meant to be solved, one row at a time. Before being inserted, it will check if each number is a valid input by using the *validEntry* function.
3. *validEntry* which is used each time a number wants to be added, either when first loading the sudoku, or when solving it. A valid entry is one where the number being inputted is not already present on the row, column, or box of the number’s position. It will return a false Boolean if the number is present in either list.
4. *solveSudoku* which solves the sudoku using recursion and backtracking. It selects the first empty cell from the 2D array and sequentially tries to fill it starting from 1 and going up to 9. For each number tried, it first checks the number with *validEntry*, then recursively tries to solve the rest of the puzzle. If at any cell there is no number between 1 and 9 that is valid, then a wrong number must have been chosen at some point during the recursion and false is returned. The function then backtracks to the last cell filled and continues. The function also keeps track of how many solutions it has found. When it finds at least two solutions, it stops and returns true; otherwise it snapshots the first solution and backtracks to try and find a second one
5. *createSudoku* fills an empty 2D array with between 17 and 41 random numbers, checking that each entry is valid. It then tries to solve it with *solveSudoku* to ensure that it has at most and at least one solution
6. *printSudoku* which prints out the newly generated or a solved sudoku puzzle
 
### Pseudo code for logic/algorithmic flow

Sudoku will run as follows:

1. Execute from command line as shown in the User Interface
2. Parse the command line argument, validate parameters
3. If the argument is "solve", then it reads the puzzle from `stdin`, which is in the format described above, and creates a 2D array
4. It iterates over each cell in the 2D array, until it finds a cell which contains 0, which indicates that the cell is empty
5. It sequentially tries to fill the cell with numbers, starting from 1 and going up to 9, checking that the number is a valid entry, that is, that the number does not occur in the current row, column, or box
6. If the number is a valid entry, it recursively tries to solve the rest of the puzzle. The recursion contains a base case where it returns false: when all numbers between 1 and 9 have been tried. If this base case occurs, the current cell being filled is reset to 0, and the program backtracks and tries to fill the previous cell with another number
7. At the end of the recursive function, it returns true because this means all empty cells have been filled with valid inputs
8. The recursion keeps track of how many solutions have been found by incrementing a count each time we reach a "terminal situation", which is when all cells in the sudoku have been filled. At this point, it snapshots the current solution, and backtracks to the previous cell to try another number, stopping when two solutions have been found, there is no number left to try for a cell, or all possible combinations have been tried.
9. The final return value of the recursive function is only true when the input sudoku has two or more solutions. We therefore use the count of solutions to determine uniqueness and solvability. The final solution value is also the most recent solution reached before the function terminates.
10. The solved sudoku is printed to `stdout`
11. If the argument is "create", then it randomly creates a sudoku puzzle by filling a 2D array with between 17 and 41 random numbers, checking that each entry is valid. It then tries to solve it to check that it has at most and at least one solution
12. The newly created sudoku is printed to `stdout`

Sudoku completes and exits after the solving or creation is complete.
 
### Dataflow through modules

1. *main* parses parameters and calls *loadSudoku* to read the sudoku from stdin and passes it to *solveSudoku* if the first parameter is "solve". It calls *createSudoku* if the first parameter is "create". It prints the solved or created sudoku with *printSudoku*
2. *loadSudoku* reads the sudoku from `stdin` into a 2D array
3. *solveSudoku* takes a sudoku, validates it with *validEntry* for each cell, and solves it
4. *validEntry* returns a Boolean, false if the number already exists in either the row, column, or box, and true if not
6. *createSudoku* creates a new sudoku, then calls *solveSudoku* to ensure that it has at most and at least one solution
7. *printSudoku* prints a sudoku as described in representing a sudoku
 
### Major data structures

The major data structure is the structure we use to represent the sudoku, which is a 2D array, that is, an array of array of numbers, *int[]/[]*
 
### Testing plan

*Integration testing* for Sudoku

1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.
2. Test both programs by randomly generating a sudoku with the creator and inputting the result onto solver
3. Test for memory leaks with valgrind

*Fuzz testing* for Sudoku
1. Create n puzzles, where n is a command line argument, and test the solver with them, checking that solver generates a valid solution and doesn't change already filled cells in the grids
2. Test that each puzzle created by the creator has a unique solution

*Unit testing* for the solver and creator
1. Test the solver with a a sudoku of the wrong size in `stdin`
2. Test the solver with an invalid sudoku (one with invalid entries)
3. Test the solver with a sudoku with multiple solutions
