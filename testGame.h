#include "Game.h"

#define NUM_DISCIPLINES 6

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

/* initState
 * Initialise a stateSet to default.
 */
stateSet initState (stateSet state);
