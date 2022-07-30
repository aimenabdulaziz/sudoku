# Testing plan

To run automated test cases, simply execute `make test`. The testing script will take care of compiling the required executables. Feel free to redirect the output to your desired path. You can run `make test &> path`, where `path` is your desired location. 

Note: we have included 1 second delay between each iteration in the testing script while generating automated. This allow us to generate different Sudokus each time as `srand` depends on time.

*Integration testing* for Sudoku

1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.
2. Test both programs by randomly generating a sudoku with the creator, saving it to a file, and later redirecting the file to solver
3. Test for memory leaks with valgrind

*Unit testing* for the solver and creator
We have included `unit testing` for our `solve` and `create` modules. The unit testing logs can be printed by uncommenting `CREATE_TEST` and/or `SOLVE_TEST` in the `Makefile` accordingly. The run `make all` or `make program`, where `program` is your preferred choice.

The unit test include:
1. Test the solver with an invalid sudoku (one with invalid entries)
2. Test the solver with a sudoku with multiple solutions
3. Generate a random sudoku with the creator

Additionally, the unit tests included tests for all the other methods in the modules 

*Fuzz testing* for Sudoku
We performed fuzz testing for our sudoku using `fuzzSudoku`. It is run with a number n as its argument, and it
1. Generates n sudokus with createSudoku
2. For each such sudoku, it solves it and confirms that it has a unique solution
3. For each solution, it confirms that none of the cells that were filled in the original sudoku have been changed.
