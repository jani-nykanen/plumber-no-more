// Transition (source)
// (c) 2018 Jani Nykänen

#include "transition.h"

#include "engine/sys.h"
#include "engine/graph.h"

#include "stdio.h"
#include "stdlib.h"

// Transition finished callback function
static void (*fnFinished) (void);

// Position
static short pos;


// Loop
static void trn_loop() {

    short p;
    
    if( (pos += 3) >= 160) {

        if(fnFinished != NULL)
            fnFinished();

        return;
    }

    p = pos / 4;
    p *= 4;

    // Draw horizontal
    fill_rect(0,0,p,200, 0);
    fill_rect(320-p,0,p,200, 0);

    // Draw vertical
    if(pos > 60) {

        fill_rect(p,0,320-p,p-60, 0);
        fill_rect(p,200 - (p-60),320-p,p-60, 0);
    }

}


// Start transition
void start_transition(void (*cb)(void)) {

    fnFinished = cb;
    pos = 0;

    set_update_func(trn_loop);
}
