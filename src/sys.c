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
static const short FRAME_WAIT = 40;

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

        input_update();
        if(fnUpdate != NULL)
            fnUpdate();

        delay(FRAME_WAIT);

    }

}


// Terminate
void sys_terminate() {

    isRunning = false;
}
