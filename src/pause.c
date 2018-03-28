// Pause screen (source)
// (c) 2018 Jani Nykänen

#include "pause.h"

#include "info.h"
#include "game.h"
#include "stage.h"

#include "engine/sys.h"
#include "engine/graph.h"
#include "engine/input.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Bitmaps
static BITMAP* bmpFont;
static BITMAP* bmpCursor;

// Constants
static const short WIDTH = 80;
static const short HEIGHT = 28;

// Cursor position
static bool cursorPos;


// Draw box
static void pause_draw_box() {

    // Box
    fill_rect(160 - WIDTH/2, 100 - HEIGHT/2, WIDTH, HEIGHT, 63);
    fill_rect(160 - WIDTH/2+1, 100 - HEIGHT/2+1, WIDTH-2, HEIGHT-2, 0);

    // Text
    draw_text(bmpFont, "RESUME", 160-WIDTH/2+22, 100-HEIGHT/2+4, 0,0, false);
    draw_text(bmpFont, "QUIT", 160-WIDTH/2+22, 100-HEIGHT/2+16, 0,0, false);
}


// Update pause
static void pause_update() {

    VEC2 stick = input_get_stick();

    // Move cursor
    if( (stick.y > 0 && !cursorPos) || (stick.y < 0 && cursorPos)) {

        cursorPos = !cursorPos;
    }

    // Enter pressed
    if(input_get_button(3) == PRESSED) {

        if(!cursorPos) {

            clear(0);
            game_redraw();
            stage_draw();
            start_game_scene();
        }
        else {

            sys_terminate();
        }
    }
}


// Draw pause
static void pause_draw() {

    // Draw cursor
    short cpos = cursorPos ? 12 : 0;
    fill_rect(160-WIDTH/2+4, 100-HEIGHT/2+2,16,24, 0);
    draw_bitmap(bmpCursor, 160-WIDTH/2+4, 100-HEIGHT/2+2 +cpos, FLIP_NONE);
}


// Pause loop
static void pause_loop() {

    pause_draw();
    pause_update();
    
}


// Pause the game
void pause_game() {

    // Set values
    bmpFont = info_get_font();
    cursorPos = false;

    // Draw static
    pause_draw_box();

    // Set update function
    set_update_func(pause_loop);
}


// Initialize pause
void pause_init() {

    // Load bitmaps
    bmpCursor = load_bitmap("ASSETS/BITMAPS/CURSOR.BIN");
}
