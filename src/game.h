#ifndef _GAME_H
#define _GAME_H

#include "snake.h"

#include "global_var.h"

#include <cmath>

void game_main ();

void init_level ();

extern snake *sn;

extern enum game_mode {MODE_PLAY, MODE_PAUSE, MODE_END, MODE_QUIT} game_mode;

extern int scores, moves, time_slices;

void update_scores_buf ();

#define SNAKE_PI 3.14159265358979323846

inline int calculate_speed () { return level < 15 ? 20 - level : 5; }

inline int calculate_maxscore () { return level * 100; }

#endif
