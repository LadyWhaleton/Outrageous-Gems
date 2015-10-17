/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

// this is the starting map
// P is where the player starts, J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP
	| X  | X  | X  | ^  | X  | 6  | 7  | 8  | 9  | X  | X  | X  | 13 |[MAP0_J1]| 15 | P  |
	| <  | 18 | 19 | 20 | 21 | 22 | X  | X  |[MAP0_T1]| 26 | 27 | 28 | 29 | X  | X  | X  |
*/

#ifndef MAP0_H
#define MAP0_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP0_J1, MAP0_T1;
treasure *MAP0_TREASURELIST[] = {&MAP0_J1, &MAP0_T1};
unsigned char MAP0_TREE_LOCATIONS [] = {1, 2, 3, 5, 10, 11, 12, 16, 23, 24, 30, 31, 32};
	
MapMarker MAP0_TO_MAP1, MAP0_TO_MAP10;
MapMarker *MAP0_MARKERSLIST[] = {&MAP0_TO_MAP1, &MAP0_TO_MAP10};
unsigned char numMarkers_Map0 = 2;
	
void initMAP0()
{
	currPlayerPos = 15;
	nextPlayerPos = 15;
	currMap = Start_Map0;
	
	// initialize treasure
	MAP0_J1.TTYPE = JEWEL; MAP0_J1.PTS = 2; MAP0_J1.LOC = 14; MAP0_J1.isTaken = NO;
	MAP0_T1.TTYPE = TEARDROP; MAP0_T1.PTS = 3; MAP0_T1.LOC = 25; MAP0_T1.isTaken = NO;
	
	// initialize map markers
	MAP0_TO_MAP1.playerStartPos = 17; MAP0_TO_MAP1.nextMap = Start_Map1;
	MAP0_TO_MAP1.markerPos = 4; MAP0_TO_MAP1.MTYPE = UP_ARROW;
	
	MAP0_TO_MAP10.playerStartPos = 32; MAP0_TO_MAP10.nextMap = Start_Map10;
	MAP0_TO_MAP10.markerPos = 17; MAP0_TO_MAP10.MTYPE = LEFT_ARROW;
}	

void displayMap0()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_Map0; k++)
		{
			LCD_Cursor(MAP0_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP0_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP0_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP0_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < 2; j++)
		{
			if ( !(MAP0_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP0_TREASURELIST[j]->LOC); LCD_WriteData(MAP0_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP0_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_Map0; i++)
	{
		if (MAP0_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP0_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP0_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP0()
{
	//person tried to run into a tree....
	for (unsigned char i = 0; i < sizeof(MAP0_TREE_LOCATIONS); i++)
	{
		if (MAP0_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < sizeof(treasure)/sizeof(treasure*); i++)
	{
		if ( MAP0_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP0_TREASURELIST[i]->isTaken) )
		{
			MAP0_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP0_TREASURELIST[i]->PTS);
		}
	}

}

#endif