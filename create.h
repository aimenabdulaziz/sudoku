/*
 * create.h - utility functions for creating a random sudoku
 * 
 * Koding Kegs, Spring 2022
 */

#ifndef __CREATE_H
#define __CREATE_H

#include <stdio.h>
#include <stdbool.h>

/* ***************************
 * Fills an empty 2D array with between 17 and 41 random numbers, 
 * checking that each entry is valid. It then tries to solve it with
 * solveSudoku to ensure that it has at most and at least one solution.
 * It prints the sudoku to stdout
 */
void createSudoku(int solution[9][9]);

#endif // __CREATE_H
