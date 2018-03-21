// Game scene (source)
// (c) 2018 Jani Nykänen

#include "game.h"

#include "sys.h"
#include "graph.h"
#include "vector.h"
#include "input.h"
#include "bitmap.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

// Test object position
static VEC2 pos;

// Test bitmap
static BITMAP* bmpTest;


// Initialize
static void game_init() {

    // Set default values
    pos = vec2(160,100);

    // Load assets
    bmpTest = load_bitmap("ASSETS/TEST.BIN");
}


// Update game
static void game_update() {

    VEC2 stick = input_get_stick();

    // Draw old
    fill_rect(pos.x-8,pos.y-8,16,16, 0);

    pos.x += stick.x *3;
    pos.y += stick.y *3;

    // Draw new
    draw_bitmap_region(bmpTest,24,24,16,16,pos.x-8,pos.y-8, FLIP_H);
}


// Start game scene
void start_game_scene() {

    // Init
    game_init();

    // Draw test bitmaps
    draw_bitmap(bmpTest, 8,8, FLIP_H);
    draw_bitmap_region(bmpTest,16,16,32,32,240,16, FLIP_H);

    // Set update function
    set_update_func(game_update);

    // Draw text
    draw_text("Hello world!",16,5, 97); 

}
