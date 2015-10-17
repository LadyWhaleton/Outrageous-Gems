/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

// updates the in-game timer
// if the timer's up, set gameOver = YES. 

#ifndef GAMETIME_H
#define GAMETIME_H

#include "globals.h"
#include "io.c"

#define timeDuration 90 // change this if you want the game to last longer than 60 seconds

unsigned long gameTimer; // in seconds
unsigned char TimeDisplayOn; // flag to set if timer display goes on

void resetGameTimer()
{
	gameOver = NO;
	gameTimer = timeDuration;
	TimeDisplayOn = NO;
}

void displayTimeOnLED(unsigned char TimeLeft)
{
	if (TimeLeft >= 80)
		PORTB = 0xFF;
		
	if (TimeLeft >= 70)
	PORTB = 0x7F;
		
	else if (TimeLeft >= 60)
		PORTB = 0x3F;
	
	else if (TimeLeft >= 50)
		PORTB = 0x1F;
	
	else if (TimeLeft >= 40)
		PORTB = 0x0F;
	
	else if (TimeLeft >= 30)
		PORTB = 0x07;
	
	else if (TimeLeft >= 20)
		PORTB = 0x03;
	
	else if (TimeLeft > 10)
		PORTB = 0x01;

	else if (TimeLeft == 10)
		PORTB = 0x00;
	else if (TimeLeft == 9)
		PORTB = 0x01;
	else if (TimeLeft == 8)
		PORTB = 0x00;
	else if (TimeLeft == 7)
		PORTB = 0x01;
	else if (TimeLeft == 6)
		PORTB = 0x00;
	else if (TimeLeft == 5)
		PORTB = 0x01;
	else if (TimeLeft == 4)
		PORTB = 0x00;
	else if (TimeLeft == 3)
		PORTB = 0x01;
	else if (TimeLeft == 2)
		PORTB = 0x00;
	else if (TimeLeft == 1)
		PORTB = 0x01;
	else
		PORTB = 0x00;
	
}


int updateTimer(int state)
{
	if (GameOn && !isPaused && !gameOver)
	{
		displayTimeOnLED(gameTimer);
		gameTimer--;
		
		if (gameTimer == 0)
		{
			gameOver = YES; PORTB = 0x00;
		}
	}
	
	if (!GameOn)
		 PORTB = 0x00;
		 	
	return state;
}

void displayTimeLeftMSG(unsigned char cursorPos)
{
	LCD_Cursor(cursorPos);
	LCD_WriteData('T'); LCD_WriteData('i'); LCD_WriteData('m'); LCD_WriteData('e'); LCD_WriteData(' ');
	LCD_WriteData('l'); LCD_WriteData('e'); LCD_WriteData('f'); LCD_WriteData('t'); LCD_WriteData(':');
}

void displayTimeLeft(unsigned char tempTime, unsigned char cursorPos)
{
	unsigned char digit = 0;
	if (tempTime >= 100)
	{
		digit = tempTime / 100;
		LCD_Cursor(cursorPos); LCD_WriteData(0 + ('0' + digit));
		tempTime = tempTime - (digit*100);
	}
	
	if (tempTime >= 10)
	{
		digit = tempTime / 10;
		LCD_Cursor(cursorPos+1); LCD_WriteData(0 + ('0' + digit));
		tempTime = tempTime - (digit*10);
	}
	
	if (tempTime >= 1)
	{
		digit = tempTime;
		LCD_Cursor(cursorPos+2); LCD_WriteData(0 + ('0' + digit));
		tempTime = tempTime - (digit*10);
	}
	
	else // time is 0
		LCD_WriteData(0 + '0');
	
	LCD_WriteData('s'); LCD_WriteData('e'); LCD_WriteData('c');
}


#endif