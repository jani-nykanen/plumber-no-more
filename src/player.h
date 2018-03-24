// Player (header)
// (c) 2018 Jani Nykänen

#ifndef __PLAYER__
#define __PLAYER__

#include "engine/vector.h"
#include "engine/sprite.h"

#include "stdbool.h"

// Player type
typedef struct {

    VEC2 pos;
    VEC2 oldPos;
    VEC2 speed;
    VEC2 target;

    SPRITE spr;
    char lastFrame;
    
    bool dir;
    bool canJump;

}
PLAYER;

// Initialize global player components
void pl_init();

// Create a player
PLAYER pl_create(VEC2 p);

// Update a player
void pl_update(PLAYER* pl);

// Pre-draw a player
void pl_pre_draw(PLAYER* pl);

// Draw a player
void pl_draw(PLAYER* pl);

// Floor collision
void pl_floor_collision(PLAYER* pl, short x, short y, short w);

#endif // __PLAYER__
