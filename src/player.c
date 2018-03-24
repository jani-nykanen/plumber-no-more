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
    char fire;

    pl->target.x = 0;
    pl->target.y = 400;

    // Horizontal movement
    if(stick.x > 0) {

        pl->target.x = 3 *100;
    }
    else if(stick.x < 0) {

        pl->target.x = -3 *100;
    }

    // Jumping
    fire = input_get_button(BUTTON_FIRE);
    if(pl->canJump && fire == PRESSED) {

        pl->speed.y = -800;
    }
    else if(!pl->canJump && pl->speed.y < 0 && fire == RELEASED) {

        pl->speed.y *= 2;
        pl->speed.y /= 3;
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

    pl_move_coord(pl, &pl->speed.x, &pl->target.x, 40);
    pl_move_coord(pl, &pl->speed.y, &pl->target.y, 80);
    pl->pos.x += pl->speed.x;
    pl->pos.y += pl->speed.y;

    // Set facing direction
    if(pl->target.x != 0)
        pl->dir = pl->target.x >= 0;
}


// Animate
static void pl_animate(PLAYER* pl) {

    short speed;
    char frame;
    VEC2 stick = input_get_stick();

    // On air
    if(!pl->canJump) {

        frame = pl->speed.y < 0 ? 0 : 1;
        pl->spr.frame = frame;
        pl->spr.row = 1;

        return;
    }

    // Not on air
    if(pl->speed.x == 0 && stick.x == 0) {

        pl->spr.frame = 0;
        pl->spr.row = 0;
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
    pl.oldPos = pl.pos;
    pl.speed = vec2(0,0);
    pl.target = pl.speed;

    pl.spr = create_sprite(16, 16);

    pl.dir = true;
    pl.canJump = false;

    return pl;

}


// Update a player
void pl_update(PLAYER* pl) {

    pl_control(pl);
    pl_move(pl);
    pl_animate(pl);

    pl->canJump = false;
    pl_floor_collision(pl, 0, 8*16 +8, 320);
}


// Pre-draw a player
void pl_pre_draw(PLAYER* pl) {
    
    int px = pl->pos.x / 100;
    int py = pl->pos.y / 100;

    fill_rect(px-8,py-16,16,16, 0);
}


// Draw a player
void pl_draw(PLAYER* pl) {

    int x = pl->pos.x / 100;
    int y = pl->pos.y / 100;

    spr_draw(&pl->spr,bmpPlayer, x-8,y-16, pl->dir ? FLIP_NONE : FLIP_H);
}


// Floor collision
void pl_floor_collision(PLAYER* pl, short x, short y, short w) {

    int px = pl->pos.x / 100;
    int py = pl->pos.y / 100;

    if(px+8 >= x && px-8 <= x+w && pl->speed.y > 0 && py > y-2 && py < y + 8) {

        pl->speed.y = 0;
        pl->pos.y = y * 100;

        pl->canJump = true;
    }
}
