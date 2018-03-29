// Input handler (header)
// (c) 2018 Jani Nykänen

#ifndef __INPUT__
#define __INPUT__

#include "vector.h"

// Buttons
enum {

    BUTTON_FIRE = 0,
    BUTTON_SELECT = 1,
};

// Button states
enum {
    UP = 0,
    DOWN = 1,
    PRESSED = 2,
    RELEASED = 3,
};

// Initialize
void input_init();

// Update
void input_update();

// Get "analogue stick"
VEC2 input_get_stick();

// Get stick delta
VEC2 input_get_stick_delta();

// Get button
char input_get_button(short id);

// Destroy
void input_destroy();

#endif // __INPUT__
