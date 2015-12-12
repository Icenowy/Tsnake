#ifndef _MAP_H
#define _MAP_H

#include "matrix.h"

struct map_tile {
	static const int
		GROUND = 0,
		WALL = 1,
		FOOD = 2;
	int type;

	map_tile () : type (GROUND) {}
	map_tile (int ty) : type (ty) {}
};

extern matrix<map_tile> *pmap;

inline matrix<map_tile> &map () { return *pmap; }

void init_map ();

void randomize_map ();

#endif
