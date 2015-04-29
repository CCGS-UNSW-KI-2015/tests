/* testGame.c
 * It's alive!
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"

typedef struct _uniSet {
	int numKPIPoints;
	int numARCs;
	int numGroupOfEights;
	int numCampuses;
	int numIPs;
	int numPublications;
	int numStudents;
	int numExchangeRate;
} uniSet;

typedef struct _actionSet {
	int action;
	int valueToAction;
	int expectedReturn;
} actionSet;

typedef struct _stateSet {
	int numDiscipline;
	int numDiceValue;
	int numMostARCs;
	int numMostPublications;
	int numTurnNumber;
	int numWhoseTurn;
	int numCampus;
	int numARC;
	uniSet unis[NUM_UNIS];
} stateSet;

typedef struct _testSet {
	actionSet action;
	stateSet state;
} testSet;

int main(int argc, char *argv[]){
	Game game;

	printf("Press enter to continue");
	char temp = 'a';
	scanf("%c", &temp);

	//--------------TESTS-----------//

	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	int universities[] = {UNI_A, UNI_B, UNI_C}
	int defaultSize = NUM_REGIONS;
	int universitiesSize = NUM_UNIS;
	int i = 0;

	game = newGame(defaultDis, defaultDice);

	path startLocA1 = { 0 };

	// Verify that everything has been loaded correctly

	i = 0;
	while (i < NUM_REGIONS) {
		assert(defaultDice[i] == getDiceValue(i));
		assert(defaultDis[i] == getDiscipline(i));
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
	action illegalAction1 = {OBTAIN_ARC, startLocA1, STUDENT_THD, STUDENT_THD};
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
