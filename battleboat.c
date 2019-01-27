#include "battleboat.h"

/************************************************************
* Function: text_color(int)
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Change Text Color
* Input parameters:  Enum Int #
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void text_color(i)
{
	printf("%c[%dm", 0x1B, i + 30);
}

/************************************************************
* Function: back_color(int)
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Change Background Color
* Input parameters: Enum Int #
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void back_color(i)
{
	printf("%c[%dm", 0x1B, i + 40);
}

/************************************************************
* Function: gameMenu()
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Main game menu. ...printed in YELLOW MY DUDES!!
* Input parameters: -
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void gameMenu()
{
	text_color(yellow);
	//back_color(black);

	printf(" *****************************************************************************************************************\n");
	printf(" *                                            Welcome to Battleship!                                             *\n");
	printf(" *                                                - A war game -                                                 *\n");
	printf(" *                                                                                                               *\n");
	printf(" *                              Select your option below                                                         *\n");
	printf(" *                                                                                                               *\n");
	printf(" *                              1: Rules and start game                                                          *\n");
	printf(" *                              2: Exit game                                                                     *\n");
	printf(" *                                                                                                               *\n");
	printf(" *****************************************************************************************************************\n");

	text_color(white);
	//back_color(black);
	return;
}

/************************************************************
* Function: getSelectOption()
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Gathers player selection for main() loop. Whether they want to view the rules and play or leave.
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions:
*************************************************************/
int getSelectOption()
{
	int selection = 0;

	scanf("%d", &selection);

	return selection;
}

/************************************************************
* Function: printRules()
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Prints rules to battleship. IN CYAN!!!
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void printRules(void)
{
	text_color(cyan);

	printf("*******************************************************************************************************************************************\n\n");
	printf(" > Rules to Battleship:                                                                                                                    *\n");
	printf("                                                                                                                                           *\n");
	printf(" - The object of Battleship is to try and sink all of the other player's before they sink all of your ships.                               *\n");
	printf(" - All of the other player's ships are somewhere on his/her board.  Each board in the physical game has two grids:                         *\n");
	printf(" - the lower (horizontal) section for the player's ships and the upper part (vertical during play) for recording the player's guesses      *\n");
	printf(" - Each player places the 5 ships somewhere on their board.  The ships can only be placed vertically or horizontally.                      *\n");
	printf(" - Diagonal placement is not allowed. No part of a ship may hang off the edge of the board.                                                *\n");
	printf(" - Ships may not overlap each other.  No ships may be placed on another ship. Once the guessing begins, the players may not move the ships.*\n");
	printf(" - The 5 ships are:  Carrier (5), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).                                           *\n");
	printf(" - Player's take turns guessing by calling out the coordinates. The system responds with 'hit' or 'miss' as appropriate.                   *\n");
	printf(" - When all of the squares that one your ships occupies have been hit, the ship will be sunk.   You should announce 'hit and sunk'.        *\n");
	printf(" - As soon as all of one player's ships have been sunk, the game ends.                                                                     *\n");
	printf("                                                                                                                                           *\n");
	printf("*******************************************************************************************************************************************\n\n");

	text_color(white);

	system("pause");
	system("cls");

	return;
}

/************************************************************
* Function: resetBoard()
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Resets main board array. Clears and suspect data that may lay in field.
* Input parameters: char player_Board[NUMOFROWS][NUMOFCOLS][NUMOFBOARDS], int numRows, int numColumns, int numBoards
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void resetBoard(char player_Board[NUMOFROWS][NUMOFCOLS][NUMOFBOARDS], int numRows, int numColumns, int numBoards)
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			for (int g = 0; g < numBoards; g++)
			{
				player_Board[j][i][g] = '~';
			}
		}
	}
	return;
}

/************************************************************
* Function: resetStats(struct stats Stats[])
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018
* Description: Resets main player statistics data structure
* Input parameters: struct stats array
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void resetStats(struct stats Stats[NUMOFPLAYERS])
{
	for (int x = 0; x < NUMOFPLAYERS; x++)
	{
		Stats[x].total_hits = 0;
		Stats[x].total_miss = 0;
		Stats[x].total_shot = 0;
		Stats[x].ratio = 0;
		Stats[x].winner = 0;		
		Stats[x].carrier = 0;		
		Stats[x].battleship = 0;	
		Stats[x].cruiser = 0;		
		Stats[x].submarine = 0;		
		Stats[x].destroyer = 0;		
	}
	return;
}

/************************************************************
* Function: playGame()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Main game play subroutine. Game loop is carried out from here
* Input parameters:
* Returns: -
* Preconditions: main()
* Postconditions: -
*************************************************************/
void playGame(FILE *battleship)
{
	int status = READY, x = -1, y = -1;
	getPlayerName(player_names);

	autoPlacement(1);  //set computer ships
	boatPlacementMethod(player_Board); //auto or manual for player
	if (pickPlayer() == 1)
	{
		computerTurn(&x, &y);
		markShot(x, y, 1);
		evaluateArray(Stats);
		callLog(battleship, 1, x, y);
	}
	evaluateArray(Stats);  //prime for display
	while (status != EXIT) //while (no winner) 
	{
		printGrid(player_Board);
		printStats(Stats);
		getPlayerShot(&x, &y);
		markShot(x, y, 0);
		evaluateArray(Stats);
		callLog(battleship, 0, x, y);
		if (Stats[0].winner == 0)
		{
			computerTurn(&x, &y);
			markShot(x, y, 1);
			evaluateArray(Stats);
			callLog(battleship, 1, x, y);
		}
		if (Stats[0].winner == 1 || Stats[1].winner == 1)
			status = EXIT;
	}//end while loop

	writeOutlog(battleship); 
	return;
}

