/*

	main.c
	
	The main program of Tic-Tac-Toe game, in which
	the player is able to interact against an
	impossible-to-win bot built upon the premade
	finite automata transition table.
	
	Includes:
	- stdio.h (input and output)
	- stdbool.h (boolean)
	- board.h (custom -- Tic-Tac-Toe board)
	- state.h (custom -- Transition Table)
	
	Asif Hummam Rais
	13517099
	Student at Bandung Institute of Technology

*/

#include<stdio.h>
#include<stdbool.h>
#include "board.h"
#include "state.h"

TransitionTable dfa, human_first, bot_first;
TicTacToeState current_state, passed_state[MAX_TRANSITIONS + 1];
Board last_board;
FILE *file;

char player_turn, rematch;
int player_move, passed_state_count;

bool is_game_ended;
char game_winner;

int main(){
	
	// Loading external files
	file = fopen("Transition Tables/human_first.txt", "r");
	loadStates(file, &human_first);
	fclose(file);
	
	file = fopen("Transition Tables/bot_first.txt", "r");
	loadStates(file, &bot_first);
	fclose(file);
	
	printf("\n");
	printf(" ##########################################\n");
	printf(" # Tic-Tac-Toe: Impossible to Win Edition #\n");
	printf(" ##########################################\n");
	
	rematch = 'y';
	
	while (rematch == 'y'){
		
		passed_state_count = 0;
		
		// Stating the game rules
		printf("\nX = player, O = bot.\n");
		printf("\n[RULES]\n");
		printf("* Tic-tac-toe is a paper-and-pencil game for two players, X and O, who take turns marking the spaces in a 3x3 grid.\n");
		printf("* The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row wins the game.\n");
		printf("* For this game, the first turn (be it from player or the bot) MUST be done to the middle of the board.\n");
		printf("* In each turn, please specify which box you want to fill in (1-9).\n");
		printf("  - First row columns are 1, 2, and 3.\n");
		printf("  - Second row columns are 4, 5, and 6.\n");
		printf("  - Third row columns are 7, 8, and 9.\n");
		
		// Player picks the turn
		player_turn = '-';
		while ((player_turn != 'f') && (player_turn != 's')){
			printf("\nSo, do you want to move in the (f)irst or (s)econd turn? (f/s): ");
			scanf(" %c", &player_turn);
			if ((player_turn != 'f') && (player_turn != 's'))
				printf("The only available inputs are 'f' or 's'.");
		}
		
		printf("\nAs the first rule of this game is to fill in the middle of the board for the first turn,\n");
		if (player_turn == 'f'){
			dfa = human_first;
			printf("I've done it for you. :)\n");
		}
		else if (player_turn == 's'){
			dfa = bot_first;
			printf("Here I go. :)\n");
		}
		
		current_state = getInitialState(dfa);
		
		passed_state_count++;
		passed_state[passed_state_count] = current_state;
		
		checkGame(getCurrentBoard(current_state), &is_game_ended, &game_winner);
		printBoard(getCurrentBoard(current_state));
		
		// Transitioning finite automata states
		while (!is_game_ended){
			
			player_move = 0;
			while ((player_move < 1) || (player_move > 9)){
				printf("Which box do you want to fill with X? (1-9): ");
				scanf("%d", &player_move);
			}
			
			last_board = getCurrentBoard(current_state);
			current_state = getNextState(dfa, current_state, player_move);
			if (isEqual(getCurrentBoard(current_state), last_board))
				printf("Hey, that board is already filled!\n");
			else {
				passed_state_count++;
				passed_state[passed_state_count] = current_state;
			}
			
			printBoard(getCurrentBoard(current_state));
			if (isFinalState(current_state))
				checkGame(getCurrentBoard(current_state), &is_game_ended, &game_winner);
		
		}
		
		// Final state dialog
		printf("Wait... the game has ended? ");
		if (game_winner == 'O')
			printf("And you lose.\nYou should've been able to put this on a draw, don't make silly mistakes!\n");
		else if (game_winner == 'X')
			printf("And you win!\nThis should never happen, my creator probably made mistakes or you have cheated.\n");
		else if (game_winner == DRAW_WINNER)
			printf("It ends with a draw!\nCongratulations for the both of us.\n");
		else
			printf("There must be a bug while loading the external files.\nCheck it now!\n");
		
		printf("\nPassed states:\n");
		for (int i = 1; i <= passed_state_count; i++){
			printf("%d. ", i);
			for (int j = 0; j < BOARD_SIZE; j++)
				printf("%c", getCurrentBoard(passed_state[i]).content[j]);
			printf("\n");
		}
		
		printf("\nRematch? (y/n): ");
		scanf(" %c", &rematch);
		while ((rematch != 'y') && (rematch != 'n')){
			printf("The only available inputs are 'y' or 'n'.\n");
			printf("So, do you want a rematch? (y/n): ");
			scanf(" %c", &rematch);
		}
		
	}
	printf("\nThat was fun, good bye! :)\n");
	return 0;
	
}
