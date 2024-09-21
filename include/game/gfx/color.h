#ifndef COLOR_H
#define COLOR_H

#include <ultra64.h>

#define RGBA(r, g, b, a) (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))

/**
 * RGBA color separated into 8-bit components
 */
typedef union RGBA {
    u32 integer;
    // u8 bytearray[4];
    struct {
        u8 r, g, b, a;
    };
} RGBA;

#endif
