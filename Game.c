//Game.c

#include "Game.h"

Game newGame(int discipline[], int dice[]){
	Game game = { 0 };
	return game;
}

void throwDice(Game g, int diceScore){
	//Read the description of the funciton in game.h...
	//It takes in a diceScore ie rolling the dice and then does stuff
}

void disposeGame (Game g) {

}

void makeAction (Game g, action a) {

}

int getDiscipline (Game g, int regionID) {
	return 0;
}


int getDiceValue (Game g, int regionID) {
	return 0;
}

int getMostARCs (Game g) {
	return NO_ONE;
}

int getMostPublications (Game g) {
	return 0;
}


int getTurnNumber(Game g) {
	return -1;
}

int getWhoseTurn (Game g) {
	return -1;
}


int getCampus(Game g, path pathToVertex) {
	return 0;
}


int getARC(Game g, path pathToEdge) {
	return FALSE;
}

int isLegalAction (Game g, action a) {
	return TRUE;
}

int getKPIpoints (Game g, int player) {
	return 0;
}

// return the number of ARC grants the specified player currently has
int getARCs (Game g, int player) {
	return 1;
}

// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, int player) {
	return 1;
}

// return the number of normal Campuses the specified player currently has
int getCampuses (Game g, int player) {
	return 1;
}

// return the number of IP Patents the specified player currently has
int getIPs (Game g, int player) {
	return 1;
}

// return the number of Publications the specified player currently has
int getPublications (Game g, int player) {
	return 1;
}

// return the number of students of the specified discipline type
// the specified player currently has
int getStudents (Game g, int player, int discipline) {
	return 1;
}

// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one
// student of discipline type disciplineTo.  This will depend
// on what retraining centers, if any, they have a campus at.
int getExchangeRate (Game g, int player,
                     int disciplineFrom, int disciplineTo) {
	return 1;
}
