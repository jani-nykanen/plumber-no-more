// Info (header)
// (c) 2018 Jani Nykänen

#ifndef __INFO__
#define __INFO__

#include "engine/bitmap.h"

#include "stdbool.h"

// Initialize info
void info_init();

// Update info
void info_update();

// Draw non-changing info material
void info_draw_static();

// Draw changing info material
void info_draw();

// Reduce a life 
char info_reduce_life();

// Add a coin
void info_add_coin();

// Get font (so we don't have to load it multiple times)
BITMAP* info_get_font();

// Reset info
void info_reset();

// Is the game over
bool info_game_over();

// Get time (no the remaining, but the total time spent)
unsigned short info_get_time();

#endif // __INFO__
