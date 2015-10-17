/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TREASURE_H
#define TREASURE_H

typedef struct _treasure
{
	unsigned char TTYPE; // treasure type (jewel, teardrop, crystal or gem)
	unsigned short PTS; // points
	unsigned char LOC; // location
	unsigned char isTaken; // 1 ("YES" if taken)
} treasure;

#endif