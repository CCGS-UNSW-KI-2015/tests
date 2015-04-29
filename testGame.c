//Do I know how to use github???
//YAY I KNOW GITHUD ;)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"

int main(int argc, char *argv[]){
	Game game;

	printf("Press enter to continue");
	char temp = 'a';
	scanf("%c", &temp);

	//--------------TESTS-----------//

	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	int universities[] = {UNI_A, UNI_B, UNI_C};
	int defaultSize = NUM_REGIONS;
	int universitiesSize = NUM_UNIS;
	int i = 0;

	game = newGame(defaultDis, defaultDice);

	// Verify that everything has been loaded correctly

	i = 0;
	while (i < NUM_REGIONS) {
		assert(defaultDice[i] == getDiceValue(game, i));
		assert(defaultDis[i] == getDiscipline(game, i));
		i++;
	}

	// Make sure the game state is intialised correctly

	assert(getMostARCs(game) == NO_ONE);
	assert(getMostPublications(game) == NO_ONE);
	assert(getWhoseTurn(game) == NO_ONE);

	i = 0;
	while (i < universitiesSize) {
		assert(getKPIpoints(game, universities[i]) == 0);
		assert(getARCs(game, universities[i]) == 0);
		assert(getGO8s(game, universities[i]) == 0);
		assert(getCampuses(game, universities[i]) == 0);
		assert(getIPs(game, universities[i]) == 0);
		assert(getPublications(game, universities[i]) == 0);
	}
	
	int isLegalAction(Game g, action a);
	action illegalAction1;
	illegalAction1.actionCode = OBTAIN_ARC;
	illegalAction1.disciplineFrom = STUDENT_THD;
	illegalAction1.disciplineTo = STUDENT_THD;
	
	assert(isLegalAction(game, illegalAction1) == FALSE);

	assert(getTurnNumber(game) == -1); // When game is first gened turnNum should be -1

	// Throw a dice of 2

	throwDice(game, 2);
	assert(getTurnNumber(game) == 0);


	printf("All tests passed. You can kind of code :D\n");

	//--------------TESTS------------//

	printf("Press Enter to continue");
	temp = 'a';
	scanf("%c", &temp);

	return EXIT_SUCCESS;
}
