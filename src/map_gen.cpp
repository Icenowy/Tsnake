#include "map.h"
#include "matrix.h"
#include "global_var.h"
#include <curses.h>
#include <cstdlib>

#include "const.h"

static void floodfill (matrix<bool> &mat, int x, int y)
{
	if (map() (x, y).type == map_tile::WALL) return;
	mat (x,y) = true;
	if (x > 1 && !mat (x-1, y)) floodfill (mat, x-1, y);
	if (y > 1 && !mat (x, y-1)) floodfill (mat, x, y-1);
	if (x < map_width - 1 && !mat (x+1, y)) floodfill (mat, x+1, y);
	if (y < map_height - 1 && !mat (x, y+1)) floodfill (mat, x, y+1);
}

bool floodfill_verify (matrix<bool> &mat)
{
	for (int i = 0;i<map_width; i++) {
		for (int j = 0; j<map_height; j++) {
			mat (i, j) = false;
		}
	}
	floodfill (mat, 0, 0);
	for (int i = 0;i<map_width; i++) {
		for (int j = 0; j<map_height; j++) {
			if (map() (i, j).type == map_tile::GROUND && !mat (i, j))
				return false;
		}
	}
	return true;
}

void randomize_map ()
{
	int map_level = (level > MAX_MAP_LEVEL) ? MAX_MAP_LEVEL : level;
	matrix<bool> vrfy_mat (map_width, map_height);
	do {
		for (int i = 0; i<map_width; i++)
			for (int j = 0; j<map_height; j++)
				map() (i, j) = map_tile (map_tile::GROUND);

		for (int t = 0; t< (MAP_VERT_WALL_BASE + MAP_VERT_WALL_ADV * map_level); t++) {
			int length = std::rand () % (map_height / 2);
			int xpos = std::rand () % map_width;
			int ypos = std::rand () % (map_height - length);
			for (int i = 0; i<length; i++) {
				if (ypos + i < map_height)
					map() (xpos, ypos + i) = map_tile (map_tile::WALL);
				else
					break;
			}
		}
		for (int t = 0; t< (MAP_HORI_WALL_BASE + MAP_HORI_WALL_ADV * map_level); t++) {
			int length = std::rand () % (map_width / 2);
			int xpos = std::rand () % (map_width - length);
			int ypos = std::rand () % map_height;
			for (int i = 0; i<length; i++) {
				if (xpos + i < map_width)
					map() (xpos + i, ypos) = map_tile (map_tile::WALL);
				else
					break;
			}
		}
	} while (!floodfill_verify (vrfy_mat));

	invalid_map_rect (0, 0, map_width, map_height);
}
