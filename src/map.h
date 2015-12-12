#ifndef _MAP_H
#define _MAP_H

#include "matrix.h"
#include <curses.h>

struct map_tile {
	static const int
		GROUND = 0,
		WALL = 1,
		FOOD = 2,
		RESERVED = 3 // RESERVED means that the tile is reserved by other modules
	;
	int type;

	union {
		int reserved_type; // for RESERVED
	};

	map_tile () : type (GROUND) {}
	map_tile (int ty) : type (ty) {}
	void reserve () {
		if (type != RESERVED) {
			reserved_type = type;
			type = RESERVED;
		}
	}

	void dereserve () {
		type = reserved_type;
	}
};

extern matrix<map_tile> *pmap;
extern WINDOW *map_win;
extern int map_width, map_height;

inline matrix<map_tile> &map () { return *pmap; }

void init_map ();

void randomize_map ();

void draw_map_tile (const map_tile &tile, int x, int y, bool refresh = true);

inline void invalid_map_tile (int x, int y, bool refresh = true) {
	draw_map_tile (map() (x, y), x, y, refresh);
}

void invalid_map_rect (int x1, int y1, int width, int height, bool refresh = true);

void generate_food ();

#endif
