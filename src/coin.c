// Coin (header)
// (c) 2018 Jani Nykänen

#include "coin.h"

#include "info.h"

#include "engine/graph.h"

#include "stdlib.h"
#include "stdio.h"

// Bitmaps
static BITMAP* bmpCoin;


// Initialize coins
void coin_init() {

    // Load bitmaps
    bmpCoin = load_bitmap("ASSETS/BITMAPS/COIN.BIN");
}


// Create a coin
void coin_create(COIN* c, VEC2 pos) {

    c->pos = pos;
    c->exist = true;
    c->die = false;
}


// Pre-draw a coint
void coin_pre_draw(COIN* c) {

    if(c->die) {

        fill_rect(c->pos.x,c->pos.y,16,16, 0);
        c->die = false;
    }
}


// Coin-player collision
void coin_player_collision(PLAYER* pl, COIN* c) {

    short px = pl->pos.x / 100;
    short py = pl->pos.y / 100;

    if(!c->exist) return;

    if(px+8 > c->pos.x-4 && px-8 < c->pos.x+12 &&
       py > c->pos.y-2 && py-16 < c->pos.y+14) {

         c->die = true;
         c->exist = false;
         info_add_coin();
    }
}


// Draw a coin
void coin_draw(COIN* c) {

    if(!c->exist) return;

    draw_bitmap(bmpCoin, c->pos.x,c->pos.y, FLIP_NONE);
}
