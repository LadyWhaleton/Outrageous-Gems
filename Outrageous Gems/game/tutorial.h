/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "CustomChar.h" // includes io.c
#include "globals.h"

unsigned char TutMSGOn;
unsigned char tutIndex;

//=================================== tutorial ==========================================================================
// "You must collect as many treasures as you can before the time runs out!"
char* tutArr[] =
{					"   Press A to       continue",
	"ÿÿÿÿCONTROLSÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ",		// "ÿ" is a black rectangle according to this LCD
	"2:up     5:down 4:left   6:right",
	"  1:loot/enter  A:next message",
	"    B:pause        C:unpause",
	"Note: pause game to view score",
	" and remaining   time",
	"  D:quit game    (when paused)",
	"ÿÿÿÿÿICONSÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ",
	"player and <^v>",						// index 9
	" Û  teleporters  1-time use each",		// index 10
	"ÿÿÿÿÿÿGEMSÿÿÿÿÿÿcollect for pts!"
	"jewel, teardrop",						// index 12
	"crysal, gem"							// index 13

};

unsigned char tutArrSize = 14;
enum tutStates {tutAsk, tutStart, tutWait, tutDisplay, tutEnd};

// function will turn the tutorial off and also display a message
// it will also initiate variables for starting the game
void endTutorial()
{
	LCD_DisplayString(1, " Tutorial over!  (A=Start Game)");
	TutorialOn = NO;
	GameOn= YES;
	updateMap = YES;
	
}

void resetTutorial()
{
	TutorialOn = NO;
	TutMSGOn = NO;
	tutIndex = 0;
}

/*
*  ---- based on the index, this function has certain operations: -----------------
*  1. handles special tutorial messages (ones that can't be display in array because
*  they are either custom characters or hard to represent with copy pasting)
*				ex: the tree icon used for this game
* 2. if it's not a special message, just use LCD_DisplayString()
*/
void tutDisplayMSG()
{
	if (tutIndex == 9)
	{
		LCD_DisplayString(1, "      player    <^v> to next map");
		LCD_Cursor(5); LCD_WriteData(PLAYER);
		LCD_Cursor(17); LCD_WriteData(LEFT_ARROW); LCD_WriteData(UP_ARROW);
		LCD_WriteData(DOWN_ARROW); LCD_WriteData(RIGHT_ARROW);
	}
	
	else if (tutIndex == 12)
	{
		LCD_DisplayString(1, "      2pts            3pts"),
		LCD_Cursor(5); LCD_WriteData(JEWEL);
		LCD_Cursor(21); LCD_WriteData(TEARDROP);
	}
	
	else if (tutIndex == 13)
	{
		LCD_DisplayString(1, "      5pts            15pts"),
		LCD_Cursor(5); LCD_WriteData(CRYSTAL);
		LCD_Cursor(21); LCD_WriteData(GEM);
	}
	
	else
		LCD_DisplayString(1, tutArr[tutIndex]);
	
}

int Tutorial(int state)
{
	if (TutorialOn)
	{
		switch (state) // transitions
		{
			case tutAsk:
				//display message asking if user wants to skip the tutorial
				if (!TutMSGOn)
				{
					LCD_DisplayString(1, " Skip Tutorial?  (A=YES,B=NO)");
					TutMSGOn = YES;
					state = tutAsk;
				}
				else
					state = tutStart;
				break;
			case tutStart:
				if (button == 'A')
					state = tutEnd;
				else if (button == 'B')
				{
					LCD_DisplayString(1, tutArr[tutIndex]);
					tutIndex++;
					state = tutWait;
				}
				else
					state = tutStart;
				break;
			
			case tutWait:
				if(  button == 'A' && tutIndex == tutArrSize )
					state = tutEnd;
				else if ( button == 'A' && tutIndex != tutArrSize )
					state = tutDisplay;
				else
					state = tutWait;
				break;
			
			case tutDisplay:
				state = tutWait; break;
			case tutEnd:
				state = tutAsk; break;
			
			default: break;
		}
		
		switch (state) // actions
		{
			case tutAsk: break;
			case tutStart: break;
			case tutWait: break;
			case tutDisplay: 
				tutDisplayMSG();
				tutIndex++;
				break;
			
			case tutEnd:
				endTutorial();
				break;
			
			default: break;
		}
		
	}
	
	return state;
}

#endif
