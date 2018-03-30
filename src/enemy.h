// Enemy (header)
// (c) 2018 Jani Nykänen

#ifndef __ENEMY__
#define __ENEMY__

#include "player.h"

#include "engine/vector.h"
#include "engine/sprite.h"

#include "stdbool.h"

// Enemy type
typedef struct {

    VEC2 pos;
    VEC2 plPos;
    VEC2 startPos;
    VEC2 speed;
    VEC2 target;
    char type;
    SPRITE spr;
    short spcTimer;
    short acc;

    bool canJump;
    bool exist;
    bool dir;
}
ENEMY;

// Initialize enemies
void enemy_init();

// Create an enemy
void enemy_create(ENEMY* e, VEC2 pos, char type);

// Update an enemy
void enemy_update(ENEMY* e);

// Pre-draw an enemy
void enemy_pre_draw(ENEMY* e);

// Draw an enemy
void enemy_draw(ENEMY* e);

// Enemy-player collision
void enemy_player_collision(ENEMY* e, PLAYER* p);

// Destroy enemy data
void enemy_destroy();

#endif // __ENEMY__
