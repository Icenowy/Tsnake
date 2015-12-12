#include "map.h"
#include "matrix.h"
#include "global_var.h"

matrix<map_tile> *pmap;

void init_map ()
{
	pmap = new matrix<map_tile> (pglines, pgrows);
}

void randomize_map ()
{
	// TODO: find a good map generating algorithm
	// I cannot design one
	for (int i = 0; i < pglines-2; i++) {
		map() (i, pgrows/2) = map_tile (map_tile::WALL);
	}
}
