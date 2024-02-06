#ifndef EASY_MODE_ENDING_MSG_H
#define EASY_MODE_ENDING_MSG_H

#include "objects/menu/mfds.h"

// ID: 0x2140
typedef struct cv64_ovl_easyending {
    cv64_object_hdr_t header;
    u8 field_0x20[28];
    mfds_state* ending_textbox;
    u32 active_time;
    u8 field_0x44[48];
} cv64_ovl_easyending_t;

typedef void (*cv64_ovl_easyending_func_t)(cv64_ovl_easyending_t*);

void cv64_ovl_easyending_entrypoint(cv64_ovl_easyending_t* self);
void cv64_ovl_easyending_init(cv64_ovl_easyending_t* self);
void func_0F00018C();
void cv64_ovl_easyending_loop(cv64_ovl_easyending_t* self);
void cv64_ovl_easyending_destroy(cv64_ovl_easyending_t* self);

/*
 *   You have completed
 *   the game in EASY mode.
 *   If you want to face
 *   the challenge
 *       of more stages,
 *   try NORMAL mode.
 */
u16 cv64_ovl_easyending_msg[] = {
#include "easy_mode_ending.msg"
};

cv64_ovl_easyending_func_t cv64_ovl_easyending_funcs[] = {
    cv64_ovl_easyending_init, cv64_ovl_easyending_loop,
    cv64_ovl_easyending_destroy};

#endif // EASY_MODE_ENDING_MSG
