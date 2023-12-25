#ifndef UNKNOWN_STRUCT_2_H
#define UNKNOWN_STRUCT_2_H

#include <ultra64.h>

typedef struct {
    u32 game_loop_time;
    u32 execution_flags;
    u8 field_0x08[0x20000 - 0x08];
} unknown_struct_2;

extern unknown_struct_2 D_80363AB8;

#endif
