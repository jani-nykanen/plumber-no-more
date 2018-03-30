// Audio (header)
// (c) 2018 Jani Nykänen

#ifndef __AUDIO__
#define __AUDIO__

// Initialize audio
void audio_init();

// Play sound
void play_sound(unsigned short* data, unsigned short n);

// Update audio
void audio_update();

#endif // __AUDIO__
