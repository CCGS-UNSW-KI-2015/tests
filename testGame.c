//Do I know how to use github???
//YAY I KNOW GITHUD ;)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "game.h"

int main(int argc, char *argv[]){
	Game game;

	printf("Press enter to continue");
	char temp = 'a';
	scanf("%c", &temp);

	//---------------TESTs-----------//

	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	game = newGame(defaultDis, defaultDice);

	path startLocA1 = { 0 };

	assert(getMostARCs(game) == NO_ONE);
	assert(getMostPublications(game) == NO_ONE);
	assert(getWhoseTurn(game) == NO_ONE);

	int isLegalAction(Game g, action a);
	action illegalAction1 = {OBTAIN_ARC, startLocA1, STUDENT_THD, STUDENT_THD};
	assert(isLegalAction(game, illegalAction1) == FALSE);

	assert(getTurnNumber(game) == -1);//When game is first gened turnNum should be -1
	throwDice(game, 2);
	assert(getTurnNumber(game) == 0);

	

	printf("All tests passed. You can kind of code :D\n");

	//--------------TESTS------------//

	printf("Press Enter to continue");
	temp = 'a';
	scanf("%c", &temp);

	return EXIT_SUCCESS;
}