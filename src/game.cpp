#include <iostream>
#include <curses.h>
#include <unistd.h>
#include "tsgettext.h"

#include "split.h"
#include "map.h"

void splash ()
{
	wininfo->putline (gettext ("***Tsnake Version 0.0.0***"));
	wininfo->putline (gettext ("To read the handbook, please use --help"));
}

void game_main ()
{
	init_split ();
	splash ();
	init_map ();
	randomize_map ();
	invalid_map_rect (0, 0, pglines, pgrows);
	sleep (5);
}
