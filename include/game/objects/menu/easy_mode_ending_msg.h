#ifndef EASY_MODE_ENDING_MSG_H
#define EASY_MODE_ENDING_MSG_H

#include "cv64.h"
#include "object.h"
#include "objects/menu/mfds.h"
#include <ultra64.h>

typedef struct cv64_ovl_easyending {
    cv64_object_hdr_t header;
    u8 field_0x20[28];
    mfds_state* ending_textbox;
    u32 active_time;
    u8 field_0x44[48];
} cv64_ovl_easyending_t;

typedef void (*cv64_ovl_easyending_func_t)(cv64_ovl_easyending_t*);

void cv64_ovl_easyending_entrypoint(cv64_ovl_easyending_t*);
void cv64_ovl_easyending_init(cv64_ovl_easyending_t*);
void cv64_ovl_easyending_loop(cv64_ovl_easyending_t*);
void cv64_ovl_easyending_destroy(cv64_ovl_easyending_t*);

extern u16 cv64_ovl_easyending_msg[];
extern cv64_ovl_easyending_func_t cv64_ovl_easyending_funcs[];

#endif // EASY_MODE_ENDING_MSG
