#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ultra64.h>

#define CONT_0 0
#define CONT_1 1
#define CONT_2 2
#define CONT_3 3

typedef struct Controller {
    u16 is_connected;
    u16 btns_held;
    u16 btns_pressed;
    s16 joy_x;
    s16 joy_y;
    s16 joy_ang;
    s16 joy_held; // TODO: Maybe search another name for this variable.
} Controller;

extern OSMesgQueue controllerMsgQ;
extern OSContStatus controller_status[MAXCONTROLLERS];

#endif
