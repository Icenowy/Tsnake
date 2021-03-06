#include <curses.h>
#include <cstdlib>
#include <clocale>
#include <iostream>
#include <cstring>
#include <ctime>
#include <signal.h>
#include "tsgettext.h"

#include "game.h"
#include "global_var.h"
#include "handbook.h"

#include "const.h"

static void init_environment ()
{
	pgrows = DEFAULT_ROWS;
	pglines = DEFAULT_LINES;
	level = 1;
	const char *str_tslines = ::getenv ("TSNAKE_LINES");
	const char *str_tsrows = ::getenv ("TSNAKE_ROWS");
	const char *str_level = ::getenv ("TSNAKE_LEVEL");

	if (str_tslines != NULL) {
		int tslines = atoi (str_tslines);
		if (tslines > 0) {
			pglines = tslines;
			if (pglines < MIN_LINES) pglines = MIN_LINES;
		}
	}
	if (str_tsrows != NULL) {
		int tsrows = atoi (str_tsrows);
		if (tsrows > 0) {
			pgrows = tsrows;
			if (pgrows < MIN_ROWS) pgrows = MIN_ROWS;
		}
	}
	if (str_level != NULL) {
		int lvl = atoi (str_level);
		if (lvl > 0) {
			level = lvl;
		}
	}

	std::setlocale (LC_ALL, "");
	bindtextdomain ("tsnake", LOCALEDIR);
	textdomain ("tsnake");

	std::srand (std::time (NULL));
}

static void init_screen ()
{
	::initscr (); // initialize the screen

	int lines, rows;
	getmaxyx (stdscr, rows, lines);

	if (rows < (pgrows + EXTRA_ROWS) || lines < (pglines + EXTRA_LINES)) {
		::endwin (); // atexit is not registered yet
		std::cerr << "Your terminal is to small to run this game.\n";
		std::cerr << "Required " << (pglines + EXTRA_LINES) << "Lines"
			<< " and " << (pgrows + EXTRA_ROWS) << "rows\n";
		std::exit (1);
	}

	if (!has_colors ()) {
		::endwin ();
		std::cerr << "Your terminal do not support color.\n";
		std::cerr << "Maybe your TERM environment variable is wrong "
			"or your terminal is too old for this game.\n";
		std::exit (1);
	}

	start_color ();

	if (COLOR_PAIRS < 16) {
		::endwin ();
		std::cerr << "Your terminal do not support enough colors.\n";
		std::cerr << "Maybe you should change to another terminal.\n";
		std::exit (1);
	}

	init_pair (1, COLOR_RED, COLOR_BLACK);
	init_pair (2, COLOR_YELLOW, COLOR_BLACK);

	::noecho();
	::cbreak();
	::curs_set(0);
}

static void finalize_screen ()
{
	::endwin (); // exit the curses mode. (Some modern terminals have two modes.)
}

static void sigwinch (int sig)
{
	// TODO: response SIGWINCH positively
	if (sig == SIGWINCH) {
		::endwin ();
		std::cerr << "Terminal size changed. Please restart the game.\n";
		::exit(1);
	}
}

int main (int argc, char **argv)
{
	init_environment ();
	if (argc > 1 && !strcmp(argv[1], "--help")) {
		show_handbook();
		return 0;
	}
	init_screen ();
	std::atexit (finalize_screen); // register an atexit procedure, to ensure the terminal is restored
	sigset (SIGWINCH, sigwinch);

	game_main();
	return 0;
}
