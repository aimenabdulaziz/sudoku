# Sudoku Implementation Spec

When running the main function of sudoku, the following will happen:

The program will first read if the user wants to solve or create a sudoku puzzle. If the user inputted `create`, then `createSudoku()` will be ran and a new random sudoku puzzle will be inputted onto the console. If the user inputted `solve`, then `handleSolve()` is repeately called until a full sudoku is given.

The functions used to create a sudoku are similar when solving one, so we will first explain how we solve a sudoku.
When `handleSolve()` is called the following occurs:
1. A 2D array is initialized to hold the whole sudoku and each number is initialized as 0 to represent blank spaces. 
2. The function `prompt()` is called to tell the user to enter a sudoku if no file holding as sudoku has been piped to the function.
3. Next a while look continously calls the user to input characters from standard input in order for us to save it in the sudoku
    * If it's a space, we simply ignore it and move to the next character
    * If it's a number, we convert it to an integer and insert it into it's appropriate location on the 2D array, once all 81 slots are full we know we have a complete sudoku input.
    * If the character received is not a space or a number, it will state that there was an invalid entry
4. Once this sudoku is made `printResult()` is passed which solves and prints the results.

The function `printResult()` can be found in the solve.h file. It works as follows:
1. A 2D 9 by 9 Sudoku array is received and is passed onto `solveSudoku()` which will return the amount of solutions the sudoku has.
2. If it has more than 1 solution, it will use `printSudoku()` to print out the 9x9 array, and state that it has multiple solutions. It again will print out 9x9 grid if there is just one solution. If no solution was found then it will also say so.

The function `prompt()` is used to print a message onto the console, it works as follows
1. It checks using `isatty()` if the input being recieved is from a file or from standard input. If it wasn't from a file, it will give a simple "Enter your sudoku" prompt.

The function `normalizeWord()` is the same as we used in query. It simply looks over all the characters in a string and makes them lowercase. This is used to normalize the command given to ./sudoku. 

The `solveSudoku()` function is also found in the solve.h file. It works as follows:
1. It first make's sure that the sudoku being passed is a valid puzzle using `validSudoku()`. If it's not valid it won't continue.
2. Next `solveSudokuHelper()` is employed to actually solve the sudoku and to also return the amount of solutions it has.

It's important to make sure that the sudoku being passed is actually even valid, if not no solutions would even be possible. This is done with `validSudoku()` found in solve.h which does the following:
1. An empty 9x9 array is initialized. The sudoku that was passed is looped over each position
2. For each position, the number is copied and attempted to be added into the previously initialized empty sudoku. Before being added, `validEntry()` is called to make sure that that number isn't violating rules. 
3. If the number being copied from the original sudoku and checked to be added to the new sudoku violates a rule, then it means the original sudoku wasn't valid from the first place and will return false. If all 81 positions are checked and the numbers added to the new sudoku, then it means the original was valid from the first place and will return true.

To check if a number being inputted doesn't violate the rules of sudoku, `validEntry()` found in solve.h is passed which does the following:
1. It receives the sudoku, positioning, and number that is trying to be added
2. With this it checks the row, column, and 3x3 it is in. If the number trying to be added isn't already there then it returns true. If any number is found as a duplicate of it, then it will return false.

The `solveSudokuHelper()` found in solve.c helper function works as follows:
1. Recursion is used to solve this problem. To make sure that there are still empty slots to solve, we loop through the whole 9x9 array until we find an empty cell and start from there.
2. If there were no empty cells, we have found a solution and increment count by 1 to represent the fact that a solution was found. This helps us track to see if a sudoku has a unique solution. 
3. Once we make sure that the location we are in has a 0, we try to input every number systematically using a for loop.
    * Before adding it onto the sudoku, we make sure that it is a valid entry using the `validEntry()` method. We check to see if adding this number solved the puzzle by running `solveSudokuHelper()`. If a previous solution was found and this one also made a solution, then we stop looking for more possibilities. We don't keep looking for more additional answers, our only goal was to make sure that the sudoku is unique.
    * If it didn't complete complete it, a zero is added back again and later the next number is checked. 

The `printSudoku()` function found in solve.h is used to print out the solved sudoku 9x9 grid onto the console. It works as follows:
1. The sudoku is looped over, starting from the top left corner and moving rightward. Each number is printed onto the console until all 81 numbers are printed. We format with spaces depeding on the location of the number.

To create a random sudoku with 1 unique solution, the `createSudoku()` function is passed which is found in `createSudoku()`. It works as follows:
1. To make sure we generate a random sudoku, 10 random numbers are placed in an empty sudoku.
    *  While 10 numbers haven't been placed yet, we make sure that the random location we had generated holds no number.
    * If it doesn't we generate a random number from 1 to 9 and see if it breaks no rules using `validEntry()`. If it holds we will add it.
    * If there was already a number in that position, we generate a new random 9x9 position and try that one.
2. Once we have a sudoku holding 10 valid randomly generated numbers, we move on and try to solve it using `solveSudoku()`. We take advantage that it will also return 2 if there are more than 1 solutions, making this a non-unique puzzle. If the count did return 2, then we try to genereate a new puzzle again usin `createSudoku()`.
3. If this puzzle did only have one solution, we start to remove numbers from the solution. As long as we still have numbers to delete, a random position will be generated.
    * If this position doesn't hold a 0, then we will try to remove the number.
    * We want to make sure that by deleting this number that we won't get a puzzle that now has two solutions. This is solved by copying the solved puzzle with an additional number removed, and passing this copy onto `solveSudoku()`, again taking advantage of the fact that it will return 2 if it has more than one solution.
        * If this returned as 1, then we are good and can continue removing numbers. 
        * If this returned as a 2, then we add the number back to the solution sudoku and try to remove another random number. The difficulty here is that it may be possible that removing any number will naturally create a new path to generate a new solution. If we try to remove another number 20 times and it keeps resulting in a puzzle with more than 1 answer, then we will stop searching to remove. 

4. Once we removed the specified amount of numbers, we print it using `printSudoku()` and state how many solutions it has. 
