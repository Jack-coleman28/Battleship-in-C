#include "battleboat.h"

//////////////////////////////////////////////////////////////////////////////////
// Company: WSU CPTS 121
// Programmer: Jack   
// 
// Create Date: 10/26/2018 
// Design Name: Programming Assignment 6 - Battleship 
// Project Name: --
// Description: -
// Revision:  -
// Additional Comments: -
//						
//////////////////////////////////////////////////////////////////////////////////
int main(void)
{
	srand((unsigned int)time(0)); //seed rando
	int mainLoopStatus = READY; //set initial status
	FILE *battleship = NULL; //outfile to NULL
	ship_length[0] = 5;
	ship_length[1] = 4;
	ship_length[2] = 3;
	ship_length[3] = 3;
	ship_length[4] = 2;
	ship_characters[0] = 'c';
	ship_characters[1] = 'b';
	ship_characters[2] = 's';
	ship_characters[3] = 'r';
	ship_characters[4] = 'd';

	battleship = fopen("battleship.log", "w+"); //open battleship (outlog) for writing and reading 

	resetBoard(player_Board, NUMOFROWS, NUMOFCOLS, NUMOFBOARDS); //initialize board array
	resetStats(Stats); //set the stats to clean numbers
	reset_player_names(player_names, NUMOFPLAYERS); //set the name strings to clean values 
	system("cls");
	while (mainLoopStatus < EXIT)
	{
		//call Do_main_menu()
		gameMenu(); //print options (rules and game or exit)	
		mainLoopStatus = getSelectOption(); //get input choice(1, 2) & set mainLoopStatus
		system("cls");
		switch (mainLoopStatus) //switch through input choice
		{
		case PLAYGAME: //play game
			printRules(); //print rules
			playGame(battleship); //call game subroutine
			mainLoopStatus = EXIT; //force exit case
		case EXIT: //leave if wanted
			system("cls");
			printf("\n               Thanks for playing Battleship!\n\n");
			printStats(Stats);
			system("pause");
			break;
		}
	}
	fclose(battleship); //close battleship (outfile)
	return 0;
}
