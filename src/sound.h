// Sound effects (header)
// (c) 2018 Jani Nykänen

#ifndef __SOUND__
#define __SOUND__

// Sounds
enum {

    SOUND_START = 0,
    SOUND_JUMP = 1,
    SOUND_COIN = 2,
    SOUND_DIE = 3,
    SOUND_TRANS = 4,
    SOUND_LIFE = 5,
    SOUND_PAUSE = 6,
    SOUND_SELECT = 7,
    SOUND_NEW = 8,
    SOUND_GAMEOVER = 9,
    SOUND_VICTORY = 10,
    SOUND_TITLE = 11,
};

// Play a sound effect
void play_sound_effect(unsigned short id);

#endif // __SOUND__
