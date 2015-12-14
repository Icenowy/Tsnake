#ifndef _MOD_INTERFACE_H
#define _MOD_INTERFACE_H

#include "../map.h"
#include "../snake.h"
#include "../game.h"
#include "../global_var.h"
#include "../matrix.h"
#include "../point.h"
#include "../const.h"
#include <curses.h>

extern "C" chtype tsnake_mod_get_tile_char (const map_tile *tile);
extern "C" void tsnake_mod_map_gen ();
extern "C" void tsnake_mod_food_gen ();
extern "C" void tsnake_mod_int_timer ();
extern "C" void tsnake_mod_int_move ();
extern "C" void tsnake_mod_init_level ();
extern "C" int tsnake_mod_hit_mod_tile (int nx, int ny);
#endif
