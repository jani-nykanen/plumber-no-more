// Info (source)
// (c) 2018 Jani Nykänen

#include "info.h"

#include "engine/graph.h"

#include "stdlib.h"
#include "stdio.h"

// Bitmaps
static BITMAP* bmpFont;


// Initialize info
void info_init() {

    // Load bitmaps
    bmpFont = load_bitmap("ASSETS/BITMAPS/FONT.BIN");
}


// Draw info
void info_draw() {

}
