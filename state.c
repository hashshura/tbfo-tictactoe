/*

	state.c
	
	Implements all the needed types and functions
	for Tic-Tac-Toe finite automata and transition
	table from state.h.
	
	Asif Hummam Rais
	13517099
	Student at Bandung Institute of Technology

*/

#include "state.h"

/* --- TICTACTOESTATE GETTERS AND SETTERS --- */
bool isFinalState(TicTacToeState s){
	return s.fs;
}
bool isInitialState(TicTacToeState s){
	return s.is;
}
void setFinalState(TicTacToeState *s, bool b){
	s->fs = b;
}
void setInitialState(TicTacToeState *s, bool b){
	s->is = b;
}
Board getCurrentBoard(TicTacToeState s){
	return s.board[CURRENT_BOARD];
}
Board getNextBoard(TicTacToeState s, int player_move){
	return s.board[player_move];
}

/* --- TRANSITIONTABLE GETTERS --- */
TicTacToeState findState(TransitionTable t, Board b){
	for (int i = 0; i < t.state_size; i++)
		if (isEqual(b, getCurrentBoard(t.state[i])))
			return t.state[i];
}
TicTacToeState getInitialState(TransitionTable t){
	for (int i = 0; i < t.state_size; i++)
		if (isInitialState(t.state[i]))
			return t.state[i];
}
TicTacToeState getNextState(TransitionTable t, TicTacToeState s, int player_move){
	return findState(t, getNextBoard(s, player_move));
}

/* --- STATE LOADER --- */
void loadStates(FILE *fp, TransitionTable *t){
	
	// Initialization
	t->state_size = 0;
	bool eof = false;
	char string[10];
	
	while (!eof){
		// Initialization
		setInitialState(&t->state[t->state_size], false);
		setFinalState(&t->state[t->state_size], false);
		
		for (int i = 0; i < STATE_BOARDS; i++){
			if (fscanf(fp, "%s", string) == 1){
				int start_at = 0; // At what indexes should the new string copy? (Default: 0-8)
				
				if (string[0] == INITIAL_STATE){
					// If string has preceding initial state symbol, copy string indexed from 1-9
					start_at = 1;
					setInitialState(&t->state[t->state_size], true);
					
				} else if (string[0] == FINAL_STATE){
					// If string has preceding final state symbol, copy string indexed from 1-9
					start_at = 1;
					setFinalState(&t->state[t->state_size], true);
				}
				
				for (int j = start_at; j < start_at + BOARD_SIZE; j++)
					t->state[t->state_size].board[i].content[j - start_at] = string[j];
				
			} else 
				// If fscanf returns other than 1 (i.e. no more input found)
				eof = true;
		}
		t->state_size++;
	}
}
