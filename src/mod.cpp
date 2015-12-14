#include "mod.h"
#include <dlfcn.h>
#include "global_var.h"

#include "const.h"
#include "tsgettext.h"
#include "snake.h"

static bool has_mod;

static void *mod_so;

static chtype (*m_get_tile_char) (const map_tile *tile);
static void (*m_map_gen) ();
static void (*m_int_timer) ();
static void (*m_int_move) ();
static void (*m_init_level) ();
static int (*m_hit_mod_tile) (int nx, int ny);

void mod_init ()
{
	const char * modname = getenv ("TSNAKE_MOD");
	if (modname) {
		wininfo->putline (gettext ("You're trying to play a mod"));
		if ((mod_so = dlopen (modname, RTLD_NOW | RTLD_GLOBAL))) {
			has_mod = true;
		}
		else {
			has_mod = false;
			wininfo->putline (dlerror ());
		}
	}
	else has_mod = false;

	if (has_mod) {
		wininfo->putline (modname);
		m_get_tile_char = (chtype (*) (const map_tile *tile)) dlsym (mod_so, "tsnake_mod_get_tile_char");
		m_map_gen = (void (*) ()) dlsym (mod_so, "tsnake_mod_map_gen");
		m_int_timer = (void (*) ()) dlsym (mod_so, "tsnake_mod_int_timer");
		m_int_move = (void (*) ()) dlsym (mod_so, "tsnake_mod_int_move");
		m_init_level = (void (*) ()) dlsym (mod_so, "tsnake_mod_init_level");
		m_hit_mod_tile = (int (*) (int nx, int ny)) dlsym (mod_so, "tsnake_mod_hit_mod_tile");
	}	
}

chtype mod_get_tile_char (const map_tile &tile)
{
	if (m_get_tile_char == nullptr) return CH_UNDEFINED;
	return m_get_tile_char (&tile);
}

bool mod_has_map_gen ()
{
	return m_map_gen != nullptr;
}

void mod_map_gen ()
{
	if (m_map_gen != nullptr) m_map_gen ();
}

void mod_int_timer ()
{
	if (m_int_timer != nullptr) m_int_timer ();
}

void mod_int_move ()
{
	if (m_int_move != nullptr) m_int_move ();
}

void mod_init_level ()
{
	if (m_init_level != nullptr) m_init_level ();
}

int mod_hit_mod_tile (int nx, int ny)
{
	if (m_hit_mod_tile == nullptr) return snake::DIE_UNKNOWN;
	else return m_hit_mod_tile (nx, ny);
}
