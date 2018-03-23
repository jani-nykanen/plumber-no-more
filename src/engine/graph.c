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
    short x;
    short offset = 320*dy + dx;

    // Go through pixels & draw them
    for(y = dy; y < dy + h; ++ y) {

        for(x = dx; x < dx + w; ++ x) {

            // Put pixel
            VGA[offset ++] = color;
        }

        offset -= w;
        offset += 320;
    }
}


// Draw a bitmap
void draw_bitmap(BITMAP* b, short dx, short dy, char flip) {

    char* VGA = (char*)VGA_POS; 
    short x,y;
    short offset = 320*dy + dx;
    short pixel = 0;
    bool fliph = (flip & FLIP_H) != 0;
    short pdir = fliph ? -1 : 1;
    char color;

     // If horizontal flip, set pixel pointer to the correct
    // place
    if(fliph) {

        pixel += b->w-1;
    }

    // Go through pixels & draw them
    for(y = dy; y < dy + b->h; ++ y) {

        for(x = dx; x < dx+b->w; ++ x) {

            // Get pixel color
            color = b->data[pixel];
            pixel += pdir;

            // If 255 ("transparent"), do not draw
            if(color == 255) {

                ++ offset;
                continue;
            }

            // Put pixel
            VGA[offset ++] = color;
        }

        // If horizontal flip, move pixel pointer forward
        if(fliph) {

            pixel += b->w*2;
        }

        offset -= b->w;
        offset += 320;
    }
}


// Draw bitmap region
void draw_bitmap_region(BITMAP* b, 
    short sx, short sy, short sw, short sh, short dx, short dy, char flip) {

    char* VGA = (char*)VGA_POS; 
    short x,y;
    short offset = 320*dy + dx;
    short pixel = 0;
    bool fliph = (flip & FLIP_H) != 0;
    short pdir = fliph ? -1 : 1;
    char color;

    short pjump = b->w - sw;

    // Set pixel pointer to the source start position
    pixel += sy * b->w + sx;

    // If horizontal flip, set pixel pointer to the correct
    // place
    if(fliph) {

        pixel += sw-1;
    }

    // Go through pixels & draw them
    for(y = dy; y < dy + sh; ++ y) {

        for(x = dx; x < dx+sw; ++ x) {

            // Get pixel color
            color = b->data[pixel];
            pixel += pdir;

            // If 255 ("transparent"), do not draw
            if(color == 255) {

                ++ offset;
                continue;
            }

            // Put pixel
            VGA[offset ++] = color;
        }

        // Move pixel to the next line
        pixel += pjump;

        // If horizontal flip, move pixel pointer forward
        if(fliph) {

            pixel += sw*2;
        }

        offset -= sw;
        offset += 320;
    }
}


// Draw text 
void draw_text(const char* text, short x, short y) {

    char pos[64];
    snprintf(pos, 64, "\033[%d;%dH", y, x);

    printf("%s%s\n",pos, text);
}
