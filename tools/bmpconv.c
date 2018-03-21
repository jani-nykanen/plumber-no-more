// PNG-to-binary converter
// (c) 2018 Jani Nykänen


#include <SDL2/SDL_image.h>

#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// Load a bitmap & convert it to a binary format
int conv_bitmap(const char* in, const char* out) {

    // Load surface
    SDL_Surface* surf = IMG_Load(in);
    if(surf == NULL) {
        
        printf("Failed to load a bitmap in %s!",in);
        return 1;
    }

    unsigned int pixelCount = surf->w * surf->h;

    // Allocate image and temp buffer data
    Uint8* data = (Uint8*)malloc(sizeof(Uint8) * pixelCount);
    if(data == NULL) {
        
        exit(1);
    }

    // Go through the data
    int i = 0;
    Uint8 pixel;
    Uint8 r,g,b,a;
    Uint8 er,eg,eb;
    Uint8* pdata = (Uint8*)surf->pixels;
    for(; i < pixelCount; i++) {

        a = pdata[i*4 +3];
        if(a != 255) {

            data[i] = 255;
            continue;
        }

        r = pdata[i*4 +2];
        g = pdata[i*4 +1];
        b = pdata[i*4 ];

        er = (r / 85);
        eg = (g / 85);
        eg = eg << 2;
        eb = (b / 85);
        eb = eb << 4;

        pixel = 0;
        pixel = er | eg | eb;
        
        data[i] = pixel;
    }

    // Save dimensions
    short w = (short)surf->w;
    short h = (short)surf->h;

    // Free surface
    free(surf);

    // Create output file
    FILE* f = fopen(out, "wb");
    if(f == NULL) {

        exit(1);
    }

    // Save dimensions
    fwrite(&w, sizeof(short), 1, f);
    fwrite(&h, sizeof(short), 1, f);

    // Save pixel data
    fwrite(data,sizeof(Uint8), w*h, f);

    // Close file
    fclose(f);

    return 0;
}


// Main
int main(int argc, char** argv) {

    // Check arguments
    if(argc < 3) {

        printf("Too few arguments! Help: bmpconv in out\n");
        return 1;
    }

    // Init SDL2_img
    IMG_Init(IMG_INIT_PNG);

    // Convert
    return conv_bitmap(argv[1], argv[2]);
}