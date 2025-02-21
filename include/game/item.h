#ifndef ITEM_H
#define ITEM_H

#include "objects/menu/mfds.h"

#define NUM_ITEMS 41 // Total number of items, not including the white jewel

// TODO: Item IDs defines / enum

#define ITEM_MODEL_SETTINGS_FLAG_SPINS                 0x01
#define ITEM_MODEL_SETTINGS_FLAG_APPEARS_IN_RENON_SHOP 0x40

extern const u32 ITEM_MATERIAL_DL;

typedef struct {
    u32 dlist;
    f32 size;
    u8 texture;
    u8 palette;
    u8 transparency;
    u8 field_0x0B;
    u8 item_ID;
    u8 flags;
    u8 field_0x0E;
    u8 field_0x0F;
} item_model_settings;

typedef enum cv64_item_kind {
    ITEM_KIND_ITEM      = 1,
    ITEM_KIND_TEXT_SPOT = 2
} cv64_item_kind_t;

typedef enum cv64_item_id {
    ITEM_ID_NOTHING           = 0,
    ITEM_ID_WHITE_JEWEL       = 1,
    ITEM_ID_RED_JEWEL_S       = 2,
    ITEM_ID_RED_JEWEL_L       = 3,
    ITEM_ID_SPECIAL1          = 4,
    ITEM_ID_SPECIAL2          = 5,
    ITEM_ID_ROAST_CHICKEN     = 6,
    ITEM_ID_ROAST_BEEF        = 7,
    ITEM_ID_HEALING_KIT       = 8,
    ITEM_ID_PURIFYING         = 9,
    ITEM_ID_CURE_AMPOULE      = 10,
    ITEM_ID_POUT_POURRI       = 11, // Unused
    ITEM_ID_POWERUP           = 12,
    ITEM_ID_KNIFE             = 13,
    ITEM_ID_HOLY_WATER        = 14,
    ITEM_ID_CROSS             = 15,
    ITEM_ID_AXE               = 16,
    ITEM_ID_WOODEN_STAKE      = 17, // Unused
    ITEM_ID_ROSE              = 18, // Unused
    ITEM_ID_THE_CONTRACT      = 19,
    ITEM_ID_ENGAGEMENT_RING   = 20, // Unused
    ITEM_ID_MAGICAL_NITRO     = 21,
    ITEM_ID_MANDRAGORA        = 22,
    ITEM_ID_SUN_CARD          = 23,
    ITEM_ID_MOON_CARD         = 24,
    ITEM_ID_INCANDESCENT_GAZE = 25, // Unused
    ITEM_ID_ARCHIVES_KEY      = 26,
    ITEM_ID_LEFT_TOWER_KEY    = 27,
    ITEM_ID_STOREROOM_KEY     = 28,
    ITEM_ID_GARDEN_KEY        = 29,
    ITEM_ID_COPPER_KEY        = 30,
    ITEM_ID_CHAMBER_KEY       = 31,
    ITEM_ID_EXECUTION_KEY     = 32,
    ITEM_ID_SCIENCE_KEY1      = 33,
    ITEM_ID_SCIENCE_KEY2      = 34,
    ITEM_ID_SCIENCE_KEY3      = 35,
    ITEM_ID_CLOCKTOWER_KEY1   = 36,
    ITEM_ID_CLOCKTOWER_KEY2   = 37,
    ITEM_ID_CLOCKTOWER_KEY3   = 38,
    ITEM_ID_GOLD_500          = 39,
    ITEM_ID_GOLD_300          = 40,
    ITEM_ID_GOLD_100          = 41
} cv64_item_id_t;

extern Model* createItemModel(s32 item_ID, Camera* display_camera, const char* name);
extern s8 item_addAmountToInventory(s32 item, s32 amount);
extern s8 item_removeAmountFromInventory(s32 item, s32 amount);
extern s8 item_getAmountUntilMaxCapacity(s32 item);
extern MfdsState* gameplayCommonTextbox_addItemAndPrepareName(s32 item);
extern item_model_settings* itemModelSettings_getEntryFromList(s32 item);

extern item_model_settings item_model_settings_list[NUM_ITEMS];

#endif
