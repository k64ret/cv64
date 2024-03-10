#ifndef ITEM_H
#define ITEM_H

#include <ultra64.h>

#define NUM_ITEMS 41 // Total number of items, not including the white jewel

// TODO: Item IDs defines / enum

#define ITEM_MODEL_SETTINGS_FLAG_SPINS                 0x01
#define ITEM_MODEL_SETTINGS_FLAG_APPEARS_IN_RENON_SHOP 0x40

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

extern s8 item_addAmountToInventory(s32 item, s32 amount);
extern s8 item_removeAmountFromInventory(s32 item, s32 amount);
extern item_model_settings* itemModelSettings_getEntryFromList(s32 item);

extern item_model_settings item_model_settings_list[NUM_ITEMS];

#endif
