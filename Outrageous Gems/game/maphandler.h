/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAP_H
#define MAP_H

/*							 LCD MAP
	| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16  |
	| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 |
*/

#include "globals.h"
#include "gameTime.h"
#include "map0.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "map4.h"
#include "map5.h"
#include "map6.h"
#include "map7.h"
#include "map8.h"
#include "map9.h"
#include "map10.h"
#include "map11.h"
#include "map12.h"
#include "map13.h"
#include "map14.h"
#include "map15.h"

//generic map handler function

void initializeMAPS()
{
	initMAP0(); initMAP1(); initMAP2(); initMAP3(); initMAP4(); initMAP5();
	initMAP6(); initMAP7(); initMAP8(); initMAP9(); initMAP10(); initMAP11();
	initMAP12(); initMAP13(); initMAP14(); initMAP15();
}

// pseudo randomizer - depending on the remaining game time, certain treasures will / will not be displayed
unsigned char TreasureOnRandomizer(treasure mapTreasure, unsigned long val)
{
	if (gameTimer % val == 0)
		mapTreasure.isTaken = NO;
	else
		mapTreasure.isTaken = YES;
		
	return mapTreasure.isTaken;
};

void mapHandler()
{
	switch(currMap)
	{
		case Start_Map0:
			displayMap0(); // after displaying the initial map, go to Map0
			currMap = Map0;
		case Map0:
			collisionDetectorMAP0();
			displayMap0();
			MAP0_checkNewMap();
			break;
		// ======================== MAP 1 ===================================	
		case Start_Map1:
			displayMap1();
			currMap = Map1;
			break;
		case Map1:
			collisionDetectorMAP1();
			displayMap1();
			MAP1_checkNewMap();
			break;
		// ======================== MAP 2 ===================================		
		case Start_Map2:
			displayMap2();
			currMap = Map2;
			break;
		case Map2:
			collisionDetectorMAP2();
			displayMap2();
			MAP2_checkNewMap();			
			break;
		// ======================== MAP 3 ===================================
		case Start_Map3:
			displayMap3();
			currMap = Map3;
			break;
		case Map3:
			collisionDetectorMAP3();
			displayMap3();
			MAP3_checkNewMap();
		break;
		// ======================== MAP 4 ===================================
		case Start_Map4:
			displayMap4();
			currMap = Map4;
			break;
		case Map4:
			collisionDetectorMAP4();
			displayMap4();
			MAP4_checkNewMap();
		break;
		// ======================== MAP 5 ===================================
		case Start_Map5:
			displayMap5();
			currMap = Map5;
			break;
		case Map5:
			collisionDetectorMAP5();
			displayMap5();
			MAP5_checkNewMap();
			break;
		// ======================== MAP 6 ===================================
		case Start_Map6:
			if (!map6_treasureRandomized) // if treasure hasn't been randomized yet
			{	// treasure gets randomized as soon as the player enters the map
				MAP6_G1.isTaken = TreasureOnRandomizer(MAP6_G1, 7); map6_treasureRandomized = YES;
			}
			displayMap6();
			currMap = Map6;
			break;
		case Map6:
			collisionDetectorMAP6();
			displayMap6();
			MAP6_checkNewMap();
			break;
		// ======================== MAP 7 ===================================
		case Start_Map7:
			displayMap7();
			currMap = Map7;
			break;
		case Map7:
			collisionDetectorMAP7();
			displayMap7();
			MAP7_checkNewMap();
			break;
		// ======================== MAP 8 ===================================
		case Start_Map8:
			displayMap8();
			currMap = Map8;
			break;
		case Map8:
			collisionDetectorMAP8();
			displayMap8();
			MAP8_checkNewMap();
			break;
		// ======================== MAP 9 ===================================		
		case Start_Map9:
			displayMap9();
			currMap = Map9;
			break;
		case Map9:
			collisionDetectorMAP9();
			displayMap9();
			MAP9_checkNewMap();
			break;
		// ======================== MAP 10 ===================================
		case Start_Map10:
			displayMap10();
			currMap = Map10;
			break;
		case Map10:
			collisionDetectorMAP10();
			displayMap10();
			MAP10_checkNewMap();
			break;
		// ======================== MAP 11 ===================================
		case Start_Map11:
			displayMap11();
			currMap = Map11;
			break;	
		case Map11:
			collisionDetectorMAP11();
			displayMap11();
			MAP11_checkNewMap();
		break;
		// ======================== MAP 12 ===================================
		case Start_Map12:
			if (!map12_treasureRandomized) // if treasure hasn't been randomized yet
			{	// treasure gets randomized as soon as the player enters the map
				MAP12_T2.isTaken = TreasureOnRandomizer(MAP12_T2, 3);
				MAP12_G1.isTaken = TreasureOnRandomizer(MAP12_G1, 11); map12_treasureRandomized = YES;
			}
			displayMap12();
			currMap = Map12;
			break;
		case Map12:
			collisionDetectorMAP12();
			displayMap12();
			MAP12_checkNewMap();
			break;
		// ======================== MAP 13 ===================================
		case Start_Map13:
			if (!map13_treasureRandomized) // if treasure hasn't been randomized yet
			{	// treasure gets randomized as soon as the player enters the map
				MAP13_C1.isTaken = TreasureOnRandomizer(MAP13_C1, 4);
				MAP13_J1.isTaken = TreasureOnRandomizer(MAP13_J1, 5);
				MAP13_G1.isTaken = TreasureOnRandomizer(MAP13_G1, 9); map13_treasureRandomized = YES;
			}
			displayMap13();
			currMap = Map13;
			break;
		case Map13:
			collisionDetectorMAP13();
			displayMap13();
			MAP13_checkNewMap();
			break;
		// ======================== MAP 14 ===================================
		case Start_Map14:
			if (!map14_treasureRandomized) // if treasure hasn't been randomized yet
			{	// treasure gets randomized as soon as the player enters the map
				MAP14_C1.isTaken = TreasureOnRandomizer(MAP14_C1, 6);
				MAP14_J5.isTaken = TreasureOnRandomizer(MAP14_J5, 5);
				MAP14_G2.isTaken = TreasureOnRandomizer(MAP14_G2, 11); map13_treasureRandomized = YES;
			}
			displayMap14();
			currMap = Map14;
			break;
		case Map14:
			collisionDetectorMAP14();
			displayMap14();
			MAP14_checkNewMap();
			break;
		// ======================== MAP 15 ===================================
		case Start_Map15:
			displayMap15();
			currMap = Map15;
			break;
		case Map15:
			collisionDetectorMAP15();
			displayMap15();
			MAP15_checkNewMap();
			break;
		default: break;
	}
}

#endif