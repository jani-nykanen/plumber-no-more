// TMX2Bin
// (c) 2018 Jani Nykänen

#include "tmxc.h"

#include "stdio.h"
#include "stdlib.h"


// Convert
int convert(const char* in, const char* out) {

    // Load
    TILEMAP* t = load_tilemap(in);
    if(t == NULL) {

        return 1;
    }

    // Open file
    FILE* f = fopen(out, "wb");
    if(f == NULL) {

        printf("Failed to create the output file!\n");
        return 1;
    }

    // Convert to byte
    unsigned char* data = (unsigned char*) malloc(t->width * t->height);
    int i = 0;
    for(; i < t->width*t->height; ++ i) {

        data[i] = (unsigned char) t->layers[0] [i];
    }

    // Write dimensions
    short w = t->width;
    short h = t->height;
    fwrite(&w,sizeof(short),1, f);
    fwrite(&h,sizeof(short),1, f);

    // Write data
    fwrite(data, w*h, 1, f);

    // Close file
    fclose(f);


    return 0;
}


// Main
int main(int argc, char** argv) {

    // Check arguments
    if(argc < 3) {

        printf("Too few arguments! Help: tmx2bin in out\n");
        return 1;
    }

    // Convert
    return convert(argv[1], argv[2]);
}
