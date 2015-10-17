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
	| <  | 2  | X  | 4  | 5  | 6  | X  | X  |  X | ^  | 11 | 12 | 13 | 14 | X  | X  |
	| 17 | 18 | 19 | 20 | X  | 22 | 23 | 24 | 25 | 26 | 27 | X  | X  | V  | 31 | 32 |
							 map 5					  map 6
*/

#ifndef MAP7_H
#define MAP7_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"
	
unsigned char MAP7_TREE_LOCATIONS [] = {3, 7, 8, 9, 15, 16, 21, 28, 29};

MapMarker MAP7_TO_MAP5, MAP7_TO_MAP8, MAP7_TO_MAP9;
MapMarker *MAP7_MARKERSLIST[] = {&MAP7_TO_MAP5, &MAP7_TO_MAP8, &MAP7_TO_MAP9};
unsigned char numMarkers_MAP7 = 3;

	
void initMAP7()
{
	// initialize map markers
	MAP7_TO_MAP5.markerPos = 10; MAP7_TO_MAP5.MTYPE = UP_ARROW;
	MAP7_TO_MAP8.markerPos = 30; MAP7_TO_MAP8.MTYPE = DOWN_ARROW;
	MAP7_TO_MAP9.markerPos = 1; MAP7_TO_MAP9.MTYPE = LEFT_ARROW;
	
	MAP7_TO_MAP5.playerStartPos = 26; MAP7_TO_MAP5.nextMap = Start_Map5;
	MAP7_TO_MAP8.playerStartPos = 5; MAP7_TO_MAP8.nextMap = Start_Map8; 
	MAP7_TO_MAP9.playerStartPos = 16; MAP7_TO_MAP9.nextMap = Start_Map9;
}	

void displayMap7()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP7; k++)
		{
			LCD_Cursor(MAP7_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP7_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP7_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP7_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP7_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP7; i++)
	{
		if (MAP7_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP7_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP7_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP7()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP7_TREE_LOCATIONS); i++)
	{
		if (MAP7_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}

}

#endif