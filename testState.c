/* testState.c
 * A bunch of tests for the game state.
 * Includes a verbose advAssert() function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Game.h"
#include "testState.h"

// Color ANSI escape sequences are in testState.h

int defaultSize = 12;
int universitiesSize = 3;
int universities[] = {UNI_A, UNI_B, UNI_C};

void advAssert(Game game, char* action, int expected, int got, char* helpText) {
	if (expected != got) {
		printf(RED         "================================================\n");
		printf(BOLD RED    "Assertion failed!\n");
		printf(            "Expected %d got %d ", expected, got);
		printf(            "for function \"%s\"\n", action);
		printf(RESET RED   "%s\n\n", helpText);
		printf(BOLD RED    "====================== Dump ====================\n");
		printf(RESET GREEN "------------------------------------------------\n");
		printf(RESET GREEN "Region Information\n");
		printf(RESET GREEN "------------------------------------------------\n");
		printf(BOLD GREEN  "getDiscipline\n");
		printf(BOLD GREEN  "Region ID | Type\n" RESET GREEN);

		int i = 0;
		while (i < defaultSize) {
			int rawType = STUDENT_THD; // getDiscipline(game, i);
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
			int diceValue = 3; // getDiceValue(game, i);

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
			printf(RESET BLUE "KPI Points            | %d\n", 1); // getKPIpoints(game, i);
			printf(           "ARCs                  | %d\n", 2); // getARCs(game, i);
			printf(           "GO8s                  | %d\n", 3); // getGO8s(game, i);
			printf(           "Campuses              | %d\n", 4); // getCampuses(game, i);
			printf(           "IPs                   | %d\n", 5); // getIPs(game, i);
			printf(           "Publications          | %d\n", 6); // getPublications(game, i);

			printf(RESET BLUE "------------------------------------------------\n");

			printf(BOLD BLUE  "Discipline            | Students\n");
			printf(RESET BLUE "THD                   | %d\n", 4); // getStudents(game, player, STUDENT_THD) ... you get the point
			printf(RESET BLUE "BPS                   | %d\n", 5);
			printf(RESET BLUE "MJ                    | %d\n", 6);
			printf(RESET BLUE "MTV                   | %d\n", 7);
			printf(RESET BLUE "MMONEY                | %d\n", 8);

			i++;
		}

		printf(RESET BLUE "================================================\n");

		printf(RESET CYAN "------------------------------------------------\n");
		printf(BOLD CYAN  "Game information\n");
		printf(RESET CYAN "------------------------------------------------\n");
		printf(BOLD CYAN  "Attribute             | Value (or player)\n");
		printf(RESET CYAN "Most ARCs             | %d\n", 1); // getMostARCs(game);
		printf(           "Most Publications     | %d\n", 2); // getMostPublications(game);
		printf(           "Turn Number           | %d\n", 3); // getTurnNumber(game);
		printf(           "Whose Turn            | %d\n", 4); // getWhoseTurn(game);

		printf(RED BOLD   "================= END OF DUMP ==================\n");

		printf(RESET);
	}
}

void assertState(Game game, stateSet state) {
    // TODO
}
