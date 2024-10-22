/**
 * @file fade.c
 *
 * Handles the screen fading in and out.
 */

#include "fade.h"
#include "cv64.h"
#include "system_work.h"

Gfx dl_fade_normal[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(
        G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
        G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH
    ),
    gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsDPSetPrimDepth(-1, -1),
    gsDPSetDepthSource(G_ZS_PRIM),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsSPEndDisplayList(),
};

Gfx dl_fade_with_outline[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(
        G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
        G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH
    ),
    gsDPSetRenderMode(
        IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
            GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_FOG, G_BL_A_MEM),
        IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
            GBL_c2(G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA)
    ),
    gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetPrimDepth(-1, -1),
    gsDPSetDepthSource(G_ZS_PRIM),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsSPEndDisplayList(),
};

void Fade_setAllFlags(FadeFlags flags) {
    sys.fade_flags = flags;
}

void Fade_setFlag(s16 flag) {
    BITS_SET(sys.fade_flags, flag);
}

void Fade_removeFlag(s16 flag) {
    BITS_UNSET(sys.fade_flags, flag);
}

void Fade_setColor(u8 R, u8 G, u8 B) {
    sys.fade_color.r = R;
    sys.fade_color.g = G;
    sys.fade_color.b = B;
}

void Fade_SetSettings(FadeFlags flags, u16 fade_time, u8 R, u8 G, u8 B) {
    sys.fade_flags    = flags;
    sys.fade_max_time = fade_time;

    sys.fade_current_time = BITS_HAS(flags, FADE_OUT) ? 1 : fade_time - 1;

    sys.fade_color.r = R;
    sys.fade_color.g = G;
    sys.fade_color.b = B;
}

u32 Fade_IsFading(void) {
    if (sys.fade_flags != 0) {
        if (BITS_HAS(sys.fade_flags, FADE_OUT) && (sys.fade_current_time == sys.fade_max_time)) {
            return FALSE;
        } else {
            return BITS_HAS(sys.fade_flags, FADE_IN | FADE_OUT);
        }
    }

    return FALSE;
}

// 0x8000E6C4 (Matched by anon. Original scratch:
// https://decomp.me/scratch/j0Te1)
void Fade_Calc(void) {
    f32 alpha;
    s32 flags = sys.fade_flags;

    if ((flags == 0) || !sys.fade_current_time) {
        return;
    }

    alpha = (f32) sys.fade_current_time / sys.fade_max_time;

    if (BITS_HAS(flags, FADE_OUT)) {
        if (sys.fade_current_time < sys.fade_max_time) {
            sys.fade_current_time++;
        }
    } else {
        sys.fade_current_time--;
        if (sys.fade_current_time == 0) {
            sys.fade_flags = 0;
        }
    }

    sys.fade_color.a = (s32) (alpha * 255.9999);

    if (BITS_HAS(flags, FADE_WITH_OUTLINE)) {
        gDPSetFogColor(
            gDisplayListHead++,
            sys.fade_color.r,
            sys.fade_color.g,
            sys.fade_color.b,
            sys.fade_color.a
        );
        gSPDisplayList(gDisplayListHead++, &dl_fade_with_outline);
    } else {
        gDPSetPrimColor(
            gDisplayListHead++,
            0,
            0,
            sys.fade_color.r,
            sys.fade_color.g,
            sys.fade_color.b,
            sys.fade_color.a
        );
        gSPDisplayList(gDisplayListHead++, &dl_fade_normal);
    }
}
