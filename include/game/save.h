#ifndef SAVE_H
#define SAVE_H

#include "event_flags.h"
#include <ultra64.h>

#define NUM_EVENT_FLAGS  16
#define NUM_ITEMS        41 // Total number of items, not including the white jewel
#define SIZE_ITEMS_ARRAY 64 // Size of the whole items array

#define REINHARDT 0
#define CARRIE    1

typedef struct cv64_save_state {
    u32 event_flags[NUM_EVENT_FLAGS];
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
    union {
        struct {
            s8 jewels[5];
            s8 healing[7];
            s8 subweapons[6];
            s8 quest[20];
            s8 gold[3];
            s8 field_0x41[SIZE_ITEMS_ARRAY - NUM_ITEMS]; // Probably unused
        } category;
        u8 array[SIZE_ITEMS_ARRAY];
    } items;
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
} cv64_save_state_t; // Size = 0xE0

#endif
