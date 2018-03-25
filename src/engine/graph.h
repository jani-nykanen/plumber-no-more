// Graphics (header)
// (c) 2018 Jani Nykänen

#ifndef __GRAPH__
#define __GRAPH__

#include "bitmap.h"

#include "stdbool.h"

// Flipping flags
enum {

    FLIP_NONE = 0,
    FLIP_H = 1,
};

// Initialize
void init_graph();

// Put a pixel
void put_pixel(char color, short x, short y);

// Fill a rectangle
void fill_rect(short x, short y, short w, short h, char color);

// Draw a bitmap
void draw_bitmap(BITMAP* b, short x, short y, char flip);

// Draw a bitmap region
void draw_bitmap_region(BITMAP* b, short sx, short sy, short sw, short sh, short dx, short dy, char flip);

// Draw text
void draw_text(BITMAP* font, const char* text, short x, short y, short xoff, short yoff, bool center);

// Clear screen
void clear(char color);

#endif // __GRAPH__
