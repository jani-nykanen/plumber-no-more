// Audio (source)
// (c) 2018 Jani Nykänen

#include "audio.h"

#include <i86.h>

#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"

// Audio buffer size
#define BUFFER_SIZE 128

// Audio buffer
static unsigned short audioBuffer[BUFFER_SIZE *2];
// Audio pointer
static unsigned short audioPointer;
// Audio size
static unsigned short audioSize;
// Audio timer
static unsigned short audioTimer;
// Audio length
static unsigned short audioLength;

// Any audio
static short anyAudio;


// Initialize audio
void audio_init() {

    anyAudio = false;
}


// Play sound
void play_sound(unsigned short* data, unsigned short n) {

    unsigned short i = 0;

    if(n == 0) return;

    // Copy data to audio buffer
    for(i = 0; i < n*2; ++ i) {

        audioBuffer[i] = data[i];
    }

    audioSize = n;
    audioPointer = 0;
    audioTimer = 0;

    anyAudio = true;

    // Play the first sound
    nosound();
    sound(audioBuffer[0]);
    audioLength = audioBuffer[1];
}


// Update audio
void audio_update() {

    if(anyAudio) {

        if(++ audioTimer >= audioLength) {

            nosound();
            if(++ audioPointer >= audioSize) {

                anyAudio = false;
                return;
            }
            
            sound(audioBuffer[audioPointer *2]);
            audioLength = audioBuffer[audioPointer *2 +1];

            audioTimer = 0;
        }
    }

}
