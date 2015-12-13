#include "map.h"
#include "matrix.h"
#include "global_var.h"
#include <curses.h>
#include <cstdlib>

#include "const.h"

matrix<map_tile> *pmap;
WINDOW *map_win;
int map_width, map_height;

void init_map ()
{
	if (pmap) delete pmap;
	pmap = new matrix<map_tile> (pglines, pgrows);
	map_win = playground;
	map_width = pglines;
	map_height = pgrows;
}

void draw_map_tile (const map_tile &tile, int x, int y, bool refresh)
{
	switch (tile.type) {
	case map_tile::GROUND:
		mvwaddch (map_win, y, x, CH_GROUND);
		break;
	case map_tile::WALL:
		mvwaddch (map_win, y, x, CH_WALL);
		break;
	case map_tile::FOOD:
		mvwaddch (map_win, y, x, CH_FOOD);
		break;
	case map_tile::RESERVED:
		break;
	default:
		mvwaddch (map_win, y, x, CH_UNDEFINED);
		break;
	}
	if (refresh) wrefresh (map_win);
}

void invalid_map_rect (int x1, int y1, int width, int height, bool refresh)
{
	for (int i = 0; i<width; i++) {
		for(int j = 0; j<height; j++) {
			invalid_map_tile (x1+i, y1+j, false);
		}
	}
	if (refresh) wrefresh (map_win);
}

void generate_food ()
{
	int x,y;
	do {
		x = std::rand () % map_width;
		y = std::rand () % map_height;
	} while ( map() (x, y).type != map_tile::GROUND);
	map() (x, y).type = map_tile::FOOD;
	invalid_map_tile (x, y);
}
