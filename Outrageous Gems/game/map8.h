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
				   map 7						 map 15
	| X  | X  | X  | 4  | ^  | 6  | X  | X  |  X | o  | X  | X  | 13 | 14 | X  | X  |
	| X  | X  | X  | X  | X  | 22 | 23 | 24 | 25 | 26 | 27 | X  | X  | X  | X  | X  |
*/

#ifndef MAP8_H
#define MAP8_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"
	
unsigned char MAP8_TREE_LOCATIONS [] = {1, 2, 3, 7, 8, 9, 15, 16, 17, 18, 19, 20, 21, 28, 29, 30, 31, 32};

MapMarker MAP8_TO_MAP7, MAP8_TO_MAP15;
MapMarker *MAP8_MARKERSLIST[] = {&MAP8_TO_MAP7, &MAP8_TO_MAP15};
unsigned char numMarkers_MAP8 = 2;

unsigned char map8_PortalON;
	
void initMAP8()
{
	// initialize map markers
	MAP8_TO_MAP7.markerPos = 5; MAP8_TO_MAP7.MTYPE = UP_ARROW;
	MAP8_TO_MAP15.markerPos = 10; MAP8_TO_MAP15.MTYPE = PORTAL;
	
	MAP8_TO_MAP7.playerStartPos = 30; MAP8_TO_MAP7.nextMap = Start_Map7;
	MAP8_TO_MAP15.playerStartPos = 8; MAP8_TO_MAP15.nextMap = Start_Map15;

	map8_PortalON = YES;
}	

void displayMap8()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers

		if (map8_PortalON)
		{
			LCD_Cursor(MAP8_TO_MAP15.markerPos); LCD_WriteData(MAP8_TO_MAP15.MTYPE);
		}
			
		LCD_Cursor(MAP8_TO_MAP7.markerPos); LCD_WriteData(MAP8_TO_MAP7.MTYPE);


		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP8_TREE_LOCATIONS); i++)
		{
			LCD_Cursor(MAP8_TREE_LOCATIONS[i]); LCD_WriteData(TREE);
		}
		
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP8_checkNewMap()
{

	if (MAP8_TO_MAP15.markerPos == currPlayerPos && button == '1')
	{
		currMap = MAP8_TO_MAP15.nextMap;
		updateMap = 1;
		nextPlayerPos = MAP8_TO_MAP15.playerStartPos;
		map8_PortalON = NO;
		LCD_ClearScreen();
	}
	
	else if (MAP8_TO_MAP7.markerPos == currPlayerPos && button == '1')
	{
		currMap = MAP8_TO_MAP7.nextMap;
		updateMap = 1;
		nextPlayerPos = MAP8_TO_MAP7.playerStartPos;
		LCD_ClearScreen();
	}

}
void collisionDetectorMAP8()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP8_TREE_LOCATIONS); i++)
	{
		if (MAP8_TREE_LOCATIONS[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}

}

#endif