#ifndef BATTLEBOAT_H
#define BATTLEBOAT_H

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DEBUG_ON 1  //For debug (see computer boats for faster debugging) 
#define NUMOFROWS 10 
#define NUMOFCOLS 10
#define NUMOFBOARDS 2
#define NUMOFBOATS 5
#define NUMOFPLAYERS 2

enum game_statuses { READY, PLAYGAME, EXIT }; //
enum colors { black, red, green, yellow, blue, purple, cyan, white }; //color enumeration 

typedef struct stats
{
	int total_hits;
	int total_miss;
	int total_shot;
	double ratio;
	int winner;
	int carrier;
	int battleship;
	int cruiser;
	int submarine;
	int destroyer;
};
struct stats Stats[NUMOFPLAYERS];

char player_Board[NUMOFROWS][NUMOFCOLS][NUMOFBOARDS];
char player_names[NUMOFPLAYERS][50];
int ship_length[NUMOFBOATS];
char ship_characters[NUMOFBOATS];

void playGame(FILE *battleships);
void printRules(void);
int getSelectOption(void);
void gameMenu(void);
void resetBoard(char player_Board[NUMOFROWS][NUMOFCOLS][NUMOFBOARDS], int numRows, int numColumns, int numBoards);
void resetStats(struct stats Stats[]);
void reset_player_names(char player_names[NUMOFPLAYERS][50], int NumberofPlayers);
void getPlayerName(char player_names[NUMOFPLAYERS][50]);
void boatPlacementMethod(char player1_Board);
void manualPlacement();
void autoPlacement(int player_index);
int pickPlayer();
void evaluateArray(struct stats Stats[]);
void printGrid();
void printStats(struct stats Stats[]);
void getPlayerShot(int *x, int *y);
void markShot();
void computerTurn(int *x, int *y);
void callLog(FILE *battleship, int player_num, int x_coor, int y_coor);
void writeOutlog(FILE *battleship);
int boundaryCheck(int x, int y, int player_index, int length, int direction);
void back_color(i);
void text_color(i);

#endif
