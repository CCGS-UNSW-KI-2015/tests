// Game.c

//----------#include-----------//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Game.h"

//----------#defines----------//

#define BOARD_SIZE 19
#define DEFAULT_PLAYERS {0, 3, 3, 1, 1, 1}
#define NUM_DISCIPLINES 6

//-----------Structs-----------//

typedef struct _game * Game;
typedef struct _hex hex;
typedef struct _vert vert;
typedef struct _edge edge;
typedef struct _player player;

typedef struct _hex {
	int hexID; // 1-19 starting with 1 at top left
	int hexDiscipline;


	hex *hexUp;
	hex *hexDown;
	hex *hexUpLeft;
	hex *hexUpRight;
	hex *hexDownLeft;
	hex *hexDownRight;

	vert *vertUpLeft;
	vert *vertUpRight;
	vert *vertLeft;
	vert *vertRight;
	vert *vertDownLeft;
	vert *vertDownRight;

	edge *edgeUp;
	edge *edgeDown;
	edge *edgeUpLeft;
	edge *edgeUpRight;
	edge *edgeDownLeft;
	edge *edgeDownRight;

} hex;

typedef struct _vert {
	int hasUni;
	int hasGO8;

	int teamID;


	hex *hexLeft;
	hex *hexRight;
	hex *hexVertical;

	vert *vertLeft;
	vert *vertRight;
	vert *vertVertical;

	edge *edgeLeft;
	edge *edgeRight;
	edge *edgeVertical;

} vert;

typedef struct _edge {
	int hasARC;

	int teamID;

	hex *hexLeft;
	hex *hexRight;

	vert *vertUp;
	vert *vertDown;

} edge;

typedef struct _player{
	int playerID;

	int numARCs;
	int numPubs;
	int numIPs;
	int students[NUM_DISCIPLINES];

	int kpiPoints;

} player;

typedef struct _game {
	int currentTurn;

	int disciplines[BOARD_SIZE];
	int dice[BOARD_SIZE];

	vert vertArray[48];
	hex hexArray[19];
	edge edgeArray[72];

	vert * entryPoint;

	player playerArray[3];

} *Game;

//------------Local Functions--------------//

static player newPlayer(int playerID);


//------------Main-------------//


//------------Building Map Functions--------//

//------------Interface functons------------//

Game newGame(int discipline[], int dice[]){
	Game game = (Game)malloc(sizeof(Game));

	int i = 0;
	while (i < BOARD_SIZE){
		game->disciplines[i] = discipline[i];
		game->dice[i] = dice[i];
		i++;
	}

	game->currentTurn = -1;


	int playerI = 0;
	while (playerI < 3){
		game->playerArray[playerI] = newPlayer(playerI + 1);
		playerI++;
	}

	return game;
}

void disposeGame(Game g) {
	free(g);
}

void makeAction(Game g, action a) {
	if (a.actionCode == PASS) {
		//Do nothing
		g->currentTurn++;
	}
	else if (a.actionCode == BUILD_CAMPUS) {
		// check if the location is connected to an ARC grant
		// TODO

		// check if there's enough students
		if (g->playerArray[g->currentTurn].students[STUDENT_BPS] < 1 ||
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_BQN] < 1 ||
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MJ] < 1 ||
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MTV] < 1) {
			//None
		}
		else {
			// Add a campus and take the cost from the user
			// TODO - add the campus
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_BPS]--;
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_BQN]--;
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MJ]--;
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MTV]--;

			// also add 10 KPI points
			g->playerArray[g->currentTurn % NUM_UNIS].kpiPoints += 10;
		}
	}
	else if (a.actionCode == BUILD_GO8) {
		// check if there's a campus by the player
		// check if there's enough students
        if (g->playerArray[g->currentTurn].students[STUDENT_MJ] < 2 ||
            g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MMONEY] < 3) {
            // None
        } else {
            // Remove the campus, add a GO8 campus and take the cost from the user
            g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MJ] -= 2;
            g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MMONEY] -= 3;
            
            // add 10 KPI points (20 for building G08, -10 for removing a campus)
            g->playerArray[g->currentTurn % NUM_UNIS].kpiPoints += 10;
        }
	}
	else if (a.actionCode == OBTAIN_ARC) {
		// check if the location of the player is connected to his/her ARC
		// check if there's enough students
		// Add arc and take the cost from the user
		// Add 2 KPI points
	}
	else if (a.actionCode == START_SPINOFF) {
		// check if there's enough students
		// 1/3 of the chance will be OBTAIN_IP_PATENT
		// if not, then OBTAIN_PUBLICATION
		if (g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MJ] < 1 ||
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MTV] < 1 ||
			g->playerArray[g->currentTurn % NUM_UNIS].students[STUDENT_MMONEY] < 1) {
			//None
		}
		else {
			// Create a sort-of-almost-random number
			srand((unsigned int)time(NULL));//Simpler
			int r = rand() % 3;
			if (r == 0) {
				a.actionCode = OBTAIN_IP_PATENT;
				makeAction(g, a);
			}
			else {
				a.actionCode = OBTAIN_PUBLICATION;
				makeAction(g, a);
			}
		}
	}
	else if (a.actionCode == OBTAIN_PUBLICATION) {
		// increase the number of publications by 1
		g->playerArray[g->currentTurn % NUM_UNIS].numPubs++;
	}
	else if (a.actionCode == OBTAIN_IP_PATENT) {
		// increase the number of IP patents by 1
		// increase the KPI points by 10
		g->playerArray[g->currentTurn % NUM_UNIS].numIPs++;
		g->playerArray[g->currentTurn % NUM_UNIS].kpiPoints += 10;
	}
	else if (a.actionCode == RETRAIN_STUDENTS) {
		// see if (disciplineFrom != STUDENT_THD)
		if (a.disciplineFrom == STUDENT_THD) {
			//None
		}
		else {
			// Use getExchangeRate()
			// see if there's enough students
			// convert the 3 students of disciplineFrom into disciplineTo
		}
	}
}

