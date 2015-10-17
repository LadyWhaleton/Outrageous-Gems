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
	| X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | X  | 15 | ^  |
	| v  | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 |[29]| 30 | 31 | X  |
*/

#ifndef MAP1_H
#define MAP1_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP1_J1, MAP1_T1, MAP1_C1;
treasure *MAP1_TREASURELIST[] = {&MAP1_J1, &MAP1_T1, &MAP1_C1};
unsigned char MAP1_TREE_LOCATIONS [] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 32};
unsigned char MAP1_indexOfTreasure;

MapMarker MAP1_TO_MAP0, MAP1_TO_MAP2;
MapMarker *MAP1_MARKERSLIST[] = {&MAP1_TO_MAP0, &MAP1_TO_MAP2};
unsigned char numMarkers_MAP1 = 2;

void initMAP1()
{
	if (MAP1_indexOfTreasure > 2)
		fakeRandomNumber = 0;
	else
		fakeRandomNumber++;
	
	MAP1_indexOfTreasure = fakeRandomNumber;
	
	MAP1_J1.TTYPE = JEWEL; MAP1_J1.PTS = 2; MAP1_J1.LOC = 29; MAP1_J1.isTaken = NO;
	MAP1_T1.TTYPE = TEARDROP; MAP1_T1.PTS = 3; MAP1_T1.LOC = 29; MAP1_T1.isTaken = NO;
	MAP1_C1.TTYPE = CRYSTAL; MAP1_C1.PTS = 5; MAP1_C1.LOC = 29; MAP1_C1.isTaken = NO;
	
	// initialize map markers
	MAP1_TO_MAP0.playerStartPos = 4; MAP1_TO_MAP0.nextMap = Start_Map0;
	MAP1_TO_MAP0.markerPos = 17; MAP1_TO_MAP0.MTYPE = DOWN_ARROW;
	
	MAP1_TO_MAP2.playerStartPos = 25; MAP1_TO_MAP2.nextMap = Start_Map2;
	MAP1_TO_MAP2.markerPos = 16; MAP1_TO_MAP2.MTYPE = UP_ARROW;
}	

void displayMap1()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP1; k++)
		{
			LCD_Cursor(MAP1_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP1_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP1_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP1_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		if ( !(MAP1_TREASURELIST[MAP1_indexOfTreasure]->isTaken) )
		{
			LCD_Cursor(MAP1_TREASURELIST[MAP1_indexOfTreasure]->LOC); LCD_WriteData(MAP1_TREASURELIST[MAP1_indexOfTreasure]->TTYPE);
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP1_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP1; i++)
	{
		if (MAP1_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP1_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP1_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}

void collisionDetectorMAP1()
{
	//person tried to run into a tree.... tree locs are 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 32
	for (unsigned char i = 0; i < sizeof(MAP1_TREE_LOCATIONS); i++)
	{
		if (MAP1_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet, mark treasure as taken
	if ( MAP1_TREASURELIST[MAP1_indexOfTreasure]->LOC == currPlayerPos && button == '1' && !(MAP1_TREASURELIST[MAP1_indexOfTreasure]->isTaken) )
	{
			MAP1_TREASURELIST[MAP1_indexOfTreasure]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP1_TREASURELIST[MAP1_indexOfTreasure]->PTS);
	}	
		
}

#endif