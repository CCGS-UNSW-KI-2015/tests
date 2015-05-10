// Runs the game for human input!

#include "Game.h"

#include <stdlib.h>
#include <stdio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"

#define RESET   "\x1b[0m"

#define NUM_DISCIPLINES 6

int rollDice();
void displayGameInfo(Game game);
void displayDiceResults(Game game, int diceRoll);
void displayPlayerAssets(Game game, int playerId);
int displayPlayerInfo(Game game);
void castPlayerAction(Game game, int playerId);
void displayMap(Game game);

int main(int argc, char *argv[]) {
	Game game;

	int defaultDis[] = DEFAULT_DISCIPLINES;
	int defaultDice[] = DEFAULT_DICE;

	game = newGame(defaultDis, defaultDice);

	printf(RESET BLUE "----------------------------------------\n");
	printf(BOLD GREEN "Game initialised!\n");

	while (1) {
		printf(RESET BLUE "------------ START NEW TURN ------------\n");
		displayGameInfo(game);
		int diceValue = rollDice(game);
		displayDiceResults(game, diceValue);
		int currentPlayer = displayPlayerInfo(game);
		castPlayerAction(game, currentPlayer);
		printf("\n");
	}
}

int rollDice(Game game) {

	int diceRoll = -1;

	while (diceRoll < 2 || diceRoll > 12) {
		printf(BOLD YELLOW "\nEnter a dice roll number: " RESET YELLOW);

		scanf("%d", &diceRoll);

		if (diceRoll >= 2 && diceRoll <= 12) {
			throwDice(game, diceRoll);
		} else {
			printf(BOLD RED "Dice rolls must be a number between 2 and 12!\n");
			printf("This is an input sink, press a letter on your keyboard\n");
			printf("followed by the enter key\n");
			char sink[10];
			scanf("%s", &sink);
		}
	}

	return diceRoll;
}

void displayGameInfo(Game game) {
	printf(BOLD BLUE "This will be turn number: %d\n", getTurnNumber(game) + 1);
	printf(RESET BLUE "Player with the most ARCs:         %d\n", getMostARCs(game));
	printf("Player with the most publications: %d\n", getMostPublications(game));
	displayMap(game);
}

void displayDiceResults(Game game, int diceRoll) {
	int i = 0;
	while (i < NUM_REGIONS) {
		if (getDiceValue(game, i) == diceRoll) {
			printf(BLUE BOLD "Region %d has its resource type of %d distributed\n", i, getDiscipline(game, i));
		}
		i++;
	}
}

void displayPlayerAssets(Game game, int playerId) {
	printf("%d KPI Points\n", getKPIpoints(game, playerId));
	printf("%d ARCs\n", getARCs(game, playerId));
	printf("%d GO8s\n", getGO8s(game, playerId));
	printf("%d campuses\n", getCampuses(game, playerId));
	printf("%d IPs\n", getIPs(game, playerId));
	printf("%d publications\n\n", getPublications(game, playerId));

	printf("%d THDs\n", getStudents(game, playerId, STUDENT_THD));
	printf("%d BPSs\n", getStudents(game, playerId, STUDENT_BPS));
	printf("%d BQNs\n", getStudents(game, playerId, STUDENT_BQN));
	printf("%d MJs\n", getStudents(game, playerId, STUDENT_MJ));
	printf("%d MTVs\n", getStudents(game, playerId, STUDENT_MTV));
	printf("%d MMONEYs\n", getStudents(game, playerId, STUDENT_MMONEY));
}

int displayPlayerInfo(Game game) {
	int currentPlayer = getWhoseTurn(game);
	printf(CYAN BOLD "\nIt's player %d's turn\n", currentPlayer);
	printf(RESET CYAN "You have:\n");
	displayPlayerAssets(game, currentPlayer);

	return currentPlayer;
}


