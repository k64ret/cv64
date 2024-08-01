#ifndef MANDRAGORA_TEXTBOX_H
#define MANDRAGORA_TEXTBOX_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x2021
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    union {
        u32 text_ID_s32;
        struct {
            u16 field_0x34;
            u16 text_ID_u16;
        };
    };
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 field_0x44[8];
    u32 nitro_amount_until_max_capacity;
    u32 mandragora_amount_until_max_capacity;
    u8 field_0x54[4];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} mandragoraTextbox;

void mandragoraTextbox_entrypoint(mandragoraTextbox* self);
void mandragoraTextbox_init(mandragoraTextbox* self);
void mandragoraTextbox_idle(mandragoraTextbox* self);
void mandragoraTextbox_prepareMessage(mandragoraTextbox* self);
void mandragoraTextbox_selectOption(mandragoraTextbox* self);
void mandragoraTextbox_closeTextbox(mandragoraTextbox* self);
void mandragoraTextbox_destroy(mandragoraTextbox* self);
s32 mandragoraIsPlacedInWall();

#endif
