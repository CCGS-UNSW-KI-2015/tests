/* testState.c
 * A bunch of tests for the game state.
 * Includes a verbose advAssert() function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "testState.h"

// Color ANSI escape sequences and 'fake' booleans
// are #defined in testState.h

int defaultSize = 12;
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
			char disciplineType[10];

			if (rawType == STUDENT_THD) {
				strcpy(disciplineType, "THD");
			} else if (rawType == STUDENT_BPS) {
				strcpy(disciplineType, "BPS");
			} else if (rawType == STUDENT_MJ) {
				strcpy(disciplineType, "MJ");
			} else if (rawType == STUDENT_MTV) {
				strcpy(disciplineType, "MTV");
			} else if (rawType == STUDENT_MMONEY) {
				strcpy(disciplineType, "MMONEY");
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
			printf(RESET BLUE "KPI Points            | %d\n", getKPIpoints(game, i));
			printf(           "ARCs                  | %d\n", getARCs(game, i));
			printf(           "GO8s                  | %d\n", getGO8s(game, i));
			printf(           "Campuses              | %d\n", getCampuses(game, i));
			printf(           "IPs                   | %d\n", getIPs(game, i));
			printf(           "Publications          | %d\n", getPublications(game, i));

			printf(RESET BLUE "------------------------------------------------\n");

			printf(BOLD BLUE  "Discipline            | Students\n");
			printf(RESET BLUE "THD                   | %d\n", getStudents(game, player, STUDENT_THD));
			printf(RESET BLUE "BPS                   | %d\n", getStudents(game, player, STUDENT_BPS));
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
	}
	printf(RESET CYAN "------------ Premature End of Tests ------------\n");
	printf(RESET "\n");
	exit(0);
}

void assertState(Game game, stateSet state) {
	// I'm assuming there will never be
	// more than 1000 checks necessary...
    assertInfo info[1000];
    assertInfo currentInfo;
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
    while (i < PATH_LIMIT) {
    	info[infoPos].action = "getCampus";
	    info[infoPos].expected = state.paths[i].numCampus;
	    info[infoPos].got = getCampus(game, state.paths[i].myPath);
	    sprintf(info[infoPos].helpText, "The game did not find the correct campus at path number %d", i);

	    infoPos++;

	    info[infoPos].action = "getARC";
	    info[infoPos].expected = state.paths[i].numARC;
	    info[infoPos].got = getARC(game, state.paths[i].myPath);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of ARCs for path number %d", i);

	    infoPos++;

	    i++;
    }

    int iterator = 0;
    while (i < NUM_UNIS) {
    	int i = universities[iterator];
    	info[infoPos].action = "getKPIPoints";
	    info[infoPos].expected = state.unis[i].numKPIPoints;
	    info[infoPos].got = getKPIpoints(game, i);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of KPIs for uni number %d", i);

	    infoPos++;

	    info[infoPos].action = "getARCs";
	    info[infoPos].expected = state.unis[i].numARCs;
	    info[infoPos].got = getARCs(game, i);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of ARCs for uni number %d", i);

	    infoPos++;

	    info[infoPos].action = "getGO8s";
	    info[infoPos].expected = state.unis[i].numGroupOfEights;
	    info[infoPos].got = getGO8s(game, i);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of GO8s for uni number %d", i);

	    infoPos++;

	    info[infoPos].action = "getCampuses";
	    info[infoPos].expected = state.unis[i].numCampuses;
	    info[infoPos].got = getCampuses(game, i);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of campuses for uni number %d", i);

	    infoPos++;

	    info[infoPos].action = "getIPs";
	    info[infoPos].expected = state.unis[i].numIPs;
	    info[infoPos].got = getIPs(game, i);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of IPs for uni number %d", i);

	    infoPos++;

	    info[infoPos].action = "getPublications";
	    info[infoPos].expected = state.unis[i].numPublications;
	    info[infoPos].got = getPublications(game, i);
	    sprintf(info[infoPos].helpText, "The game did not find the correct number of publications for uni number %d", i);

	    infoPos++;

	    int j = 0;
	    while (j < NUM_DISCIPLINES) {
		    info[infoPos].action = "getStudents";
		    info[infoPos].expected = state.unis[i].numStudents[j];
		    info[infoPos].got = getStudents(game, i, j);
		    sprintf(info[infoPos].helpText, "The game did not find the correct number of ARCs for uni number %d and discipline %d", i, j);

		    infoPos++;

		    int k = 0;
		    while (k < NUM_DISCIPLINES) {
			    info[infoPos].action = "getExchangeRate";
			    info[infoPos].expected = state.unis[i].numExchangeRate[j][k];
			    info[infoPos].got = getExchangeRate(game, i, j, k);
			    sprintf(info[infoPos].helpText, "The game did not find the correct number of ARCs for uni number %d, discipline from %d and discipline to %d", i, j, k);

			    infoPos++;

			    k++;
		    }

		    j++;
	    }

		iterator++;
    }

    advAssert(game, info, infoPos);
}


int printAction(char* action, int actionStep) {
	if (actionStep == 0) {
		printf(RESET CYAN  "------------------ Start Tests -----------------\n");
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
