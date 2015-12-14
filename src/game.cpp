#include <iostream>
#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include "tsgettext.h"

#include "split.h"
#include "map.h"
#include "snake.h"

#include "game.h"
#include "mode_pause.h"
#include "mode_play.h"
#include "mode_end.h"

#include "mod.h"

snake *sn;

enum game_mode game_mode;

int scores, moves, time_slices;

static void splash ()
{
	wininfo->putline (gettext ("***Welcome to Tsnake***"));
	wininfo->putline (gettext ("To read the handbook, please use --help option"));
}

void init_level ()
{
	init_map ();
	randomize_map ();
	generate_food ();
	if (sn) delete sn;
	sn = snake::init_snake ();
	time_slices = scores = moves = 0;
	update_scores_buf ();
	mod_init_level ();
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

void update_scores_buf ()
{
	std::string sc, mv;
	sc += gettext ("Scores: ");
	sc += std::to_string (scores);
	sc += "/";
	sc += std::to_string (calculate_maxscore ());
	mv += gettext ("Moves: ");
	mv += std::to_string (moves);
	bufgoods->buffer[0] = sc;
	bufgoods->buffer[1] = mv;
	bufgoods->refresh_buffer ();
}

void game_main ()
{
	init_split ();
	splash ();
	mod_init ();
	init_level ();
	enter_end (true, true);
	main_loop ();
}
