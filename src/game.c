// Game scene (source)
// (c) 2018 Jani Nykänen

#include "game.h"

#include "stage.h"
#include "player.h"

#include "engine/sys.h"
#include "engine/graph.h"
#include "engine/vector.h"
#include "engine/bitmap.h"

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

// Game objects
static PLAYER player;


// Update game
static void game_update() {

    // Update game objects
    pl_update(&player);
    stage_player_collision(&player);
}


// Draw before update
static void game_pre_draw() {

    // Pre-draw moving objects
    pl_pre_draw(&player);
}


// Draw
static void game_draw() {

    // Draw moving objects
    pl_draw(&player);
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

    // Load default map
    stage_load(1);

    // Create objects
    player = pl_create(vec2(6*16 +8, 10*16 +8));
}


// Start game scene
void start_game_scene() {

    // Set update function
    set_update_func(game_loop);

}
