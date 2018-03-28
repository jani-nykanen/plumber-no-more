// Stage (source)
// (c) 2018 Jani Nykänen

#include "stage.h"

#include "game.h"
#include "info.h"

#include "engine/sys.h"
#include "engine/bitmap.h"
#include "engine/graph.h"

#include "stdio.h"
#include "stdlib.h"

// Map size (in tiles)
#define MAP_SIZE 260

// Stage tile data
static char tiles[MAP_SIZE];

// Map width (unneeded)
static short width;
// Map height (unneeded)
static short height;

// Map index
static short mapIndex;

// Bitmaps
static BITMAP* bmpTiles;


// Calculate start position for the player
static short calc_start_pos() {

    short y = 4;
    for(; y < height-1; ++ y) {

        if(tiles[y * width] == 0 && tiles[(y+1) * width ] != 0) {

            return y;
        }
    }

    return y;
}


// Initialize stage
void stage_init() {

    // Load assets
    bmpTiles = load_bitmap("ASSETS/BITMAPS/TILES.BIN");
}


// Load stage
void stage_load(unsigned short index, bool redraw) {

    short t = 0;
    short x,y;
    char path[64];
    FILE* f;

    mapIndex = index;

    snprintf(path,64, "ASSETS/MAPS/%d.BIN", index);

    // Open
    f = fopen(path,"rb");
    if(f == NULL) {

        printf("Failed to open %s!\n", path);
        exit(1);
    }

    // Read dimensions
    fread(&width,sizeof(short), 1, f);
    fread(&height,sizeof(short),1, f);

    // Read data
    fread(tiles, width*height, 1, f);

    // Remove object tiles
    for(y = 0; y < height; ++ y) {

        for(x = 0; x < width; ++ x) {

            t = tiles[y*width + x];
            if(t >= 6*16 +1) {
            
                switch(t) {

                case 97:
                    game_add_coin(vec2(x * 16, y * 16 -8 ));
                    break;

                case 98:
                case 99:
                case 100:
                case 101:
                case 102:
                case 103:
                case 104:

                    game_add_enemy(vec2(x * 16 +8, y * 16 -8 +16), t-98);
                    break;

                case 105:

                    game_add_boss(vec2(x * 16 +8, y * 16 -8 +16));
                    break;

                default: 
                    break;
                }
            
                tiles[y*width + x] = 0;
            }
        }
    }

    // Close
    fclose(f);

    // Draw
    if(redraw)
        stage_draw();
}


// Load next stage
void stage_load_next() {

    stage_load(++ mapIndex, true);
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

            draw_bitmap_region(bmpTiles, sx*16,sy*16,16,16, x*16,y*16-8, FLIP_NONE);
        }
    }

}


// Stage-to-player collisions
void stage_player_collision(PLAYER* pl) {

    pl_stage_collision(pl, tiles, width, height);

    if(pl->pos.x/100 >= 320-8) {

        // Clear
        clear(0);

        // Reset game
        game_reset();

        // Load next
        stage_load_next();

        // Redraw game
        game_redraw();

        // Move player back to left side
        pl->pos.x = 800 + ( pl->pos.x - (320-8)*100);

        // Calculate new starting position
        pl->startPos.x = 800;
        pl->startPos.y = (calc_start_pos()) * 16 * 100 +800;
    }
}


// Get stage data
char* stage_get_data(short* w, short *h) {

    *w = width;
    *h = height;
    return tiles;
}


// ------------------------------- //


// Timer
static short timer;

// Tile pos
static short tilePos;


// Draw stage
static void stage_draw_column(short x) {

    short y;
    short sx, sy;
    char tile;

    for(y = 0; y < height; ++ y) {

        tile = tiles[y * width +x];
        if(tile -- == 0)
            continue;

        sx = ( (short)tile) % 16;
        sy = ( (short)tile) / 16;

        draw_bitmap_region(bmpTiles, sx*16,sy*16,16,16, x*16,y*16-8, FLIP_NONE);
    }

}


// Draw by parts loop
static void draw_by_parts_loop() {

    if(++ timer >= 4) {

        if(tilePos -- <= 0) {

            info_reset();
            game_redraw();
            start_game_scene();
            return;
        }

        stage_draw_column(tilePos);
        stage_draw_column(width-1 - tilePos);

        timer = 0;
        
    }
}


// Draw the stage "by parts"
void stage_draw_by_parts() {

    clear(0);
    timer = 0;
    tilePos = width / 2;
    
    set_update_func(draw_by_parts_loop);
}


// Is the stage the final stage
bool stage_is_final() {

    return (mapIndex == 13);
}
