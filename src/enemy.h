// Enemy (header)
// (c) 2018 Jani Nykänen

#ifndef __ENEMY__
#define __ENEMY__

#include "engine/vector.h"
#include "engine/sprite.h"

#include "stdbool.h"

// Enemy type
typedef struct {

    VEC2 pos;
    VEC2 speed;
    VEC2 target;
    char type;
    SPRITE spr;

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

#endif // __ENEMY__
