#include "mode_play.h"
#include "game.h"
#include "mode_end.h"
#include "mode_pause.h"

#include <curses.h>
#include "tsgettext.h"
#include "global_var.h"

#include "const.h"

#include "mod.h"

int last_move_time;

void enter_play ()
{
	game_mode = MODE_PLAY;
	wtimeout (playground, TIME_SLICE_LENGTH);
}

volatile bool mode_play_force_exit;

bool game_play_step ()
{
	switch (sn->step ()) {
	case snake::ALIVE:
		goto good_end;
	case snake::FOOD_FOUND:
		sn->increase++;
		generate_food ();
		scores += SCORES_PER_FOOD;
		goto good_end;
	case snake::DIE_KNOCK_WALL:
		wininfo->putline (gettext ("So hard the wall is!"));
		goto bad_end;
	case snake::DIE_CROSS_EDGE:
		wininfo->putline (gettext ("Destiny cannot be escaped."));
		goto bad_end;
	case snake::DIE_KNOCK_SELF:
		wininfo->putline (gettext ("Why is my body so hard..."));
		goto bad_end;
	case snake::DIE_MOD:
		// Say nothing
		goto bad_end;
	case snake::DIE_UNKNOWN:
		wininfo->putline (gettext ("What the hell is this?!"));
		goto bad_end;
	}
	good_end:
	moves++;
	mod_int_move ();
	scores += SCORES_PER_MOVE;
	return true;
	bad_end:
	enter_end (false);
	return false;
}

void game_play ()
{
	mode_play_force_exit = false;
	last_move_time = time_slices;
	while (! mode_play_force_exit) {
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
		case 'w':
		case 'k':
		case KEY_UP:
			if (sn->direction == snake::DOWN) break;
			sn->direction = snake::UP;
			if (!game_play_step ()) return;
			last_move_time = time_slices;
			break;
		case 's':
		case 'j':
		case KEY_DOWN:
			if (sn->direction == snake::UP) break;
			sn->direction = snake::DOWN;
			if (!game_play_step ()) return;
			last_move_time = time_slices;
			break;
		case 'a':
		case 'h':
		case KEY_LEFT:
			if (sn->direction == snake::RIGHT) break;
			sn->direction = snake::LEFT;
			if (!game_play_step ()) return;
			last_move_time = time_slices;
			break;
		case 'd':
		case 'l':
		case KEY_RIGHT:
			if (sn->direction == snake::LEFT) break;
			sn->direction = snake::RIGHT;
			if (!game_play_step ()) return;
			last_move_time = time_slices;
			break;
		default:
			// Timeout
			if (time_slices - last_move_time < calculate_speed ()) break;
			if (!game_play_step ()) return;
			last_move_time = time_slices;
			break;
		}
		update_scores_buf ();
		if (scores >= calculate_maxscore()) {
			level++;
			enter_end (true);
			return;
		}
		mod_int_timer ();
	}
}
