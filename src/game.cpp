#include <iostream>
#include <curses.h>
#include <unistd.h>

#include "split.h"

void splash ()
{
	wininfo->putline ("Tsnake Version 0.0.0");
	wininfo->putline ("To read the handbook");
	wininfo->putline ("please use --help");
}

void game_main ()
{
	init_split ();
	splash ();
	sleep (5);
}
