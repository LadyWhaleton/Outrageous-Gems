/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAP11_H
#define MAP11_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP11_G1, MAP11_C1, MAP11_J1, MAP11_J2, MAP11_J3, MAP11_T1;
treasure* MAP11_TREASURELIST[] = {&MAP11_G1, &MAP11_C1, &MAP11_J1, &MAP11_J2, &MAP11_J3, &MAP11_T1};
unsigned numTreasures_MAP11 = 6;
	
unsigned char MAP11_TREELIST [] = {5, 6, 11, 12, 13, 14, 18, 19, 24, 25};

MapMarker MAP11_TO_MAP10, MAP11_TO_MAP14;
MapMarker *MAP11_MARKERSLIST[] = {&MAP11_TO_MAP10, &MAP11_TO_MAP14};
unsigned char numMarkers_MAP11 = 2;

// J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP
	|  1 | 2  | 3  |[J2]| X  | X  | 7  | 8  |[J3]| 10  | 11  | X  | X  | X   |[J1]| >  | map 10 (SP:1)
	| v  | X  | X  | 20 | 21 | 22 |[G1]| X  | X  | 26  | 27  | 28 | 29 | 30  |[T1]|[C1]|
	 map 14
*/

void initMAP11()
{
	MAP11_G1.TTYPE = GEM; MAP11_G1.PTS = 15; MAP11_G1.LOC = 23; MAP11_G1.isTaken = NO;
	MAP11_C1.TTYPE = CRYSTAL; MAP11_C1.PTS = 5; MAP11_C1.LOC = 9; MAP11_C1.isTaken = NO;
	MAP11_T1.TTYPE = TEARDROP; MAP11_T1.PTS = 3; MAP11_T1.LOC = 31; MAP11_T1.isTaken = NO;
	MAP11_J1.TTYPE = JEWEL; MAP11_J1.PTS = 2; MAP11_J1.LOC = 15; MAP11_J1.isTaken = NO;
	MAP11_J2.TTYPE = JEWEL; MAP11_J2.PTS = 2; MAP11_J2.LOC = 4; MAP11_J2.isTaken = NO;
	MAP11_J3.TTYPE = JEWEL; MAP11_J3.PTS = 2; MAP11_J3.LOC = 32; MAP11_J3.isTaken = NO;
	
	// initialize map markers
	MAP11_TO_MAP10.markerPos = 16; MAP11_TO_MAP10.MTYPE = RIGHT_ARROW;
	MAP11_TO_MAP14.markerPos = 17; MAP11_TO_MAP14.MTYPE = DOWN_ARROW;
	
	MAP11_TO_MAP10.playerStartPos = 1; MAP11_TO_MAP10.nextMap = Start_Map10;
	MAP11_TO_MAP14.playerStartPos = 2; MAP11_TO_MAP14.nextMap = Start_Map14;
	
}	

void displayMap11()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP11; k++)
		{
			LCD_Cursor(MAP11_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP11_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP11_TREELIST); i++)
		{
			LCD_Cursor(MAP11_TREELIST[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP11; j++)
		{
			if ( !(MAP11_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP11_TREASURELIST[j]->LOC); LCD_WriteData(MAP11_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP11_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP11; i++)
	{
		if (MAP11_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP11_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP11_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP11()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP11_TREELIST); i++)
	{
		if (MAP11_TREELIST[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP11; i++)
	{
		if ( MAP11_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP11_TREASURELIST[i]->isTaken) )
		{
			MAP11_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP11_TREASURELIST[i]->PTS);
		}
	}

}

#endif