// Main (source)
// (c) 2018 Jani Nykänen

#include "stdio.h"

#include "engine/graph.h"
#include "engine/sys.h"
#include "engine/input.h"

#include "game.h"
#include "pause.h"
#include "title.h"


// Main
void main() {

    // Init
    init_graph();
    sys_init();
    input_init();
    pause_init();

    // Set scene & loop
    play_intro();
    sys_loop();

    // Destroy
    input_destroy();
}
