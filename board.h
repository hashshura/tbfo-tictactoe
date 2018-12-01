/*

	board.h
	
	Includes all the needed types and functions
	for Tic-Tac-Toe boards as abstract data types.
	
	Asif Hummam Rais
	13517099
	Student at Bandung Institute of Technology

*/

#ifndef __BOARD_H_
#define __BOARD_H_

#include<stdio.h>
#include<stdbool.h>

#define BOARD_SIZE 9	// Tic-Tac-Toe board has 9 contents (3 rows x 3 columns)

#define DRAW_WINNER 'D'	// Winner (char), should the game ends in a draw
#define CURRENT_BOARD 0	// Current board of a state
#define FIRST_ROW 1
#define FIRST_COLUMN 1
#define LAST_ROW 3
#define LAST_COLUMN 3

typedef struct{	char content[BOARD_SIZE]; } Board;
// A Tic-Tac-Toe board ("Board") is defined as an array of 9 characters
// in which, the first 3 are 1st row, next 3 are 2nd row, last 3 are 3rd row

/* --- BOARD GETTERS --- */
char getContent(Board b, int row, int col);
// Gets the content (sign) of a specific row and column of a board

bool isEqual(Board a, Board b);
// Checks if two boards have the exact same contents

bool isContentEqual(Board b, int i1, int j1, int i2, int j2);
// Checks if two contents of a board are of the same sign

bool isContentEmpty(Board b, int i, int j);
// Checks if a board has empty content at row i, column j

void printBoard(Board b);
// Prints the board to the screen

void checkGame(Board b, bool *end, char *winner);
// Checks board contents if a game should already be ended

#endif
