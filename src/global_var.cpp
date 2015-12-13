#include "global_var.h"
#include <curses.h>
#include "cur_strutils.h"

WINDOW *playground, *goods, *info;

int pglines, pgrows;

cur_strwin *wininfo;
cur_strbuf *bufgoods;

int level;
