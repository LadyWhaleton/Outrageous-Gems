/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

// J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP
	|[J1]| 2  | 3  | 4 | X  | X  | X  | X  |  X | 10 | 11 | X  | 13 | 14 | 15 | ^ |
	| X  | X  | X  | 20| 21 | v  | 23 | 24 | 25 | 26 | v  | 28 | 29 | X  | X  | X |
							 map 5					  map 6
*/

#ifndef MAP4_H
#define MAP4_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP4_J1;
treasure* MAP4_TREASURELIST[] = {&MAP4_J1};
unsigned numTreasures_MAP4 = 1;
	
unsigned char MAP4_TREE_LOCATIONS [] = {5, 6, 7, 8, 9, 12, 17, 18, 19, 30, 31, 32};

MapMarker MAP4_TO_MAP3, MAP4_TO_MAP5, MAP4_TO_MAP6;
MapMarker *MAP4_MARKERSLIST[] = {&MAP4_TO_MAP3, &MAP4_TO_MAP5, &MAP4_TO_MAP6};
unsigned char numMarkers_MAP4 = 3;

	
void initMAP4()
{
	MAP4_J1.TTYPE = JEWEL; MAP4_J1.PTS = 2; MAP4_J1.LOC = 1; MAP4_J1.isTaken = NO;
	
	// initialize map markers
	MAP4_TO_MAP3.markerPos = 16; MAP4_TO_MAP3.MTYPE = UP_ARROW;
	MAP4_TO_MAP5.markerPos = 22; MAP4_TO_MAP5.MTYPE = DOWN_ARROW;
	MAP4_TO_MAP6.markerPos = 27; MAP4_TO_MAP6.MTYPE = DOWN_ARROW;
	
	MAP4_TO_MAP3.playerStartPos = 32; MAP4_TO_MAP3.nextMap = Start_Map3;
	MAP4_TO_MAP5.playerStartPos = 14; MAP4_TO_MAP5.nextMap = Start_Map5;
	MAP4_TO_MAP6.playerStartPos = 2; MAP4_TO_MAP6.nextMap = Start_Map6;
}	

void displayMap4()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP4; k++)
		{
			LCD_Cursor(MAP4_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP4_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP4_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP4_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP4; j++)
		{
			if ( !(MAP4_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP4_TREASURELIST[j]->LOC); LCD_WriteData(MAP4_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP4_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP4; i++)
	{
		if (MAP4_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP4_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP4_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP4()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP4_TREE_LOCATIONS); i++)
	{
		if (MAP4_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP4; i++)
	{
		if ( MAP4_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP4_TREASURELIST[i]->isTaken) )
		{
			MAP4_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP4_TREASURELIST[i]->PTS);
		}
	}

}

#endif