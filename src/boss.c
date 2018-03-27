// "Boss" (header)
// (c) 2018 Jani Nykänen

#include "boss.h"

#include "engine/graph.h"

#include "stdlib.h"
#include "math.h"

// Bitmaps
static BITMAP* bmpRocket;

// Move axis
static void boss_move_axis( short* coord,  short* target, short speed) {

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


// Move
static void boss_move(BOSS* b, PLAYER* pl) {

    // Set target
    b->target.y = 140;
    b->target.x = 200 * (pl->pos.x < b->pos.x ? -1 : 1);

    // Update axes
    boss_move_axis(&b->speed.x, &b->target.x, 4);
    boss_move_axis(&b->speed.y, &b->target.y, 8);

    // Move position
    b->pos.x += b->speed.x;
    b->pos.y += b->speed.y;

    // Limit
    if(b->pos.x/100-16 < 48) {

        b->pos.x = 64 * 100;
        b->speed.x = abs(b->speed.x);
    }
    else if(b->pos.x/100+16 > 320-48) {

        b->pos.x = (320-64) * 100;
        b->speed.x = -abs(b->speed.x);
    }

    // Floor collision
    if(b->pos.y/100 >= 10*16-8 && b->speed.y > 0) {

        b->pos.y = 100*(10*16-8);
        b->speed.y = -(200 + (b->jmpHeight % 4) * 50);

        b->jmpHeight += 7;
    }
}


// Boss-player collision
static void boss_player_collision(BOSS* b, PLAYER* pl) {

    short w = 12;
    short h = 28;

    short px = pl->pos.x / 100;
    short py = pl->pos.y / 100;

    short ex = b->pos.x / 100;
    short ey = b->pos.y / 100;
    
    if(px+8 > ex-w && px-8 < ex+w && py > ey-h && py-16 < ey-(16-h)) {

        pl_kill(pl);
    }
}


// Initialize boss
void boss_init() {

    // Load bitmaps
    bmpRocket = load_bitmap("ASSETS/BITMAPS/ROCKET.BIN");
}


// Create an boss
void boss_create(BOSS* b, VEC2 pos) {

    b->pos = pos;
    b->pos.x *= 100;
    b->pos.y *= 100;
    b->speed = vec2(0,0);
    b->target = b->speed;
    b->exist = true;
    b->spr = create_sprite(32, 32);
    b->jmpHeight = 0;
    b->wait = true;
}


// Update an boss
void boss_update(BOSS* b, PLAYER* pl) {

    if(b->exist == false) return;

    // Move
    if(!b->wait) {

        boss_move(b, pl);
    }
    else if(pl->pos.x/100 -8 > 32) {

        b->wait = false;
    }

    // Animate
    spr_animate(&b->spr, b->target.x < 0 ? 0 : 1,0,3, 6);

    // Player collision
    boss_player_collision(b, pl);
}


// Pre-draw an boss
void boss_pre_draw(BOSS* b) {

    short bx, by;

    if(b->exist == false) return;

    bx = b->pos.x / 100;
    by = b->pos.y / 100;

    fill_rect(bx-16,by-32, 32,32, 0);

}


// Draw an boss
void boss_draw(BOSS* b) {

    short bx, by;

    if(b->exist == false) return;

    bx = b->pos.x / 100;
    by = b->pos.y / 100;

    spr_draw(&b->spr,bmpRocket,bx-16,by-32, FLIP_NONE);
}
