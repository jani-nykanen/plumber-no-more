// Graphics (source)
// (c) 2018 Jani Nykänen

#include "graph.h"

#include <dos.h>
#include <conio.h>
#include <graph.h>

#include "stdbool.h"
#include "string.h"
#include "stdio.h"

// VGA position
static const long VGA_POS = 0xA0000000;

// Palette constants
static const long PALETTE_INDEX = 0x03c8;
static const long PALETTE_DATA = 0x03c9;


// Initialize default palette
static void init_default_palette() {

    // Generate colors (we need only 64 first colors)
    char colors[64 *3];
    int i = 0;
    char r,g,b;
    for(; i < 64; i++)
    {
        r = i >> 4;
        g = i << 4;
        g = g >> 6;
        b = i << 6;
        b = b >> 6; 

        colors[i*3] = r *85;
        colors[i*3 +1] = g *85;
        colors[i*3 +2] = b *85;
    }

    // Set palette
    outp(PALETTE_INDEX,0);

    for(i = 0; i < 255*3 ; ++ i) {

        
        if(i >= 64*3) {

            outp(PALETTE_DATA,255);
        }
        else {

            outp(PALETTE_DATA,colors[i]);
        }
    }

}


// Initialize
void init_graph() {

    // Set video mode to 320x200 256 colors
    _setvideomode(_MRES256COLOR);

    // Set palette
    init_default_palette();
}


// Put pixel
void put_pixel(char color, short x, short y) {

    char* VGA = (char*)VGA_POS;     
    short offset = 320*y + x;
    VGA[offset] = color;
}


// Fill a rectangle
void fill_rect(short dx, short dy, short w, short h, char color) {

    char* VGA = (char*)VGA_POS;     
    short y = dy;
    short offset = 320*dy + dx;

    // Go through pixels & draw them
    for(y = dy; y < dy + h; ++ y) {

        memset(VGA + offset, color ,w);
        offset += 320;
    }
}


// Draw a bitmap
void draw_bitmap(BITMAP* b, short dx, short dy, char flip) {

    char* VGA = (char*)VGA_POS; 
    char* bmp = (char*)b->data;
    short y;
    short offset = 320*dy + dx;
    short bmpOff = 0;

    for(y=0; y < b->h; ++ y) {

        memcpy(VGA + offset, bmp + bmpOff, b->w);
        offset += 320;
        bmpOff += b->w;
    }
}


// Draw bitmap region
void draw_bitmap_region(BITMAP* b, 
    short sx, short sy, short sw, short sh, short dx, short dy, char flip) {

    char* VGA = (char*)VGA_POS; 
    char* bmp = (char*)b->data;
    short y;
    short offset = 320*dy + dx;
    short bmpOff = b->w*sy + sx;

    for(y=0; y < sh; ++ y) {

        memcpy(VGA + offset, bmp + bmpOff, sw);
        offset += 320;
        bmpOff += b->w;
    }
}


// Draw text 
void draw_text(BITMAP* b, const char* text, short dx, short dy, short xoff, short yoff, bool center) {
    
    char len = strlen((const char*)text);

    short x = dx;
    short y = dy;
    short cw = b->w / 16;
    short ch = cw; //  b->h / 16;
    short i=0;
    char c;
    short sx;
    short sy;

    if(center) {

        dx -= (len* + cw) / 2;
        x = dx;
    }

    for(; i < len;  ++ i) {

        c = text[i];
        if(c == '\n') {

            x = dx;
            y += yoff + ch;
            continue;
        }

        sx = c % 16;
        sy = c / 16;

        draw_bitmap_region(b,sx*cw,sy*ch,cw,ch,x,y,0);

        x += cw + xoff;
    }
}


// Clear screen
void clear(char color) {

    memset((char*)VGA_POS, color, 320*200);
}
