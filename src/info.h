// Info (header)
// (c) 2018 Jani Nykänen

#ifndef __INFO__
#define __INFO__

// Initialize info
void info_init();

// Update info
void info_update();

// Draw non-changing info material
void info_draw_static();

// Draw changing info material
void info_draw();

// Reduce a life 
char info_reduce_life();

// Add a coin
void info_add_coin();

#endif // __INFO__
