# Testing plan

To run automated test cases, simply execute `make test`. The testing script will take care of compiling the required executables. Feel free to redirect the output to your desired path. You can run `make test &> path`, where `path` is your desired location. 

Note: we have included a one second delay between each iteration in the testing script while generating a random sudoku and saving it in the specified location. This allows us to generate different sudoku puzzles each time as `srand` depends on time.

## Integration Test
1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing and validation of those parameters works correctly.
2. Test both the solver and creator by randomly generating a unique sudoku using the **sudoku creator**, saving the generated puzzle to a file, and later redirecting the file to the solver.
3. Test for memory leaks with valgrind

## Unit Test
We have included a unit test for our `solve` and `create` modules. The unit testing logs can be printed by uncommenting `SOLVE_TEST` and/or `CREATE_TEST` in the `Makefile`. Then run `make all` or `make program` in the command line, where `program` is your preferred choice. Afterwards, run `./solve` or `./create` to view the unittesting logs.

The unit test for solver include:
1. Test with an invalid sudoku (one with invalid entries)
2. Test with a sudoku with that has multiple solutions
3. Test with a sudoku that has unique solution

The unit test for creator include generate a random sudoku puzzle that has a unique solution

## Fuzz Test
We performed fuzz testing for our sudoku using `fuzzSudoku`. It is run with a number n as its argument, and it
1. Generates n sudokus with createSudoku
2. For each such sudoku, it solves it and confirms that it has a unique solution
3. For each solution, it confirms that none of the cells that were filled in the original sudoku have been changed.