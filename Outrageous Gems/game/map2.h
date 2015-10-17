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
	| X  | X  | X  | X  | X  | 6  |[T1]| 8  | X  | X  | X  | X  | X | X  | 15 | > |
	| X  | X  | X  |[J1]| 21 | 22 | X  |[T2]| v  | 26 | 27 | 28 | 29 |[J2]|[J3]| X |
*/

#ifndef MAP2_H
#define MAP2_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP2_J1, MAP2_J2, MAP2_J3, MAP2_T1, MAP2_T2;
treasure *MAP2_TREASURELIST[] = {&MAP2_J1, &MAP2_J2, &MAP2_J3, &MAP2_T1, &MAP2_T2};
unsigned char MAP2_TREE_LOCATIONS [] = {1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 17, 18, 19, 23, 32};

MapMarker MAP2_TO_MAP1, MAP2_TO_MAP3;
MapMarker *MAP2_MARKERSLIST[] = {&MAP2_TO_MAP1, &MAP2_TO_MAP3};
unsigned char numMarkers_MAP2 = 2;

	
void initMAP2()
{
	MAP2_J1.TTYPE = JEWEL; MAP2_J1.PTS = 2; MAP2_J1.LOC = 20; MAP2_J1.isTaken = NO;
	MAP2_J2.TTYPE = JEWEL; MAP2_J2.PTS = 2; MAP2_J2.LOC = 30; MAP2_J2.isTaken = NO;
	MAP2_J3.TTYPE = JEWEL; MAP2_J3.PTS = 2; MAP2_J3.LOC = 31; MAP2_J3.isTaken = NO;
	MAP2_T1.TTYPE = TEARDROP; MAP2_T1.PTS = 3; MAP2_T1.LOC = 7; MAP2_T1.isTaken = NO;
	MAP2_T2.TTYPE = TEARDROP; MAP2_T2.PTS = 3; MAP2_T1.LOC = 24; MAP2_T2.isTaken = NO;
	
	// initialize map markers
	MAP2_TO_MAP1.playerStartPos = 16; MAP2_TO_MAP1.nextMap = Start_Map1;
	MAP2_TO_MAP1.markerPos = 25; MAP2_TO_MAP1.MTYPE = DOWN_ARROW;
	
	MAP2_TO_MAP3.playerStartPos = 1; MAP2_TO_MAP3.nextMap = Start_Map3;
	MAP2_TO_MAP3.markerPos = 16; MAP2_TO_MAP3.MTYPE = RIGHT_ARROW;
}	

void displayMap2()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP2; k++)
		{
			LCD_Cursor(MAP2_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP2_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP2_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP2_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < 5; j++)
		{
			if ( !(MAP2_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP2_TREASURELIST[j]->LOC); LCD_WriteData(MAP2_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP2_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP2; i++)
	{
		if (MAP2_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP2_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP2_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP2()
{
	//person tried to run into a tree.... {1, 2, 3, 4, 5, 9, 10, 11, 12, 14, 17, 18, 19, 23, 30, 31, 32}
	for (unsigned char i = 0; i < sizeof(MAP2_TREE_LOCATIONS); i++)
	{
		if (MAP2_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < 5; i++)
	{
		if ( MAP2_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP2_TREASURELIST[i]->isTaken) )
		{
			MAP2_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP2_TREASURELIST[i]->PTS);
		}
	}

}

#endif