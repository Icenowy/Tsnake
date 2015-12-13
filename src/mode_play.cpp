#include "mode_play.h"
#include "game.h"
#include "mode_end.h"
#include "mode_pause.h"

#include <curses.h>
#include "tsgettext.h"
#include "global_var.h"

#define TIME_SLICE_LENGTH 50 // in ms

#define SCORES_PER_FOOD 10
#define SCORES_PER_MOVE 1

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
	case snake::DIE_UNKNOWN:
		wininfo->putline (gettext ("What the hell is this?!"));
		goto bad_end;
	}
	good_end:
	moves++;
	scores += SCORES_PER_MOVE;
	return true;
	bad_end:
	enter_end (false);
	return false;
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
	}
}
