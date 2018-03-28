// Game scene (source)
// (c) 2018 Jani Nykänen

#include "game.h"

#include "stage.h"
#include "player.h"
#include "info.h"
#include "coin.h"
#include "enemy.h"
#include "boss.h"
#include "pause.h"
#include "gameover.h"

#include "engine/sys.h"
#include "engine/graph.h"
#include "engine/vector.h"
#include "engine/bitmap.h"
#include "engine/input.h"

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
static BOSS boss;

// Scene terminated
static bool sceneTerminated;

// Victory timer
static short victoryTimer;


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

    // Pause, if enter pressed
    if(input_get_button(3) == PRESSED) {

        sceneTerminated = true;
        pause_game();
        return;
    }

    // Update player
    pl_update(&player);
    stage_player_collision(&player);

    // If victory
    if(player.victorious) {

        if(++ victoryTimer >= 180) {

            game_over(2);
        }

        return;
    }

    // Update coins
    for(; i < COIN_COUNT; ++ i) {

        coin_player_collision(&player, &coins[i]);
    }

    // Update enemies
    for(i=0; i < ENEMY_COUNT; ++ i) {

        enemy_update(&enemies[i]);
        enemy_player_collision(&enemies[i], &player);
    }

    // Update boss
    boss_update(&boss, &player);

    // Update info
    info_update();

    // DEBUG
    if(input_get_button(2) == PRESSED) {

        player.pos.x = (320-7)*100;
    }
}


// Draw before update
static void game_pre_draw() {

    short i = 0;

    // "Draw" coins (not really)
    for(; i < COIN_COUNT; ++ i) {

        coin_pre_draw(&coins[i]);
    }

     // Pre-draw enemies
    for(i=0; i < ENEMY_COUNT; ++ i) {

        enemy_pre_draw(&enemies[i]);
    }

    // Pre-draw boss
    boss_pre_draw(&boss);

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

    // Draw boss
    boss_draw(&boss);

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
    if(sceneTerminated || info_game_over() ) {

        sceneTerminated = false;
        return;
    }
    
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
    boss_init();

    // Reset
    game_reset();

    // Load default map
    stage_load(1, true);

    // Redraw
    game_redraw();

    // Create objects
    player = pl_create(vec2(6*16 +8, 10*16 +8));

    // Set default values
    sceneTerminated = false;

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


// Add the boss to the screen
void game_add_boss(VEC2 pos) {

    boss_create(&boss, pos);
}


// Reset game
void game_reset() {

    short i = 0;
    
    // Destroy coins
    for(; i < COIN_COUNT; ++ i) {

        coins[i].pos = vec2(-1,-1);
        coins[i].exist = false;
        coins[i].die = false;
    }

    // Destroy enemies
    for(i=0; i < ENEMY_COUNT; ++ i) {

        enemies[i].exist = false;
    }

    // Destroy boss
    boss.exist = false;
}


// Hard-reset the game
void game_hard_reset() {

    clear(0);
    game_reset();
    stage_load(1, false);
    player = pl_create(vec2(6*16 +8, 10*16 +8));

    stage_draw_by_parts(); 
}


// Start game scene
void start_game_scene() {

    // Set update function
    set_update_func(game_loop);

}
