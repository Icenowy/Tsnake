#include "mod_interface.h"

chtype tsnake_mod_get_tile_char (const map_tile *tile)
{
	if (tile->type == map_tile::MOD_MIN) {
		return 'O' | A_REVERSE;
	}
	return CH_UNDEFINED;
}

void tsnake_mod_map_gen ()
{
	for (int i = 0; i < map_width; i++)
		for (int j = 0; j < map_height; j++)
			map() (i,j) = map_tile (map_tile::GROUND);
	for (int i = 0; i < map_width-2; i++) {
		map() (i, map_height/2) = map_tile (map_tile::WALL);
	}
	map() (0,0) = map_tile (map_tile::MOD_MIN);
}

void tsnake_mod_int_timer ()
{
}

static int movcnt;

void tsnake_mod_int_move ()
{
	movcnt++;
	if (! (movcnt % 30))
		for (int i = 0; i<10; i++) {
			if (map() (i,0).type == map_tile::GROUND) {
				map() (i,0) = map_tile (map_tile::MOD_MIN);
				invalid_map_tile (i, 0);
				wininfo->putline ("Test tile grown.");
				break;
			}
		}
}

void tsnake_mod_init_level ()
{
	movcnt = 0;
}

int tsnake_mod_hit_mod_tile (int nx, int ny)
{
	if(sn->body.size() > 1) {
		point bk = sn->body.back ();
		map() (bk.x, bk.y).dereserve ();
		invalid_map_tile (bk.x, bk.y);
		sn->body.pop_back ();
	}
	return snake::ALIVE;
}
