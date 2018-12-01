/*

	state.h
	
	Includes all the needed types and functions
	for Tic-Tac-Toe finite automata and transition
	table as abstract data types.
	
	Asif Hummam Rais
	13517099
	Student at Bandung Institute of Technology

*/

#ifndef __STATE_H_
#define __STATE_H_

#include<stdio.h>
#include<stdbool.h>
#include "board.h"

#define STATE_BOARDS 10	// 0th = current board, 1st-9th = transition board
#define MAX_STATES 200
#define MAX_TRANSITIONS 5

#define INITIAL_STATE '>'
#define FINAL_STATE '*'

typedef struct{
	
	bool fs; // Is the state a final state?
	bool is; // Is the state an initial state?
	Board board[STATE_BOARDS];
	
} TicTacToeState;
// Tic-Tac-Toe finite automata state is defined as an array of boards
// in which, the 0th board is the "current board", and the 1st to 9th
// boards are the "transition" boards

/* --- TICTACTOESTATE GETTERS AND SETTERS --- */
bool isFinalState(TicTacToeState s);
// Checks if a state is a final state

bool isInitialState(TicTacToeState s);
// Checks if a state is an initial state

void setFinalState(TicTacToeState *s, bool b);
// Sets the final state boolean of a state

void setInitialState(TicTacToeState *s, bool b);
// Sets the initial state boolean of a state

Board getCurrentBoard(TicTacToeState s);
// Gets the current board of a state

Board getNextBoard(TicTacToeState s, int player_move);
// Gets the next board of a state when the human player inputs a move

typedef struct{
	
	TicTacToeState state[MAX_STATES];
	int state_size;
	
} TransitionTable;
// Tic-Tac-Toe complete transition table is defined as an array of TicTacToeState
// in which, each state has "transition" boards that have the same boards with the
// corresponding "next" states.

/* --- TRANSITIONTABLE GETTERS --- */
TicTacToeState findState(TransitionTable t, Board b);
// Returns a state that has a specific "current board"

TicTacToeState getInitialState(TransitionTable t);
// Gets the initial state of a transition table

TicTacToeState getNextState(TransitionTable t, TicTacToeState s, int player_move);
// Gets the next state of a state from a transition table when the human player inputs a move

/* --- STATE LOADER --- */
void loadStates(FILE *fp, TransitionTable *t);
// Loads all the contents of a file to a transition table

#endif
