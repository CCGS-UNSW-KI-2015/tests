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
	
} player;

typedef struct _game { 
	int currentTurn;
	
	int disciplines[BOARD_SIZE];
	int dice[BOARD_SIZE];
	
	player playerArray[3];
	
} * Game;

//------------Main-------------//



Game newGame(int discipline[], int dice[]){
	Game game = (Game) malloc(sizeof(Game));
	
	int i = 0;
	while(i < BOARD_SIZE){
		game->disciplines[i] = discipline[i];
		game->dice[i] = dice[i];
		i++;
	}
	
	//DEBUG//
	
	printf("Game dice[0] : %d", game->dice[0]);
	
	//DEBUG//
	
	return game;
}

//------------Building Map Functions--------//

int getTurnNumber(Game g){ 
	return -1; 
}

void throwDice(Game g, int diceScore){
	//Read the description of the funciton in game.h...
	//It takes in a diceScore ie rolling the dice and then does stuff
}
