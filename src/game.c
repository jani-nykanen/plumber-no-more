// Game scene (source)
// (c) 2018 Jani Nykänen

#include "game.h"

#include "stage.h"
#include "player.h"
#include "info.h"
#include "coin.h"
#include "enemy.h"

#include "engine/sys.h"
#include "engine/graph.h"
#include "engine/vector.h"
#include "engine/bitmap.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

// Object counts
#define COIN_COUNT 16
#define ENEMY_COUNT 16

// Game objects
static PLAYER player;
static COIN coins[COIN_COUNT];
static ENEMY enemies[ENEMY_COUNT];


// Draw coins
static void draw_coins() {

    short i = 0;
    for(; i < COIN_COUNT; ++ i) {

        coin_draw(&coins[i]);
    }
}


// Update game
static void game_update() {

    short i = 0;

    // Update player
    pl_update(&player);
    stage_player_collision(&player);

    // Update coins
    for(; i < COIN_COUNT; ++ i) {

        coin_player_collision(&player, &coins[i]);
    }

    // Update enemies
    for(i=0; i < ENEMY_COUNT; ++ i) {

        enemy_update(&enemies[i]);
    }

    // Update info
    info_update();
}


// Draw before update
static void game_pre_draw() {

    short i = 0;

    // "Draw" coins (not really)
    for(; i < COIN_COUNT; ++ i) {

        coin_pre_draw(&coins[i]);
    }

     // Pre-draw enemies
    for(; i < ENEMY_COUNT; ++ i) {

        enemy_pre_draw(&enemies[i]);
    }

    // Pre-draw moving objects
    pl_pre_draw(&player);
}


// Draw
static void game_draw() {
    
    short i = 0;

    // Draw enemies
    for(; i < ENEMY_COUNT; ++ i) {

        enemy_draw(&enemies[i]);
    }

    // Draw player
    pl_draw(&player);

    // Draw changing info
    info_draw();
}


// Update game
static void game_loop() {

    // Pre-draw
    game_pre_draw();

    // Update
    game_update();
    
    // Post-draw
    game_draw();
    
}


// Initialize
void game_init() {

    // Initialize components
    stage_init();
    pl_init();
    info_init();
    coin_init();
    enemy_init();

    // Reset
    game_reset();

    // Load default map
    stage_load(1);

    // Redraw
    game_redraw();

    // Create objects
    player = pl_create(vec2(6*16 +8, 10*16 +8));

}


// Redraw the game
void game_redraw() {

    info_draw_static();
    draw_coins();

}


// Add a coin
void game_add_coin(VEC2 pos) {

    short i = 0;
    for(; i < COIN_COUNT; ++ i) {

        if(!coins[i].exist) {

            coin_create(&coins[i], pos);
            break;
        }
    }
}


// Add an enemy
void game_add_enemy(VEC2 pos, char type) {

    short i = 0;
    for(; i < ENEMY_COUNT; ++ i) {

        if(!enemies[i].exist) {

            enemy_create(&enemies[i], pos, type);
            break;
        }
    }
}


// Reset game
void game_reset() {

    short i = 0;
    for(; i < COIN_COUNT; ++ i) {

        coins[i].pos = vec2(-1,-1);
        coins[i].exist = false;
        coins[i].die = false;
    }

    for(i=0; i < ENEMY_COUNT; ++ i) {

        enemies[i].exist = false;
    }
}


// Start game scene
void start_game_scene() {

    // Set update function
    set_update_func(game_loop);

}
