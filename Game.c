//Game.c

//----------#include-----------//

#include <stdio.h>
#include <stdlib.h>

#include "game.h"

//----------#defines----------//

#define BOARD_SIZE 19

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
	int hasRoad;
	
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
	
	int kpiPoints;

} player;

typedef struct _game { 
	int currentTurn;
	
	int disciplines[BOARD_SIZE];
	int dice[BOARD_SIZE];
	
	player playerArray[3];
	
} * Game;

//------------Local Functions--------------//

static player newPlayer(playerID);


//------------Main-------------//


//------------Building Map Functions--------//

//------------Interface functons------------//

Game newGame(int discipline[], int dice[]){
	Game game = (Game) malloc(sizeof(Game));
	
	int i = 0;
	while(i < BOARD_SIZE){
		game.disciplines[i] = discipline[i];
		game.dice[i] = dice[i];
		i++;
	}
	
	game->currentTurn = -1;


	int playerI = 0;
	while (playerI < 3){
		game.playerArray[playerI] = newPlayer(playerI + 1);
	}

	//Map info

	vert vertArray[48];
	hex hexArray[19];
	edge edgeArray[72];

	vert * entryPoint;

	//DEBUG//
	
	printf("Game dice[0] : %d", game.dice[0]);
	
	//DEBUG//
	
	return game;
}

void disposeGame (Game g) {
	free(g);
}
 
void makeAction (Game g, action a);
 
void throwDice(Game g, int diceScore){
	//Adv turn
	g.currentTurn++;
	//Give resources??
}
 
int getDiscipline (Game g, int regionID){
	return g.disciplines[regionID];
}

int getDiceValue (Game g, int regionID){
	return g.dice[regionID];   
}

int getMostARCs (Game g){
	int uniWithARCs = NO_ONE;
	int mostARCs = 0;
	
	int i = 1;
	while (i <= 3){
		if(g.playerArray[i-1].numARCs > mostARCs ){
			uniWithARCs = i;
			mostARCs = g.playerArray[i-1].numARCs;
		}
		i++;
	}

	return uniWithARCs;
}

int getMostPublications (Game g){
	int uniWithPubs = NO_ONE;
	int mostPubs = 0;
	
	int i = 1;
	while (i <= 3){
		if( g.playerArray[i-1].numPubs > mostPubs ){
			uniWithPubs = i;
			mostPubs = g.playerArray[i-1].numPubs;
		}
		i++;
	}

	return uniWithPubs; 
}

int getTurnNumber(Game g){ 
	return g.currentTurn; 
}
 
int getWhoseTurn (Game g);
 
int getCampus(Game g, path pathToVertex);
 
int getARC(Game g, path pathToEdge);
 
int isLegalAction (Game g, action a);
 
int getKPIpoints(Game g, int player){
	return g.playerArray[player - 1].kpiPoints;
}
 
int getARCs (Game g, int player) {
	return g.playerArray[player - 1].numARCs;
}
 
int getGO8s (Game g, int player);
 
int getCampuses (Game g, int player);
 
int getIPs (Game g, int player);
 
int getPublications (Game g, int player);
 
int getStudents (Game g, int player, int discipline);
 
int getExchangeRate (Game g, int player, 
                     int disciplineFrom, int disciplineTo);

static player newPlayer(playerID){
	player playerNew;

	playerNew.playerID = playerID;

	return playerNew;
}
