#include "split.h"
#include <curses.h>

#define INFO_ROWS 4
#define GOODS_LINES 30

void init_split ()
{
	playground = newwin (pgrows, pglines, 0, 0);
	info = newwin (INFO_ROWS, pglines, pgrows, 0);
	goods = newwin (pgrows + INFO_ROWS, GOODS_LINES, 0, pglines);
}
