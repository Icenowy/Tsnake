#include "mod_interface.h"

void tsnake_mod_map_gen ()
{
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
			map() (i,j) = map_tile (map_tile::GROUND);
	for (int i = 0; i < map_width-2; i++) {
		map() (i, map_height/2) = map_tile (map_tile::WALL);
	}
	for (int i = 2; i < map_height-2; i++) {
		map() (map_width/2, i) = map_tile (map_tile::WALL);
	}
}
