/////////////////////////////////////////////////////////////////////////////////////////////////
/* Author: Stephanie Tong
* Email: stong002@ucr.edu
* CS120B: Custom Lab
* Game: Outrageous Gems
 * Summer 2014
*/
/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAPMARKERS_H
#define MAPMARKERS_H

typedef struct _mapmarker
{
	unsigned char playerStartPos; // player's starting position for the next map
	unsigned char nextMap; // nextMap
	unsigned char markerPos; // position of the map marker
	unsigned char MTYPE; // marker type
} MapMarker;

#endif