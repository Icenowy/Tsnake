#ifndef _MOD_H
#define _MOD_H

#include "map.h"

void mod_init ();

chtype mod_get_tile_char (const map_tile &tile);

bool mod_has_map_gen ();

void mod_map_gen ();

void mod_int_timer ();

void mod_int_move ();

void mod_init_level ();

int mod_hit_mod_tile (int nx, int ny);
#endif
