// Player (header)
// (c) 2018 Jani Nykänen

#include "player.h"

#include "engine/graph.h"
#include "engine/input.h"

#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpPlayer;

// Constants
static const short H_SPEED = 60;
static const short WALL_H_SPEED = 160;
static const short V_SPEED = 140;
static const short H_ACC = 6;
static const short V_ACC = 8;
static const short JUMP1 = 240;
static const short JUMP2 = 180;


// Control player
static void pl_control(PLAYER* pl) {

    VEC2 stick = input_get_stick();
    char fire;

    pl->target.x = 0;
    pl->target.y = V_SPEED;

    // If wall-sliding, reduce gravity
    if(pl->touchWall && pl->wallSlideTimer > 0) {

        pl->target.y = V_SPEED / 2;
    }

    // Horizontal movement
    if(stick.x > 0) {

        pl->target.x = H_SPEED;
    }
    else if(stick.x < 0) {

        pl->target.x = -H_SPEED;
    }

    // Jumping
    fire = input_get_button(BUTTON_FIRE);
    if(fire == PRESSED) {

        if(pl->canJump) {

            pl->speed.y = -JUMP1;

        }
        else if(pl->wallSlideTimer > 0) {

            pl->speed.x = (pl->dir == 0 ? 1 : -1) * WALL_H_SPEED;
            pl->speed.y = -JUMP1;
            pl->doubleJump = false;
            pl->wallSlideTimer = 0;
        }
        else if(!pl->doubleJump) {

            pl->speed.y = -JUMP2;
            pl->doubleJump = true;
        }
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

    pl_move_coord(pl, &pl->speed.x, &pl->target.x, H_ACC);
    pl_move_coord(pl, &pl->speed.y, &pl->target.y, V_ACC);
    pl->pos.x += pl->speed.x;
    pl->pos.y += pl->speed.y;

    // Set facing direction
    if(pl->target.x != 0 && pl->wallSlideTimer <= 0)
        pl->dir = pl->target.x >= 0;

    // Update wall slide timer
    if(pl->wallSlideTimer > 0) {

        -- pl->wallSlideTimer;
    }
}


// Animate
static void pl_animate(PLAYER* pl) {

    short speed;
    char frame;
    VEC2 stick = input_get_stick();

    // On air
    if(!pl->canJump) {


        // Wall sliding
        if(pl->touchWall && pl->wallSlideTimer > 0) {

            pl->spr.frame = 6;
            pl->spr.row = 1;
        }
        else {

            // Double jump
            if(pl->doubleJump && pl->speed.y < 0) {

                spr_animate(&pl->spr, 1, 2,5, 4);
            }
            // Normal jump
            else {

                frame = pl->speed.y < 0 ? 0 : 1;
                pl->spr.frame = frame;
                pl->spr.row = 1;
            }

        }

        return;
    }

    // Not on air
    if(pl->speed.x == 0 && stick.x == 0) {

        pl->spr.frame = 0;
        pl->spr.row = 0;
    }
    else {


        speed = 8 - abs(pl->speed.x/40)*2;
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
    pl.doubleJump = false;
    pl.touchWall = false;
    pl.wallSlideTimer = 0;

    return pl;

}


// Update a player
void pl_update(PLAYER* pl) {

    pl_control(pl);
    pl_move(pl);
    pl_animate(pl);

    pl->canJump = false;
    pl->touchWall = false;

}


// Pre-draw a player
void pl_pre_draw(PLAYER* pl) {
    
    short px = pl->pos.x / 100;
    short py = pl->pos.y / 100;

    fill_rect(px-8,py-16,16,16, 0);
}


// Draw a player
void pl_draw(PLAYER* pl) {

    short x = pl->pos.x / 100;
    short y = pl->pos.y / 100;

    spr_draw(&pl->spr,bmpPlayer, x-8,y-16, pl->dir ? FLIP_NONE : FLIP_H);
}


// Floor collision
void pl_floor_collision(PLAYER* pl, short x, short y, short w) {

    short px = pl->pos.x / 100;
    short py = pl->pos.y / 100;

    if(px+8 > x && px-8 < x+w && pl->speed.y > 0 && py > y-2 && py < y + 8) {

        pl->speed.y = 0;
        pl->pos.y = y * 100;

        pl->canJump = true;
        pl->doubleJump = false;
    }
}


// Ceiling collision
void pl_ceiling_collision(PLAYER* pl, short x, short y, short w) {

    short px = pl->pos.x / 100;
    short py = pl->pos.y / 100 -16;

    if(px+8 > x && px-8 < x+w && pl->speed.y < 0 && py < y+2 && py > y - 8) {

        pl->speed.y = 0;
        pl->pos.y = (y+16) * 100;
    }
}


// Wall collision
void pl_wall_collision(PLAYER* pl, short x, short y, short h, bool dir) {

    short px = pl->pos.x / 100;
    short py = pl->pos.y / 100;
    bool collided = false;
    VEC2 stick = input_get_stick();

    if(py > y && py-16 < y+h ) {

        if(dir) {

            if(px+8 >= x && px+8 < x+8 && pl->speed.x > 0) {

                pl->pos.x = (x-8) * 100;
                pl->speed.x = 0;
                collided = true;
            }
        }
        else {

            if(px-8 <= x && px-8 > x-8 && pl->speed.x < 0) {

                pl->pos.x = (x+8) * 100;
                pl->speed.x = 0;
                collided = true;
            }
        }
    }

    if(collided ) {

        pl->touchWall = true;

        if(pl->speed.y > 0.0 && !pl->canJump
        && ( (dir && stick.x > 0) || (!dir && stick.x < 0) ))
            pl->wallSlideTimer = 16;
        
        else
            pl->wallSlideTimer = 0;
    }
}


// Stage collision
void pl_stage_collision(PLAYER* pl, char* data, short w, short h) {

    short px = (pl->pos.x / 100) / 16;
    short py = (pl->pos.y / 100) / 16;

    short sx = px-2;
    short sy = py-2;
    short ex = px+2;
    short ey = py+2;

    short x,y;
    char tile;

    // Limit
    if(sx < 0) sx = 0;
    if(sy < 0) sy = 0;
    if(ex >= w-1) ex = w-1;
    if(ey >= h-1) ey = h-1;

    // Go through nearby tiles & get collisions
    for(y=sy; y <= ey; ++ y) {

        for(x=sx; x <= ex; ++ x) {

            tile = data[y * w + x];
            if(tile == 0)
                continue;

            pl_floor_collision(pl, x*16, y*16 +8, 16);
            pl_wall_collision(pl, x*16, y*16 +8, 16, true);
            pl_wall_collision(pl, x*16 +16, y*16 +8, 16, false);
            pl_ceiling_collision(pl, x*16, y*16 +16 +8, 16);
        }
    }
}