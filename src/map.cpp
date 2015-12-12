#include "map.h"
#include "matrix.h"
#include "global_var.h"
#include <curses.h>

matrix<map_tile> *pmap;
WINDOW *map_win;

void init_map ()
{
	pmap = new matrix<map_tile> (pglines, pgrows);
	map_win = playground;
}

void randomize_map ()
{
	// TODO: find a good map generating algorithm
	// I cannot design one
	for (int i = 0; i < pglines-2; i++) {
		map() (i, pgrows/2) = map_tile (map_tile::WALL);
	}
}

#define CH_GROUND ' '
#define CH_WALL '+'
#define CH_FOOD 'O'
#define CH_UNDEFINED '?'

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
