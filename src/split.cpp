#include "split.h"
#include <curses.h>
#include <string>

#include "const.h"

void init_split ()
{
	WINDOW *pg_with_box = subwin (stdscr, pgrows+2, pglines+2, 0,0);
	playground = subwin (pg_with_box, pgrows, pglines, 1, 1);
	info = subwin (stdscr, INFO_ROWS, pglines, pgrows + 2, 0);
	WINDOW *goods_line = subwin (stdscr, pgrows + INFO_ROWS + 2, 1, 0, pglines+2);
	goods = subwin (stdscr, pgrows + INFO_ROWS + 2, GOODS_LINES, 0, pglines+3);

	wattron (pg_with_box, A_REVERSE);
	wborder (pg_with_box, 0, 0, 0, 0, 0, 0, 0, 0);
	wattroff (pg_with_box, A_REVERSE);
	mvwvline (goods_line, 0, 0, 0, pgrows + INFO_ROWS + 2);

	wininfo = new cur_strwin (info, INFO_ROWS);

	bufgoods = new cur_strbuf (goods);
	for (int i = 0; i<GOODS_FIXED_ROWS; i++)
		bufgoods->buffer.push_back (std::string (""));

	keypad (playground, true);
	refresh ();
}