/************************************************************
* Function: reset_player_names()
* Date Created: Oct 26, 2018
* Date Last Modified: Oct 27, 2018, 2018
* Description: resets and clears player name array.
* Input parameters: int player_names[NUMOFPLAYERS][50]
* Returns: -
* Preconditions: -
* Postconditions: Clean array, ready for new name input.
*************************************************************/
void reset_player_names(char player_names[NUMOFPLAYERS][50], int NumberofPlayers)
{
	for (int x = 0; x < NumberofPlayers; x++)
		player_names[x][0] = 0;

	return;
}//INITIALIZATION

 /************************************************************
 * Function: getPlayerName()
 * Date Created: Oct 26, 2018
 * Date Last Modified: Oct 27, 2018
 * Description: Gathers player 1 (Human) name and records in char array.
 * Input parameters:
 * Returns: -
 * Preconditions: -
 * Postconditions: -  NOTES: computer name is skipped
 *************************************************************/
void getPlayerName(char player_names[NUMOFPLAYERS][50]) //fill in char array for name
{
	printf("\nInput player 1 name: ");
	scanf("%s", ((char*)player_names[0]));
	strcpy(player_names[1], "COMPUTER");
	//player 2 name is computer
		//printf("\nInput player 2 name: ");
		//scanf("%s", ((char*)player_names[0]));
	return;
}

/************************************************************
* Function: boatPlacementMeathod()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Gathers player preferance for ship placement.
* Input parameters: char player_Board
* Returns: -
* Preconditions: -
* Postconditions: -
*************************************************************/
void boatPlacementMethod(char player_Board) //select M for manual or A for auto
{
	char manual;
	int placement_catch = 0;
	printf("Would you like to manually place your boats? If so press 'M', or press 'A' for autoplacement.\n"); //manual or auto?
	scanf(" %c", &manual);

	while (placement_catch == 0)
	{

		switch (manual)
		{
		case 'M': // manual placement
			manualPlacement();
			placement_catch = 1;
			break;
		case 'A': //auto placement
			autoPlacement(0);  //set human player's boats
			placement_catch = 1;
			break;
		default:
			printf("Please make a valid selection.\n");
			break;
		}
	}
}

