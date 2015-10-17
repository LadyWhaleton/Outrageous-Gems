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
	| <  | X  |[C1]| 4 | 5  | X  | X  | 8  |[J2]| 10 | 11 | X  |[C2]| 14 | 15 | X |
	| 17 | 18 | 19 | X | 21 |[J1]| 23 | 24 | X  | X  | 27 | 28 | 29 | X  | 31 | v |
*/

#ifndef MAP3_H
#define MAP3_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP3_J1, MAP3_J2, MAP3_C1, MAP3_C2;
treasure* MAP3_TREASURELIST[] = {&MAP3_J1, &MAP3_J2, &MAP3_C1, &MAP3_C2};
unsigned numTreasures_MAP3 = 4;
	
unsigned char MAP3_TREE_LOCATIONS [] = {2, 6, 7, 12, 16, 20, 25, 26, 30};

MapMarker MAP3_TO_MAP2, MAP3_TO_MAP4;
MapMarker *MAP3_MARKERSLIST[] = {&MAP3_TO_MAP2, &MAP3_TO_MAP4};
unsigned char numMarkers_MAP3 = 2;

	
void initMAP3()
{
	MAP3_J1.TTYPE = JEWEL; MAP3_J1.PTS = 2; MAP3_J1.LOC = 22; MAP3_J1.isTaken = NO;
	MAP3_J2.TTYPE = JEWEL; MAP3_J2.PTS = 2; MAP3_J2.LOC = 9; MAP3_J2.isTaken = NO;
	MAP3_C1.TTYPE = CRYSTAL; MAP3_C1.PTS = 3; MAP3_C1.LOC = 3; MAP3_C1.isTaken = NO;
	MAP3_C2.TTYPE = CRYSTAL; MAP3_C2.PTS = 3; MAP3_C2.LOC = 13; MAP3_C2.isTaken = NO;
	
	// initialize map markers
	MAP3_TO_MAP2.playerStartPos = 16; MAP3_TO_MAP2.nextMap = Start_Map2;
	MAP3_TO_MAP2.markerPos = 1; MAP3_TO_MAP2.MTYPE = LEFT_ARROW;
	
	MAP3_TO_MAP4.playerStartPos = 16; MAP3_TO_MAP4.nextMap = Start_Map4;
	MAP3_TO_MAP4.markerPos = 32; MAP3_TO_MAP4.MTYPE = DOWN_ARROW;
}	

void displayMap3()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP3; k++)
		{
			LCD_Cursor(MAP3_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP3_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP3_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP3_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP3; j++)
		{
			if ( !(MAP3_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP3_TREASURELIST[j]->LOC); LCD_WriteData(MAP3_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP3_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP3; i++)
	{
		if (MAP3_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP3_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP3_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP3()
{
	//person tried to run into a tree.... {1, 2, 3, 4, 5, 9, 10, 11, 12, 14, 17, 18, 19, 23, 30, 31, 32}
	for (unsigned char i = 0; i < sizeof(MAP3_TREE_LOCATIONS); i++)
	{
		if (MAP3_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP3; i++)
	{
		if ( MAP3_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP3_TREASURELIST[i]->isTaken) )
		{
			MAP3_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP3_TREASURELIST[i]->PTS);
		}
	}

}

#endif