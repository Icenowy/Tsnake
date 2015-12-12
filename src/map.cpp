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
	
}
