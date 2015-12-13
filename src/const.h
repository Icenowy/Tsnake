#ifndef _CONST_H
#define _CONST_H

// Screen
#define MIN_ROWS 18
#define MIN_LINES 48
#define EXTRA_ROWS 6
#define EXTRA_LINES 32
#define DEFAULT_ROWS 18
#define DEFAULT_LINES 48
#define INFO_ROWS 4
#define GOODS_LINES 29
#define GOODS_FIXED_ROWS 24

// Chars
#define CH_GROUND ' '
#define CH_WALL '+'
#define CH_FOOD 'O'
#define CH_UNDEFINED '?'
#define CH_SNAKE_HEAD '@'
#define CH_SNAKE_BODY '.'

// Gameplay
#define INITIAL_LEVEL 1
#define INITIAL_INCREASE 3
#define GAME_END_DELAY 3
#define TIME_SLICE_LENGTH 50
#define SCORES_PER_FOOD 10
#define SCORES_PER_MOVE 0

#endif
