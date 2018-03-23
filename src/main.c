// Main (source)
// (c) 2018 Jani Nykänen

#include "stdio.h"

#include "engine/graph.h"
#include "engine/sys.h"
#include "engine/input.h"

#include "game.h"


// Main
void main() {

    // Init
    init_graph();
    sys_init();
    input_init();
    game_init();

    // Set scene & loop
    start_game_scene();
    sys_loop();

    // Destroy
    input_destroy();
}
