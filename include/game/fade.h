#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "gfx/color.h"
#include <ultra64.h>

/*
 * Needed to avoid addition of padding between variables like
 * D_80383AB8's 'should_end_master_display_list' and 'fade_settings'
 *
 * This needs to be removed soon so that we don't pollute other areas
 * of the code that do not need this.
 */
#pragma pack(1)

// clang-format off
typedef enum cv64_fade_flag {
    FADE_WITH_OUTLINE = 0x0001, // Shows a black outline in the edges of all models while fading
    FADE_IN           = 0x4000,
    FADE_OUT          = 0x8000
} cv64_fade_flag_t;
// clang-format on

typedef struct cv64_fade_settings {
    s16 flags;
    cv64_color_t color;
    u16 current_time;
    u16 max_time;
} cv64_fade_settings_t;

#pragma pack()

#endif
