#include "snake.h"

#include <cstdlib>

#include "const.h"
#include "mod.h"

void snake::draw_body (point p)
{
	mvwaddch (map_win, p.y, p.x, CH_SNAKE_BODY);
	wrefresh (map_win);
}

void snake::draw_head ()
{
	switch (direction) {
	case UP:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_UP);
		break;
	case DOWN:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_DOWN);
		break;
	case LEFT:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_LEFT);
		break;
	case RIGHT:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_RIGHT);
		break;
	}
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
		for (point pt : body) {
			if (pt.x == nx && pt.y == ny)
				return DIE_KNOCK_SELF;
		}
	default:
		if ((map() (nx, ny).type >= map_tile::MOD_MIN &&
			map() (nx, ny).type <= map_tile::MOD_MAX) ||
			map() (nx, ny).type == map_tile::RESERVED ) {
			int tmp_val;
			if ( (tmp_val = mod_hit_mod_tile (nx, ny)) > 0) {
				return tmp_val;
			}
			else {
				ret = tmp_val;
				goto cont;
			}
		}
	}
	unknown:
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
