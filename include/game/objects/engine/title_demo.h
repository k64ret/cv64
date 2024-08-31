#ifndef TITLE_DEMO_H
#define TITLE_DEMO_H

#include "object.h"

typedef enum titleDemo_state {
    TITLE_DEMO_STATE_INIT,
    TITLE_DEMO_STATE_RUNNING,
    TITLE_DEMO_STATE_END,
    TITLE_DEMO_STATE_SKIP
} titleDemo_state_t;

typedef struct {
    u16 keyframe_duration;
    u16 stick_X;
    u16 stick_Y;
    s16 buttons_held;
    s16 buttons_pressed;
} titleDemo_controller;

// ID: 0x0019
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    u32 field_0x34;
    u32 field_0x38;
    u32 controller_data_current_keyframe;
    u32 state;
    u32 controller_data_current_keyframe_duration; // In frames
    u32 controller_data_max_keyframe;
    u8 field_0x4C[24];
    u32 wait_cont; // Delay time until start reading controller data
    u8 field_0x68[OBJECT_SIZE - 0x68];
} titleDemo;

void titleDemo_entrypoint(titleDemo* self);
void titleDemo_init(titleDemo* self);
void titleDemo_loop(titleDemo* self);
void titleDemo_exit(titleDemo* self);

typedef void (*titleDemo_func_t)(titleDemo*);

#endif
