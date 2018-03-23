// Player (header)
// (c) 2018 Jani Nykänen

#include "player.h"

#include "engine/graph.h"
#include "engine/input.h"

#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpPlayer;


// Control player
static void pl_control(PLAYER* pl) {

    VEC2 stick = input_get_stick();

    pl->target.x = 0;
    pl->target.y = 0;

    if(stick.x > 0) {

        pl->target.x = 2 *150;
    }
    else if(stick.x < 0) {

        pl->target.x = -2 *150;
    }
}


// Coordinate movement
static void pl_move_coord(PLAYER* pl, short* coord,  short* target, short speed)
{
    if(*target > *coord)
    {
        *coord += speed ;
        if(*coord >= *target)
        {
            *coord = *target;
        }
    }
    else if(*target < *coord)
    {
        *coord -= speed ;
        if(*coord  <= *target)
        {
            *coord = *target;
        }
    }
}



// Move player
static void pl_move(PLAYER* pl) {

    // Calculate old position
    pl->oldPos = vec2(pl->pos.x/100, pl->pos.y/100);

    pl_move_coord(pl, &pl->speed.x, &pl->target.x, 20);
    pl->pos.x += pl->speed.x;

    // Set facing direction
    if(pl->target.x != 0)
        pl->dir = pl->target.x >= 0;
}


// Animate
static void pl_animate(PLAYER* pl) {

    short speed;
    VEC2 stick = input_get_stick();
    pl->hasMoved = true;

    if(pl->speed.x == 0 && stick.x == 0) {

        pl->spr.frame = 0;
        pl->spr.row = 0;

        if(pl->lastFrame == pl->spr.frame)
            pl->hasMoved = false;
    }
    else {

        speed = 4 - abs(pl->speed.x/100);
        spr_animate(&pl->spr,0, 1,6, (char)speed);
    }

    pl->lastFrame = pl->spr.frame;
}


// Initialize global player components
void pl_init() {

    // Load assets
    bmpPlayer = load_bitmap("ASSETS/BITMAPS/PLAYER.BIN");
}


// Create a player
PLAYER pl_create(VEC2 p) {

    PLAYER pl;
    pl.pos = vec2(p.x * 100, p.y * 100);
    pl.speed = vec2(0,0);
    pl.target = pl.speed;

    pl.spr = create_sprite(16, 16);

    pl.hasMoved = false;
    pl.dir = true;

    return pl;

}


// Update a player
void pl_update(PLAYER* pl) {

    pl_control(pl);
    pl_move(pl);
    pl_animate(pl);
}


// Pre-draw a player
void pl_pre_draw(PLAYER* pl) {
    

}


// Draw a player
void pl_draw(PLAYER* pl) {

    int x = pl->pos.x / 100;
    int y = pl->pos.y / 100;

    if(pl->hasMoved) {

        fill_rect(pl->oldPos.x-8,pl->oldPos.y-16,16,16, 0);
        spr_draw(&pl->spr,bmpPlayer, x-8,y-16, pl->dir ? FLIP_NONE : FLIP_H);
    }
}
