#ifndef ENTRANCE_MAP_NAME_DISPLAY_H
#define ENTRANCE_MAP_NAME_DISPLAY_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x213A
typedef struct entranceMapNameDisplay {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* bg_model;
    u8 field_0x28[16];
    s32 bg_model_transparency;
    Vec2f text_position_offset;
    u8 field_0x44[4];
    s32 max_active_time;
    s32 current_active_time;
    s32 text_not_active;
    MfdsState* textbox;
    s32 disable_text;
    s32 field_0x5C;
    s32 text_ID;
    u8 field_0x64[12];
    ActorConfig* settings;
} entranceMapNameDisplay;

void entranceMapNameDisplay_entrypoint(entranceMapNameDisplay* self);
void entranceMapNameDisplay_init(entranceMapNameDisplay* self);
void entranceMapNameDisplay_display(entranceMapNameDisplay* self);
void entranceMapNameDisplay_loop(entranceMapNameDisplay* self);
void entranceMapNameDisplay_hide(entranceMapNameDisplay* self);
void entranceMapNameDisplay_destroy(entranceMapNameDisplay* self);

typedef void (*entranceMapNameDisplayFuncs)(entranceMapNameDisplay*);

#endif
