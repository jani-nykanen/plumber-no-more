// Bitmap (source)
// (c) 2018 Jani Nykänen

#include "bitmap.h"

#include "stdio.h"
#include "stdlib.h"


// Load a bitmap
BITMAP* load_bitmap(const char* path) {

    short w, h;
    BITMAP* bmp;

    // Open file
    FILE* f = fopen(path, "rb");
    if(f == NULL) {

        printf("Could not load a file in:\n%s", path);
        exit(1);
    }

    // Read size
    fread(&w, sizeof(short),1, f);
    fread(&h, sizeof(short),1, f);

    // Allocate memory
    bmp = (BITMAP*)malloc(sizeof(BITMAP));
    if(bmp == NULL) {

        printf("Memory allocation error!\n");
        exit(1);
    }
    bmp->data = (unsigned char*)malloc(sizeof(char) * w * h);
    if(bmp->data == NULL) {

        printf("Memory allocation error!\n");
        exit(1);
    }

    // Read data
    fread(bmp->data, sizeof(char), w*h, f);

    // Store dimensions
    bmp->w = w;
    bmp->h = h;

    // Close file
    fclose(f);

    return bmp;
}


// Destroy a bitmap
void destoy_bitmap(BITMAP* bmp) {

    if(bmp == NULL)
        return;

    free(bmp->data);
    free(bmp);
}
