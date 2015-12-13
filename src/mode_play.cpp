#include "mode_play.h"
#include "game.h"
#include "mode_end.h"
#include "mode_pause.h"

#include <curses.h>
#include "tsgettext.h"
#include "global_var.h"

#define TIME_SLICE_LENGTH 50 // in ms

int last_move_time;

void enter_play ()
{
	game_mode = MODE_PLAY;
	wtimeout (playground, TIME_SLICE_LENGTH);
}

bool game_play_step ()
{
	switch (sn->step ()) {
	case snake::ALIVE:
		return true;
	case snake::FOOD_FOUND:
		sn->increase++;
		return true;
	case snake::DIE_KNOCK_WALL:
		wininfo->putline (gettext ("So hard the wall is!"));
		enter_end (false);
		return false;
	case snake::DIE_CROSS_EDGE:
		wininfo->putline (gettext ("Destiny cannot be escaped."));
		enter_end (false);
		return false;
	case snake::DIE_KNOCK_SELF:
		wininfo->putline (gettext ("Why is my body so hard..."));
		enter_end (false);
		return false;
	case snake::DIE_UNKNOWN:
		wininfo->putline (gettext ("What the hell is this?!"));
		enter_end (false);
		return false;
	}
}

int calculate_speed ()
{
	return 20;
}

void game_play ()
{
	last_move_time = time_slices;
	while (true) {
		int ch;
		ch = wgetch (playground);
		time_slices++;
		switch (ch) {
		case 'p':
			enter_pause ();
			return;
		case 'q':
			game_mode = MODE_QUIT;
			return;
		case ERR:
			// Timeout
			if (time_slices - last_move_time < calculate_speed ()) break;
			if (!game_play_step ()) return;
			last_move_time = time_slices;
			break;
		}
	}
}
