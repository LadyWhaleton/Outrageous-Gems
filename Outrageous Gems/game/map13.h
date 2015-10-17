/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAP13_H
#define MAP13_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP13_C1, MAP13_J1, MAP13_J2, MAP13_J3, MAP13_G1;
treasure* MAP13_TREASURELIST[] = {&MAP13_C1, &MAP13_J1, &MAP13_J2, &MAP13_J3, &MAP13_G1};
unsigned numTreasures_MAP13 = 5;
	
unsigned char MAP13_TREELIST [] = {1,2,3,4,5,6,14,15,16,24,25,31,32};

MapMarker MAP13_TO_MAP12;
MapMarker *MAP13_MARKERSLIST[] = {&MAP13_TO_MAP12};
unsigned char numMarkers_MAP13 = 1;

unsigned char map13_treasureRandomized;

// J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP							map 10
	|  X | X  | X  | o  | X  | X  | 7  |[C1]| 9  | 10  | 11  | 12 | 13 | X   | X | X  | map 13 (SP:17)
	|  < | 18 | 19 | 20 |[J1]| 22 |[J2]| X  | X  | 26  |[J3] | 28 | 29 |[G1] | X | X  |
								map 15 
*/

void initMAP13()
{	
	MAP13_C1.TTYPE = CRYSTAL; MAP13_C1.PTS = 5; MAP13_C1.LOC = 8; MAP13_C1.isTaken = YES;
	MAP13_J1.TTYPE = JEWEL; MAP13_J1.PTS = 2; MAP13_J1.LOC = 21; MAP13_J1.isTaken = YES;
	MAP13_J2.TTYPE = JEWEL; MAP13_J2.PTS = 2; MAP13_J2.LOC = 23; MAP13_J2.isTaken = NO;
	MAP13_J3.TTYPE = TEARDROP; MAP13_J3.PTS = 3; MAP13_J3.LOC = 27; MAP13_J3.isTaken = NO;
	MAP13_G1.TTYPE = GEM; MAP13_G1.PTS = 15; MAP13_G1.LOC = 30; MAP13_G1.isTaken = YES;
	
	// initialize map markers
	MAP13_TO_MAP12.markerPos = 17; MAP13_TO_MAP12.MTYPE = LEFT_ARROW;
	MAP13_TO_MAP12.playerStartPos = 32; MAP13_TO_MAP12.nextMap = Start_Map12;

	map13_treasureRandomized = NO;
}	

void displayMap13()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP13; k++)
		{
			LCD_Cursor(MAP13_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP13_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP13_TREELIST); i++)
		{
			LCD_Cursor(MAP13_TREELIST[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP13; j++)
		{
			if ( !(MAP13_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP13_TREASURELIST[j]->LOC); LCD_WriteData(MAP13_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP13_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP13; i++)
	{
		if (MAP13_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP13_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP13_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP13()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP13_TREELIST); i++)
	{
		if (MAP13_TREELIST[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP13; i++)
	{
		if ( MAP13_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP13_TREASURELIST[i]->isTaken) )
		{
			MAP13_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP13_TREASURELIST[i]->PTS);
		}
	}

}

#endif