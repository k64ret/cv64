#ifndef COLOR_H
#define COLOR_H

#include <ultra64.h>

/**
 * RGBA color separated into 8-bit components
 */
typedef struct cv64_rgba {
    u8 R;
    u8 G;
    u8 B;
    u8 A;
} cv64_rgba_t;

#define CV64_COLOR_RGBA_TO_U32(color) *((u32*)&color)

#endif
