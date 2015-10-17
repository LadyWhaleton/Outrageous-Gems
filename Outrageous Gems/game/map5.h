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
	| X  | X  | 3  | 4 | X  | X  | X  | X  |  9 | 10 | 11 | 12 | 13 | ^  | X  | X |
	| 17 | 18 | X  | 20| 21 | 22 | X  | X  | X  | V  | 27 | 28 | 29 | X  | 31 | X |
*/

#ifndef MAP5_H
#define MAP5_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

unsigned char MAP5_TREE_LOCATIONS [] = {1, 2, 5, 6, 7, 8, 15, 16, 19, 23, 24, 25, 30, 32};

MapMarker MAP5_TO_MAP4, MAP5_TO_MAP7;
MapMarker *MAP5_MARKERSLIST[] = {&MAP5_TO_MAP4, &MAP5_TO_MAP7};
unsigned char numMarkers_MAP5 = 2;

	
void initMAP5()
{
	// initialize map markers
	MAP5_TO_MAP4.markerPos = 14; MAP5_TO_MAP4.MTYPE = UP_ARROW;
	MAP5_TO_MAP7.markerPos = 26; MAP5_TO_MAP7.MTYPE = DOWN_ARROW;
	
	MAP5_TO_MAP4.playerStartPos = 16; MAP5_TO_MAP4.nextMap = Start_Map4;
	MAP5_TO_MAP7.playerStartPos = 10; MAP5_TO_MAP7.nextMap = Start_Map7;

}	

void displayMap5()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP5; k++)
		{
			LCD_Cursor(MAP5_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP5_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP5_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP5_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
			
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP5_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP5; i++)
	{
		if (MAP5_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP5_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP5_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP5()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP5_TREE_LOCATIONS); i++)
	{
		if (MAP5_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}

}

#endif