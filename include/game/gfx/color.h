#ifndef COLOR_H
#define COLOR_H

#include <ultra64.h>

/**
 * RGBA color separated into 8-bit components
 */
typedef struct cv64_color_rgba {
    u8 R;
    u8 G;
    u8 B;
    u8 A;
} cv64_color_rgba_t;

/**
 * RGBA color
 */
typedef union cv64_color {
    /**
     * Packed 32-bit RGBA color
     */
    u32 color_u32;
    /**
     * 8-bit R, G, B, A color components
     */
    cv64_color_rgba_t color_u8;
} cv64_color_t;

#endif
