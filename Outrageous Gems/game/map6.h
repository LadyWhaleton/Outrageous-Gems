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
	|  X | ^  | 3  | 4 | X  | X  | 7  | 8  | 9  | X  | X  | X  | X  | X  | 15  | 16 |
	| 17 | 18 | X  | 20| 21 | 22 | 23 | X  | 25 | 26 | 27 | 28 | 29 | 30  | 31 |[C1]|
*/

#ifndef MAP6_H
#define MAP6_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP6_G1, MAP6_C1;
treasure* MAP6_TREASURELIST[] = {&MAP6_G1, &MAP6_C1};
unsigned numTreasures_MAP6 = 2;
	
unsigned char MAP6_TREELIST [] = {1, 5, 6, 10, 11, 12, 13, 14, 19, 24};

MapMarker MAP6_TO_MAP4;
MapMarker *MAP6_MARKERSLIST[] = {&MAP6_TO_MAP4};
unsigned char numMarkers_MAP6 = 1;
unsigned char map6_treasureRandomized;

void initMAP6()
{
	MAP6_G1.TTYPE = GEM; MAP6_G1.PTS = 15; MAP6_G1.LOC = 9; MAP6_G1.isTaken = YES;
	MAP6_C1.TTYPE = CRYSTAL; MAP6_C1.PTS = 5; MAP6_C1.LOC = 32; MAP6_C1.isTaken = NO;
	
	// initialize map markers
	MAP6_TO_MAP4.markerPos = 2; MAP6_TO_MAP4.MTYPE = UP_ARROW;
	MAP6_TO_MAP4.playerStartPos = 27; MAP6_TO_MAP4.nextMap = Start_Map4;
	
	map6_treasureRandomized = NO;
}	

void displayMap6()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP6; k++)
		{
			LCD_Cursor(MAP6_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP6_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP6_TREELIST); i++)
		{
			LCD_Cursor(MAP6_TREELIST[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP6; j++)
		{
			if ( !(MAP6_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP6_TREASURELIST[j]->LOC); LCD_WriteData(MAP6_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP6_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP6; i++)
	{
		if (MAP6_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP6_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP6_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP6()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP6_TREELIST); i++)
	{
		if (MAP6_TREELIST[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP6; i++)
	{
		if ( MAP6_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP6_TREASURELIST[i]->isTaken) )
		{
			MAP6_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP6_TREASURELIST[i]->PTS);
		}
	}

}

#endif