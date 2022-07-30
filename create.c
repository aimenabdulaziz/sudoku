/* 
 * create.c - generates a unique sudoku
 * 
 * Assumptions: number entered into createSudoku is between 17 and 41
 * Usage: see create.h
 * 
 * Koding Kegs, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "solve.h"
#include "create.h"

/* local functions not visible outside this file */
static void fillSudoku(int solution[9][9]);
static void deleteCells(int solution[9][9]);

/******************** createSudoku() ********************/
/* see create.h for description */
void createSudoku(int solution[9][9])
{
    memset(solution, 0, sizeof(int) * 9 * 9);
    fillSudoku(solution);
    deleteCells(solution);
}

/* ***************************
 * Fills an empty 2D array with a few valid numbers, then
 * tries to solve it to see if it leads to a sudoku with a unique
 * solution
 * @param solution the sudoku to be filled
 */
static void fillSudoku(int solution[9][9])
{
    int count = 0;
    int count2 = 0;

    // rand() % 9 returns a random integer between 0 and 9
    int row = rand() % 9;
    int col = rand() % 9;

    int numFilled = 10; 

    // fills in a blank grid with a few valid numbers,
    // so generated sudoku will be unique
    while (numFilled > 0) {
        if (solution[row][col] == 0) {
            // count2 ensures that while loop does get stuck in a dead end
            if (count2 < 50) {
                int fill = rand() % 10;
                // if entry is valid, add it to sudoku and change row/col
                if (validEntry(solution, row, col, fill)) {
                    solution[row][col] = fill;
                    numFilled = numFilled - 1;
                    row = rand() % 9;
                    col = rand() % 9;
                    count2 = 0;
                }
                count2++;
            }
            else {
                row = rand() % 9;
                col = rand() % 9;
            }
        }
        else {
            count2 = 0;
            // if a number is already there pick a new row/col
            row = rand() % 9;
            col = rand() % 9;
        }
    }
    // try to solve the sudoku
    // we are not interested in the final solution, only its validity
    count = solveSudoku(solution, solution, false);

    // randomly generated sudoku is invalid, so try again
    if (count == 0) {
        createSudoku(solution);
    }
}

/* ***************************
 *Deletes a random num in range [25, 40] cells from a sudoku
 * @param solution the sudoku to delete cells from
 */
static void deleteCells(int solution[9][9])
{
    int deadEnd = 0;

    // the number of filled cells in the final sudoku is randomly
    // generated. it is in the range [25, 40]
    int upper = 40;
    int lower = 25;
    int num = (rand() % (upper - lower + 1)) + lower;
    
    int count = 0;

    // delete cells
    int numToDelete = 81 - num;
    while (numToDelete > 0) {
        count = 0;
        int solution2[9][9] = {0};
        int row = rand() % 9;
        int col = rand() % 9;

        // if random cell at row, column has not already been removed
        // attempt to remove it
        if (solution[row][col] != 0){
            int numHere = solution[row][col];
            solution[row][col] = 0;
            memcpy(solution2, solution, sizeof(int) * 9 * 9);
            count = solveSudoku(solution2, solution2, true);

            // only remove it if it will lead to a puzzle with a unique solution
            if (count == 1) {
                deadEnd = 0;
                numToDelete--;
            }
            else {
                deadEnd = deadEnd + 1;
                // ensures that a dead end it not reached
                if(deadEnd > 20){
                    deadEnd = 0;
                    int solution[9][9] = {0};
                    solveSudoku(solution, solution, false);
                    numToDelete = num;
                }
                else {
                    solution[row][col] = numHere;
                }
            }
        }

    }

    printSudoku(solution);
    count = 0;
    count = solveSudoku(solution, solution, true);
    #ifdef CREATETEST
    printf("count is %d\n", count);
    #endif // CREATETEST
}

#ifdef CREATETEST
int main(int argc, char const *argv[])
{
    //unit testing purposes
    srand(time(NULL));   // Initialization
    int sudoku[9][9] = {0};
    createSudoku(sudoku);
}
#endif // CREATETEST
