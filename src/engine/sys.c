// System (source)
// (c) 2018 Jani Nykänen

#include "sys.h"

#include "input.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "stdlib.h"
#include "stdbool.h"

// Frame wait
static const unsigned short FRAME_WAIT = 0;

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

        delay(FRAME_WAIT);

    }

}


// Terminate
void sys_terminate() {

    isRunning = false;
}
