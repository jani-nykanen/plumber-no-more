// Game scene (header)
// (c) 2018 Jani Nykänen

#ifndef __GAME__
#define __GAME__

#include "engine/vector.h"

// Initialize
void game_init();

// Redraw the game
void game_redraw();

// Add a coin
void game_add_coin(VEC2 pos);

// Reset game
void game_reset();

// Start game scene
void start_game_scene();

#endif // __GAME__
