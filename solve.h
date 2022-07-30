/*
 * solve.h - utility functions for solving and printing a sudoku
 * 
 * Koding Kegs, Spring 2022
 */

#ifndef __SOLVE_H
#define __SOLVE_H

#include <stdio.h>
#include <stdbool.h>
#define SIZE 9 // size of the Sudoku board

/**************** validEntry ****************/
/* Validate the row, columns, and 3*3 sub-boxes don't violate the specs 
 * 
 * Caller provides:
 *      valid sudoku board of 9 by 9, row, column, num (for checking)
 * 
 * We return:
 *      true if num doesn't violate any of the row, column and 3*3 sub-box rules
 *      false if num violates any/either/all of the three rules
 */ 
bool validEntry(int sudoku[SIZE][SIZE], int row, int col, int num);

/**************** validSudoku ****************/
/* Validate a sudoku board
 *
 * Caller provides:
 *      sudoku board of 9 by 9
 * 
 * We return:
 *      true if every cell in the sudoku keeps to the row, column,
 *          and 3*3 box rules
 *      false otherwise
 */
bool validSudoku(int sudoku[SIZE][SIZE]);

/**************** printSudoku ****************/
/* Prints a sudoku board to the provided fp in the format specified below
 *
 * Caller is provides:  
 *      a sudoku board of 9 by 9 and fp
 * 
 * We print the sudoku board in the provided fp in following format:
 *      add white space between every number
 *      add another white space in every three numbers within the columns
 *          to easily identify 3*3 sub-boxes
 *      add new line between each rows
 *      add another new line in every three rows to easily identify
 *          3*3 sub-boxes
 */
void printSudoku(int sudoku[SIZE][SIZE]);

/**************** solveSudoku ****************/
/* Solves the sudoku board using recursion and backtracking
 * 
 * If we are solving the sudoku to create a unique solution, 
 *      we won't modify the original sudoku.
 * 
 * We return:
 *      2, if the passed sudoku has two or more solutions
 *      1, if the passed sudoku has one solution
 *      0, if the passed sudoku does not have any solutions
 * 
 * Caller is responsible for:
 *      later calling printSudoku to print the solved sudoku on the terminal
 * 
 * @size - number of elements in each row and column 
 */
int solveSudoku(int sudoku[SIZE][SIZE], int solution[SIZE][SIZE], bool uniqCheck);

/**************** printResult ****************/
/* Solves a sudoku and prints the solution along
 * with a message about the number of solutions
 * @param sudoku the sudoku to solve and print
 */
void printResult(int sudoku[SIZE][SIZE]);

#endif // __SOLVE_H
