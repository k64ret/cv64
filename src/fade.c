#include "cv64.h"
#include <ultra64.h>

typedef struct {
    u8 R;
    u8 G;
    u8 B;
    u8 A;
} Color8;

// Needed to avoid addition of padding between variables like
// D_80383AB8's 'should_end_master_display_list' and 'fade_settings'
#pragma pack(1)
typedef union {
    u32 color_u32;
    Color8 color_u8;
} color_union;

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

typedef struct controller_state {
    u16 is_connected;
    u16 buttons_held;
    u16 buttons_pressed;
    s16 joystick_x;
    s16 joystick_y;
    s16 joystick_angle;
    s16 joystick_held; // TODO: Maybe search another name for this variable.
} controller_state_t;

typedef struct save_state {
    u32 event_flags[16];
    u32 flags;
    u16 week;
    u16 day;
    u16 hour;
    u16 minute;
    u16 seconds;
    u16 milliseconds;        // Assumption.
    u32 gameplay_framecount; // Updates at 60fps
    s16 button_config;
    s16 sound_mode;
    u16 character;
    u16 life;
    u16 field13_0x5c; // Maybe related to the scrapped Magic meter?
    u16 subweapon;
    u32 money;
    u8 inventory_items_amount[42];
    u8 field22_0x8e;
    u8 field23_0x8f;
    u8 field24_0x90;
    u8 field25_0x91;
    u8 field26_0x92;
    u8 field27_0x93;
    u8 field28_0x94;
    u8 field29_0x95;
    u8 field30_0x96;
    u8 field31_0x97;
    u8 field32_0x98;
    u8 field33_0x99;
    u8 field34_0x9a;
    u8 field35_0x9b;
    u8 field36_0x9c;
    u8 field37_0x9d;
    u8 field38_0x9e;
    u8 field39_0x9f;
    u8 field40_0xa0;
    u8 field41_0xa1;
    u8 field42_0xa2;
    u8 field43_0xa3;
    u32 player_status;
    u16 health_depletion_rate_while_poisoned;
    u16 current_hour_VAMP; // If greater than 24, you turn into vampire
    s16 map_ID;
    s16 map_entrance_ID;
    u8 save_crystal_number;
    u8 field50_0xb1;
    u8 field51_0xb2;
    u8 field52_0xb3;
    u32 time_saved_counter;
    u32 death_counter;
    s32 field55_0xbc;
    s32 field59_0xc0;
    s32 field63_0xc4;
    s16 field67_0xc8;
    s16 field69_0xca;
    s32 field71_0xcc;
    s32 field75_0xd0;
    s16 field77_0xd2;
    s16 field79_0xd4;
    s32 field83_0xd8;
    u32 money_spent_on_Renon;
} save_state_t;

