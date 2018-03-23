// Sprite (header)
// (c) 2018 Jani Nykänen

#include "sprite.h"

#include "graph.h"

#include "stdlib.h"
#include "stdio.h"
#include "math.h"


// Create a new sprite
SPRITE create_sprite(char w, char h)
{
    SPRITE s;
    s.w = w;
    s.h = h;
    s.count = 0;
    s.frame = 0;
    s.row = 0;

    return s;
}


// Animate a sprite
void spr_animate(SPRITE*s, char row, char start, char end, char speed) {

    if(start == end) {

		s->count = 0;
		s->frame = start;
		s->row = row;
		return;
	}

	if(s->row != row) {

		s->count = 0;
		s->frame = end > start ? start : end;
		s->row = row;
	}

	if(start < end && s->frame < start) {

		s->frame = start;
    }
    else if(end < start && s->frame < end) {

        s->frame = end;
    }

	if(++ s->count >= speed) {

        if(start < end) {

            if(++ s->frame > end) {

                s->frame = start;
            }

        }
        else {

            if(-- s->frame < end) {

                s->frame = start;
            }
        }

		s->count = 0;
	}
}


// Draw a sprite
void spr_draw(SPRITE* s, BITMAP* bmp, short x, short y, char flip) {

    draw_bitmap_region(bmp,s->w*s->frame,s->h*s->row,s->w,s->h,x,y,flip);
}
