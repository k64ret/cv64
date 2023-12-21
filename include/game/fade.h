#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "gfx/color.h"
#include <ultra64.h>

// clang-format off
typedef enum fade_flag {
    FADE_WITH_OUTLINE = 0x0001, // Shows a black outline in the edges of all models while fading
    FADE_IN           = 0x4000,
    FADE_OUT          = 0x8000
} fade_flag_t;
// clang-format on

typedef struct fade_settings {
    s16 flags;
    color_union color;
    u16 current_time;
    u16 max_time;
} fade_settings_t;

#endif
