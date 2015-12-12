#include "split.h"
#include <curses.h>

#define INFO_ROWS 4
#define GOODS_LINES 30

void init_split ()
{
	WINDOW *pg_with_box = subwin (stdscr, pgrows+2, pglines+2, 0,0);
	playground = subwin (pg_with_box, pgrows, pglines, 1, 1);
	info = subwin (stdscr, INFO_ROWS, pglines, pgrows + 2, 0);
	goods = subwin (stdscr, pgrows + INFO_ROWS + 1, GOODS_LINES, 0, pglines + 2);

	wborder (pg_with_box, 0, 0, 0, 0, 0, 0, 0, 0);

	wininfo = new cur_strwin (info, INFO_ROWS);
	refresh ();
}
