// System (source)
// (c) 2018 Jani Nykänen

#include "sys.h"

#include "input.h"
#include "graph.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "stdlib.h"
#include "stdbool.h"

// Is running
static bool isRunning;


// Update function
static void (*fnUpdate)(void) = NULL;


// Initialize
void sys_init() {

    isRunning = true;
}


// Set update function
void set_update_func(void (*update)(void)) {

    fnUpdate = update;
}


// Loop
void sys_loop() {

    while(isRunning) {

        // VSync
        while(inp(0x3DA) & 8);
        while(!(inp(0x3DA) & 8));

        if(fnUpdate != NULL)
            fnUpdate();

        input_update();
    }

}


// Terminate
void sys_terminate() {

    clear(0);
    input_destroy();
    isRunning = false;
}
