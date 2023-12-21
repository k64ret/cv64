#ifndef COLOR_H
#define COLOR_H

#include <ultra64.h>

typedef struct {
    u8 R;
    u8 G;
    u8 B;
    u8 A;
} Color8;

// Needed to avoid addition of padding between variables like
// D_80383AB8's 'should_end_master_display_list' and 'fade_settings'
#pragma pack(1)
typedef union {
    u32 color_u32;
    Color8 color_u8;
} color_union;

#endif
