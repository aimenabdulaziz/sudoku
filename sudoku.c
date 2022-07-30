/* 
 * sudoku.c - *sudoku* can be used to create or solve a sudoku puzzle.
 *          Will prompt the user for more information if solve is selected.
 *  
 * usage: ./sudoku command where command is solve/create
 * 
 * Koding Kegs, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include "solve.h"
#include "create.h" 
#define SIZE 9

/********************** local function prototypes ********************* */
int fileno(FILE *stream);
bool handleSolve(void);
void normalizeWord(char *word);
static void prompt(void);

/* ******************** main ******************** */
/* Parse arguments and call appropriate methods */
int main(const int argc, char *argv[])
{
    char *usage = "usage: ./sudoku command, where command is solve or create";
   
    // validate the number of command line arguments
	if (argc != 2) {
		fprintf(stderr, "%s\n", usage);
		return 1; 
	}

    char* command = argv[1];
    // convert the command to lowercase
    normalizeWord(command);

    srand(time(NULL));
    if (strcmp(command, "create") == 0) {
        int sudoku[SIZE][SIZE] = {0};
        createSudoku(sudoku);
    }
    else if (strcmp(command, "solve") == 0) {
        while (handleSolve()){
            handleSolve();
        }
    }
    return 0;
}

/**************** handleSolve() ****************/
/*Reads a sudoku from stdin and attempts to solve it
 * If the sudoku is valid, the solution (the first solution, if there
 * are multiple) is printed to stdin
 */
// can pass each index separated by new lines || with white space || without white space
bool handleSolve(void)
{
    // initialize a 2D array
    int sudoku[SIZE][SIZE] = {0};
    int row = 0, col = 0;
    char ch;

    prompt();

    // read each character at a time
    while ((ch = fgetc(stdin)) != EOF){
        if (isspace(ch)){
            continue; 
        }

        // insert to sudoku if ch is a digit
        if (isdigit(ch)) {
            sudoku[row][col] = ch - '0';  // convert ch to int and insert to sudoku
            
            // increment row,col values accordingly
            if (++col == 9) {
                col = 0;
                row += 1;
                
                if (row == 9){
                    // all 81 slots have been filled
                    break;
                }
            }
            continue;
        }
        printf("Invalid input in row %d.\n", row+1);
        if (isatty(fileno(stdin))){
            return true;
        }
        return false;
    }

    printResult(sudoku);
    return false;
}

/**************** normalizeWord() ****************/
/** 
 * Converts all letters in a word to lower case
 * @param *word the word to normalize
 */
void normalizeWord(char *word)
{
    for (int i = 0; i < strlen(word); i++) {
        word[i] = tolower(word[i]);
    }
}

/**************** prompt() ****************/
/* print a prompt is stdin is terminal for an interactive user interface */
static void prompt(void)
{
  // print a prompt if stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("Enter your sudoku:\n");
  }
}
