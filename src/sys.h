// System (header)
// (c) 2018 Jani Nykänen

#ifndef __SYS__
#define __SYS__

// Initialize
void sys_init();

// Set update function
void set_update_func(void (*update)(void));

// Loop
void sys_loop();

// Terminate
void sys_terminate();

#endif // __SYS__
