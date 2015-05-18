/* testGame.c
 * It's alive!
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

#define NUM_VERTS 54
#define NUM_DISCIPLINES 6
#define ALL_PATHS {"RRLR", "RRLRL", "RRLRLL", "RRLRLLR", "RRLRLLRL",\
 "RRLRLLRLR", "RRLRLLRLRL", "RR", "RRL", "RRLL", "RRLLR", "RRLLRL", "RRLLRLR",\
 "RRLLRLRL", "RRLLRLRLR", "RRLLRLRLRL", "", "R", "RL", "RLR", "RLRL", "RLRLR",\
 "RLRLRL", "RLRLRLR", "RLRLRLRL", "RLRLRLRLR", "RLRLRLRLRL", "L", "LR", "LRR",\
 "LRRL", "LRRLR", "LRRLRL", "LRRLRLR", "LRRLRLRL", "LRRLRLRLR", "LRRLRLRLRL",\
 "LRRLRLRLRLR", "LRL", "LRLR", "LRLRR", "LRLRRL", "LRLRRLR", "LRLRRLRL",\
 "LRLRRLRLR", "LRLRRLRLRL", "LRLRRLRLRLR", "LRLRL", "LRLRLR", "LRLRLRR",\
 "LRLRLRRL", "LRLRLRRLR", "LRLRLRRLRL", "LRLRLRRLRLR"}

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
	pathSet vertices[NUM_VERTS];
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

	currentAction = printAction("Integrity check with building a campus at \"L\" (should be illegal)",
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

	currentAction = printAction("Integrity check with building an ARC at \"B\" (should be illegal)",
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
	currentState.vertices[27].numARC = ARC_A;
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
	currentState.vertices[27].numCampus = CAMPUS_A;

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
	currentState.unis[UNI_A].numStudents[STUDENT_MJ]++;
	currentState.numWhoseTurn = UNI_B;

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

	char paths[NUM_VERTS][PATH_LIMIT] = ALL_PATHS;

	i = 0;
	while (i < NUM_VERTS) {
		state.vertices[i].numCampus = VACANT_VERTEX;
		state.vertices[i].numARC = VACANT_ARC;
		strcpy(state.vertices[i].myPath, paths[i]);
		i++;
	}

	state.vertices[16].numCampus = CAMPUS_A;
	state.vertices[37].numCampus = CAMPUS_A;
	state.vertices[1].numCampus = CAMPUS_B;
	state.vertices[53].numCampus = CAMPUS_B;
	state.vertices[47].numCampus = CAMPUS_C;
	state.vertices[6].numCampus = CAMPUS_C;

	i = 0;
	while (i < universitySize) {
		state.unis[i].numKPIPoints = 20;
		state.unis[i].numARCs = 0;
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


int defaultSize = NUM_REGIONS;
int universitiesSize = NUM_UNIS;
int universities[] = {UNI_A, UNI_B, UNI_C};

void advAssert(Game game, assertInfo info[], int infoLen) {
	boolean passed = TRUE;

	// Print errors for all of the checks.
	int i = 0;
	int displayedErrors = 0;
	while (i < infoLen) {
		if (info[i].expected != info[i].got) {
			if (displayedErrors < 5) {
				passed = FALSE;
				// printf(RED         "================================================\n");
				printf(BOLD RED    "\nAssertion failed!\n");
				printf(            "Expected %d got %d ", info[i].expected, info[i].got);
				printf(            "for function \"%s\"\n", info[i].action);
				printf(RESET RED   "%s\n", info[i].helpText);
			}

			displayedErrors++;
		}
		i++;
	}

	if (displayedErrors > 5) {
		printf(BOLD RED "\nand %d additional assertion failures...\n", displayedErrors - 5);
	}

	if (passed) {
		printf(BOLD GREEN "Tests passed!\n");
	} else {
		printf(BOLD RED    "\n====================== Dump ====================\n");
		printf(RESET GREEN "------------------------------------------------\n");
		printf(RESET GREEN "Region Information\n");
		printf(RESET GREEN "------------------------------------------------\n");
		printf(BOLD GREEN  "getDiscipline\n");
		printf(BOLD GREEN  "Region ID | Type\n" RESET GREEN);

		i = 0;
		while (i < defaultSize) {
			int rawType = getDiscipline(game, i); // getDiscipline(game, i);
			char disciplineType[20];

			if (rawType == STUDENT_THD) {
				strcpy(disciplineType, "THD");
			} else if (rawType == STUDENT_BPS) {
				strcpy(disciplineType, "BPS");
			} else if (rawType == STUDENT_BQN) {
				strcpy(disciplineType, "BQN");
			} else if (rawType == STUDENT_MJ) {
				strcpy(disciplineType, "MJ");
			} else if (rawType == STUDENT_MTV) {
				strcpy(disciplineType, "MTV");
			} else if (rawType == STUDENT_MMONEY) {
				strcpy(disciplineType, "MMONEY");
			} else {
				sprintf(disciplineType, "INVALID: %d", rawType);
			}


			if (i >= 10) {
				printf(      "%d        | %s\n", i, disciplineType);
			} else {
				printf(      "%d         | %s\n", i, disciplineType);
			}

			i++;
		}

		printf(RESET GREEN "------------------------------------------------\n");
		printf(BOLD GREEN  "getDiceValue\n");
		printf(            "Region ID | Dice Value\n" RESET GREEN);

		i = 0;
		while (i < defaultSize) {
			int diceValue = getDiceValue(game, i);

			if (i >= 10) {
				printf(      "%d        | %d\n", i, diceValue);
			} else {
				printf(      "%d         | %d\n", i, diceValue);
			}

			i++;
		}


		printf(RESET BLUE  "------------------------------------------------\n");
		printf(BOLD BLUE   "Player Information\n");
		printf(RESET BLUE  "------------------------------------------------\n");

		i = 0;
		while (i < universitiesSize) {
			printf(RESET BLUE "================================================\n");

			int player = universities[i];
			printf(BOLD BLUE  "Player %d\n", player);
			printf(RESET BLUE "------------------------------------------------\n");
			printf(BOLD BLUE  "Attribute             | Value\n");
			printf(RESET BLUE "KPI Points            | %d\n", getKPIpoints(game, player));
			printf(           "ARCs                  | %d\n", getARCs(game, player));
			printf(           "GO8s                  | %d\n", getGO8s(game, player));
			printf(           "Campuses              | %d\n", getCampuses(game, player));
			printf(           "IPs                   | %d\n", getIPs(game, player));
			printf(           "Publications          | %d\n", getPublications(game, player));

			printf(RESET BLUE "------------------------------------------------\n");

			printf(BOLD BLUE  "Discipline            | Students\n");
			printf(RESET BLUE "THD                   | %d\n", getStudents(game, player, STUDENT_THD));
			printf(RESET BLUE "BPS                   | %d\n", getStudents(game, player, STUDENT_BPS));
			printf(RESET BLUE "BQN                   | %d\n", getStudents(game, player, STUDENT_BQN));
			printf(RESET BLUE "MJ                    | %d\n", getStudents(game, player, STUDENT_MJ));
			printf(RESET BLUE "MTV                   | %d\n", getStudents(game, player, STUDENT_MTV));
			printf(RESET BLUE "MMONEY                | %d\n", getStudents(game, player, STUDENT_MMONEY));

			i++;
		}

		printf(RESET BLUE "================================================\n");

		printf(RESET CYAN "------------------------------------------------\n");
		printf(BOLD CYAN  "Game information\n");
		printf(RESET CYAN "------------------------------------------------\n");
		printf(BOLD CYAN  "Attribute             | Value (or player)\n");
		printf(RESET CYAN "Most ARCs             | %d\n", getMostARCs(game));
		printf(           "Most Publications     | %d\n", getMostPublications(game));
		printf(           "Turn Number           | %d\n", getTurnNumber(game));
		printf(           "Whose Turn            | %d\n", getWhoseTurn(game));

		printf(RED BOLD   "================= END OF DUMP ==================\n");

		printf(RESET CYAN "------------ Premature End of Tests ------------\n");
		printf(RESET "\n");
		exit(1);
	}
}

void assertState(Game game, stateSet state) {
	// I'm assuming there will never be
	// more than 1000 checks necessary...
	assertInfo info[1000];
	int infoPos = 0;

	// The way this works is it just
	// passes everything into advAssert to
	// have it checked. (At once.)
	// :D

	int i = 0;
	while (i < NUM_REGIONS) {
		info[infoPos].action = "getDiscipline";
		info[infoPos].expected = state.regions[i].numDiscipline;
		info[infoPos].got = getDiscipline(game, i);
		sprintf(info[infoPos].helpText, "The game did not find the correct discipline at region number %d", i);

		infoPos++;

		info[infoPos].action = "getDiceValue";
		info[infoPos].expected = state.regions[i].numDiceValue;
		info[infoPos].got = getDiceValue(game, i);
		sprintf(info[infoPos].helpText, "The game did not find the correct dice value for region number %d", i);

		infoPos++;

		i++;
	}

	info[infoPos].action = "getMostARCs";
	info[infoPos].expected = state.numMostARCs;
	info[infoPos].got = getMostARCs(game);
	sprintf(info[infoPos].helpText, "The game did not find the correct player number.");
	infoPos++;

	info[infoPos].action = "getMostPublications";
	info[infoPos].expected = state.numMostPublications;
	info[infoPos].got = getMostPublications(game);
	sprintf(info[infoPos].helpText, "The game did not find the correct player number.");
	infoPos++;

	info[infoPos].action = "getTurnNumber";
	info[infoPos].expected = state.numTurnNumber;
	info[infoPos].got = getTurnNumber(game);
	sprintf(info[infoPos].helpText, "The game did not find the correct turn number.");
	infoPos++;

	info[infoPos].action = "getWhoseTurn";
	info[infoPos].expected = state.numWhoseTurn;
	info[infoPos].got = getWhoseTurn(game);
	sprintf(info[infoPos].helpText, "The game did not find the correct player number.");
	infoPos++;

	i = 0;
	while (i < NUM_VERTS) {
		info[infoPos].action = "getCampus";
		info[infoPos].expected = state.vertices[i].numCampus;
		info[infoPos].got = getCampus(game, state.vertices[i].myPath);
		sprintf(info[infoPos].helpText, "The game did not find the correct campus at path %s", state.vertices[i].myPath);

		infoPos++;

		info[infoPos].action = "getARC";
		info[infoPos].expected = state.vertices[i].numARC;
		info[infoPos].got = getARC(game, state.vertices[i].myPath);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of ARCs for path %s", state.vertices[i].myPath);

		infoPos++;

		i++;
	}

	i = 0;
	while (i < universitiesSize) {

		int currentUni = universities[i];

		info[infoPos].action = "getKPIPoints";
		info[infoPos].expected = state.unis[currentUni].numKPIPoints;
		info[infoPos].got = getKPIpoints(game, currentUni);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of KPIs for uni number %d", currentUni);

		infoPos++;

		info[infoPos].action = "getARCs";
		info[infoPos].expected = state.unis[currentUni].numARCs;
		info[infoPos].got = getARCs(game, currentUni);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of ARCs for uni number %d", currentUni);

		infoPos++;

		info[infoPos].action = "getGO8s";
		info[infoPos].expected = state.unis[currentUni].numGroupOfEights;
		info[infoPos].got = getGO8s(game, currentUni);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of GO8s for uni number %d", currentUni);

		infoPos++;

		info[infoPos].action = "getCampuses";
		info[infoPos].expected = state.unis[currentUni].numCampuses;
		info[infoPos].got = getCampuses(game, currentUni);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of campuses for uni number %d", currentUni);

		infoPos++;

		info[infoPos].action = "getIPs";
		info[infoPos].expected = state.unis[currentUni].numIPs;
		info[infoPos].got = getIPs(game, currentUni);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of IPs for uni number %d", currentUni);

		infoPos++;

		info[infoPos].action = "getPublications";
		info[infoPos].expected = state.unis[currentUni].numPublications;
		info[infoPos].got = getPublications(game, currentUni);
		sprintf(info[infoPos].helpText, "The game did not find the correct number of publications for uni number %d", currentUni);

		infoPos++;

		int j = 0;
		while (j < NUM_DISCIPLINES) {
			info[infoPos].action = "getStudents";
			info[infoPos].expected = state.unis[currentUni].numStudents[j];
			info[infoPos].got = getStudents(game, currentUni, j);
			sprintf(info[infoPos].helpText, "The game did not find the correct number of students for uni number %d and discipline %d", currentUni, j);

			infoPos++;

			int k = 0;
			while (k < NUM_DISCIPLINES) {
				info[infoPos].action = "getExchangeRate";
				info[infoPos].expected = state.unis[currentUni].numExchangeRate[j][k];
				info[infoPos].got = getExchangeRate(game, currentUni, j, k);
				sprintf(info[infoPos].helpText, "The game did not find the correct exchange rate for uni number %d, discipline from %d and discipline to %d", currentUni, j, k);

				infoPos++;

				k++;
			}

				j++;
			}

		i++;
	}

	advAssert(game, info, infoPos);
}


int printAction(char* action, int actionStep) {
	if (actionStep == 0) {
		printf(RESET CYAN  "\n------------------ Start Tests -----------------\n");
	} else {
		printf(RESET CYAN  "------------------------------------------------\n");
	}
	printf(RESET CYAN  "Action %d: %s" RESET "\n", actionStep, action);

	actionStep++;

	return actionStep;
}

void printEnd() {
	printf(RESET CYAN  "------------------- End Tests ------------------\n\n");
	printf(RESET YELLOW);
	printf("            ,:/+/-                      \n");
	printf("            /M/              .,-=;//;-  \n");
	printf("       .:/= ;MH/,    ,=/+%%$XH@MM#@:     \n");
	printf("      -$##@+$###@H@MMM#######H:.    -/H#\n");
	printf(" .,H@H@ X######@ -H#####@+-     -+H###@X\n");
	printf("  .,@##H;      +XM##M/,     =%%@###@X;-  \n");
	printf("X%%-  :M##########$.    .:%%M###@%%:       \n");
	printf("M##H,   +H@@@$/-.  ,;$M###@%%,          -\n");
	printf("M####M=,,---,.-%%%%H####M$:          ,+@##\n");
	printf("@##################@/.         :%%H##@$- \n");
	printf("M###############H,         ;HM##M$=     \n");
	printf("#################.    .=$M##M$=         \n");
	printf("################H..;XM##M$=          .:+\n");
	printf("M###################@%%=           =+@MH%%\n");
	printf("@################M/.          =+H#X%%=   \n");
	printf("=+M##############M,       -/X#X+;.      \n");
	printf("  .;XM##########H=    ,/X#H+:,          \n");
	printf("     .=+HM######M+/+HM@+=.              \n");
	printf("         ,:/%%XM####H/.                  \n");
	printf("               ,.:=-.                   \n\n");
	printf(BOLD GREEN  "All tests passed! You are awesome!!1!1 :D\n");
	printf(RESET);

}