/************************************************************
* Function: manualPlacement()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Gets player input for ship placement.
* Input parameters:
* Returns: -
* Preconditions: boatPlacementMethod()
* Postconditions: -
*************************************************************/
void manualPlacement()
{
	int xl = 0, yl = 0;
	char direction;
	//text_color(green);
	printf("\nNote: Ships cannot be placed diagonally.\n"); //print Boats cannot be placed diagonally
	printf("Ship placement follows the order: Carrier(5 units), Battleship(4 units), Cruiser(3 units), Submarine(3 units), Destroyer(2 units).\n"); //place boats (Carrier first, Battleship second, Cruiser third, Submarine fourth, and the Destroyer last)
	printf("\nSo remember, you are placing the carrier (size 5) first!\n\n");
	system("pause");
	//text_color(white);
	for (int b = 0; b < NUMOFBOATS; b++) //loop through boats in specific order.
	{
		do
		{
			system("cls");
			printGrid();
			//text_color(green);
			printf("\nPlace the %c-ship ", ship_characters[b]);
			switch (ship_characters[b]) {
			case 'c': printf("(Carrier)"); break;
			case 'b': printf("(Battleship)"); break;
			case 'r': printf("(Cruiser)"); break;
			case 's': printf("(Submarine)"); break;
			case 'd': printf("(Destroyer)"); break;
			}
			printf(", this ship is %d cells long.\n", ship_length[b]);
			printf("Input valid X-Coordinate (Between A and J): ");
			scanf(" %c", &xl);
			printf("Input valid Y-Coordinate (1-10): ");
			scanf("%d", &yl);
			printf("Input a valid direction (V for vertical (Down) or H for horizontal (Right)): ");
			scanf(" %c", &direction);
			//text_color(white);
			xl = xl - 65;  //convert to index 0
			yl = yl - 1;   //convert to index 0
		} while (xl > 9 || xl < 0 || yl > 9 && yl < 0 || (direction != 'V' && direction != 'H')
			|| boundaryCheck(xl, yl, 0, ship_length[b], (direction == 'V') ? (1) : (0)) == 0);

		for (int i = 0; i < ship_length[b]; i++) //write to grid
		{
			if (direction == 'V')
				player_Board[xl][yl + i][0] = ship_characters[b];
			else
				player_Board[xl + i][yl][0] = ship_characters[b];
		}
	}//end loop
	return;
}

/************************************************************
* Function: autoPlacement()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Places ships in array based on randomly populated x and y coordinates.
* Input parameters: -
* Returns: -
* Preconditions: -
* Postconditions: Ships placed in array.
*************************************************************/
void autoPlacement(int player_index)
{
	int xl = 0, yl = 0, direction = 0;

	for (int b = 0; b < NUMOFBOATS; b++) //loop through boats in specific order.
	{
		do
		{
			xl = (rand() % 7);
			yl = (rand() % 7);
			direction = ((rand() % 10) > 5) ? (0) : (1);
		} while (boundaryCheck(xl, yl, player_index, ship_length[b], direction) == 0);

		for (int i = 0; i < ship_length[b]; i++) //write to grid
		{
			if (direction == 1)
				player_Board[xl][yl + i][player_index] = ship_characters[b];
			else
				player_Board[xl + i][yl][player_index] = ship_characters[b];
		}
	}//end loop
	return;
}

/************************************************************
* Function: pickPlayer()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Picks a random player to start with.
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions: -  NOTES: Program will not inform when computer has gone first.
*************************************************************/
int pickPlayer()
{
	return ((rand() % 10) > 5) ? (0) : (1);
}

