/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAP14_H
#define MAP14_H

#include "globals.h"
#include "CustomChar.h"
#include "treasure.h"
#include "score.h"
#include "mapmarkers.h"

treasure MAP14_G1, MAP14_G2, MAP14_G3, MAP14_G4, MAP14_C1, MAP14_C2, MAP14_J1, MAP14_J2, MAP14_J3, MAP14_J4, MAP14_T1, MAP14_T2, MAP14_J5;
treasure* MAP14_TREASURELIST[] = {&MAP14_G1, &MAP14_G2, &MAP14_G3, &MAP14_G4, &MAP14_C1, &MAP14_C2, &MAP14_J1,
								  &MAP14_J2, &MAP14_J3, &MAP14_J4, &MAP14_T1, &MAP14_J5, &MAP14_T2};
unsigned numTreasures_MAP14 = 13;
	
unsigned char MAP14_TREELIST [] = {3, 5, 6, 17, 18, 19, 27, 29, 31, 32};

MapMarker MAP14_TO_MAP15, MAP14_TO_MAP11;
MapMarker *MAP14_MARKERSLIST[] = {&MAP14_TO_MAP15, &MAP14_TO_MAP11};
unsigned char numMarkers_MAP14 = 2;

unsigned char map14_treasureRandomized;

// J is jewel, T is teardrop jewel, C is crystal, G is gem
// X is tree obstacle
/*							 LCD MAP
	 map 11 (SP:17)
	| 1 |  ^   | X  |[G1]| X  | X  |[J1]|[C1]|[J2]|[j5] |[ T1]| 12 | 13 | 14  |[G4]| >  | map 15 (SP:1)
	| X  | X   | X  | 20 | 21 | 22 |[G2]|[J4]|[J3]|[C2] | X   |[G3]| X  | [T2]| X  | X |
*/

void initMAP14()
{
	MAP14_G1.TTYPE = GEM; MAP14_G1.PTS = 15; MAP14_G1.LOC = 4; MAP14_G1.isTaken = NO;
	MAP14_J1.TTYPE = JEWEL; MAP14_J1.PTS = 2; MAP14_J1.LOC = 8; MAP14_J1.isTaken = NO;
	MAP14_C1.TTYPE = CRYSTAL; MAP14_C1.PTS = 5; MAP14_C1.LOC = 7; MAP14_C1.isTaken = NO;
	MAP14_J2.TTYPE = JEWEL; MAP14_J2.PTS = 2; MAP14_J2.LOC = 9; MAP14_J2.isTaken = NO;
	MAP14_J5.TTYPE = JEWEL; MAP14_J5.PTS = 2; MAP14_J5.LOC = 10; MAP14_J5.isTaken = YES;
	MAP14_G4.TTYPE = GEM; MAP14_G4.PTS = 15; MAP14_G4.LOC = 15; MAP14_G4.isTaken = NO;
	MAP14_T1.TTYPE = TEARDROP; MAP14_T1.PTS = 3; MAP14_T1.LOC = 25; MAP14_T1.isTaken = YES;
	
	MAP14_G2.TTYPE = GEM; MAP14_G2.PTS = 15; MAP14_G2.LOC = 23; MAP14_G2.isTaken = YES;
	MAP14_J4.TTYPE = JEWEL; MAP14_J4.PTS = 2; MAP14_J4.LOC = 26; MAP14_J4.isTaken = NO;
	MAP14_J3.TTYPE = JEWEL; MAP14_J3.PTS = 2; MAP14_J3.LOC = 11; MAP14_J3.isTaken = NO;
	MAP14_C2.TTYPE = CRYSTAL; MAP14_C2.PTS = 5; MAP14_C2.LOC = 24; MAP14_C2.isTaken = NO;
	MAP14_G3.TTYPE = GEM; MAP14_G3.PTS = 15; MAP14_G3.LOC = 28; MAP14_G3.isTaken = NO;
	MAP14_T2.TTYPE = TEARDROP; MAP14_T2.PTS = 2; MAP14_T2.LOC = 30; MAP14_T2.isTaken = NO;
	
	// initialize map markers
	MAP14_TO_MAP15.markerPos = 16; MAP14_TO_MAP15.MTYPE = RIGHT_ARROW;
	MAP14_TO_MAP11.markerPos = 2; MAP14_TO_MAP11.MTYPE = UP_ARROW;
	
	MAP14_TO_MAP15.playerStartPos = 1; MAP14_TO_MAP15.nextMap = Start_Map15;
	MAP14_TO_MAP11.playerStartPos = 17; MAP14_TO_MAP11.nextMap = Start_Map11;
	
	map14_treasureRandomized = NO;
}	

void displayMap14()
{
	if (updateMap)
	{
		// clear the previous current position
		LCD_Cursor(currPlayerPos); LCD_WriteData(' ');
		
		// display the next_map markers
		for(unsigned char k = 0; k < numMarkers_MAP14; k++)
		{
			LCD_Cursor(MAP14_MARKERSLIST[k]->markerPos); LCD_WriteData(MAP14_MARKERSLIST[k]->MTYPE);
		}

		//display the trees
		for (unsigned char i = 0; i < sizeof(MAP14_TREELIST); i++)
		{
			LCD_Cursor(MAP14_TREELIST[i]); LCD_WriteData(TREE);
		}
		
		// displays the jewels in the current map
		for (unsigned char j = 0; j < numTreasures_MAP14; j++)
		{
			if ( !(MAP14_TREASURELIST[j]->isTaken) )
			{
				LCD_Cursor(MAP14_TREASURELIST[j]->LOC); LCD_WriteData(MAP14_TREASURELIST[j]->TTYPE);
			}
		}
		
		// moves the player
		LCD_Cursor(nextPlayerPos); LCD_WriteData(PLAYER);
		currPlayerPos = nextPlayerPos;
		updateMap = 0;
	}
}

void MAP14_checkNewMap()
{
	for (unsigned char i = 0; i < numMarkers_MAP14; i++)
	{
		if (MAP14_MARKERSLIST[i]->markerPos == currPlayerPos && button == '1')
		{
			currMap = MAP14_MARKERSLIST[i]->nextMap;
			updateMap = 1;
			nextPlayerPos = MAP14_MARKERSLIST[i]->playerStartPos;
			LCD_ClearScreen();
		}
	}
}
void collisionDetectorMAP14()
{
	//person tried to run into a tree.... 
	for (unsigned char i = 0; i < sizeof(MAP14_TREELIST); i++)
	{
		if (MAP14_TREELIST[i] == nextPlayerPos)
		{
			nextPlayerPos = currPlayerPos; // player doesn't move anywhere
			updateMap = 0;
			break;
		}
	}
	
	// player is on top of a treasure, pressed '1', and item hasn't been taken yet
	for (unsigned char i = 0; i < numTreasures_MAP14; i++)
	{
		if ( MAP14_TREASURELIST[i]->LOC == currPlayerPos && button == '1' && !(MAP14_TREASURELIST[i]->isTaken) )
		{
			MAP14_TREASURELIST[i]->isTaken = YES; // mark the treasure as taken
			// increment the score
			updateScore(MAP14_TREASURELIST[i]->PTS);
		}
	}

}

#endif