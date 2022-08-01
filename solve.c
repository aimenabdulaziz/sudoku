/*
 * solve.c - solves a sudoku
 * 
 * see solve.h for more information
 * 
 * Assumptions:
 *      sudoku board is 9 * 9
 *      each index in the board is a digit 0-9
 *      value of 0 means a missing number
 * 
 * Koding Kegs, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define SIZE 9 // size of the Sudoku board

/**************** local functions ****************/
/* not visible outside this file */
static bool solveSudokuHelper(int sudoku[SIZE][SIZE], int solution[SIZE][SIZE],
                              int *count);

/******************** validEntry() ********************/
/* see solve.h for description */
bool validEntry(int sudoku[SIZE][SIZE], int row, int col, int num)
{
    for (int i = 0; i < SIZE; i++){
        // validate row
        if (sudoku[row][i] == num) return false;

        // validate column
        if (sudoku[i][col] == num) return false;
        
        // validate sub-box
        int x = 3 * (row / 3) + (i / 3); 
        int y = 3 * (col / 3 ) + (i % 3); 
        if (sudoku[x][y] == num) return false;
    }
    return true;
}

/******************** validSudoku() ********************/
/* see solve.h for description */
bool validSudoku(int sudoku[SIZE][SIZE])
{
    int temp[SIZE][SIZE] = {0};
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            int num = sudoku[row][col];
            if (num == 0){
                // don't do anything if num is 0
                continue; 
            } 
            if (!validEntry(temp, row, col, num)){ 
                return false;
            }
            temp[row][col] = num;
        }
    }
    return true;
}

/******************** printSudoku() ********************/
/* see solve.h for description */
void printSudoku(int sudoku[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){

            // print each value and a white space
            printf("%d ", sudoku[row][col]);
            
            // extra white space every 3 columns to make clear distinction between boxes
            if ((col + 1) % 3 == 0){
                printf(" "); 
            }
        }
        // new line between every rows
        printf("\n");

        // extra new line every 3 rows to make clear distinction between boxes
        if ((row + 1) % 3 == 0 && (row + 1) < SIZE){
            printf("\n"); 
        }
    }
}

/******************** solveSudoku() ********************/
/* see solve.h for description */
int solveSudoku(int sudoku[SIZE][SIZE], int solution[SIZE][SIZE],
                bool uniqCheck)
{  
    int count = 0; // accumulates the total number of solutions
    
    // check if the sudoku is valid
    if (!validSudoku(sudoku)){
        fprintf(stderr, "The sudoku is invalid\n");
        return count;
    }

    if (uniqCheck) {
        // make temporary sudoku as we don't want to modify the main sudoku
        int temp[SIZE][SIZE] = {0}; 
        
        // copy everything in the main sudoku to temp
        memcpy(temp, sudoku, sizeof(int) * SIZE * SIZE); 
        solveSudokuHelper(temp, solution, &count);
        return count;
    }

    // solve the sudoku by modifying the passed board
    else {
        solveSudokuHelper(sudoku, solution, &count);
        return count;
    }
}

/* ***************************
 * Helper function for solving a sudoku
 * @param sudoku the sudoku to solve
 * @param solution the first solution found by the solver
 * @param count the count for the number of solutions. Goes up to 2
 */
static bool solveSudokuHelper(int sudoku[SIZE][SIZE], int solution[SIZE][SIZE],
                              int *count)
{
    // non-existent cell for empty slot check
    int row = SIZE;
    int col = 0;

    // check if there is any empty slot in the sudoku puzzle
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (sudoku[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
    }   

    // base case -> all elements have been visited
    if (row == SIZE && col == 0) {
        (*count)++; // increment count for number of solutions

        // copy the first solution from sudoku to solution 2D array 
        if (*count == 1) {
            memcpy(solution, sudoku, sizeof(int) * SIZE * SIZE); 
        }

        else if (*count == 2) {
            return false; // has multiple solutions
        }
        return true;
    }

    // sudoku[row][col] == zero -> empty slot 
    for (int num = 1; num <= SIZE; num++) {
        if (validEntry(sudoku, row, col, num)){
            sudoku[row][col] = num;
            if(!solveSudokuHelper(sudoku, solution, count)){
                // if second solution is found, stop recursing
                return false; 
            }
            sudoku[row][col] = 0; // change the added number back to 0
        }

    }
    // no valid input after checking 1-9, backtrack to the last added num and change it
    return true;
}

/**************** printResult() ****************/
/* see solve.h for description */
void printResult(int sudoku[SIZE][SIZE])
{
    int solution[SIZE][SIZE] = {0};
    int count = solveSudoku(sudoku, solution, false);
    if (count == 2) {
        printf("The sudoku has two or more solutions. The following is one:\n");
        printSudoku(solution);
    }
    else if (count == 1) {
        printf("The sudoku has just one solution\n");
        printSudoku(solution);
    }
    else {
        printf("The sudoku does not have any solutions\n");
    }
}

#ifdef SOLVETEST

#include <time.h>

/* ***************************
 * Main function for the program
 * @param argc the argument count
 * @param *argv the argument values
 */
int main(int argc, char const *argv[])
{   
    // valid sudoku with multiple solutions
    printf("test 1\n");
    int sudoku[9][9] = {0}; // 9 by 9 sudoku with all values set to 0
    printResult(sudoku); 

    // valid sudoku with 1 solution
    printf("test 2\n");
    int sudoku2[9][9] = {
        {0,7,0,0,2,0,0,4,6},
        {0,6,0,0,0,0,8,9,0},
        {2,0,0,8,0,0,7,1,5},
        {0,8,4,0,9,7,0,0,0},
        {7,1,0,0,0,0,0,5,9},
        {0,0,0,1,3,0,4,8,0},
        {6,9,7,0,0,2,0,0,8},
        {0,5,8,0,0,0,0,6,0},
        {4,3,0,0,8,0,0,7,0}
    };

    printResult(sudoku2); 

    // valid sudoku with 1 solution
    printf("test 3\n");
    int sudoku3[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, 
        {8, 0, 0, 0, 6, 0, 0, 0, 3}, 
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, 
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0}, 
        {0, 0, 0, 4, 1, 9, 0, 0, 5}, 
        {0, 0, 0, 0, 8, 0, 0, 7, 9} 
    };

    printResult(sudoku3); 

    // invalid sudoku (4 is repeated in col 4)
    printf("test 4\n");
    int sudoku4[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, 
        {8, 0, 0, 0, 6, 0, 0, 0, 3}, 
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, 
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 4, 0, 0, 2, 8, 0}, 
        {0, 0, 0, 4, 1, 9, 0, 0, 5}, 
        {0, 0, 0, 0, 8, 0, 0, 7, 9} 
    };
    printResult(sudoku4); 
    
    // valid sudoku with multiple solutions
    printf("test 5\n");
    int sudoku5[9][9] = {
        {2, 9, 5, 7, 4, 3, 8, 6, 1},
        {4, 3, 1, 8, 6, 5, 9, 0, 0},
        {8, 7, 6, 1, 9, 2, 5, 4, 3},
        {3, 8, 7, 4, 5, 9, 2, 1, 6},
        {6, 1, 2, 3, 8, 7, 4, 9, 5},
        {5, 4, 9, 2, 1, 6, 7, 3, 8},
        {7, 6, 3, 5, 2, 4, 1, 8, 9},
        {9, 2, 8, 6, 7, 1, 3, 5, 4},
        {1, 5, 4, 9, 3, 8, 6, 0, 0}
    };
    printResult(sudoku5); 
}
#endif // SOLVETEST
