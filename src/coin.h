// Coin (header)
// (c) 2018 Jani Nykänen

#ifndef __COIN__
#define __COIN__

#include "engine/vector.h"

#include "player.h"

#include "stdbool.h"

// Coin type
typedef struct {

    VEC2 pos;
    bool exist;
    bool die;
}
COIN;

// Initialize coins
void coin_init();

// Create a coin
void coin_create(COIN* c, VEC2 pos);

// Pre-draw a coint
void coin_pre_draw(COIN* c);

// Coin-player collision
void coin_player_collision(PLAYER* pl, COIN* c);

// Draw a coin
void coin_draw(COIN* c);

// Destroy coin data
void coin_destroy();

#endif // __COIN__
