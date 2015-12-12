#include "cur_strutils.h"

#include <curses.h>
#include <string>

void cur_strwin::refresh_buffer ()
{
	int y,x;
	getmaxyx (win, y, x);
	werase (win);
	int startpos = buffer.size() - y;
	if (startpos < 0) startpos = 0;
	for (int i = 0, j = startpos;i < y;i++,j++)
	{
		if (j < buffer.size ())
			mvwaddnstr (win, i, 0, buffer.at (j).c_str (), x);
	}
	wrefresh (win);
}

void cur_strwin::putline (std::string s)
{
	buffer.push_back (s);
	if (buffer.size () > max_bufsize) buffer.pop_front ();
	refresh_buffer ();
}
