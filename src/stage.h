// Stage (header)
// (c) 2018 Jani Nykänen

#ifndef __STAGE__
#define __STAGE__

#include "player.h"

#include "stdbool.h"

// Initialize stage
void stage_init();

// Load stage
void stage_load(unsigned short index, bool redraw);

// Load next stage
void stage_load_next();

// Draw stage
void stage_draw();

// Stage-to-player collisions
void stage_player_collision(PLAYER* pl);

// Get stage data
char* stage_get_data(short* w, short *h);

// Draw the stage "by parts"
void stage_draw_by_parts();

// Is the stage the final stage
bool stage_is_final();

#endif // __STAGE__
