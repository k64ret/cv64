#ifndef SAVE_H
#define SAVE_H

#include "event_flags.h"
#include <ultra64.h>

#define REINHARDT 0
#define CARRIE    1

typedef struct cv64_save_state {
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
    s16 character;
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
} cv64_save_state_t;

#endif
