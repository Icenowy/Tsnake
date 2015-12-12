#include <iostream>
#include <curses.h>
#include <unistd.h>
#include "tsgettext.h"

#include "split.h"

void splash ()
{
	wininfo->putline (gettext ("***Tsnake Version 0.0.0***"));
	wininfo->putline (gettext ("To read the handbook, please use --help"));
}

void game_main ()
{
	init_split ();
	splash ();
	sleep (5);
}
