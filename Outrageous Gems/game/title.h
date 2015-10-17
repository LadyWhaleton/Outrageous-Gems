/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TITLE_H
#define TITLE_H

#include "keypad.h"
#include "globals.h"

unsigned char TitleOn; // flag for enabling the titleScreen

char *TitleArray = "Outrageous Gems ";
char *Title2Array = "press A to start";

unsigned char TitleIndex;
unsigned char Title2Index;

// "clears" the lower half of the LCD
void clearLCD_lower()
{
	for (unsigned char i = 17; i < 33; i++)
	{
		LCD_Cursor(i); LCD_WriteData(' ');
	}
}

void resetTitle()
{
	TitleOn = YES;
	TitleIndex = 0;
	Title2Index = 0;
}

void displayTitle1()
{
	//display title screen here if it hasn't been displayed yet.
	//we have a flag so the LCD doesn't keep refreshing
	LCD_Cursor(1);
	unsigned char j = JEWEL;
	for (unsigned char i = 1; i < 17; i++)
	{
		if (j > GEM)
			j = JEWEL;
		LCD_Cursor(i); LCD_WriteData(j); j++;
	}
	LCD_Cursor(1);
}

void displayTitle2()
{
	LCD_DisplayString(1, "Outrageous Gems ");
}

void displayTitle3()
{
	unsigned char j = 0;
	for (unsigned char i = 17; i < 33; i++)
	{
		LCD_Cursor(i); LCD_WriteData(Title2Array[j]); j++;
	}
}

void displayTitleAni()
{
	LCD_WriteData(TitleArray[TitleIndex]);
	TitleIndex++;
}


enum titleStates {initTitle, titleAni, flash_on, flash_off, doneTitle};
int TitleScreen(int state)
{
	// if the game has already been started ignore this and don't display title screen
	if (TitleOn)
	{
		switch(state)
		{
			case initTitle: 
				LCD_ClearScreen();
				displayTitle1();
				state = titleAni;
				break;
			case titleAni:
				if (TitleIndex > 15)
					state = flash_on;
				else if (button == 'A')
				{
					displayTitle2();
					state = flash_on;
				}
				else
					state = titleAni;
				break;
			case flash_on: 
				if (button == 'A')
					state = doneTitle;
				else
					state = flash_off;
				break;
			case flash_off:
				if (button == 'A')
					state = doneTitle;
				else
					state = flash_on;
				break;
			case doneTitle:
				state = initTitle;
				break;
			default: break;
		} // end of first switch
		
		switch (state)
		{
			case initTitle: break;
			case titleAni: displayTitleAni(); break;
			case flash_on: displayTitle3(); break;
			case flash_off: clearLCD_lower(); break;
			case doneTitle: 
				TitleOn = NO;
				TutorialOn = YES;
				break;
			default: break;
		}
	} // end of if (TitleOn) statement
	
	return state;
}

#endif