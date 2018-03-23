// Sprite (header)
// (c) 2018 Jani Nykänen

#ifndef __SPRITE__
#define __SPRITE__

#include "bitmap.h"

// Sprite object
typedef struct {
    
    char w;
    char h;
    char frame;
    char row;
    short count;
}
SPRITE;

// Create a new sprite
SPRITE create_sprite(char w, char h);

// Animate a sprite
void spr_animate(SPRITE*s, char row, char start, char end, char speed);

// Draw a sprite
void spr_draw(SPRITE* s, BITMAP* bmp, short x, short y, char flip);

#endif // __SPRITE__
