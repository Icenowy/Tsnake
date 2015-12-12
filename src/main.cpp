#include <curses.h>
#include <cstdlib>
#include <clocale>
#include <iostream>
#include <cstring>
#include <signal.h>

#include "game.h"
#include "global_var.h"
#include "handbook.h"

#define MIN_ROWS 10
#define MIN_LINES 30

#define EXTRA_ROWS 4
#define EXTRA_LINES 30

#define DEFAULT_ROWS 18
#define DEFAULT_LINES 48

static void init_environment ()
{
	pgrows = DEFAULT_ROWS;
	pglines = DEFAULT_LINES;
	const char *str_tslines = ::getenv ("TSNAKE_LINES");
	const char *str_tsrows = ::getenv ("TSNAKE_ROWS");

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
}

static void init_screen ()
{
	std::setlocale (LC_ALL, "");
	::initscr (); // initialize the screen

	int lines, rows;
	getmaxyx (stdscr, rows, lines);

	if (rows < (pgrows + EXTRA_ROWS) || lines < (pglines + EXTRA_LINES)) {
		std::cerr << "Your terminal is to small to run this game.\n";
		std::cerr << "Required " << (pglines + EXTRA_LINES) << "Lines"
			<< " and " << (pgrows + EXTRA_ROWS) << "rows\n";
		::endwin (); // atexit is not registered yet
		std::exit (1);
	}

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
