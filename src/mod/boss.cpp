#include "mod_interface.h"

#include "../mode_play.h"
#include "../mode_end.h"

#define LENGTH_PER_LEVEL 4

class boss {
	void draw_head ();
	void draw_body (point p);
public:
	std::deque<point> body;
	int increase;
	int direction;
	boss (point p) {
		map() (p.x, p.y).reserve ();
		body.push_back (p);
		increase = 0;
		direction = snake::RIGHT;
		draw_head ();
	}
	boss (int x, int y) {
		map() (x, y).reserve ();
		body.push_back (point (x, y));
		increase = 0;
		direction = snake::RIGHT;
		draw_head ();
	}
	static boss *init_boss ();
	int step ();
};

void boss::draw_body (point p)
{
	mvwaddch (map_win, p.y, p.x, CH_SNAKE_BODY | A_REVERSE);
	wrefresh (map_win);
}

void boss::draw_head ()
{
	switch (direction) {
	case snake::UP:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_UP | A_REVERSE);
		break;
	case snake::DOWN:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_DOWN | A_REVERSE);
		break;
	case snake::LEFT:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_LEFT | A_REVERSE);
		break;
	case snake::RIGHT:
		mvwaddch (map_win, body.front ().y, body.front ().x, CH_SNAKE_HEAD_RIGHT | A_REVERSE);
		break;
	}
	wrefresh (map_win);
}

boss *boss::init_boss ()
{
	int x, y;
	do {
		x = std::rand () % map_width;
		y = std::rand () % map_height;
	} while ( map() (x, y).type != map_tile::GROUND);

	boss *tmp = new boss (x,y);
	tmp->increase = (level * LENGTH_PER_LEVEL) - 1;
	tmp->direction = snake::RIGHT;

	return tmp;	
}

int boss::step ()
{
	int nx, ny;
	nx = body.front ().x;
	ny = body.front ().y;
	int ret = snake::ALIVE;
	switch (direction) {
	case snake::UP:
		ny--;
		break;
	case snake::DOWN:
		ny++;
		break;
	case snake::RIGHT:
		nx++;
		break;
	case snake::LEFT:
		nx--;
		break;
	}
	if (ny < 0 || ny >= map_height || nx < 0 || nx >= map_width) {
		nx = (nx + map_width) % map_width;
		ny = (ny + map_height) % map_height;
	}
	if (map() (nx, ny).type == map_tile::RESERVED) {
		for (point pt : sn->body) {
			if (pt.x == nx && pt.y == ny) {
				wininfo->putline ("You got knocked by the boss!");
				return snake::DIE_MOD;
			}
		}
	}
	else map() (nx, ny).reserve ();
	draw_body (body.front ());
	body.push_front (point (nx,ny));
	draw_head ();
	if (increase) increase--;
	else {
		point bk = body.back ();
		body.pop_back ();
		bool noderes = false;
		for (point pt : body) {
			if (pt.x == bk.x && pt.y == bk.y) noderes = true;
		}
		if (!noderes) map() (bk.x, bk.y).dereserve ();
		invalid_map_tile (bk.x, bk.y);
	}
	return ret;
}

chtype tsnake_mod_get_tile_char (const map_tile *tile)
{
	if (tile->type == map_tile::MOD_MIN) return CH_FOOD; // Pretend to be food
	return CH_UNDEFINED;
}

// Override food generation with a null function in order to disable the original food
void tsnake_mod_food_gen ()
{
}

static boss *bs;

static int tmcnt;

void tsnake_mod_int_timer ()
{
	tmcnt++;
	if (tmcnt > calculate_speed ()) {
		tmcnt = 0;
		if (! (std::rand() % 4)) {
			int newdir = std::rand() % 4;
			if ( (newdir == snake::RIGHT && bs->direction == snake::LEFT) ||
				(newdir == snake::LEFT && bs->direction == snake::RIGHT) ||
				(newdir == snake::UP && bs->direction == snake::DOWN) ||
				(newdir == snake::DOWN && bs->direction == snake::UP) ) {
			}
			else
				bs->direction = newdir;
		}
		int res = bs->step ();
		if (res == snake::DIE_MOD) {
			level++;
			enter_end (true);
			mode_play_force_exit = true;
		}
	}
}

static void generate_pseudo_food ()
{
	int x,y;
	do {
		x = std::rand () % map_width;
		y = std::rand () % map_height;
	} while ( map() (x, y).type != map_tile::GROUND);
	map() (x, y).type = map_tile::MOD_MIN;
	invalid_map_tile (x, y);
}

void tsnake_mod_init_level ()
{
	bs = boss::init_boss ();
	generate_pseudo_food ();
	sn->allow_cross_edge = true;
	wininfo->putline ("BOSS mode. Inspired and designed by");
	wininfo->putline ("Shangguan Lingyun");
}

int tsnake_mod_hit_mod_tile (int nx, int ny)
{
	if (map() (nx, ny).type == map_tile::RESERVED) {
		// Boss got hit
		wininfo->putline ("Do you think you're harder than boss?");
		return snake::DIE_MOD;
	}
	else {
		generate_pseudo_food ();
		map() (nx, ny).type = map_tile::GROUND;
		scores += 100 / LENGTH_PER_LEVEL;
		if (bs->increase) bs->increase--;
		else if (bs->body.size() > 1) {
			point bk = bs->body.back ();
			bs->body.pop_back ();
			bool noderes = false;
			for (point pt : bs->body) {
				if (pt.x == bk.x && pt.y == bk.y) noderes = true;
			}
			if (!noderes) map() (bk.x, bk.y).dereserve ();
			invalid_map_tile (bk.x, bk.y);
		}
		sn->increase++;
		return snake::ALIVE;
	}
}
