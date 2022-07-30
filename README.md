# CS50 Spring 2022, Sudoku

## Koding Kegs
Aimen Abdulaziz -> aimenabdulaziz

Chibuzo Chiwike -> hack-heart

Cristian Antonio-Santiago -> Cristian Antonio-Santiago

Dara Casey -> caseydara

Sudoku is a standalone program that can be called with two commands. If the command is `create`, then it creates a random sudoku with between 25 and 40 filled cells. If the command is `solve`, then it reads a sudoku from `stdin` and prints the solution to `stdout`, along with a message that contains the number of solutions.

## Usage
`./sudoku command` where command is `solve` or `create`

## Assumptions
Specific assumptions are included in the file headings, but here are a few.
1. sudoku board is 9 * 9
2. each cell in the board is a digit 0-9
3. value of 0 means a missing number

### Textual Representation of the Sudoku
This is an example of how the sudoku is printed. This is for better visibility
```
0 0 0  7 0 0  0 5 0  
0 0 1  5 4 0  3 8 0  
2 3 0  9 0 8  7 0 0  

6 9 8  0 7 5  2 3 1  
4 5 7  0 1 0  8 0 6  
0 2 0  0 0 0  0 4 7  

0 0 0  0 0 0  0 0 0  
0 8 4  0 0 6  9 0 5  
9 1 2  3 0 7  0 0 8  
```

For reading from `stdin`, our program allows a varying number of spaces between digits. The format above is parsable by our reader, but so is this format, for example
```
0 0 0 7 0 0 0 5 0  
0 0 1 5 4 0 3 8 0  
2 3 0 9 0 8 7 0 0  
6 9 8 0 7 5 2 3 1  
4 5 7 0 1 0 8 0 6  
0 2 0 0 0 0 0 4 7  
0 0 0 0 0 0 0 0 0  
0 8 4 0 0 6 9 0 5  
9 1 2 3 0 7 0 0 8 
```

The reader for `Sudoku Solver` is dynamic. It can read files in any format (with spaces, without spaces, one row at a time, one number at a time).


## Compilation
To compile `sudoku`, `fuzzSudoku`, `create`, or `solve`, run `make` or `make all`.

To compile only one program, run `make program`, where program is the name of the program.

Run tests with `make test`. See `TESTING.md` for more details.

To test `sudoku` valgrind, run `make valgrind`. We have added a test case in the `Makefile`, but feel free to modify that and test with your preferred test case.

To clean all the files created during compilation and testing, run `make clean`.

## Extra credit
A GUI that shows how our algorithm runs by showing the state of the board. Written in python.

## Notes
- The `tests` folder contains files needed to run the test script.
- The sudoku-gui folder contains python code for displaying a GUI. See that folder's README for more.
