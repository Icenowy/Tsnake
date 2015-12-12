#include "snake.h"

#include <cstdlib>

#define INITIAL_INCREASE 3

#define CH_SNAKE_HEAD '@'
#define CH_SNAKE_BODY '.'

void snake::draw_body (point p)
{
	mvwaddch (map_win, p.y, p.x, CH_SNAKE_BODY);
	wrefresh (map_win);
}

void snake::draw_head ()
{
	mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD);
	wrefresh (map_win);
}

snake *snake::init_snake ()
{
	int x, y;
	do {
		x = std::rand () % map_width;
		y = std::rand () % map_height;
	} while ( map() (x, y).type != map_tile::GROUND);

	snake *tmp = new snake (x,y);
	tmp->increase = INITIAL_INCREASE;
	tmp->direction = RIGHT;

	return tmp;	
}

int snake::step ()
{
	int nx, ny;
	nx = body.front ().x;
	ny = body.front ().y;
	int ret = ALIVE;
	switch (direction) {
	case UP:
		ny--;
		break;
	case DOWN:
		ny++;
		break;
	case RIGHT:
		nx++;
		break;
	case LEFT:
		nx--;
		break;
	}
	if (ny < 0 || ny >= map_height || nx < 0 || nx >= map_width) {
		if (!allow_cross_edge) return DIE_CROSS_EDGE;
		else {
			nx = (nx + map_width) % map_width;
			ny = (ny + map_height) % map_height;
		}
	}
	switch (map() (nx, ny).type) {
	case map_tile::GROUND:
		goto cont;
	case map_tile::WALL:
		return DIE_KNOCK_WALL;
	case map_tile::FOOD:
		map() (nx, ny).type = map_tile::GROUND;
		ret = FOOD_FOUND;
		goto cont;
	case map_tile::RESERVED:
		// TODO: Do not assume it's a snake section
		return DIE_KNOCK_SELF;
	}
	return DIE_UNKNOWN;
	cont:
	map() (nx, ny).reserve ();
	draw_body (body.front ());
	body.push_front (point (nx,ny));
	draw_head ();
	if (increase) increase--;
	else {
		point bk = body.back ();
		map() (bk.x, bk.y).dereserve ();
		invalid_map_tile (bk.x, bk.y);
		body.pop_back ();
	}
	return ret;
}
