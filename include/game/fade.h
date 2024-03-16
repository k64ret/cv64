#ifndef FADE_H
#define FADE_H

#include <ultra64.h>

typedef enum cv64_fade_flag {
    /**
     * Shows a black outline in the edges of all models while fading
     */
    FADE_WITH_OUTLINE = 0x0001,
    FADE_IN           = 0x4000,
    FADE_OUT          = 0x8000
} cv64_fade_flag_t;

void fade_setAllFlags(s16 flags);
void fade_setFlag(s16 flag);
void fade_removeFlag(s16 flag);
void fade_setColor(u8 R, u8 G, u8 B);
void fade_setSettings(s16 flags, u16 fade_time, u8 R, u8 G, u8 B);
u32 fade_isFading(void);
void fade_calc(void);

#endif
