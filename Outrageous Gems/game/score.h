/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

// does operation on score
// updates high score if score > highscore
// also displays the score if requested
// also loads high score from EEPROM and writes high score to EEPROM

#ifndef SCORE_H
#define SCORE_H

#include <avr/eeprom.h>
#include "globals.h"
#include "io.c"

#define EEPROM_ADDR 14

// http://deans-avr-tutorials.googlecode.com/svn/trunk/EEPROM/Output/EEPROM.pdf
void loadHighScore()
{
	uint16_t HS_data =  eeprom_read_word( (uint16_t*) EEPROM_ADDR);
	highScore = (unsigned short) HS_data;
	
	if (highScore >= 6000) // score will never get this high
		highScore = 0;
}

void writeHighScore(unsigned short newScore)
{
	uint16_t HS_data = (uint16_t) newScore;
	eeprom_update_word( (uint16_t*) EEPROM_ADDR, HS_data);
}

void updateScore(unsigned short points)
{
	score += points;
}

void resetScore()
{
	score = 0;
	scoreDisplayOn = NO;
	scoreToggle = 0;
}

void displayCongratz()
{
	LCD_DisplayString(1, "CONGRATULATIONS!NEW HIGH SCORE!!");
}

void updateHighScore()
{
		highScore = score;
		writeHighScore(highScore);
}

void displayScore(unsigned short tempScore, unsigned char cursorPos)
{
	unsigned char digit = 0;
	
	if (tempScore >= 100)
	{
		digit = tempScore / 100;
		LCD_Cursor(cursorPos); LCD_WriteData(0 + ('0' + digit));
		tempScore = tempScore - (digit*100);
	}
	
	if (tempScore >= 10)
	{
		digit = tempScore / 10;
		LCD_Cursor(cursorPos+1); LCD_WriteData(0 + ('0' + digit));
		tempScore = tempScore - (digit*10);
	}
	
	if (tempScore >= 1)
	{
		digit = tempScore;
		LCD_Cursor(cursorPos+2); LCD_WriteData(0 + ('0' + digit));
		tempScore = tempScore - (digit*10);
	}
	
	else
	{
		LCD_Cursor(cursorPos+2); LCD_WriteData(0 + '0');
	}
}

void displayScoreMSG(unsigned char Toggle, unsigned char cursorPos)
{
		if (Toggle == 0) // display score
		{
			LCD_Cursor(cursorPos); LCD_WriteData('S'); LCD_WriteData('c');LCD_WriteData('o'); LCD_WriteData('r');LCD_WriteData('e'); // scoore
			LCD_WriteData(':');
			LCD_Cursor(cursorPos+9); LCD_WriteData('p'); LCD_WriteData('t');LCD_WriteData('s'); // pts
		}
		
		else // display high score
		{
			LCD_Cursor(cursorPos); LCD_WriteData('H'); LCD_WriteData('i'); LCD_WriteData('g'); LCD_WriteData('h'); // "high
			LCD_WriteData('S'); LCD_WriteData('c');LCD_WriteData('o'); LCD_WriteData('r');LCD_WriteData('e'); // "score
			LCD_WriteData(':');
			LCD_Cursor(cursorPos+13); LCD_WriteData('p'); LCD_WriteData('t');LCD_WriteData('s'); // pts
		}
}


#endif