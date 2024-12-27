#ifndef PICKABLE_ITEM_FLASH_H
#define PICKABLE_ITEM_FLASH_H

#include "effect.h"
#include "object.h"

// ID: 0x00E5
typedef struct pickableItemFlash {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[7];
    u8 textbox_option;
    u8 field_0x30[60];
    EffectVisualInfo* visual_info;
    ActorConfig* settings;
} pickableItemFlash;

void pickableItemFlash_entrypoint(pickableItemFlash* self);
void pickableItemFlash_init(pickableItemFlash* self);
void pickableItemFlash_loop(pickableItemFlash* self);
void pickableItemFlash_destroy(pickableItemFlash* self);

typedef void (*cv64_pickableItemFlash_func_t)(pickableItemFlash*);

#endif
