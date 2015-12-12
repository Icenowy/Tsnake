#ifndef _CUR_STRUTILS_H
#define _CUR_STRUTILS_H

#include <curses.h>
#include <deque>
#include <string>

class cur_strwin {
	std::deque<std::string> buffer;
	WINDOW *win;

	void refresh_buffer ();
	int max_bufsize;

public:
	void putline (std::string s);
	void putline (const char *cs) { putline (std::string (cs)); }

	cur_strwin (WINDOW *w, int bsz = 100) : win (w), max_bufsize (bsz) {}

};

#endif
