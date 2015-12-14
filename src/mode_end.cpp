#include "mode_end.h"
#include "game.h"
#include "mode_play.h"

#include <curses.h>
#include <unistd.h>
#include "tsgettext.h"
#include "global_var.h"

#include "const.h"

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
	wininfo->putline (gettext ("Press 'p' to play, 'r' to refresh map"));
	wininfo->putline (gettext ("or press 'q' to quit"));
	game_mode = MODE_END;
	wtimeout (playground, -1);
}

void game_end ()
{
	while(true) {
		switch (wgetch (playground)) {
		case 'p':
			enter_play ();
			return;
		case 'q':
			game_mode = MODE_QUIT;
			return;
		case 'r':
			init_level ();
			return;
		default:
			break;
		}
	}
}
