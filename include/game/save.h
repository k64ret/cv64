#ifndef SAVE_H
#define SAVE_H

#include "event_flags.h"
#include "item.h"
#include <ultra64.h>

#define NUM_EVENT_FLAGS  16
#define SIZE_ITEMS_ARRAY 64 // Size of the whole items array

#define REINHARDT 0
#define CARRIE    1

#define SUBWEAPON_NONE       0
#define SUBWEAPON_KNIFE      1
#define SUBWEAPON_HOLY_WATER 2
#define SUBWEAPON_CROSS      3
#define SUBWEAPON_AXE        4

typedef enum cv64_map_ID {
    MORI = 0,
    TOU = 1,
    TOUOKUJI = 2,
    NAKANIWA = 3,
    BEKKAN_1F = 4,
    BEKKAN_2F = 5,
    MEIRO_TEIEN = 6,
    CHIKA_KODO = 7,
    CHIKA_SUIRO = 8,
    HONMARU_B1F = 9,
    HONMARU_1F = 10,
    HONMARU_2F = 11,
    HONMARU_3F_MINAMI = 12,
    HONMARU_4F_MINAMI = 13,
    HONMARU_3F_KITA = 14,
    HONMARU_5F = 15,
    SHOKEI_TOU = 16,
    MAHOU_TOU = 17,
    KAGAKU_TOU = 18,
    KETTOU_TOU = 19,
    TURO_TOKEITOU = 20,
    TENSHU = 21,
    ENDING_DUMMY = 22,
    TOKEITOU_NAI = 23,
    DRACULA = 24,
    ROSE = 25,
    BEKKAN_BOSS = 26,
    TOU_TURO = 27,
    ENDING = 28,
    TEST_GRID = 29,
    NONE = -1
} cv64_map_ID_t;

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

typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    s32 field_0x34;
    s32 saveFile_errors;
    u8 field_0x3C[4];
    s16 save_crystal_number;
    u8 field_0x42[2];
    s32 field_0x44;
    void* saveGameResults; // saveGameResults*
    mfds_state* textbox;
    u8 field_0x50[36];
} saveGame;

#endif
