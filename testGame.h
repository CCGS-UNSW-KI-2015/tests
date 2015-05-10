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

/* initState
 * Initialise a stateSet to default.
 */
stateSet initState (stateSet state);

/* testState.h
 * Defines functions for testState.c
 * Includes color ANSI escape sequences
 * and boolean integers.
 */

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

#define RESET   "\x1b[0m"

#define TRUE 1
#define FALSE 0

typedef char boolean;

typedef struct _assertInfo {
	char* action;
	int expected;
	int got;
	char helpText[200];
} assertInfo;

/* void advAssert(Game game, char* action, int expected, int got, char* helpText)
 * A verbose assert that checks, for every check inputted, if expected is equal to got.
 * If it is not, it prints a description, and dumps the current
 * game state. (All of it.)
 */
void advAssert(Game game, assertInfo info[], int infoLen);

/* void assertState(Game game, stateSet state)
 * Performs checks on the ENTIRE game state
 */
void assertState(Game game, stateSet state);

/* void printAction(char* action)
 * Prints action information to the terminal
 */
int printAction(char* action, int actionStep);

/* void printAction(char* action)
 * Prints the end success message to the terminal
 */
void printEnd();
