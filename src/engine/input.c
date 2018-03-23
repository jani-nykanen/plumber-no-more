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

// Handlers
void far interrupt (*oldHandler)(void);


// "Analogue stick"
static VEC2 stick;

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

    // Init handleres
    hook_keyb_int();
}


// Update
void input_update() {

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
}


// Get "analogue stick"
VEC2 input_get_stick() {

    return stick;
}


// Destroy
void input_destroy() {

    unhook_keyb_int();
}
