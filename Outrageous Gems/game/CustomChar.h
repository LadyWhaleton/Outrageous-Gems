/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
* Date Created: 8/21/14
*
* CustomChar.h contains several functions for creating custom characters and storing
* them to the LCD CGRAM. This file also contains some other functions that can turn off 
* the cursor on the LCD and turn the cursor back on (and make it blink again).
*/
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CUSTOMCHAR_H
#define CUSTOMCHAR_H
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include "io.c"

#define PLAYER 0
#define JEWEL 1
#define TEARDROP 2
#define CRYSTAL 3
#define GEM 4
#define TREE 5
#define UP_ARROW 6
#define DOWN_ARROW 7
#define RIGHT_ARROW 126
#define LEFT_ARROW 127
#define PORTAL 219

// WriteData(255) = ÿ = black box

/* source: http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=48424&start=0 */
#define C_ON 0b00001100 // turns cursor on and makes it blink
#define C_OFF 0b00001111 // turns cursor off

void cursorOn()
{
	LCD_WriteCommand(C_OFF);
}

void cursorOff()
{
	LCD_WriteCommand(C_ON);
}

void createPlayerIcon()
{
	LCD_WriteData(0xE);
	LCD_WriteData(0xA);
	LCD_WriteData(0xE);
	LCD_WriteData(0x15);
	
	LCD_WriteData(0x4);
	LCD_WriteData(0xE);
	LCD_WriteData(0xA);
	LCD_WriteData(0xA);
}

void createHouseIcon()
{
	LCD_WriteData(0x0);
	LCD_WriteData(0x4);
	LCD_WriteData(0xE);
	LCD_WriteData(0x1F);
	
	LCD_WriteData(0x1F);
	LCD_WriteData(0x11);
	LCD_WriteData(0x11);
	LCD_WriteData(0x1F);
}

void createJewelIcon()
{
	LCD_WriteData(0x0);
	LCD_WriteData(0x0);
	LCD_WriteData(0xE);
	LCD_WriteData(0x11);
	
	LCD_WriteData(0xA);
	LCD_WriteData(0x4);
	LCD_WriteData(0x0);
	LCD_WriteData(0x0);
}

void createGemIcon()
{
		LCD_WriteData(0xE);
		LCD_WriteData(0x15);
		LCD_WriteData(0x15);
		LCD_WriteData(0x1B);
		
		LCD_WriteData(0x15);
		LCD_WriteData(0x15);
		LCD_WriteData(0x15);
		LCD_WriteData(0xE);
}

void createTeardropIcon()
{
	LCD_WriteData(0x0);
	LCD_WriteData(0x4);
	LCD_WriteData(0xA);
	LCD_WriteData(0x15);
	
	LCD_WriteData(0x1B);
	LCD_WriteData(0x15);
	LCD_WriteData(0xE);
	LCD_WriteData(0x0);
}

void createCrystalIcon()
{
		LCD_WriteData(0x4);
		LCD_WriteData(0xA);
		LCD_WriteData(0x11);
		LCD_WriteData(0x1B);
		
		LCD_WriteData(0x15);
		LCD_WriteData(0x15);
		LCD_WriteData(0xA);
		LCD_WriteData(0x4);
}

void createTreeIcon()
{
		LCD_WriteData(0x4);
		LCD_WriteData(0xE);
		LCD_WriteData(0x1F);
		LCD_WriteData(0x4);
		
		LCD_WriteData(0xE);
		LCD_WriteData(0x1F);
		LCD_WriteData(0x4);
		LCD_WriteData(0x4);
}

// 0x4,0xe,0x15,0x4,0x4,0x4,0x4,0x4
void createUARROWIcon()
{
		LCD_WriteData(0x4);
		LCD_WriteData(0xE);
		LCD_WriteData(0x15);
		LCD_WriteData(0x4);
		
		LCD_WriteData(0x4);
		LCD_WriteData(0x0);
		LCD_WriteData(0x0);
		LCD_WriteData(0x0);
}

//0x4,0x4,0x4,0x4,0x4,0x15,0xe,0x4
void createDARROWIcon()
{
		
		LCD_WriteData(0x0);
		LCD_WriteData(0x0);
		LCD_WriteData(0x0);
		LCD_WriteData(0x4);
		
		LCD_WriteData(0x4);
		LCD_WriteData(0x15);
		LCD_WriteData(0xE);
		LCD_WriteData(0x4);
}

void createFishIcon()
{
	LCD_WriteData(0x1F);
	LCD_WriteData(0x1F);
	LCD_WriteData(0x16);
	LCD_WriteData(0xA);
	
	LCD_WriteData(0xD);
	LCD_WriteData(0xD);
	LCD_WriteData(0x12);
	LCD_WriteData(0x1F);

}

// ======================= custom characters for specific states ====================

// writes to CGRAM the icons to be used for the tutorial 
void initIcons()
{
	LCD_WriteCommand(0x40);
	createPlayerIcon();
	createJewelIcon();
	createTeardropIcon();
	createCrystalIcon();
	createGemIcon();
	createTreeIcon();
	createUARROWIcon();
	createDARROWIcon();
}


#endif