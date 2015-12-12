#ifndef _SNAKE_H
#define _SNAKE_H

#include "map.h"
#include "point.h"

#include <deque>

class snake {
	std::deque<point> body;
public:
	int increase;
	int direction;
	snake (point p) { body.push_back (p); increase = 0; DIRECTION = RIGHT; }
	snake (int x, int y) { body.push_back (point (x, y)); increase = 0; direction = RIGHT; }
	static snake *init_snake ();
	bool step ();

	const int UP = 0;
	const int DOWN = 1;
	const int RIGHT = 2;
	const int LEFT = 3;
};

#endif
