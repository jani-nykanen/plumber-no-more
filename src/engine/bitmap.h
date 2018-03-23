// Bitmap (header)
// (c) 2018 Jani Nykänen

#ifndef __BITMAP__
#define __BITMAP__

// Bitmap type
typedef struct {

    short w,h;
    unsigned char* data;

}
BITMAP;

// Load a bitmap
BITMAP* load_bitmap(const char* path);

// Destroy a bitmap
void destoy_bitmap(BITMAP* bmp);

#endif // __BITMAP__
