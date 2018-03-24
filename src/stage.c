// Stage (source)
// (c) 2018 Jani Nykänen

#include "stage.h"

#include "engine/bitmap.h"
#include "engine/graph.h"

#include "stdio.h"
#include "stdlib.h"

// Map size (in tiles)
#define MAP_SIZE 240

// Stage tile data
static char tiles[MAP_SIZE];

// Map width (unneeded)
static short width;
// Map height (unneeded)
static short height;

// Bitmaps
static BITMAP* bmpTiles;


// Initialize stage
void stage_init() {

    // Load assets
    bmpTiles = load_bitmap("ASSETS/BITMAPS/TILES.BIN");
}


// Load stage
void stage_load(const char* path) {

    // Open
    FILE* f = fopen(path,"rb");
    if(f == NULL) {

        printf("Failed to open %s!\n", path);
        exit(1);
    }

    // Read dimensions
    fread(&width,sizeof(short), 1, f);
    fread(&height,sizeof(short),1, f);

    // Read data
    fread(tiles, width*height, 1, f);

    // Close
    fclose(f);
}


// Draw stage
void stage_draw() {

    short x, y;
    short sx, sy;
    char tile;

    for(y = 0; y < height; ++ y) {

        for(x = 0; x < width; ++ x) {

            tile = tiles[y * width +x];
            if(tile -- == 0)
                continue;


            sx = ( (short)tile) % 16;
            sy = ( (short)tile) / 16;

            draw_bitmap_region(bmpTiles, sx*16,sy*16,16,16, x*16,y*16 +8, FLIP_NONE);
        }
    }

}


// Stage-to-player collisions
void stage_player_collision(PLAYER* pl) {

    pl_stage_collision(pl, tiles, width, height);
}
