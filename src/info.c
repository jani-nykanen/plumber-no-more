// Info (source)
// (c) 2018 Jani Nykänen

#include "info.h"

#include "engine/graph.h"

#include "stdlib.h"
#include "stdio.h"

// Bitmaps
static BITMAP* bmpFont;

// Lives
static unsigned char lives;
// Time
static unsigned short time;
// Coins
static unsigned char coins;

// Lives changed
static bool livesChanged;
// Coins changed
static bool coinsChanged;


// Get time string
static void get_time_string(char* buf) {

    unsigned short seconds = (time/ 60) % 60;
    unsigned short minutes = time / 3600;

    if(seconds >= 10)
        snprintf(buf, 64, "%d:%d", minutes, seconds);
    else
        snprintf(buf, 64, "%d:0%d", minutes, seconds);
}


// Get lives string
static void get_lives_string(char* buf) {

    snprintf(buf,64, "xx%d", lives);
    buf[0] = 1;
    buf[1] = 3;

    livesChanged = false;
}


// Get coins string
static void get_coins_string(char* buf) {

    snprintf(buf,64, "xx%d", coins);
    buf[0] = 2;
    buf[1] = 3;

    coinsChanged = false;
}


// Initialize info
void info_init() {

    // Load bitmaps
    bmpFont = load_bitmap("ASSETS/BITMAPS/FONT.BIN");

    // Set time
    time = 60 * 60 * 5;

    // Set default values
    livesChanged = true;
    coinsChanged = true;
    lives = 10;
    coins = 0;
}


// Update info
void info_update() {

    -- time;
}


// Draw non-changing info material
void info_draw_static() {

    draw_text(bmpFont, "LIVES", 48,2,0,0, true);
    draw_text(bmpFont, "TIME", 160,2,0,0, true);
    draw_text(bmpFont, "COINS", 320-48,2,0,0, true);

    livesChanged = true;
    coinsChanged = true;
}


// Draw changing info material
void info_draw() {

    char str[64];

    // Draw time
    get_time_string(str);
    draw_text(bmpFont, str, 160,12,0,0, true);

    // Draw lives
    if(livesChanged) {

        get_lives_string(str);
        draw_text(bmpFont, str, 48,12,0,0, true);
    }

    // Draw coins
    if(coinsChanged) {

        get_coins_string(str);
        draw_text(bmpFont, str, 320-48,12,0,0, true);
    }

}
