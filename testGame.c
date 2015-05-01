/* testGame.c
 * It's alive!
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "testState.h"

/*
 * Function prototypes
 */
stateSet initState (stateSet myState);

/* uniSet
 * Information on a single
 * university
 */
typedef struct _uniSet {
	int numKPIPoints;
	int numARCs;
	int numGroupOfEights;
	int numCampuses;
	int numIPs;
	int numPublications;
	int numStudents[NUM_DISCIPLINES];
	int numExchangeRate[NUM_DISCIPLINES][NUM_DISCIPLINES];
} uniSet;

/* regionSet
 * Information on a single
 * region
 */
typedef struct _regionSet {
	int numDiscipline;
	int numDiceValue;
} regionSet;

/* pathSet
 * Information on a single
 * path
 */
typedef struct _pathSet {
	path myPath;
	int numCampus;
	int numARC;
} pathSet;

/* actionSet
 * Information on which actions
 * go with which expected
 * returns
 */
typedef struct _actionSet {
	int action;
	int valueToAction;
	int expectedReturn;
} actionSet;

/* stateSet
 * A game state.
 */
typedef struct _stateSet {
	regionSet regions[NUM_REGIONS];
	int numMostARCs;
	int numMostPublications;
	int numTurnNumber;
	int numWhoseTurn;
	pathSet paths[PATH_LIMIT];
	uniSet unis[20];
} stateSet;

/* testSet
 * A testing struct.
 */
typedef struct _testSet {
	actionSet action;
	stateSet state;
} testSet;

int main(int argc, char *argv[]){
	Game game;

	printf("Press the any key to continue: ");
	char temp = 'a';
	scanf("%c", &temp);

	//--------------TESTS-----------//
	
	game = newGame(defaultDis, defaultDice);
	stateSet currentState;
	
	// Inititalise currentState game state
	currentState = initState(currentState);
	
	// Check it!
	assertState(game, currentState);

	/*
	// Throw a dice of 2

	throwDice(game, 2);
	assert(getTurnNumber(game) == 0);
	*/


	printf("All tests passed. You can kind of code :D\n");

	//--------------TESTS------------//

	printf("Press the any key to continue: ");
	temp = 'a';
	scanf("%c", &temp);

	return EXIT_SUCCESS;
}

stateSet initState (stateSet myState) {
	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;
	int universities[] = {UNI_A, UNI_B, UNI_C};
	int defaultSize = NUM_REGIONS;
	int universitiesSize = NUM_UNIS;
	
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
	while (i < NUM_UNIS) {
		state.unis[i].numKPIPoints = 0;
		state.unis[i].numARCs = 0;
		state.unis[i].numGroupOfEights = 0;
		state.unis[i].numCampuses = 0;
		state.unis[i].numIPs = 0;
		state.unis[i].numPublications = 0;
		
		// Mega-array-setter-quicker Get-a-lotta-stuff-done-like-a mega-super-awesome-looking setter-everything-to-zero
		memset(array, 0, sizeof(states.unis[i].numStudents) / sizeof(states.unis[i].numStudents[0]));
		memset(array, 0, sizeof(states.unis[i].numExchangeRate) / sizeof(states.unis[i].numExchangeRate[0][0]));
		
		i++;
	}
	
	return state;
}
