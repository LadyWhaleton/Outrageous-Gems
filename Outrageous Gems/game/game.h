/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include <avr/io.h>
#include <stdio.h>

#include "timer.h"
#include "globals.h"

#include "CustomChar.h" // includes io.c
#include "player.h"
#include "maphandler.h"
#include "score.h"
#include "gameTime.h"

#include "keypad.h"		// task #0
#include "title.h"		// task #1
#include "tutorial.h"	// task #2

unsigned char pauseMenuIndex;
unsigned char resultsOn;

void resetGame()
{	
	initIcons();
	resetTutorial();
	resetScore();
	loadHighScore();
	initializeMAPS();
	resetGameTimer();
	
	PauseMenuOn = NO;
	pauseMenuIndex = 3;
	GameOn = NO;
	isPaused = NO;
	resultsOn = NO;
	endingOn = NO;
}

void displayResults()
{
	if (!resultsOn)		
	{
		LCD_ClearScreen();
		displayScoreMSG(0, 3); displayScore(score,9); // display score
		displayScoreMSG(1, 17); displayScore(highScore, 27); // display high score
		resultsOn = YES;
		
		if (score > highScore)
			updateHighScore();
	}
}

void displayPauseMenu()
{
	if (!PauseMenuOn)
	{
		LCD_DisplayString(1, "ÿÿÿÿÿPAUSEDÿÿÿÿÿ");
		PauseMenuOn = YES;
	}
	
	switch (pauseMenuIndex)
	{
		case 0:
			if (!scoreDisplayOn) // score display is not on
			{
				clearLCD_lower();
				displayScoreMSG(0, 19);
				displayScore(score, 25);
				scoreDisplayOn = YES;
			}	
			break;
		case 1:
			if (!scoreDisplayOn) 
			{
				clearLCD_lower();
				displayScoreMSG(1, 17);
				displayScore(highScore, 27);
				scoreDisplayOn = YES;
			}
			break;
		case 2:
			if (!TimeDisplayOn)
			{
				clearLCD_lower();
				displayTimeLeftMSG(17);
				displayTimeLeft(gameTimer, 27);
				TimeDisplayOn = YES;
			}
			break;
		default: break;
	}	
}

void playGame()
{
	getNextPosition();
	mapHandler();
}

enum GameStates{loadStartMap, notPaused, pauseWait, pauseDisplay, gameDone, congratz, dispResults, finalMSG, reset, dispEnding};
int game(int state)
{
	if (GameOn)
	{
		switch(state)
		{
			case loadStartMap:
				if (button == 'A')
				{
					LCD_ClearScreen(); displayMap0();
					state = notPaused;
				}
				else
					state = loadStartMap;
				break;
			case notPaused:	
				if (gameOver)
				{
					state = gameDone;
					LCD_DisplayString(1, "ÿÿÿTIME'S UP!ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ");	
				}
				else if (button == 'B')
				{
					state = pauseDisplay; isPaused = YES;
					scoreDisplayOn = NO; TimeDisplayOn = NO;
					pauseMenuIndex = 0;
				}
				else
				{
					state = notPaused; playGame();
				}
				break;
				
			case pauseWait:
				if(  button == 'A') // && button != 'C'?
				{	
					scoreDisplayOn = NO; TimeDisplayOn = NO;
					pauseMenuIndex++;
					if (pauseMenuIndex == 3)
						pauseMenuIndex = 0;
					state = pauseDisplay;
				}
				else if ( button == 'C' ) // unpause the game
				{
					state = notPaused;
					LCD_ClearScreen();
					updateMap = 1; // redisplay the map after unpausing
					
					isPaused = NO; PauseMenuOn = NO;
				}
				else if ( button == 'D') // quit the game
				{
					state = reset;
				}
				else
					state = pauseWait;
				break;

			case pauseDisplay:
				state = pauseWait; break;
			case gameDone:
				if (button == 'A' && score > highScore)
				{
					state = congratz; displayCongratz();
				}
				else if (button == 'A' && score <= highScore)
					state = dispResults; 
				else
					state = gameDone;
				break;
			case congratz:
				if (button == 'A')
					state = dispResults;
				else
					state = congratz;
				break;
			case dispResults:
				if (button == 'A')
				{
					state = finalMSG;
					LCD_DisplayString(1, " Your adventure    has ended.");
				}
				else
					state = dispResults;
				break;
			case finalMSG:
				if (button == 'A')
					state = dispEnding;
				else
					state = finalMSG;
				break;
			case reset: state = loadStartMap; break;
			case dispEnding: state = loadStartMap; break;
			default: break;
		} // end of first switch statement
		
		// second switch for actions
		switch (state)
		{	case loadStartMap: break;
			case notPaused: break;
			case pauseWait: break;
			case pauseDisplay: displayPauseMenu();break;
			case gameDone: break;
			case congratz: break;
			case dispResults: displayResults(); break;
			case finalMSG: break;
			case reset: resetTitle(); resetGame(); LCD_ClearScreen(); break;
			case dispEnding: resetGame(); endingOn = YES; break;
			default: break;
		}
		
	} // end of if statement
	
	return state;
}


#endif