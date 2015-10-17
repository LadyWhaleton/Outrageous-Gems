/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
* Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ENDANI_H
#define ENDANI_H

#include "CustomChar.h"
#include "globals.h"
#include "title.h"

enum _ENDANI_STATES {start, go, finish};
unsigned char endex; // cursor position

int endAnimation(int state)
{
	if (endingOn)
	{
		switch (state)
		{
			case start:
				endex = 31;
				state = go;
				break;
			case go:
				if (endex == 0) 
					state = finish;
				else if (button == 'A')
				{
					LCD_ClearScreen();
					state = finish;
				}
				else
					state = go;
				break;
			case finish:
				state = start;
				break;
		}
		
		switch (state)
		{
			case start: break;
			case go:
				LCD_Cursor(endex); LCD_WriteData(PLAYER);
				LCD_Cursor(endex+1); LCD_WriteData(' ');
				endex--;
				
				if (endex == 0)
					LCD_Cursor(1); LCD_WriteData(' ');
				
				break;
			case finish:
				resetTitle();
				endingOn = NO;
			break;
		}
	}
	
	return state;

}
#endif