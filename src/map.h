#ifndef _MAP_H
#define _MAP_H

#include "matrix.h"

struct map_tile {
	enum {
		GROUND, WALL, FOOD
	} type;
};

extern matrix<map_tile> *pmap;

inline matrix<map_tile> &map () { return *pmap; }

#endif
