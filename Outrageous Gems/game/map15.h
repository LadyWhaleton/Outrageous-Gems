/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MAP15_H
#define MAP15_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP15_T1;
treasure* MAP15_TREASURELIST[] = {&MAP15_T1};
unsigned numTreasures_MAP15 = 1;
	
unsigned char MAP15_TREE_LOCATIONS [] = {2,3,4,5, 6, 7,11,12,13,14,15,16, 25, 26,28,29,30,31,32};

MapMarker MAP15_TO_MAP12, MAP15_TO_MAP9, MAP15_TO_MAP14;
MapMarker *MAP15_MARKERSLIST[] = {&MAP15_TO_MAP12, &MAP15_TO_MAP9, &MAP15_TO_MAP14};
unsigned char numMarkers_MAP15 = 3;

unsigned char PORTAL_UP; // 

// J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP
	|<,o | X  | X  | X | X  | X  | X  | 8  | ^  | 10 | X  | X | X  | X  | X | X |
	| 17 | 18 | 19 |20 | 21 |[T1]| 23 | 24 | X  | X | 27 | X | X  | X  | X | X |
*/

	
void initMAP15()
{
	MAP15_T1.TTYPE = TEARDROP; MAP15_T1.PTS = 3; MAP15_T1.LOC = 22; MAP15_T1.isTaken = NO;
	
	// initialize map markers
	MAP15_TO_MAP9.markerPos = 1; MAP15_TO_MAP9.MTYPE = PORTAL;
	MAP15_TO_MAP14.markerPos = 1; MAP15_TO_MAP14.MTYPE = LEFT_ARROW;
	MAP15_TO_MAP12.markerPos = 9; MAP15_TO_MAP12.MTYPE = UP_ARROW;
	
	MAP15_TO_MAP9.playerStartPos = 3; MAP15_TO_MAP9.nextMap = Start_Map9;
	MAP15_TO_MAP12.playerStartPos = 23; MAP15_TO_MAP12.nextMap = Start_Map12;
	MAP15_TO_MAP14.playerStartPos = 16; MAP15_TO_MAP14.nextMap = Start_Map14;
	
	PORTAL_UP = YES;
}	

void displayMap15()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers

		if (PORTAL_UP)
		{
			LCD_Cursor(MAP15_TO_MAP9.markerPos); LCD_WriteData(PORTAL);
		}
				
		else
		{
			LCD_Cursor(MAP15_TO_MAP14.markerPos); LCD_WriteData(LEFT_ARROW);
		}
			
			LCD_Cursor(MAP15_TO_MAP12.markerPos); LCD_WriteData(UP_ARROW);


		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP15_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP15_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP15; j++)
		{
			if ( !(MAP15_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP15_TREASURELIST[j]->LOC); LCD_WriteData(MAP15_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP15_checkNewMap()
{

	if (MAP15_TO_MAP9.markerPos == currPlayerPos && button == '1')
	{
		if (PORTAL_UP)
		{
			PORTAL_UP = NO;
			currMap = MAP15_TO_MAP9.nextMap;
			updateMap = 1;
			nextPlayerPos = MAP15_TO_MAP9.playerStartPos;
			LCD_ClearScreen();
		}
		
		else
		{
			currMap = MAP15_TO_MAP14.nextMap;
			updateMap = 1;
			nextPlayerPos = MAP15_TO_MAP14.playerStartPos;
			LCD_ClearScreen();
		}		
	}
	
	else if (MAP15_TO_MAP12.markerPos == currPlayerPos && button == '1')
	{
			currMap = MAP15_TO_MAP12.nextMap;
			updateMap = 1;
			nextPlayerPos = MAP15_TO_MAP12.playerStartPos;
			LCD_ClearScreen();
	}

}
void collisionDetectorMAP15()
{
	//person tried to run into a tree.... {1, 2, 3, 4, 5, 9, 10, 11, 12, 14, 17, 18, 19, 23, 30, 31, 32}
	for (unsigned char i = 0; i < sizeof(MAP15_TREE_LOCATIONS); i++)
	{
		if (MAP15_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP15; i++)
	{
		if ( MAP15_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP15_TREASURELIST[i]->isTaken) )
		{
			MAP15_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP15_TREASURELIST[i]->PTS);
		}
	}

}

#endif