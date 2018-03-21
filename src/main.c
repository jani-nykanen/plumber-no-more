// Main (source)
// (c) 2018 Jani Nykänen

#include "stdio.h"

#include "graph.h"
#include "game.h"
#include "sys.h"
#include "input.h"


// Main
void main() {

    // Init
    init_graph();
    sys_init();
    input_init();

    // Set scene & loop
    start_game_scene();
    sys_loop();

    // Destroy
    input_destroy();
}