/************************************************************
* Function: evaluateArray()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 4, 2018
* Description: Evaluates stats based on hits and misses. Plots stats in the fields of the structure.
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions:
*************************************************************/
void evaluateArray(struct stats Stats[NUMOFPLAYERS]) //write to struct?
{
	int oppositePlayer = 0;
	resetStats(Stats);
	//determine if there is a winner (17 HITS)
	for (int i = 0; i < NUMOFROWS; i++) //y-coordinate
	{
		for (int j = 0; j < NUMOFCOLS; j++)  //x-coordinate
		{
			for (int k = 0; k < NUMOFPLAYERS; k++)
			{
				oppositePlayer = (k == 0) ? (1) : (0);
				switch (player_Board[j][i][k])  //Check player board for Opposite player's hit/misses, but own ships.
				{
				case '*':
					Stats[oppositePlayer].total_hits++; break;
				case 'm':
					Stats[oppositePlayer].total_miss++; break;
				case 'c':
					Stats[k].carrier++;  break;
				case 'b':
					Stats[k].battleship++;  break;
				case 'r':
					Stats[k].cruiser++;  break;
				case 's':
					Stats[k].submarine++;  break;
				case 'd':
					Stats[k].destroyer++;  break;
				}
			}
		}
	}
	if (Stats[0].total_hits >= 17)
		Stats[0].winner = 1;
	if (Stats[1].total_hits >= 17)
		Stats[1].winner = 1;

	//determine stats
	//total shots
	Stats[0].total_shot = Stats[0].total_hits + Stats[0].total_miss;
	Stats[1].total_shot = Stats[1].total_hits + Stats[1].total_miss;
	//hit/miss ratio -- cast for ratio
	Stats[0].ratio = (Stats[0].total_miss == 0) ? (0) : ((double)Stats[0].total_hits / (double)Stats[0].total_miss);
	Stats[1].ratio = (Stats[1].total_miss == 0) ? (0) : ((double)Stats[1].total_hits / (double)Stats[1].total_miss);

	return;
}

/************************************************************
* Function: printGrid()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Prints grid with x and y axises (A - J) & (1 - 10)
* Input parameters: -
* Returns: -
* Preconditions: -
* Postconditions:
*************************************************************/
void printGrid()
{
	system("cls");
	text_color(yellow);
	back_color(black);
	//Hits & Misses
	printf("   A B C D E F G H I J - Your Shots\n");
	for (int i = 0; i < NUMOFROWS; i++)
	{
		if (i + 1 < 10)
		{
			text_color(yellow);
			back_color(black);
			printf("%d  ", (i)+1);
		}
		else if (i + 1 == 10)
		{
			text_color(yellow);
			back_color(black);
			printf("%d ", (i)+1);
		}
		back_color(blue);
		for (int j = 0; j < NUMOFCOLS; j++)
		{
			if (DEBUG_ON)
				printf("%c ", player_Board[j][i][1]);
			else
				switch (player_Board[j][i][1])
				{
				case '*':
					text_color(red);
					printf("* ");
					break;
				case 'm':
					text_color(white);
					printf("m ");
					break;
				case '~':
				default:  //or the other player's boats
					text_color(white);
					printf("~ ");
					break;
				}
		}
		putchar('\n');
	}
	//Boats with hits
	text_color(yellow);
	back_color(black);
	printf("\n   A B C D E F G H I J - Your Ships\n");

	for (int i2 = 0; i2 < NUMOFROWS; i2++)
	{
		if (i2 + 1 < 10)
		{
			text_color(yellow);
			printf("%d  ", (i2)+1);
		}
		else if (i2 + 1 == 10)
		{
			text_color(yellow);
			printf("%d ", (i2)+1);
		}
		for (int j2 = 0; j2 < NUMOFCOLS; j2++)
		{
			switch (player_Board[j2][i2][0])
			{
			case 'm':
			case '~':
				text_color(white);
				back_color(blue);
				printf("~ ");
				back_color(black);
				break;
			case '*':
				text_color(red);
				back_color(blue);
				printf("* ");
				back_color(black);
				break;
			default:
				text_color(white);
				back_color(blue);
				printf("%c ", player_Board[j2][i2][0]);
				back_color(black);
			}
		}
		putchar('\n');
	}
	text_color(white);
	back_color(black);
	return;
}

