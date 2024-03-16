#ifndef COLOR_H
#define COLOR_H

#include <ultra64.h>

/**
 * RGBA color separated into 8-bit components
 */
typedef union cv64_rgba {
    u32 integer;
    // u8 bytearray[4];
    struct {
        u8 r, g, b, a;
    };
} cv64_rgba_t;

#endif
