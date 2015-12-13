#include "mode_end.h"
#include "game.h"
#include "mode_play.h"

#include <curses.h>
#include <unistd.h>
#include "tsgettext.h"
#include "global_var.h"

#define GAME_END_DELAY 3

void enter_end (bool good_end, bool init)
{
	char str[100];
	if (!init) {
		if (good_end)
			snprintf (str, 99, gettext ("You win! Welcome to level %d"), level);
		else
			snprintf (str, 99, gettext ("You lose. What a pity."));
		wininfo->putline (str);
		sleep (GAME_END_DELAY);
		init_level ();
	}
	wininfo->putline (gettext ("Press 'p' to play, or press 'q' to quit"));
	game_mode = MODE_END;
	wtimeout (playground, -1);
}

void game_end ()
{
	while(true) {
		switch (wgetch (playground)) {
		case 'p':
			enter_play();
			return;
		case 'q':
			game_mode = MODE_QUIT;
			return;
		default:
			wininfo->putline (gettext ("Invalid input"));
			wininfo->putline (gettext ("Press 'p' to play, or press 'q' to quit"));
			break;
		}
	}
}