/************************************************************
* Function: printStats(struct stat)
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Prints current stats after each turn.
* Input parameters: Stats
* Returns: -
* Preconditions: -
* Postconditions:
*************************************************************/
void printStats(struct stats Stats[NUMOFPLAYERS])//print from struct 
{
	char SUNK[20] = "";
	sprintf(SUNK, "%c[31mSUNK%c[37m", 0x1B, 0x1B);
	char ACTIVE[20] = "";
	sprintf(ACTIVE, "%c[32mACTIVE%c[37m", 0x1B, 0x1B);

	text_color(white);
	printf("Total Hits   : %d  \t\tTotal Shots    : %d\n", Stats[0].total_hits, Stats[0].total_shot); //total hits
	printf("Total Misses : %d  \t\tHit/Miss Ratio : %0.2lf\n", Stats[0].total_miss, Stats[0].ratio); //total shots
	printf("Player: %s -- Carrier: %s Battleship: %s, Cruiser: %s Submarine: %s, Destroyer: %s\n",
		player_names[0]
		, (Stats[0].carrier > 0) ? (ACTIVE) : (SUNK)
		, (Stats[0].battleship > 0) ? (ACTIVE) : (SUNK)
		, (Stats[0].cruiser > 0) ? (ACTIVE) : (SUNK)
		, (Stats[0].submarine > 0) ? (ACTIVE) : (SUNK)
		, (Stats[0].destroyer > 0) ? (ACTIVE) : (SUNK));
	printf("Player: %s -- Carrier: %s Battleship: %s, Cruiser: %s Submarine: %s, Destroyer: %s\n",
		player_names[1]
		, (Stats[1].carrier > 0) ? (ACTIVE) : (SUNK)
		, (Stats[1].battleship > 0) ? (ACTIVE) : (SUNK)
		, (Stats[1].cruiser > 0) ? (ACTIVE) : (SUNK)
		, (Stats[1].submarine > 0) ? (ACTIVE) : (SUNK)
		, (Stats[1].destroyer > 0) ? (ACTIVE) : (SUNK));
	text_color(white);
	if (Stats[0].winner == 1)
		printf("Winner is %s\n\n", player_names[0]);
	if (Stats[1].winner == 1)
		printf("Winner is %s\n\n", player_names[1]);
	return;
}

/************************************************************
* Function: getPlayerShot()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 5, 2018
* Description: Takes shot coordinates from player and validates them "in house".
* Input parameters:
* Returns: -
* Preconditions: -
* Postconditions:
*************************************************************/
void getPlayerShot(int *x, int *y)//actual firing loop/routine
{
	char str = 0;
	int selection = 0;
	*x = -1;
	*y = -1;
	while ((boundaryCheck(*x, *y, 0, 0, 0) == 0)
		|| (player_Board[*x][*y][1] == 'm')
		|| (player_Board[*x][*y][1] == '*'))
		//keep asking for coordinates
	{
		printf("Please input X-Coordinate, within bounds (A - J): "); //get column letter and row num
		scanf(" %c", &str);
		*x = (int)str - 65;  //convert to index 0
		printf("Please input Y-Coordinate, within bounds (1 - 10): ");
		scanf("%d", &selection);
		*y = selection - 1;  //convert to index 0
	}
	return;
}

/************************************************************
* Function: boundaryCheck()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 6, 2018
* Description: Checks to see if shot coords. and boat placement are within grid. Also check to see if there is overlap when placing boats.
* Input parameters: int x, int y, int player_index, int length, int direction
* Returns: -
* Preconditions: -
* Postconditions: Shots and placement limited
*************************************************************/
int boundaryCheck(int x, int y, int player_index, int length, int direction /* hor = 0 & vert = 1*/)
{
	//will call with either 40% or 60% info depending on the call
	//getPlayerShot calls in with (x, y, 0, 0, 0)
	//autoPlacement and manualPlacement call in with (x, y, 0, length, direction)

	if (x < 0 || x > 9)
	{
		return 0; //kick it back and assign false
	}
	if (y < 0 || y > 9)
	{
		return 0; //kick it back and assign false
	}
	if (length > 0)
	{
		if (direction == 0) //horizontal
		{
			if (x + length - 1 > 9)  //index + length - length offset
				return 0;
		}
		if (direction == 1) //vertical
		{
			if (y + length - 1 > 9)  //index + length - length offset
				return 0;
		}
		for (int i = 0; i < length; i++)  //checking for ship collisions
		{
			if (direction == 0) //horizontal
			{
				if (player_Board[x + i][y][player_index] != '~')
					return 0;
			}
			else
			{
				if (player_Board[x][y + i][player_index] != '~')
					return 0;
			}
		}
	}
	return 1;
}

/************************************************************
* Function: markShot()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 4, 2018
* Description:
* Input parameters: int x, int y, int player
* Returns: -
* Preconditions:
* Postconditions: Marks shot in the board if it is an unused cell
*************************************************************/
void markShot(int x, int y, int player)
{
	int whichBoard = (player == 0) ? (1) : (0);
	player_Board[x][y][whichBoard] = (player_Board[x][y][whichBoard] == '~') ? ('m') : ('*');
	return;
}