void throwDice(Game g, int diceScore){
	//Adv turn
	g->currentTurn++;
	//Give resources
}

int getDiscipline(Game g, int regionID){
	return g->disciplines[regionID];
}

int getDiceValue(Game g, int regionID){
	return g->dice[regionID];
}

int getMostARCs(Game g){
	int uniWithARCs = NO_ONE;
	int mostARCs = 0;

	char allEqual = 1;

	int i = 1;
	while (i <= NUM_UNIS){
		if (g->playerArray[i - 1].numARCs > mostARCs){
			uniWithARCs = i;
			mostARCs = g->playerArray[i - 1].numARCs;
		}

		if (g->playerArray[i - 1].numARCs != mostARCs && i != 1) {
			allEqual = 0;
		}
		i++;
	}

	if (allEqual == 1) {
		uniWithARCs = NO_ONE;
	}

	return uniWithARCs;
}

int getMostPublications(Game g){
	int uniWithPubs = NO_ONE;
	int mostPubs = 0;

	int i = 1;
	while (i <= 3){
		if (g->playerArray[i - 1].numPubs > mostPubs){
			uniWithPubs = i;
			mostPubs = g->playerArray[i - 1].numPubs;
		}
		i++;
	}

	return uniWithPubs;
}

int getTurnNumber(Game g){
	return g->currentTurn;
}

int getWhoseTurn(Game g){
	int returnValue;
	if (g->currentTurn == -1) {
		returnValue = NO_ONE;
	}
	else {
		returnValue = g->playerArray[g->currentTurn % NUM_UNIS].playerID;
	}
	return returnValue;
}

int getCampus(Game g, path pathToVertex){
	return 0; // Placeholder so it compiles
}

int getARC(Game g, path pathToEdge){
	return 0; // Placeholder
}

int isLegalAction(Game g, action a){
	return 0; // Placeholder
}

int getKPIpoints(Game g, int player){
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return g->playerArray[player].kpiPoints;
}

int getARCs(Game g, int player) {
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return g->playerArray[player].numARCs;
}

int getGO8s(Game g, int player){
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return 0; // Placeholder
}

int getCampuses(Game g, int player){
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return 0; // Placeholder
}

int getIPs(Game g, int player){
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return g->playerArray[player].numIPs;
}

int getPublications(Game g, int player){
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return g->playerArray[player].numPubs;
}

int getStudents(Game g, int player, int discipline){
	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_UNIS) {
		if (g->playerArray[i].playerID == player) {
			player = i;
		}
		i++;
	}
	return g->playerArray[player].students[discipline];
}

int getExchangeRate(Game g, int player,
	int disciplineFrom, int disciplineTo){
	return 0; // Placeholder
}

static player newPlayer(int playerID){
	player playerNew;

	playerNew.playerID = playerID;

	int buffer[NUM_DISCIPLINES] = DEFAULT_PLAYERS;
	int i = 0;
	while (i < NUM_DISCIPLINES) {
		playerNew.students[i] = buffer[i];
		i++;
	}

	playerNew.numARCs = 0;
	playerNew.numPubs = 0;
	playerNew.numIPs = 0;
	playerNew.kpiPoints = 0;

	return playerNew;
}

