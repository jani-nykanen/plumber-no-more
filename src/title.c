// Title screen (header)
// (c) 2018 Jani Nykänen

#include "title.h"

#include "info.h"
#include "game.h"
#include "stage.h"
#include "transition.h"

#include "engine/sys.h"
#include "engine/graph.h"
#include "engine/input.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Bitmaps
static BITMAP* bmpLogo;
static BITMAP* bmpFont;

// Blue timer
static short blueTimer;
static short bluePos;

// Title timer
static short titleTimer;
static char titlePhase;
static short startTimer;


// Go to the game
static void go_to_game() {

    clear(0);
    game_init();
}


// Update title
static void title_update() {

    if(titleTimer <= 96)
        ++ titleTimer;

    else {

        if(titlePhase == 0) {

            if(++ startTimer >= 60)
                startTimer = 0;
        }

        if(input_get_button(3) == PRESSED) {

            startTimer = 30;

            // Set transition
            start_transition(go_to_game);
        }

    }
}


// Draw press start
static void draw_press_start() {

    if(startTimer < 30) {

        draw_text(bmpFont, "PRESS ENTER TO START",160,200-48,0,0, true);

    }
    else {

        fill_rect(0,200-48,320,8, 6);
    }   
}


// Draw title
static void title_draw() {

    short t = titleTimer / 4;
    t *= 4;

    if(titleTimer == 1) {

        draw_bitmap_region(bmpLogo,0,96,bmpLogo->w,18,
            160-bmpLogo->w/2, 16 + 96, FLIP_NONE);
    }
    else if(titleTimer < 96) {

        draw_bitmap_region(bmpLogo,0,0,bmpLogo->w,t,
            160-bmpLogo->w/2, 16 + 96-t, FLIP_NONE);
    }
    else if(titleTimer == 96) {

        // Draw copyright
        draw_text(bmpFont, "(c) 2018 Jani Nyk*nen",160,200-11,0,0, true);
    }
    else {

        if(titlePhase == 0) {

            draw_press_start();
        }
    }
}


// Title update loop
static void title_loop() {

    title_update();
    title_draw();
}


// Load bitmaps
static void load_bitmaps() {

    bmpLogo = load_bitmap("ASSETS/BITMAPS/LOGO.BIN");
    bmpFont = load_bitmap("ASSETS/BITMAPS/FONT2.BIN");
}


// Draw blue
static void draw_blue() {

    if(++ blueTimer == 4) {

        fill_rect(160-bluePos*8, 0,8, 200, 6);
        fill_rect(160+bluePos*8, 0,8, 200, 6);

        blueTimer = 0;
        
        if(bluePos ++ >= 20) {

            load_bitmaps();
            titleTimer = 0;
            titlePhase = 0;
            startTimer = 0;
            set_update_func(title_loop);
        }
    }

}


// ----------------------------------------- //

// Bitmaps
static BITMAP* bmpCreator;

// Loop timer
static short loopTimer;


// Intro must die
static void destroy_intro() {

    destoy_bitmap(bmpCreator);
}


// Intro loop
static void loop_intro() {

    short t;

    ++ loopTimer;

    if(loopTimer < 60) {

        t = loopTimer / 20;
    }
    else if(loopTimer > 180) {

        t = 2 - (loopTimer-180) / 20;
    }
    else {

        t = 3;
    }
    
    if(loopTimer == 240) {

        // Go to the game scene
        blueTimer = 0;
        set_update_func(draw_blue);
        
        destroy_intro();
        return;
    }
    else if(loopTimer == 220) {

        clear(0);
    }

    if(t <= 0) return;

    // Draw face
    draw_bitmap_region(bmpCreator, 64*(t-1),0,64,64, 160-32,32, FLIP_NONE);

    // Draw "created by"
    draw_bitmap_region(bmpCreator, 0,64 + (t-1)*24,96,24, 160-48,104, FLIP_NONE);

    // DEBUG
    if(input_get_button(2) == PRESSED) {

        go_to_game();
    }

}


// Play intro (and automaticall go to the title screen)
void play_intro() {

    // Load bitmaps
    bmpCreator = load_bitmap("ASSETS/BITMAPS/CREATOR.BIN");

    // Clear
    clear(0);

    // Loop
    loopTimer = 0;
    set_update_func(loop_intro);
}
