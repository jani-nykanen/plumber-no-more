// Input handler (header)
// (c) 2018 Jani Nykänen

#include "input.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "stdio.h"
#include "stdbool.h"

// Normal keys
static unsigned char normalKeys[0x60];
// Extended keys
static unsigned char extKeys[0x60];

// Old key states
static unsigned char oldNormals[0x60];
// Read states
static bool statesRead[0x60];

// Handlers
static void far interrupt (*oldHandler)(void);

// "Analogue stick"
static VEC2 stick;
// Button key codes
static const short buttons[] = {
    45, 44, 25
};


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

        oldNormals[scancode] = normalKeys[scancode];
        normalKeys[scancode] = make_break;

        if(normalKeys[scancode] != oldNormals[scancode])
            statesRead[scancode] = false;
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
    for(; i < 0x60; ++ i) {

        oldNormals[i] = 255;
    }

    // Init handlers
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

// Get button
char input_get_button(short id) {

    char state = normalKeys[ buttons[id] ];
    bool read = statesRead[ buttons[id] ];
    char ret = 0;

    if(state == DOWN) {

        ret = read ? DOWN : PRESSED;
    }
    else if(state == UP) {

        ret = read ? UP : RELEASED;
    }
    statesRead[buttons[id]] = true;

    return ret;
}


// Destroy
void input_destroy() {

    unhook_keyb_int();
}
