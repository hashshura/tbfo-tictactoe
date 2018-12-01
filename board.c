/*

	board.c
	
	Implements all the needed types and functions
	for Tic-Tac-Toe boards from board.h.
	
	Asif Hummam Rais
	13517099
	Student at Bandung Institute of Technology

*/

#include "board.h"

/* --- BOARD GETTERS --- */
char getContent(Board b, int row, int col){
	return b.content[(row-1)*3 + (col-1)];
}
bool isEqual(Board a, Board b){
	for (int i = 0; i < BOARD_SIZE; i++)
		if (a.content[i] != b.content[i])
			return false;
			// If there is a difference, returns false
	return true;
	// Else (when no difference is found after all iterations), returns true
}
bool isContentEqual(Board b, int i1, int j1, int i2, int j2){
	return (getContent(b, i1, j1) == getContent(b, i2, j2));
}
bool isContentEmpty(Board b, int i, int j){
	return (getContent(b, i, j) == '_');
}
void printBoard(Board b){
	printf("\n");
	for (int i = FIRST_ROW; i <= LAST_ROW; i++){
		printf(" ");
		// Printing the actual current board
		for (int j = FIRST_COLUMN; j <= LAST_COLUMN; j++)
			printf("%c", getContent(b, i, j));
		printf("   ");
		// Printing the board numbering guide (1-9)
		for (int j = FIRST_COLUMN; j <= LAST_COLUMN; j++)
			printf("%d", (i-1)*3 + j);
		printf("\n");
	}
	printf("\n");
}

// Checks board contents if a game is already ended
void checkGame(Board b, bool *end, char *winner){
	
	*end = false;
	*winner = DRAW_WINNER;
	bool end_tmp;
	
	// Checks for horizontal wins
	for (int i = FIRST_ROW; i <= LAST_ROW; i++){
		if (isContentEmpty(b, i, FIRST_COLUMN)) continue; // Skips if the first column is empty
		end_tmp = true;
		for (int j = FIRST_COLUMN; j <= LAST_COLUMN; j++)
			if (!isContentEqual(b, i, j, i, FIRST_COLUMN))
				end_tmp = false;
		if (end_tmp)
			*winner = getContent(b, i, FIRST_COLUMN);
		*end = *end || end_tmp;
	}
		
	// Checks for vertical wins
	for (int j = FIRST_COLUMN; j <= LAST_COLUMN; j++){ 
		if (isContentEmpty(b, FIRST_ROW, j)) continue; // Skips if the first row is empty
		end_tmp = true;
		for (int i = FIRST_ROW; i <= LAST_ROW; i++)
			if (!isContentEqual(b, i, j, FIRST_ROW, j))
				end_tmp = false;
		if (end_tmp)
			*winner = getContent(b, FIRST_ROW, j);
		*end = *end || end_tmp;
	}
	
	// Checks for diagonal wins
	if (!isContentEmpty(b, 2, 2) && (!*end)){
		if (isContentEqual(b, 1, 1, 2, 2) && isContentEqual(b, 2, 2, 3, 3)) // Diagonal: [\]
			*end = true;
		else if (isContentEqual(b, 1, 3, 2, 2) && isContentEqual(b, 2, 2, 3, 1)) // Diagonal: [/]
			*end = true;
		if (*end)
			*winner = getContent(b, 2, 2);
	}
	
	bool all_filled = true;
	// Checks if all contents of the board are filled
	for (int i = FIRST_ROW; i <= LAST_ROW; i++)
		for (int j = FIRST_COLUMN; j <= LAST_COLUMN; j++)
			if (getContent(b, i, j) == '_')
				all_filled = false;
	if (all_filled)
		*end = true;
	
}