typedef struct {
    u8 unk1[0x4010];
    color_union background_color;
    s16 should_setup_background_color;
    s16 should_setup_Z_buffer;
    s16 code_execution_max_delay;
    s16 code_execution_delay_timer;
    s16 should_end_master_display_list;
    fade_settings_t fade_settings;
    u8 unk2[0x29C];
    controller_state_t controllers[4];
    u8 file_load_array_ID;
    u8 field_80387db5[3];
    void *Nisitenma_Ichigo_loaded_files_ptr[0x255];
    u8 field_803881b4[4];
    void *file_load_array[8]; // fileLoad*
    u8 unk3[0x1A0C];
    save_state_t SaveStruct_gameplay; // 80389be4
    u8 unk4[0x28];
    s16 current_PowerUp_level; // 80389cec
    u8 unk5[0x18C];
    s16 field25313_0x63c0; // 80389e78
    u8 field25315_0x63c2;
    u8 field25316_0x63c3;
    u8 field25317_0x63c4;
    u8 field25318_0x63c5;
    u8 field25319_0x63c6;
    u8 field25320_0x63c7;
    u8 field25321_0x63c8;
    u8 field25322_0x63c9;
    u8 field25323_0x63ca;
    u8 field25324_0x63cb;
    u8 field25325_0x63cc;
    u8 field25326_0x63cd;
    u8 field25327_0x63ce;
    u8 field25328_0x63cf;
    u8 field25329_0x63d0;
    u8 field25330_0x63d1;
    u8 field25331_0x63d2;
    u8 field25332_0x63d3;
    u8 field25333_0x63d4;
    u8 field25334_0x63d5;
    u8 field25335_0x63d6;
    u8 field25336_0x63d7;
    u8 field25337_0x63d8;
    u8 field25338_0x63d9;
    u8 field25339_0x63da;
    u8 field25340_0x63db;
    u8 field25341_0x63dc;
    u8 field25342_0x63dd;
    u8 field25343_0x63de;
    u8 field25344_0x63df;
    u8 field25345_0x63e0;
    u8 field25346_0x63e1;
    u8 field25347_0x63e2;
    u8 field25348_0x63e3;
    u8 field25349_0x63e4;
    u8 field25350_0x63e5;
    u8 field25351_0x63e6;
    u8 field25352_0x63e7;
    u8 field25353_0x63e8;
    u8 field25354_0x63e9;
    u8 field25355_0x63ea;
    u8 field25356_0x63eb;
    u8 field25357_0x63ec;
    u8 field25358_0x63ed;
    u8 field25359_0x63ee;
    u8 field25360_0x63ef;
    u8 field25361_0x63f0;
    u8 field25362_0x63f1;
    u8 field25363_0x63f2;
    u8 field25364_0x63f3;
    u8 field25365_0x63f4;
    u8 field25366_0x63f5;
    u8 field25367_0x63f6;
    u8 field25368_0x63f7;
    u8 field25369_0x63f8;
    u8 field25370_0x63f9;
    u8 field25371_0x63fa;
    u8 field25372_0x63fb;
    u8 field25373_0x63fc;
    u8 field25374_0x63fd;
    u8 field25375_0x63fe;
    u8 field25376_0x63ff;
    u8 field25377_0x6400;
    u8 field25378_0x6401;
    u8 field25379_0x6402;
    u8 field25380_0x6403;
    u8 field25381_0x6404;
    u8 field25382_0x6405;
    u8 field25383_0x6406;
    u8 field25384_0x6407;
    u8 field25385_0x6408;
    u8 field25386_0x6409;
    u8 field25387_0x640a;
    u8 field25388_0x640b;
    u8 field25389_0x640c;
    u8 field25390_0x640d;
    u8 field25391_0x640e;
    u8 field25392_0x640f;
    u8 field25393_0x6410;
    u8 field25394_0x6411;
    u8 field25395_0x6412;
    u8 field25396_0x6413;
    u8 field25397_0x6414;
    u8 field25398_0x6415;
    u8 field25399_0x6416;
    u8 field25400_0x6417;
    u8 field25401_0x6418;
    u8 field25402_0x6419;
    u8 field25403_0x641a;
    u8 field25404_0x641b;
    u8 field25405_0x641c;
    u8 field25406_0x641d;
    u8 field25407_0x641e;
    u8 field25408_0x641f;
    u8 field25409_0x6420;
    u8 field25410_0x6421;
    u8 field25411_0x6422;
    u8 field25412_0x6423;
    u8 field25413_0x6424;
    u8 field25414_0x6425;
    u8 field25415_0x6426;
    u8 field25416_0x6427;
    s16 map_ID; // 80389ee0
    s16 map_entrance_ID;
    color_union map_fade_in_color; // 80389ee4
    s16 map_fade_out_time;         // 80389ee8
    s16 map_fade_in_time;
    u16 field25429_0x6434;
    u16 current_opened_menu;
    u8 field25433_0x6438[4];
    s32 cutscene_ID;
    s32 entrance_cutscene_ID; // 80389efc
    u32 cutscene_flags;
    s32 field25453_0x644c; // 80389f04
    u8 field25457_0x6450;
    u8 field25458_0x6451;
    u8 field25459_0x6452;
    u8 field25460_0x6453;
    u8 field25461_0x6454;
    u8 field25462_0x6455;
    u8 field25463_0x6456;
    u8 unk[0x19BA8];
} unknown_struct;

extern unknown_struct D_80383AB8;
// extern Gfx *gDisplayListHead;

// Gfx DL_fade_normal[] = {
//     gsDPPipeSync(),
//     gsDPSetCycleType(G_CYC_1CYCLE),
//     gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
//                           G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
//                           G_LOD | G_SHADING_SMOOTH),
//     gsDPSetRenderMode(G_RM_CLD_SURF, G_RM_CLD_SURF2),
//     gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
//     gsDPSetPrimDepth(-1, -1),
//     gsDPSetDepthSource(G_ZS_PRIM),
//     gsDPSetAlphaCompare(G_AC_NONE),
//     gsDPSetColorDither(G_CD_MAGICSQ),
//     gsDPSetAlphaDither(G_AD_NOISE),
//     gsDPFillRectangle(0, 0, 319, 239),
//     gsSPEndDisplayList(),
// };

