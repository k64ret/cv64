#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ultra64.h>

typedef struct controller_state {
    u16 is_connected;
    u16 buttons_held;
    u16 buttons_pressed;
    s16 joystick_x;
    s16 joystick_y;
    s16 joystick_angle;
    s16 joystick_held; // TODO: Maybe search another name for this variable.
} controller_state_t;

#endif
