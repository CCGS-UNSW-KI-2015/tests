//Do I know how to use github???
//YAY I KNOW GITHUD ;)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "game.h"

int main(int argc, char *argv[]){
	Game game;

	game = newGame(DEFAULT_DISCIPLINES, DEFAULT_DICE);


	assert(getTurnNumber(game) == -1);//When game is first gened turnNum should be -1

	return EXIT_SUCCESS;
}