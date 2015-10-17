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
	|[T2]| X  | 3  | 4  | 5  | X  | X  |[J3]|[J4]| 10 | 11 | X  |[C1]| 14 | 15 | > | map7
	| 17 | 18 | 19 | X  | 21 |[J1]|[J2]| 24  | X | X  | 27 | 28 | 29 | X  |[T1]| X |
*/

#ifndef MAP9_H
#define MAP9_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP9_J1, MAP9_J2, MAP9_J3, MAP9_J4, MAP9_T1, MAP9_G1, MAP9_C1;
treasure* MAP9_TREASURELIST[] = {&MAP9_J1, &MAP9_J2, &MAP9_J3, &MAP9_J4, &MAP9_T1, &MAP9_G1, &MAP9_C1};
unsigned numTreasures_MAP9 = 7;
	
unsigned char MAP9_TREE_LOCATIONS [] = {2, 6, 7, 12, 20, 25, 26, 30, 32};

MapMarker MAP9_TO_MAP7;
MapMarker *MAP9_MARKERSLIST[] = {&MAP9_TO_MAP7};
unsigned char numMarkers_MAP9 = 1;

	
void initMAP9()
{
	MAP9_J1.TTYPE = JEWEL; MAP9_J1.PTS = 2; MAP9_J1.LOC = 22; MAP9_J1.isTaken = NO;
	MAP9_J2.TTYPE = JEWEL; MAP9_J2.PTS = 2; MAP9_J2.LOC = 23; MAP9_J2.isTaken = NO;
	MAP9_J3.TTYPE = JEWEL; MAP9_J3.PTS = 2; MAP9_J3.LOC = 8; MAP9_J3.isTaken = NO;
	MAP9_J4.TTYPE = JEWEL; MAP9_J4.PTS = 2; MAP9_J4.LOC = 9; MAP9_J4.isTaken = NO;
	MAP9_T1.TTYPE = TEARDROP; MAP9_T1.PTS = 3; MAP9_T1.LOC = 31; MAP9_T1.isTaken = NO;
	MAP9_G1.TTYPE = GEM; MAP9_G1.PTS = 15; MAP9_G1.LOC = 1; MAP9_G1.isTaken = NO;
	MAP9_C1.TTYPE = CRYSTAL; MAP9_C1.PTS = 5; MAP9_C1.LOC = 13; MAP9_C1.isTaken = NO;

	// initialize map markers
	MAP9_TO_MAP7.playerStartPos = 1; MAP9_TO_MAP7.nextMap = Start_Map7;
	MAP9_TO_MAP7.markerPos = 16; MAP9_TO_MAP7.MTYPE = RIGHT_ARROW;
	
}	

void displayMap9()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP9; k++)
		{
			LCD_Cursor(MAP9_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP9_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP9_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP9_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP9; j++)
		{
			if ( !(MAP9_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP9_TREASURELIST[j]->LOC); LCD_WriteData(MAP9_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP9_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP9; i++)
	{
		if (MAP9_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP9_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP9_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP9()
{
	//person tried to run into a tree.... {1, 2, 3, 4, 5, 9, 10, 11, 12, 14, 17, 18, 19, 23, 30, 31, 32}
	for (unsigned char i = 0; i < sizeof(MAP9_TREE_LOCATIONS); i++)
	{
		if (MAP9_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP9; i++)
	{
		if ( MAP9_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP9_TREASURELIST[i]->isTaken) )
		{
			MAP9_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP9_TREASURELIST[i]->PTS);
		}
	}

}

#endif