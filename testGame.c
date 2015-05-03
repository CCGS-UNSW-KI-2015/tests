/* testGame.c
 * It's alive!
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "testState.h"

int main(int argc, char *argv[]){
	Game game;

	//--------------TESTS-----------//

	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	int currentAction = 0;

	game = newGame(defaultDis, defaultDice);
	stateSet currentState;

	currentAction = printAction("Initializing game with default values",
		currentAction);

	// Inititalise currentState game state
	currentState = initState(currentState);

	// Check it!
	assertState(game, currentState);


	// Throw a dice of 2

	currentAction = printAction("Throwing dice with value 2",
		currentAction);

	throwDice(game, 2);

	currentState.numTurnNumber++;

	assertState(game, currentState);


	printEnd();


	return EXIT_SUCCESS;
}

stateSet initState (stateSet state) {
	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	int universities[] = {UNI_A, UNI_B, UNI_C};
	int defaultSize = NUM_REGIONS;
	int universitySize = 20;

	int i = 0;
	while (i < NUM_REGIONS) {
		state.regions[i].numDiscipline = defaultDis[i];
		state.regions[i].numDiceValue = defaultDice[i];

		i++;
	}

	state.numMostARCs = NO_ONE;
	state.numMostPublications = NO_ONE;
	state.numTurnNumber = -1;
	state.numWhoseTurn = NO_ONE;

	i = 0;
	while (i < PATH_LIMIT) {
		state.paths[i].numCampus = VACANT_VERTEX;
		state.paths[i].numARC = VACANT_ARC;

		i++;
	}

	memset(state.unis, 0, sizeof(state.unis[0]) * universitySize);

	return state;
}
