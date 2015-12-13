#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include "tsgettext.h"

#include "split.h"
#include "map.h"
#include "snake.h"

static snake *sn;

enum game_mode {MODE_PLAY, MODE_PAUSE, MODE_END, MODE_QUIT} game_mode;

void splash ()
{
	wininfo->putline (gettext ("***Tsnake Version 0.0.0***"));
	wininfo->putline (gettext ("To read the handbook, please use --help option"));
}

void init_level ()
{
	init_map ();
	randomize_map ();
	generate_food ();
	if (sn) delete sn;
	sn = snake::init_snake ();
}

void main_loop ()
{
	
}

void game_main ()
{
	init_split ();
	splash ();
	init_level ();
}
