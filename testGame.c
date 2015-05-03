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

	// Throw a dice of 2 (Also tests getWhoseTurn)
	currentAction = printAction("Throwing dice with value 2",
		currentAction);

	throwDice(game, 2);

	currentState.numTurnNumber++;
	currentState.numWhoseTurn = UNI_A;

	assertState(game, currentState);


	// Test action PASS
	currentAction = printAction("Testing action PASS",
		currentAction);

	action myAction;
	myAction.actionCode = PASS;
	makeAction(game, myAction);

	currentState.numTurnNumber++;
	currentState.numWhoseTurn = UNI_B;

	assertState(game, currentState);

	// Done!
	printEnd();


	return EXIT_SUCCESS;
}

stateSet initState (stateSet state) {
	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
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
