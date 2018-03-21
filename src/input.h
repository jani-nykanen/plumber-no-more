// Input handler (header)
// (c) 2018 Jani Nykänen

#ifndef __INPUT__
#define __INPUT__

#include "vector.h"

// Initialize
void input_init();

// Update
void input_update();

// Get "analogue stick"
VEC2 input_get_stick();

// Destroy
void input_destroy();

#endif // __INPUT__
