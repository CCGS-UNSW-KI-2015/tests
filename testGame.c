/* testGame.c
 * It's alive!
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "testState.h"

#define DEFAULT_PLAYERS {0, 3, 3, 1, 1, 1}

void basicAssertFailure(int expected, int got, char* helpText);

int main(int argc, char *argv[]){
	Game game;



	//--------------TESTS-----------//

	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	int currentAction = 0;
	action myAction;

	game = newGame(defaultDis, defaultDice);
	stateSet currentState;

	//
	// ACTION 0
	//

	currentAction = printAction("Initializing game with default values",
		currentAction);

	// Inititalise currentState game state
	currentState = initState(currentState);

	// Check it!
	assertState(game, currentState);

	//
	// ACTION 1
	//

	// Throw a dice of 2 (Also tests getWhoseTurn)
	currentAction = printAction("Throwing dice with value 2",
		currentAction);

	throwDice(game, 2);

	currentState.numTurnNumber++;
	currentState.numWhoseTurn = UNI_A;

	// TODO: Give all universities who have campuses at dice values 2 resources

	assertState(game, currentState);

	//
	// ACTION 2
	//

	currentAction = printAction("Integrity check with buiilding a campus at \"L\" (should be illegal)",
		currentAction);

	myAction.actionCode = BUILD_CAMPUS;
	myAction.destination[0] = 'L';

	if (isLegalAction(game, myAction) == TRUE) {
		basicAssertFailure(0, 1, "UNI_A building a campus at \"L\" should be illegal!");
	}

	//
	// ACTION 3
	//

	myAction.actionCode = OBTAIN_ARC;
	myAction.destination[0] = 'B';

	currentAction = printAction("Integirty check with building an ARC at \"B\" (should be illegal)",
		currentAction);

	if (isLegalAction(game, myAction) == TRUE) {
		basicAssertFailure(0, 1, "UNI_A building an ARC at \"B\" should be illegal!");
	}

	//
	// ACTION 4
	//

	currentAction = printAction("Integrity check with building an ARC at \"L\" (should be legal)",
		currentAction);

	myAction.actionCode = OBTAIN_ARC;
	myAction.destination[0] = 'L';

	if (isLegalAction(game, myAction) == FALSE) {
		basicAssertFailure(1, 0, "UNI_A building an ARC at \"L\" should be legal!");
	}

	//
	// ACTION 5
	//

	currentAction = printAction("Building an ARC at \"L\"",
		currentAction);

	makeAction(game, myAction);

	currentState.unis[UNI_A].numKPIPoints += 2;
	currentState.unis[UNI_A].numARCs += 1;
	currentState.unis[UNI_A].numStudents[STUDENT_BPS]--;
	currentState.unis[UNI_A].numStudents[STUDENT_BQN]--;
	currentState.numMostARCs = UNI_A;

	assertState(game, currentState);

	//
	// ACTION 6
	//

	currentAction = printAction("Integrity check with building a campus at \"L\" (should be legal)",
		currentAction);

	myAction.actionCode = BUILD_CAMPUS;
	myAction.destination[0] = 'L';

	if (isLegalAction(game, myAction) == FALSE) {
		basicAssertFailure(1, 0, "UNI_A building a campus at \"L\" should be legal!");
	}

	//
	// ACTION 7
	//

	currentAction = printAction("Building a campus at \"L\"",
		currentAction);

	makeAction(game, myAction);

	currentState.unis[UNI_A].numKPIPoints += 10;
	currentState.unis[UNI_A].numCampuses += 1;
	currentState.unis[UNI_A].numStudents[STUDENT_BPS]--;
	currentState.unis[UNI_A].numStudents[STUDENT_BQN]--;
	currentState.unis[UNI_A].numStudents[STUDENT_MJ]--;
	currentState.unis[UNI_A].numStudents[STUDENT_MTV]--;

	assertState(game, currentState);

	//
	// ACTION 8
	//

	currentAction = printAction("Integrity check with building a campus at \"L\" (should be illegal)",
		currentAction);

	if (isLegalAction(game, myAction) == TRUE) {
		basicAssertFailure(1, 0, "UNI_A building a campus at \"L\" should be illegal!");
	}

	//
	// ACTION 9
	//

	currentAction = printAction("Throwing dice with value 6",
		currentAction);

	throwDice(game, 6);

	currentState.numTurnNumber++;
	currentState.numWhoseTurn = UNI_B;

	// TODO: Give all universities who have campuses at dice values 6 resources

	assertState(game, currentState);

	//
	// ACTION 10
	//

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

	i = 0;
	while (i < universitySize) {
		state.unis[i].numKPIPoints = 24;
		state.unis[i].numARCs = 2;
		state.unis[i].numGroupOfEights = 0;
		state.unis[i].numCampuses = 2;
		state.unis[i].numIPs = 0;
		state.unis[i].numPublications = 0;
		int disBuffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
		int j = 0;
		while (j < NUM_DISCIPLINES) {
			state.unis[i].numStudents[j] = disBuffer[j];
			j++;
		}


		int exA = 0;
		while (exA < NUM_DISCIPLINES) {
			int exB = 0;
			while (exB < NUM_DISCIPLINES) {
				state.unis[i].numExchangeRate[exA][exB] = 3;
				exB++;
			}
			exA++;
		}

		i++;
	}

	return state;
}

void basicAssertFailure(int expected, int got, char* helpText) {
	printf(BOLD RED    "\nAssertion failed!\n");
	printf(            "Expected %d got %d ", expected, got);
	printf(RESET RED   "%s", helpText);
	printf(RESET);
	exit(1);
}
