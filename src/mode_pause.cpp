#include "mode_pause.h"
#include "game.h"
#include "mode_play.h"

#include <curses.h>
#include "global_var.h"


void enter_pause ()
{
	wininfo->putline (gettext ("PAUSED. Press any key to continue."));
	game_mode = MODE_PAUSE;
	wtimeout (playground, -1);
}

void game_pause ()
{
	wgetch (playground);
	enter_play ();
}
