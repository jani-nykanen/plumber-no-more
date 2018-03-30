// Sound effects (header)
// (c) 2018 Jani Nykänen

#include "sound.h"

#include "engine/audio.h"


// Start sound
static unsigned short sndStart[] = {
    200, 30,
};

// Coin sound
static unsigned short sndCoin[] = {
    200, 5,
    300, 5,
    400, 10,
};

// Jump sound
static unsigned short sndJump[] = {
    100, 10,
    200, 15,
};

// Death sound
static unsigned short sndDie[] = {
    175, 20,
    75, 10,
    150, 30,
};

// Transition sound
static unsigned short sndTrans[] = {
    100, 5,
    150, 10,
};

// Life sound
static unsigned short sndLife[] = {
    300, 15,
    200, 10,
    400, 20,
};

// Pause sound
static unsigned short sndPause[] = {
    150, 20,
};

// Select sound
static unsigned short sndSelect[] = {
    200, 5,
};

// New game sound
static unsigned short sndNew[] = {
    150, 15,
    200, 10,
    250, 10,
    200, 10,
    125, 20,
};

// Game over sound
static unsigned short sndGameOver[] = {
    75, 20,
    125, 20,
    100, 30,
    75, 60,
};

// Victory sound
static unsigned short sndVictory[] = {
    150, 15,
    175, 15,
    200, 15,
    250, 30,
    225, 15,
    300, 30,
    250, 15,
    275, 45,
};

// Title screen "music"
static unsigned short sndTitle[] = {
    150, 30,
    175, 10,
    200, 20,
    175, 10,
    200, 15,
    150, 15,
    175, 20,
    150, 30,
};


// Play a sound effect
void play_sound_effect(unsigned short id) {

    switch(id) {

    case SOUND_START:
        play_sound(sndStart, 1);
        break;

    case SOUND_JUMP:
        play_sound(sndJump, 2);
        break;

    case SOUND_COIN:
        play_sound(sndCoin, 3);
        break;

    case SOUND_DIE:
        play_sound(sndDie, 3);
        break;

    case SOUND_TRANS:
        play_sound(sndTrans, 2);
        break;

    case SOUND_LIFE:
        play_sound(sndLife, 3);
        break;

    case SOUND_PAUSE:
        play_sound(sndPause, 1);
        break;

    case SOUND_SELECT:
        play_sound(sndSelect, 1);
        break;

    case SOUND_NEW:
        play_sound(sndNew, 5);
        break;

    case SOUND_GAMEOVER:
        play_sound(sndGameOver, 4);
        break;

    case SOUND_VICTORY:
        play_sound(sndVictory, 8);
        break;

    case SOUND_TITLE:
        play_sound(sndTitle, 8);
        break;

    default: 
        break;
    }

}
