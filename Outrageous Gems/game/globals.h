/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GLOBALS_H
#define GLOBALS_H

enum YAY_O_NAY {NO, YES};
enum Maps {
		   Start_Map0, Map0, 
		   Start_Map1, Map1, 
		   Start_Map2, Map2, 
		   Start_Map3, Map3, 
		   Start_Map4, Map4,
		   Start_Map5, Map5,
		   Start_Map6, Map6,
		   Start_Map7, Map7,
		   Start_Map8, Map8,
		   Start_Map9, Map9,
		   Start_Map10, Map10,
		   Start_Map11, Map11,
		   Start_Map12, Map12,
		   Start_Map13, Map13,
		   Start_Map14, Map14,
		   Start_Map15, Map15
		   };
	
unsigned char button; // the button that is pressed
unsigned gameOver; // flag indicating that the game is over

unsigned char TutorialOn;
unsigned char GameOn; // flag indicating that the game is currently on
unsigned char PauseMenuOn; // flag indicating that the "ÿÿÿÿPAUSEDÿÿÿÿ" is already been displayed or not
unsigned char isPaused;
unsigned char endingOn;

unsigned char currMap;	// location of the current map
unsigned char updateMap; // flag that is set to 1 if map needs to be updated

unsigned char currPlayerPos;
unsigned char nextPlayerPos;

unsigned char movePlayer; // flag determining if player should move

unsigned char fakeRandomNumber;

unsigned short score;
unsigned short highScore;
unsigned char scoreToggle;
unsigned char scoreDisplayOn;

#endif