/************************************************************
* Function: computerTurn()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 3, 2018
* Description:
* Input parameters: int x, int y
* Returns: -
* Preconditions: Picks random x and y shot placement for "AI"
* Postconditions: Firing coordinates returned
*************************************************************/
void computerTurn(int *x, int *y) //return random unused x and y(not hit or miss)
{
	do
	{
		*x = (rand() % 9);
		*y = (rand() % 9);
	} while ((player_Board[*x][*y][0] == 'm') || (player_Board[*x][*y][0] == '*'));
	return;
}

/************************************************************
* Function: callLog()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 2, 2018
* Description: Writes data to log file with results and stats from each shot
* Input parameters: FILE *battleship, int player_num, int x_coor, int y_coor
* Returns: -
* Preconditions: Battleship outfile opened
* Postconditions: Writes updating data to .txt file
*************************************************************/
void callLog(FILE *battleship, int player_num, int x_coor, int y_coor) //log player, shot, and hit/miss
{
	fprintf(battleship, "____________________________________________________________________________________\n");
	fprintf(battleship, "Player %s stats -- ", player_names[player_num]); //player
	fprintf(battleship, "Targeted position: (%c, %d)\n", x_coor + 65, y_coor + 1); //targeted position

	fprintf(battleship, "Player: %s -- Carrier: %s Battleship: %s, Cruiser: %s Submarine: %s, Destroyer: %s\n",
		player_names[0]
		, (Stats[0].carrier > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[0].battleship > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[0].cruiser > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[0].submarine > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[0].destroyer > 0) ? ("ACTIVE") : ("SUNK"));
	fprintf(battleship, "Player: %s -- Carrier: %s Battleship: %s, Cruiser: %s Submarine: %s, Destroyer: %s\n",
		player_names[1]
		, (Stats[1].carrier > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[1].battleship > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[1].cruiser > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[1].submarine > 0) ? ("ACTIVE") : ("SUNK")
		, (Stats[1].destroyer > 0) ? ("ACTIVE") : ("SUNK"));

	if (DEBUG_ON)
		fflush(battleship);
	//fprintf(battleship, "Shot result: %d\n", ); //shot result
	return;
}

/************************************************************
* Function: writeOutlog()
* Date Created: Oct 26, 2018
* Date Last Modified: Nov 1, 2018
* Description: Writes to log file with final stats for each player
* Input parameters: FILE *battleship
* Returns: -
* Preconditions: Battleship outfile opened
* Postconditions: Writes data to .txt file
*************************************************************/
void writeOutlog(FILE *battleship)
{
	//write final stats to battleship.log - this is concurrent to printStats
	//struct w/		
	fprintf(battleship, "\nPlayer %s stats: \n", player_names[0]); //human player
	fprintf(battleship, "_______________ \n"); //system player 
	fprintf(battleship, "Total hits: %d\n", Stats[0].total_hits); //total hits
	fprintf(battleship, "Total misses: %d\n", Stats[0].total_miss); //total misses
	fprintf(battleship, "Total shots: %d\n", Stats[0].total_shot); //total shots
	fprintf(battleship, "Hit/Miss Ratio: %lf\n", Stats[0].ratio); //hit/miss ratio
	if (Stats[0].winner == 1)
		fprintf(battleship, "Winner!\n");
	else
		fprintf(battleship, "Loser!\n");

	fprintf(battleship, "\nPlayer 2 stats: \n"); //system player 
	fprintf(battleship, "_______________ \n"); //system player 
	fprintf(battleship, "Total hits: %d\n", Stats[1].total_hits);
	fprintf(battleship, "Total misses: %d\n", Stats[1].total_miss);
	fprintf(battleship, "Total shots: %d\n", Stats[1].total_shot);
	fprintf(battleship, "Hit/Miss Ratio: %lf\n", Stats[1].ratio);
	if (Stats[1].winner == 1)
		fprintf(battleship, "Winner!\n");
	else
		fprintf(battleship, "Loser!\n");

	return;
}
