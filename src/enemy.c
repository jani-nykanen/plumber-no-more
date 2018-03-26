// Enemy (source)
// (c) 2018 Jani Nykänen

#include "enemy.h"

#include "engine/graph.h"

#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpEnemies;


// Initialize enemies
void enemy_init() {

    // Load bitmaps
    bmpEnemies = load_bitmap("ASSETS/BITMAPS/ENEMIES.BIN");
}


// Create an enemy
void enemy_create(ENEMY* e, VEC2 pos, char type) {

    e->spr = create_sprite(16,16);
    e->pos = pos;
    e->pos.x *= 100;
    e->pos.y *= 100;
    e->type = type;
    e->spr.row = type;
    e->spr.frame = 0;
    e->speed = vec2(0,0);
    e->target = vec2(0,0);

    e->dir = false;
    e->exist = true;
}


// Update an enemy
void enemy_update(ENEMY* e) {

    if(!e->exist) return;

}


// Pre-draw an enemy
void enemy_pre_draw(ENEMY* e) {

    short ex, ey;

    if(!e->exist) return;

    ex = e->pos.x / 100;
    ey = e->pos.y / 100;

    fill_rect(ex-8,ey-16, 16, 16, 0);
}


// Draw
void enemy_draw(ENEMY* e) {
    
    short ex, ey;

    if(!e->exist) return;

    ex = e->pos.x / 100;
    ey = e->pos.y / 100;

    spr_draw(&e->spr, bmpEnemies, ex-8,ey-16, e->dir ? FLIP_H : FLIP_NONE);
}
