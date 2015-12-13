#include "map.h"
#include "matrix.h"
#include "global_var.h"
#include <curses.h>
#include <cstdlib>

#include "const.h"

void randomize_map ()
{
	// TODO: find a good map generating algorithm
	// I cannot design one
	for (int i = 0; i < map_width-2; i++) {
		map() (i, map_height/2) = map_tile (map_tile::WALL);
	}
	for (int i = 2; i < map_height-2; i++) {
		map() (map_width/2, i) = map_tile (map_tile::WALL);
	}
	invalid_map_rect (0, 0, map_width, map_height);
}
