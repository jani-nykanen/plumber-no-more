// Enemy (source)
// (c) 2018 Jani Nykänen

#include "enemy.h"

#include "stage.h"

#include "engine/graph.h"

#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpEnemies;


// Move horizontal
static void move_horizontal(ENEMY* e, short speed, bool ground) {

    short w,h;
    short ex = (e->pos.x/100 -8) / 16;
    short ey = (e->pos.y/100 - 16) / 16 +1;
    char tile1, tile2;
    char* data = stage_get_data(&w,&h);

    // Get the left tile, if moving that way
    if(e->dir == false) {

        tile1 = data[ey * w + (ex)];
        if(ground) {

            tile2 = data[(ey+1) * w + (ex)];
        }
    }
    // Otherwise get the right tile
    else {

        tile1 = data[ey * w + (ex+1)];
        if(ground) {

            tile2 = data[(ey+1) * w + (ex+1)];
        }
    }

    // If collision, change dir
    if( (tile1 > 0 && tile1 < 97) || (ground && tile2 == 0) ) {

        e->dir = !e->dir;
        e->speed.x = 0;
    }

    e->target.x = speed* (e->dir ? 1 : -1);
    e->target.y = 0;
}


// Move vertical
static void move_vertical(ENEMY* e, short speed) {

    short w,h;
    short ex = (e->pos.x/100 -8) / 16;
    short ey = (e->pos.y/100 - 8) / 16;
    char tile;
    char* data = stage_get_data(&w,&h);

    // Get the left tile, if moving that way
    if(e->dir == false) {

        tile = data[(ey) * w + (ex)];
    }
    // Otherwise get the right tile
    else {

        tile = data[ (ey+1) * w + (ex)];
    }

    // If collision, change dir
    if(tile > 0 && tile < 97){

        e->dir = !e->dir;
        e->speed.y = 0;
    }

    e->target.y = speed* (e->dir ? 1 : -1);
    e->target.x = 0;

}


// Jump behavior
static void jump(ENEMY* e) {

    const short JUMP_TIME = 60;

    e->speed.x = 0;
    e->target.x = 0;

    if(e->canJump) {

        e->target.y = 0;
        e->speed.y = 0;
        
        if(++ e->spcTimer >= JUMP_TIME) {
            
            e->speed.y = -200;
            e->spcTimer = 0;
            e->canJump = false;
        }
    }
    else {

        e->target.y = 140;
        if(e->pos.y >= e->startPos.y) {

            e->pos.y = e->startPos.y;
            e->canJump = true;
            e->speed.y = 0;
            e->target.y = 0;
        }
    }
}


// Move axis
static void enemy_move_axis( short* coord,  short* target, short speed) {
    if(*target > *coord) {

        *coord += speed ;
        if(*coord >= *target) {

            *coord = *target;
        }
    }
    else if(*target < *coord) {

        *coord -= speed ;
        if(*coord  <= *target) {

            *coord = *target;
        }
    }
}


// Move an enemy
static void enemy_move(ENEMY* e) {

    const short ACC = 6;

    enemy_move_axis( &e->speed.x, &e->target.x, ACC);
    enemy_move_axis( &e->speed.y, &e->target.y, ACC);
    e->pos.x += e->speed.x;
    e->pos.y += e->speed.y;

}


// Animate
static void enemy_animate(ENEMY* e) {

    if(e->type != 3) {

        spr_animate(&e->spr, e->type, 0,3, 6);
    }
    else {

        e->spr.row = e->type;

        if(e->canJump) {

            e->spr.frame = 0;
        }
        else {

            e->spr.frame = e->speed.y < 0 ? 1 : 2;
        }
    }
}


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
    e->startPos = e->pos;
    e->type = type;
    e->spr.row = type;
    e->spr.frame = 0;
    e->speed = vec2(0,0);
    e->target = vec2(0,0);
    e->spcTimer = 0;

    e->dir = false;
    e->exist = true;
    e->canJump = true;
}


// Update an enemy
void enemy_update(ENEMY* e) {

    if(!e->exist) return;

    // Type-specific behavior
    switch(e->type) {

        case 0:
        case 1:

            move_horizontal(e, e->type == 0 ? 50 : 40, e->type == 0);
            break;

        case 2:

            move_vertical(e,40);
            break;

        case 3:

            jump(e);
            break;

        default:
            break;
    }

    // Move
    enemy_move(e);

    // Animate
    enemy_animate(e);
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
    short sprf = e->spr.frame;

    if(!e->exist) return;

    ex = e->pos.x / 100;
    ey = e->pos.y / 100;

    if(e->dir) {

        e->spr.frame += 4;
    }

    spr_draw(&e->spr, bmpEnemies, ex-8,ey-16, 0);

    if(e->dir) {

        e->spr.frame = sprf;
    }
}
