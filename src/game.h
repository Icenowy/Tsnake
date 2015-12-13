#ifndef _GAME_H
#define _GAME_H

#include "snake.h"

void game_main ();

void init_level ();

extern snake *sn;

extern enum game_mode {MODE_PLAY, MODE_PAUSE, MODE_END, MODE_QUIT} game_mode;

#endif
