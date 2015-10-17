/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

// doesn't handle map obstables such as trees yet. just determines if the 
// designated player movement is within bounds of the LCD screen
// if it is, then nextPlayerPos = currPlayerPos + offset
/*							 LCD MAP
	| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
	| 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 |
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void validateMoveUp()
{
	if (currPlayerPos < 17)  // character is on the upper half
		nextPlayerPos = currPlayerPos; // character can't move
	else
	{
		nextPlayerPos = currPlayerPos - 16; // character moves up
		updateMap = 1;
	}

}

void validateMoveDown()
{
	if (currPlayerPos > 16) // character is on the lower half
		nextPlayerPos = currPlayerPos;
	else
	{
		nextPlayerPos = currPlayerPos + 16; // character moves down
		updateMap = 1;
	}
}

void validateMoveLeft()
{
	if (currPlayerPos == 1 || currPlayerPos == 17)
		nextPlayerPos = currPlayerPos;
	else
	{
		nextPlayerPos = currPlayerPos - 1;
		updateMap = 1;
	}

}

void validateMoveRight()
{
	if (currPlayerPos == 16 || currPlayerPos == 32)
		nextPlayerPos = currPlayerPos;
	else
	{
		nextPlayerPos = currPlayerPos + 1;
		updateMap = 1;
	}
}

void getNextPosition()
{	
		if (button == '2') // player presses up
			validateMoveUp();
		
		else if (button == '5') // player presses down
			validateMoveDown();
		
		else if (button == '4') // player presses left
			validateMoveLeft();
		
		else if (button == '6') // player presses right
			validateMoveRight();
}

#endif