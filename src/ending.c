// Ending (source)
// (c) 2018 Jani Nykänen

#include "ending.h"

#include "game.h"
#include "stage.h"
#include "info.h"
#include "transition.h"

#include "engine/sys.h"
#include "engine/graph.h"
#include "engine/input.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Bitmaps
static BITMAP* bmpFont;

// Timer
static short timer;

// Interval
static const short _INVERVAL = 90;
// Text position
static const short POS = 40;

// Reset
static void reset() {

    game_hard_reset();
}


// Get time string
static void get_time_string(char* buf) {

    unsigned short time = info_get_time();

    unsigned short seconds = (time/ 60) % 60;
    unsigned short minutes = time / 3600;

    if(seconds >= 10)
        snprintf(buf, 64, "Total time: %d:%d", minutes, seconds);
    else
        snprintf(buf, 64, "Total time: %d:0%d", minutes, seconds);
}


// Ending loop
static void ending_loop() {

    char buf[64];

    ++ timer;

    if(timer == _INVERVAL) {

        draw_text(bmpFont,"You beat the game.", 160,POS + 24,0,0, true);
    }
    else if(timer == _INVERVAL*2) {

        draw_text(bmpFont,"And no one cares, loser.", 160,POS +36,0,0, true);
    }
    else if(timer == _INVERVAL*3) {

        get_time_string(buf);
        draw_text(bmpFont,buf, 160,POS + 68,0,0, true);

    }
    else if(timer == _INVERVAL*6) {

        start_transition(reset);
    }
    
}


// Play the ending
void play_ending() {

    // Clear screen
    clear(0);

    // Get font
    bmpFont = info_get_font();

    // Reset timer
    timer = 0;

    // Draw "Congratulations!"
    draw_text(bmpFont,"CONGRATULATIONS!", 160,POS,0,0, true);

    // Start looping
    set_update_func(ending_loop);
}
