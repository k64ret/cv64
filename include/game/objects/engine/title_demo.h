#ifndef TITLE_DEMO_H
#define TITLE_DEMO_H

#include "object.h"

typedef enum cv64_ovl_titledemo_state {
    TITLE_DEMO_STATE_INIT,
    TITLE_DEMO_STATE_RUNNING,
    TITLE_DEMO_STATE_END,
    TITLE_DEMO_STATE_SKIP
} cv64_ovl_titledemo_state_t;

typedef struct cv64_ovl_titledemo_cont {
    u16 keyframe_duration;
    u16 joy_x;
    u16 joy_y;
    s16 btns_held;
    s16 btns_pressed;
} cv64_ovl_titledemo_cont_t;

// ID: 0x0019
typedef struct cv64_ovl_titledemo {
    cv64_object_hdr_t header;
    u8 field_0x20[28];
    u32 cont_data_curr_keyframe;
    u32 state;
    /**
     * In frames
     */
    u32 cont_data_curr_keyframe_duration;
    u32 cont_data_max_keyframe;
    u8 field_0x4C[24];
    /**
     * Delay time until the game starts reading controller data
     */
    u32 wait_cont;
    u8 field_0x68[OBJECT_SIZE - 0x68];
} cv64_ovl_titledemo_t;

void cv64_ovl_titledemo_entrypoint(cv64_ovl_titledemo_t* self);
void cv64_ovl_titledemo_init(cv64_ovl_titledemo_t* self);
void cv64_ovl_titledemo_loop(cv64_ovl_titledemo_t* self);
void cv64_ovl_titledemo_exit(cv64_ovl_titledemo_t* self);

typedef void (*cv64_ovl_titledemo_func_t)(cv64_ovl_titledemo_t*);

#endif
