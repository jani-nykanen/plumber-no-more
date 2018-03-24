// Input handler (header)
// (c) 2018 Jani Nykänen

#include "input.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "stdio.h"

// Normal keys
unsigned char normalKeys[0x60];
// Extended keys
unsigned char extKeys[0x60];

// Normal key states
unsigned char keyStates[0x60];

// Handlers
void far interrupt (*oldHandler)(void);

// "Analogue stick"
static VEC2 stick;
// Button key codes
static const short buttons[] = {
    44, 28
};


// Key down
static void key_down(short sc) {

    if(sc < 0 || sc >= 0x60 || keyStates[sc] == DOWN)
        return;

    keyStates[sc] = PRESSED;

}


// Key up
static void key_up(short sc) {

    if(sc < 0 || sc >= 0x60 || keyStates[sc] == UP)
        return;

    keyStates[sc] = RELEASED;

}


// Keyboard interruption
// (Happily copied from one very helpful Stack Overflow answer!)
static void far interrupt handler() {

    static unsigned char buffer;
    unsigned char rawcode;
    unsigned char make_break;
    int scancode;

    rawcode = inp(0x60); 
    make_break = !(rawcode & 0x80); 
    scancode = rawcode & 0x7F;

    if (buffer == 0xE0) { 

        if (scancode < 0x60) {

            extKeys[scancode] = make_break;
        }
        buffer = 0;

    } 
    else if (buffer >= 0xE1 && buffer <= 0xE2) {

        buffer = 0;

    } 
    else if (rawcode >= 0xE0 && rawcode <= 0xE2) {

        buffer = rawcode; 

    } 
    else if (scancode < 0x60) {

        normalKeys[scancode] = make_break;

        // Normal key events
        if(make_break == 1)
            key_down(scancode);
        else
            key_up(scancode);
    }

    outp(0x20, 0x20);
}


// Hook interruption
static void hook_keyb_int() {

    oldHandler = _dos_getvect(0x09);
    _dos_setvect(0x09, handler);
}


// Unhook
static void unhook_keyb_int() {

    if (oldHandler != NULL) {

        _dos_setvect(0x09, oldHandler);
        oldHandler = NULL;
    }
}


// Initialize
void input_init() {

    short i = 0;

    // Init handleres
    hook_keyb_int();

    // Set key states to UP
    for(; i < 0x60; ++ i) {

        keyStates[i] = UP;
    }
}


// Update
void input_update() {

    short i = 0;

    // Update stick
    stick.x = 0;
    stick.y = 0;
    
    if(extKeys[77] == 1)
        stick.x = 1;
    else if(extKeys[75] == 1)
        stick.x = -1;

    if(extKeys[72] == 1)
        stick.y = -1;
    else if(extKeys[80] == 1)
        stick.y = 1;     

    // Update key states
    for(; i < 0x60; ++ i) {

        if(keyStates[i] == PRESSED) {

            keyStates[i] = DOWN;
        }
        else if(keyStates[i] == RELEASED) {

            keyStates[i] = UP;
        }
    }
}


// Get "analogue stick"
VEC2 input_get_stick() {

    return stick;
}

// Get button
char input_get_button(short id) {

    return keyStates[ buttons[id] ];
}


// Destroy
void input_destroy() {

    unhook_keyb_int();
}
