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
 map 11	| <  | 2  | X  | 4  | 5  | 6  | X  | X  |  X | X  | X  | X | X | X  | X  | X |
		| X  | 18 | 19 | v  | X  | 22 | 23 | 24 | 25 | 26 | 27 | 28  | 29  | V  | 31 | > | map 0
						map 12
*/

#ifndef MAP10_H
#define MAP10_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"
	
unsigned char MAP10_TREE_LOCATIONS [] = {3, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 21};

MapMarker MAP10_TO_MAP1, MAP10_TO_MAP11, MAP10_TO_MAP12;
MapMarker *MAP10_MARKERSLIST[] = {&MAP10_TO_MAP1, &MAP10_TO_MAP11, &MAP10_TO_MAP12};
unsigned char numMarkers_MAP10 = 3;

	
void initMAP10()
{
	// initialize map markers
	MAP10_TO_MAP1.markerPos = 32; MAP10_TO_MAP1.MTYPE = RIGHT_ARROW;
	MAP10_TO_MAP11.markerPos = 1; MAP10_TO_MAP11.MTYPE = LEFT_ARROW;
	MAP10_TO_MAP12.markerPos = 20; MAP10_TO_MAP12.MTYPE = DOWN_ARROW;
	
	MAP10_TO_MAP1.playerStartPos = 17; MAP10_TO_MAP1.nextMap = Start_Map0;
	MAP10_TO_MAP11.playerStartPos = 16; MAP10_TO_MAP11.nextMap = Start_Map11; 
	MAP10_TO_MAP12.playerStartPos = 13; MAP10_TO_MAP12.nextMap = Start_Map12; 
}	

void displayMap10()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP10; k++)
		{
			LCD_Cursor(MAP10_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP10_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP10_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP10_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP10_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP10; i++)
	{
		if (MAP10_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP10_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP10_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP10()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP10_TREE_LOCATIONS); i++)
	{
		if (MAP10_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}

}

#endif