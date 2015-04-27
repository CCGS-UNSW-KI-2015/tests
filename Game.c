//Game.c

#include "game.h"

Game newGame(int discipline[], int dice[]){
	Game game = { 0 };
	return game;
}

int getTurnNumber(Game g){ 
	return -1; 
}

void throwDice(Game g, int diceScore){
	// Correct me if I'm wrong, this might
	// be bad style but I don't see an
	// alternative.
	srand(clock());
	
	// Return a random number
	return rand() % 6 + 1;
}