void castPlayerAction(Game game, int playerId) {
	int complete = 0;

	while (complete == 0) {
		int discardAction = 0;

		printf(BOLD YELLOW "\nEnter action code (or 9 to end turn): " RESET YELLOW);
		int actionCode = -1;

		scanf("%d", &actionCode);

		char confirmationMessage[500];

		action playerAction;

		playerAction.actionCode = actionCode;

		if (actionCode == PASS) {
			sprintf(confirmationMessage, "Pass");
		        complete = 1;
		} else if (actionCode == BUILD_CAMPUS) {
			printf(BOLD YELLOW "Enter path to build campus: " RESET YELLOW);
			scanf("%s", playerAction.destination);
			sprintf(confirmationMessage, "Build campus at: %s", playerAction.destination);
		} else if (actionCode == BUILD_GO8) {
			printf("Enter path to build Go8: ");
			scanf("%s", playerAction.destination);
			sprintf(confirmationMessage, "Build Go8 at: %s", playerAction.destination);
		} else if (actionCode == OBTAIN_ARC) {
			sprintf(confirmationMessage, "Obtain ARC");
		} else if (actionCode == START_SPINOFF) {
			sprintf(confirmationMessage, "Start spinoff");
		} else if (actionCode == OBTAIN_PUBLICATION) {
			sprintf(confirmationMessage, "Obtain publication");
		} else if (actionCode == OBTAIN_IP_PATENT) {
			sprintf(confirmationMessage, "Obtain IP patent");
		} else if (actionCode == RETRAIN_STUDENTS) {
			playerAction.disciplineFrom = -1;
			playerAction.disciplineTo = -1;
			printf(BOLD YELLOW "Discipline from? " RESET YELLOW);
			scanf("%d", &playerAction.disciplineFrom);
			printf(BOLD YELLOW "Discipline to? " RESET YELLOW);
			scanf("%d", &playerAction.disciplineTo);
			sprintf(confirmationMessage,
				"Retrain student from type %d to %d",
				playerAction.disciplineFrom, playerAction.disciplineTo);

			if (playerAction.disciplineFrom < 0 ||
				playerAction.disciplineTo < 0) {
				discardAction = 1;
			}
		} else if (actionCode == 9) {
			printf(BOLD GREEN "Player turn completed!\n");
			complete = 1;
		} else {
			printf(BOLD RED "You entered an invalid action code! Try again.\n");
			printf("This is an input sink, press a letter on your keyboard\n");
			printf("followed by the enter key\n");
			char sink[10];
			scanf("%s", &sink);
			discardAction = 1;
		}

		if (discardAction == 0 && complete == 0) {
			printf(BOLD CYAN "You have selected the action: %s\n", confirmationMessage);
			printf(BOLD YELLOW "Confirm (y/n)? " RESET YELLOW);
			char response;
			scanf(" %c", &response);

			if (response == 'y') {
				makeAction(game, playerAction);
				printf(BOLD GREEN "Action completed!\n");

				printf(RESET CYAN "\nYou now have:\n");
				displayPlayerAssets(game, playerId);
			} else {
				printf(BOLD RED "Action cancelled!\n");
			}
		}
	}
}

void displayMap(Game game) {
	char* colorMap[NUM_DISCIPLINES] = {BLUE, RED, CYAN, YELLOW, GREEN, MAGENTA};

	printf (RESET BLUE    "\nTHD, ");
	printf (RESET RED     "BPS, ");
	printf (RESET CYAN    "BQN, ");
	printf (RESET YELLOW  "MJ, ");
	printf (RESET GREEN   "MTV, ");
	printf (RESET MAGENTA "MMONEY\n");

	// Disciplines and dice rolls
	printf (RESET BLUE    "Disciplines and dice rolls:\n");

	// It's beautiful
	printf ("      %s%02d\n", colorMap[getDiscipline(game, 7)], getDiceValue(game, 7));
	printf ("   %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 3)],
	        getDiceValue(game, 3),
	        colorMap[getDiscipline(game, 12)],
	        getDiceValue(game, 12));
	printf ("%s%02d    %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 0)],
	        getDiceValue(game, 0),
	        colorMap[getDiscipline(game, 8)],
	        getDiceValue(game, 8),
	        colorMap[getDiscipline(game, 16)],
	        getDiceValue(game, 16));
	printf ("   %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 4)],
	        getDiceValue(game, 4),
	        colorMap[getDiscipline(game, 13)],
	        getDiceValue(game, 13));
	printf ("%s%02d    %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 1)],
	        getDiceValue(game, 1),
	        colorMap[getDiscipline(game, 9)],
	        getDiceValue(game, 9),
	        colorMap[getDiscipline(game, 17)],
	        getDiceValue(game, 17));
	printf ("   %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 5)],
	        getDiceValue(game, 5),
	        colorMap[getDiscipline(game, 14)],
	        getDiceValue(game, 14));
	printf ("%s%02d    %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 2)],
	        getDiceValue(game, 2),
	        colorMap[getDiscipline(game, 10)],
	        getDiceValue(game, 10),
	        colorMap[getDiscipline(game, 18)],
	        getDiceValue(game, 18));
	printf ("   %s%02d    %s%02d\n",
	        colorMap[getDiscipline(game, 6)],
	        getDiceValue(game, 6),
	        colorMap[getDiscipline(game, 15)],
	        getDiceValue(game, 15));
	printf ("      %s%02d\n\n", colorMap[getDiscipline(game, 11)], getDiceValue(game, 11));

	// Campuses and GO8s
	printf (RESET RED   "Player One, ");
	printf (RESET GREEN "Player Two, ");
	printf (RESET CYAN  "Player Three\n");
	printf (RESET BLUE  "C means Campus, G means GO8\n");
	
	printf (            "Campuses / GO8s: TODO\n");
	
	// When resolvePath() is working, this should be implemented.

	/*    * *
           * *   * *
        * *   * *   * *
       *   * *   * *   *
        * *   * *   * *
       *   * *   * *   *
        * *   * *   * *
       *   * *   * *   *
        * *   * *   * *
           * *   * *
              * *
       */

	printf (RESET BLUE "ARCs: TODO\n");
}
