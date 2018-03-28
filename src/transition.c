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

    if( (pos += 3) >= 160) {

        // We do not have to make checks if fnFinished is NULL,
        // because THAT SHOULD NOT HAPPEN!
        fnFinished();
        return;
    }

    // Draw horizontal
    fill_rect(0,0,pos,200, 0);
    fill_rect(320-pos,0,pos,200, 0);

    // Draw vertical
    if(pos > 60) {

        fill_rect(pos,0,320-pos,pos-60, 0);
        fill_rect(pos,200 - (pos-60),320-pos,pos-60, 0);
    }

}


// Start transition
void start_transition(void (*cb)(void)) {

    fnFinished = cb;
    pos = 0;

    set_update_func(trn_loop);
}
