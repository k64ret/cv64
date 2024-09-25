#ifndef SAVE_H
#define SAVE_H

#include "event_flags.h"
#include "item.h"
#include <ultra64.h>

#define NUM_EVENT_FLAGS  16
#define SIZE_ITEMS_ARRAY 64 // Size of the whole items array

enum PlayerCharacterID {
    REINHARDT = 0,
    CARRIE    = 1
};

enum SubweaponID {
    SUBWEAPON_NONE       = 0,
    SUBWEAPON_KNIFE      = 1,
    SUBWEAPON_HOLY_WATER = 2,
    SUBWEAPON_CROSS      = 3,
    SUBWEAPON_AXE        = 4
};

typedef enum MapID {
    MORI              = 0,
    TOU               = 1,
    TOUOKUJI          = 2,
    NAKANIWA          = 3,
    BEKKAN_1F         = 4,
    BEKKAN_2F         = 5,
    MEIRO_TEIEN       = 6,
    CHIKA_KODO        = 7,
    CHIKA_SUIRO       = 8,
    HONMARU_B1F       = 9,
    HONMARU_1F        = 10,
    HONMARU_2F        = 11,
    HONMARU_3F_MINAMI = 12,
    HONMARU_4F_MINAMI = 13,
    HONMARU_3F_KITA   = 14,
    HONMARU_5F        = 15,
    SHOKEI_TOU        = 16,
    MAHOU_TOU         = 17,
    KAGAKU_TOU        = 18,
    KETTOU_TOU        = 19,
    TURO_TOKEITOU     = 20,
    TENSHU            = 21,
    ENDING_DUMMY      = 22,
    TOKEITOU_NAI      = 23,
    DRACULA           = 24,
    ROSE              = 25,
    BEKKAN_BOSS       = 26,
    TOU_TURO          = 27,
    ENDING            = 28,
    TEST_GRID         = 29,
    NONE              = -1
} MapID;

enum SaveFlag {
    SAVE_FLAG_GAME_WAS_SAVED_MID_PLAY    = BIT(0),
    SAVE_FLAG_EASY                       = BIT(4),
    SAVE_FLAG_NORMAL                     = BIT(5),
    SAVE_FLAG_HARD                       = BIT(6),
    SAVE_FLAG_HARD_MODE_UNLOCKED         = BIT(8),
    SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME = BIT(9),
    SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME    = BIT(10),
    SAVE_FLAG_REINDHART_GOOD_ENDING      = BIT(17),
    SAVE_FLAG_CARRIE_GOOD_ENDING         = BIT(18),
    SAVE_FLAG_REINDHART_BAD_ENDING       = BIT(19),
    SAVE_FLAG_CARRIE_BAD_ENDING          = BIT(20),
    SAVE_FLAG_COSTUME_IS_BEING_USED      = BIT(30),
    SAVE_FLAG_CAN_EXPLODE_ON_JUMPING     = BIT(31)
};

/**
 * Accepts values from `SaveFlag` OR'ed together
 */
typedef u32 SaveFlags;

typedef struct SaveData {
    u32 event_flags[NUM_EVENT_FLAGS];
    SaveFlags flags;
    s16 week;
    s16 day;
    s16 hour;
    s16 minute;
    s16 seconds;
    u16 milliseconds;        // Assumption.
    u32 gameplay_framecount; // Updates at 60fps
    s16 button_config;
    s16 sound_mode;
    s16 character;
    s16 life;
    /**
     * Only set to 100, like the life, and never used otherwise.
     * Maybe related to the scrapped S / E meter?
     */
    s16 field_0x5C;
    s16 subweapon;
    u32 gold;
    union {
        struct {
            s8 jewels[5];
            s8 healing[7];
            s8 subweapons[6];
            s8 quest[20];
            s8 gold[3];
            s8 field_0x41[SIZE_ITEMS_ARRAY - NUM_ITEMS]; // Probably unused
        } category;
        s8 array[SIZE_ITEMS_ARRAY];
    } items;
    u32 player_status;
    s16 health_depletion_rate_while_poisoned; // TODO: Double check
    /**
    * If greater than 24 (midnight), the player turns into a vampire
    */
    u16 current_hour_VAMP;
    s16 map;
    s16 spawn;
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
    u32 gold_spent_on_Renon;
} SaveData; // Size = 0xE0

#endif
