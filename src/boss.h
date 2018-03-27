// "Boss" (header)
// (c) 2018 Jani Nykänen

#ifndef __BOSS__
#define __BOSS__

#include "player.h"

#include "engine/vector.h"
#include "engine/sprite.h"

#include "stdbool.h"

// Boss type
typedef struct {

    VEC2 pos;
    VEC2 speed;
    VEC2 target;
    short jmpHeight;
    SPRITE spr;
    
    bool exist;
    bool wait;
}
BOSS;

// Initialize boss
void boss_init();

// Create an boss
void boss_create(BOSS* e, VEC2 pos);

// Update an boss
void boss_update(BOSS* e, PLAYER* pl);

// Pre-draw an boss
void boss_pre_draw(BOSS* e);

// Draw an boss
void boss_draw(BOSS* e);

#endif // __BOSS__
