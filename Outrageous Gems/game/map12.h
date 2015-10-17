/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAP12_H
#define MAP12_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP12_C1, MAP12_J1, MAP12_J2, MAP12_T1, MAP12_T2, MAP12_G1;
treasure* MAP12_TREASURELIST[] = {&MAP12_C1, &MAP12_J1, &MAP12_J2, &MAP12_T1, &MAP12_T2, &MAP12_G1};
unsigned numTreasures_MAP12 = 6;
	
unsigned char MAP12_TREELIST [] = {1, 6, 7, 14, 17, 19, 20, 25, 27, 28, 32};

MapMarker MAP12_TO_MAP10, MAP12_TO_MAP13, MAP12_TO_MAP15;
MapMarker *MAP12_MARKERSLIST[] = {&MAP12_TO_MAP10, &MAP12_TO_MAP13, &MAP12_TO_MAP15};
unsigned char numMarkers_MAP12 = 3;

unsigned char map12_treasureRandomized;

// J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP							map 10
	|  X | 2  | 3  | 4  |[J1]| X  | X  | 8  |[T2]| 10  | 11  | 12 | ^  | X   | 15 | >  | map 13 (SP:17)
	|  X |[C1]| X  | X  | 21 | 22 | v  | 24 | X  |[J2]| X   | X   |[T1]|[G1] | 31 | X |
								map 15 
*/

void initMAP12()
{	
	MAP12_J1.TTYPE = JEWEL; MAP12_J1.PTS = 2; MAP12_J1.LOC = 5; MAP12_J1.isTaken = NO;
	MAP12_C1.TTYPE = CRYSTAL; MAP12_C1.PTS = 5; MAP12_C1.LOC = 18; MAP12_C1.isTaken = NO;
	MAP12_J2.TTYPE = JEWEL; MAP12_J2.PTS = 2; MAP12_J2.LOC = 26; MAP12_J2.isTaken = NO;
	MAP12_T1.TTYPE = TEARDROP; MAP12_T1.PTS = 3; MAP12_T1.LOC = 29; MAP12_T1.isTaken = NO;
	MAP12_T2.TTYPE = TEARDROP; MAP12_T2.PTS = 3; MAP12_T2.LOC = 9; MAP12_T2.isTaken = YES;
	MAP12_G1.TTYPE = GEM; MAP12_G1.PTS = 15; MAP12_G1.LOC = 31; MAP12_G1.isTaken = YES;
	
	// initialize map markers
	MAP12_TO_MAP10.markerPos = 13; MAP12_TO_MAP10.MTYPE = UP_ARROW;
	MAP12_TO_MAP13.markerPos = 16; MAP12_TO_MAP13.MTYPE = RIGHT_ARROW;
	MAP12_TO_MAP15.markerPos = 23; MAP12_TO_MAP15.MTYPE = DOWN_ARROW;
	
	MAP12_TO_MAP10.playerStartPos = 20; MAP12_TO_MAP10.nextMap = Start_Map10;
	MAP12_TO_MAP13.playerStartPos = 17; MAP12_TO_MAP13.nextMap = Start_Map13;
	MAP12_TO_MAP15.playerStartPos = 10; MAP12_TO_MAP15.nextMap = Start_Map15;
	
	map12_treasureRandomized = NO;
}	

void displayMap12()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP12; k++)
		{
			LCD_Cursor(MAP12_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP12_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP12_TREELIST); i++)
		{
			LCD_Cursor(MAP12_TREELIST[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP12; j++)
		{
			if ( !(MAP12_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP12_TREASURELIST[j]->LOC); LCD_WriteData(MAP12_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP12_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP12; i++)
	{
		if (MAP12_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP12_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP12_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP12()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP12_TREELIST); i++)
	{
		if (MAP12_TREELIST[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP12; i++)
	{
		if ( MAP12_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP12_TREASURELIST[i]->isTaken) )
		{
			MAP12_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP12_TREASURELIST[i]->PTS);
		}
	}

}

#endif