#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include "tsgettext.h"

#include "split.h"
#include "map.h"
#include "snake.h"

#include "mode_pause.h"
#include "mode_play.h"
#include "mode_end.h"

snake *sn;

enum game_mode {MODE_PLAY, MODE_PAUSE, MODE_END, MODE_QUIT} game_mode;

static void splash ()
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
	time_slices = 0;
}

static void main_loop ()
{
	while (true) {
		switch (game_mode) {
		case MODE_PLAY:
			game_play ();
			break;
		case MODE_PAUSE:
			game_pause ();
			break;
		case MODE_END:
			game_end ();
			break;
		case MODE_QUIT:
			std::exit (0);
		}
	}
}

void game_main ()
{
	init_split ();
	splash ();
	init_level ();
	enter_end (true, true);
	main_loop ();
}