// Gfx DL_fade_with_outline[] = {
//     gsDPPipeSync(),
//     gsDPSetCycleType(G_CYC_2CYCLE),
//     gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
//                           G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
//                           G_LOD | G_SHADING_SMOOTH),
//     gsDPSetRenderMode(
//         IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
//             GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_FOG, G_BL_A_MEM),
//         IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL |
//             GBL_c2(G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA)),
//     gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
//     gsDPSetPrimDepth(-1, -1),
//     gsDPSetDepthSource(G_ZS_PRIM),
//     gsDPSetAlphaCompare(G_AC_NONE),
//     gsDPSetColorDither(G_CD_MAGICSQ),
//     gsDPSetAlphaDither(G_AD_NOISE),
//     gsDPFillRectangle(0, 0, 319, 239),
//     gsSPEndDisplayList(),
// };

void fade_setAllFlags(s16 flags) { D_80383AB8.fade_settings.flags = flags; }

void fade_setFlag(s16 flag) { D_80383AB8.fade_settings.flags |= flag; }

void fade_removeFlag(s16 flag) { D_80383AB8.fade_settings.flags &= ~flag; }

void fade_setColor(u8 R, u8 G, u8 B) {
    D_80383AB8.fade_settings.color.color_u8.R = R;
    D_80383AB8.fade_settings.color.color_u8.G = G;
    D_80383AB8.fade_settings.color.color_u8.B = B;
}

void fade_setSettings(s16 flags, u16 fade_time, u8 R, u8 G, u8 B) {
    D_80383AB8.fade_settings.flags = flags;
    D_80383AB8.fade_settings.max_time = fade_time;

    if (flags & FADE_OUT) {
        D_80383AB8.fade_settings.current_time = 1;
    } else {
        D_80383AB8.fade_settings.current_time = fade_time - 1;
    }

    D_80383AB8.fade_settings.color.color_u8.R = R;
    D_80383AB8.fade_settings.color.color_u8.G = G;
    D_80383AB8.fade_settings.color.color_u8.B = B;
}

// The cleaner version
// u32 fade_isFading() {
//     if (!D_80383AB8.fade_settings.flags ||
//         ((D_80383AB8.fade_settings.flags & FADE_OUT) &&
//          (D_80383AB8.fade_settings.current_time ==
//           D_80383AB8.fade_settings.max_time))) {
//         return FALSE;
//     }
//
//     return D_80383AB8.fade_settings.flags & (FADE_IN | FADE_OUT);
// }

// The matching version
u32 fade_isFading() {
    if (D_80383AB8.fade_settings.flags != 0) {
        if ((D_80383AB8.fade_settings.flags & FADE_OUT) &&
            (D_80383AB8.fade_settings.current_time ==
             D_80383AB8.fade_settings.max_time)) {
            return FALSE;
        } else {
            return D_80383AB8.fade_settings.flags & (FADE_IN | FADE_OUT);
        }
    } else {
        return FALSE;
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/fade/fade_calc.s")

// 0x8000E6C4 (Matched by anon. Original scratch:
// https://decomp.me/scratch/j0Te1)

// void fade_calc() {
//     f32 alpha;
//     s32 flags = D_80383AB8.fade_settings.flags;
//
//     if ((flags != 0) && (D_80383AB8.fade_settings.current_time)) {
//         alpha = (f32)D_80383AB8.fade_settings.current_time /
//                 D_80383AB8.fade_settings.max_time;
//
//         if (flags & FADE_OUT) {
//             if (D_80383AB8.fade_settings.current_time <
//                 D_80383AB8.fade_settings.max_time) {
//                 D_80383AB8.fade_settings.current_time++;
//             }
//         } else {
//             D_80383AB8.fade_settings.current_time--;
//             if (D_80383AB8.fade_settings.current_time == 0) {
//                 D_80383AB8.fade_settings.flags = 0;
//             }
//         }
//
//         D_80383AB8.fade_settings.color.color_u8.A = (s32)(alpha * 255.9999);
//
//         if (flags & FADE_WITH_OUTLINE) {
//             gDPSetFogColor(gDisplayListHead++,
//                            D_80383AB8.fade_settings.color.color_u8.R,
//                            D_80383AB8.fade_settings.color.color_u8.G,
//                            D_80383AB8.fade_settings.color.color_u8.B,
//                            D_80383AB8.fade_settings.color.color_u8.A);
//             gSPDisplayList(gDisplayListHead++, &DL_fade_with_outline);
//         } else {
//             gDPSetPrimColor(gDisplayListHead++, 0, 0,
//                             D_80383AB8.fade_settings.color.color_u8.R,
//                             D_80383AB8.fade_settings.color.color_u8.G,
//                             D_80383AB8.fade_settings.color.color_u8.B,
//                             D_80383AB8.fade_settings.color.color_u8.A);
//             gSPDisplayList(gDisplayListHead++, &DL_fade_normal);
//         }
//     }
// }
