#ifndef FADE_H
#define FADE_H

#include "bit.h"
#include <ultra64.h>

enum FadeFlag {
    /**
     * Shows a black outline in the edges of all models while fading
     */
    FADE_WITH_OUTLINE = BIT(0),
    FADE_IN           = BIT(14),
    FADE_OUT          = BIT(15)
};

/**
 * Variables with this type can accept values from `FadeFlag` OR'ed together
 */
typedef s16 FadeFlags;

void Fade_SetSettings(FadeFlags flags, u16 fade_time, u8 R, u8 G, u8 B);
u32 Fade_IsFading(void);
void Fade_Calc(void);

#endif
