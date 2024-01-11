#include "fade.h"
#include "cv64.h"
#include "system_work.h"

Gfx cv64_dl_fade_normal[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
                          G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                          G_LOD | G_SHADING_SMOOTH),
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

Gfx cv64_dl_fade_with_outline[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
                          G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                          G_LOD | G_SHADING_SMOOTH),
    gsDPSetRenderMode(
        IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
            GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_FOG, G_BL_A_MEM),
        IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
            GBL_c2(G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetPrimDepth(-1, -1),
    gsDPSetDepthSource(G_ZS_PRIM),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsSPEndDisplayList(),
};

void fade_setAllFlags(s16 flags) { sys.fade_flags = flags; }

void fade_setFlag(s16 flag) { sys.fade_flags |= flag; }

void fade_removeFlag(s16 flag) { sys.fade_flags &= ~flag; }

void fade_setColor(u8 R, u8 G, u8 B) {
    sys.fade_color.R = R;
    sys.fade_color.G = G;
    sys.fade_color.B = B;
}

// The cleaner version
// void fade_setSettings(s16 flags, u16 fade_time, u8 R, u8 G, u8 B) {
//     fade_setAllFlags(flags);
//     sys.fade_max_time = fade_time;
//     sys.fade_current_time =
//         (flags & FADE_OUT) ? 1 : fade_time - 1;
//     fade_setColor(R, G, B);
// }

// The matching version
void fade_setSettings(s16 flags, u16 fade_time, u8 R, u8 G, u8 B) {
    sys.fade_flags = flags;
    sys.fade_max_time = fade_time;

    sys.fade_current_time = (flags & FADE_OUT) ? 1 : fade_time - 1;

    sys.fade_color.R = R;
    sys.fade_color.G = G;
    sys.fade_color.B = B;
}

// The cleaner version
// u32 fade_isFading() {
//     if (!sys.fade_flags ||
//         ((sys.fade_flags & FADE_OUT) &&
//          (sys.fade_current_time ==
//           sys.fade_max_time))) {
//         return FALSE;
//     }
//
//     return sys.fade_flags & (FADE_IN | FADE_OUT);
// }

// The matching version
u32 fade_isFading(void) {
    if (sys.fade_flags != 0) {
        if ((sys.fade_flags & FADE_OUT) &&
            (sys.fade_current_time == sys.fade_max_time)) {
            return FALSE;
        } else {
            return sys.fade_flags & (FADE_IN | FADE_OUT);
        }
    } else {
        return FALSE;
    }
}

// 0x8000E6C4 (Matched by anon. Original scratch:
// https://decomp.me/scratch/j0Te1)
void fade_calc() {
    f32 alpha;
    s32 flags = sys.fade_flags;

    if ((flags != 0) && (sys.fade_current_time)) {
        alpha = (f32) sys.fade_current_time / sys.fade_max_time;

        if (flags & FADE_OUT) {
            if (sys.fade_current_time < sys.fade_max_time) {
                sys.fade_current_time++;
            }
        } else {
            sys.fade_current_time--;
            if (sys.fade_current_time == 0) {
                sys.fade_flags = 0;
            }
        }

        sys.fade_color.A = (s32) (alpha * 255.9999);

        if (flags & FADE_WITH_OUTLINE) {
            gDPSetFogColor(gDisplayListHead++, sys.fade_color.R,
                           sys.fade_color.G, sys.fade_color.B,
                           sys.fade_color.A);
            gSPDisplayList(gDisplayListHead++, &cv64_dl_fade_with_outline);
        } else {
            gDPSetPrimColor(gDisplayListHead++, 0, 0, sys.fade_color.R,
                            sys.fade_color.G, sys.fade_color.B,
                            sys.fade_color.A);
            gSPDisplayList(gDisplayListHead++, &cv64_dl_fade_normal);
        }
    }
}
