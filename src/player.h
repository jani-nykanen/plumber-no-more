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
    VEC2 startPos;
    VEC2 oldPos;
    VEC2 speed;
    VEC2 target;

    SPRITE spr;
    char lastFrame;
    
    bool dir;
    bool canJump;
    bool doubleJump;
    bool victorious;
    short wallSlideTimer;
    bool touchWall;
    bool wallDir;
    bool respawning;
    bool dying;

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

// Kill the player
void pl_kill(PLAYER* pl);

// Floor collision
void pl_floor_collision(PLAYER* pl, short x, short y, short w, bool fatal);

// Ceiling collision
void pl_ceiling_collision(PLAYER* pl, short x, short y, short w, bool fatal);

// Wall collision
void pl_wall_collision(PLAYER* pl, short x, short y, short h, bool dir, bool fatal);

// Stage collision
void pl_stage_collision(PLAYER* pl, char* data, short w, short h);

// Destroy player data
void player_destroy();

#endif // __PLAYER__
