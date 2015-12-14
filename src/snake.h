#ifndef _SNAKE_H
#define _SNAKE_H

#include "map.h"
#include "point.h"

#include <deque>

extern "C" int tsnake_mod_hit_mod_tile (int nx, int ny);

class snake {
	void draw_head ();
	void draw_body (point p);
public:
	std::deque<point> body;
	int increase;
	int direction;
	bool allow_cross_edge;
	snake (point p) {
		map() (p.x, p.y).reserve ();
		body.push_back (p);
		increase = 0;
		direction = RIGHT;
		allow_cross_edge = false;
		draw_head ();
	}
	snake (int x, int y) {
		map() (x, y).reserve ();
		body.push_back (point (x, y));
		increase = 0;
		direction = RIGHT;
		allow_cross_edge = false;
		draw_head ();
	}
	static snake *init_snake ();
	int step ();

	static const int UP = 0;
	static const int DOWN = 1;
	static const int RIGHT = 2;
	static const int LEFT = 3;

	// negative value means do not die
	// positive value means death
	static const int FOOD_FOUND = -1;
	static const int ALIVE = 0;
	static const int DIE_CROSS_EDGE = 1;
	static const int DIE_KNOCK_WALL = 2;
	static const int DIE_KNOCK_SELF = 3;
	static const int DIE_UNKNOWN = 255;

	friend int tsnake_mod_hit_mod_tile (int nx, int ny);
};

#endif
