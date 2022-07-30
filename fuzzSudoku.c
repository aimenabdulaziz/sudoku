/*
 * fuzzSudoku.c - generates n sudoku puzzles for testing
 *
 * usage: ./fuzzSudoku n
 * 
 * ./sudoku command
 * 
 * Koding Kegs, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"
#include "solve.h"
#define SIZE 9

void fuzzTest(int n);

/* ***************************
 * Main function for the program
 * @param argc the argument count
 * @param *argv the argument values
 */
int main(const int argc, char *argv[])
{
    char *usage = "usage: ./fuzzSudoku n";
    // validate the number of command line arguments
    if (argc != 2) {
        fprintf(stderr, "%s\n", usage);
        exit(1);
    }

    int n = atoi(argv[1]);
    fuzzTest(n);
    exit(0);
}

/* ***************************
 * Performs fuzz testing for the sudoku program
 * @param n the number of puzzles to generate
 */
void fuzzTest(int n)
{
    int i = 0;
    int count;
    int sudoku[SIZE][SIZE] = {0};
    int solution[SIZE][SIZE] = {0};

    while (i < n) {
        createSudoku(sudoku);

        // solve the sudoku
        count = solveSudoku(sudoku, solution, true);

        // TEST 1: creator makes puzzles with unique solutions
        if (count != 1) {
            fprintf(stderr, "Sudoku from creator does not have one solution\n");
        }
        else {
            fprintf(stdout, "Sudoku from creator has one solution\n");
        }

        // TEST 2: solver does not change any provided numbers
        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                // ignore empty cells
                if (sudoku[row][col] == 0) {
                    continue;
                }
                if (sudoku[row][col] != solution[row][col]) {
                    fprintf(stderr, "Solver changes already filled cells\n");
                    break;
                }
            }
        }
        fprintf(stdout, "Solver does not change already filled cells\n");
        i++;
    }
}
