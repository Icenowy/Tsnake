#include <iostream>
#include <curses.h>
#include <unistd.h>
#include "tsgettext.h"

#include "split.h"
#include "map.h"
#include "snake.h"

static snake *sn;

void splash ()
{
	wininfo->putline (gettext ("***Tsnake Version 0.0.0***"));
	wininfo->putline (gettext ("To read the handbook, please use --help option"));
}

void game_main ()
{
	init_split ();
	splash ();
	init_map ();
	randomize_map ();
	generate_food ();
	sn = snake::init_snake ();
	for (int i = 0; i<10; i++) {
		sleep (1);
		sn->step();
	}
}
