#include "mod_interface.h"

#include <cstdlib>

#define TILE_CUT1 (map_tile::MOD_MIN)
#define TILE_SUPERFOOD (map_tile::MOD_MIN + 1)

#define PROPS_INTERVAL 100

chtype tsnake_mod_get_tile_char (const map_tile *tile)
{
	switch (tile->type) {
	case TILE_CUT1:
		return 'O' | A_REVERSE;
	case TILE_SUPERFOOD:
		return 'O' | COLOR_PAIR (1);
	}
	return CH_UNDEFINED;
}

static int movcnt;

#define TILES 2

int tiles_prob[] = {1, 1, };
int tiles_val[] = {TILE_CUT1, TILE_SUPERFOOD, };

static int random_tile ()
{
	int r = std::rand ();
	int ps = 0;
	for (int i = 0; i<TILES; i++)
		ps += tiles_prob[i];
	r %= ps;
	for (int i = 0; i<TILES; i++) {
		r -= tiles_prob[i];
		if (r < 0) return tiles_val[i];
	}
	return tiles_val[TILES-1];
}

void tsnake_mod_int_move ()
{
	movcnt++;
	if (! (movcnt % PROPS_INTERVAL)) {
		int x,y;
		do {
			x = std::rand () % map_width;
			y = std::rand () % map_height;
		} while ( map() (x, y).type != map_tile::GROUND);
		map() (x, y).type = random_tile ();
		invalid_map_tile (x, y);
	}
}

void tsnake_mod_init_level ()
{
	movcnt = 0;
}

int tsnake_mod_hit_mod_tile (int nx, int ny)
{
	switch (map() (nx, ny).type) {
	case TILE_CUT1:
		if (sn->body.size() > 1) {
			point bk = sn->body.back ();
			map() (bk.x, bk.y).dereserve ();
			invalid_map_tile (bk.x, bk.y);
			sn->body.pop_back ();
		}
		goto cont;
	case TILE_SUPERFOOD:
		scores += 50;
		sn->increase += 3;
		goto cont;
	}
	cont:
	map() (nx, ny) = map_tile (map_tile::GROUND);
	return snake::ALIVE;
}
