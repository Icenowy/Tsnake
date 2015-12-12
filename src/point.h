#ifndef _POINT_H
#define _POINT_H

struct point {
	int x,y;
	point () {}
	point (int xx, int yy) : x (xx), y (yy) {}
};

#endif
