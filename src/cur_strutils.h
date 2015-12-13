#ifndef _CUR_STRUTILS_H
#define _CUR_STRUTILS_H

#include <curses.h>
#include <deque>
#include <vector>
#include <string>

// What's the difference of cur_strwin and cur_strbuf?
// cur_strwin is like a terminal, it can scroll; 
// However, cur_strbuf cannot scroll, but all it's
// lines are controllable.

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

class cur_strbuf {
	WINDOW *win;

public:
	std::vector<std::string> buffer;
	
	void refresh_buffer ();

	cur_strbuf (WINDOW *w) : win (w) {}
};

#endif
