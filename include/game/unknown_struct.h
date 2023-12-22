#ifndef UNKNOWN_STRUCT_H
#define UNKNOWN_STRUCT_H

#include "controller.h"
#include "fade.h"
#include "gfx/color.h"
#include "save.h"
#include <ultra64.h>

typedef struct {
    u8 unk1[0x4010];
    cv64_color_t background_color;
    s16 should_setup_background_color;
    s16 should_setup_Z_buffer;
    s16 code_execution_max_delay;
    s16 code_execution_delay_timer;
    s16 should_end_master_display_list;
    cv64_fade_settings_t fade_settings;
    u8 unk2[0x29C];
    cv64_controller_state_t controllers[4];
    u8 file_load_array_ID;
    u8 field_80387db5[3];
    void* Nisitenma_Ichigo_loaded_files_ptr[0x255];
    u8 field_803881b4[4];
    void* file_load_array[8]; // fileLoad*
    u8 unk3[0x1A0C];
    cv64_save_state_t SaveStruct_gameplay; // 80389be4
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
    cv64_color_t map_fade_in_color; // 80389ee4
    s16 map_fade_out_time;          // 80389ee8
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

#endif
