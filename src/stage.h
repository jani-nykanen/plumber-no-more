// Stage (header)
// (c) 2018 Jani Nykänen

#ifndef __STAGE__
#define __STAGE__

#include "player.h"

// Initialize stage
void stage_init();

// Load stage
void stage_load(const char* path);

// Draw stage
void stage_draw();

// Stage-to-player collisions
void stage_player_collision(PLAYER* pl);

#endif // __STAGE__
