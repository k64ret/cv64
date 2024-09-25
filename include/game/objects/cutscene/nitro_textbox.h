#ifndef NITRO_TEXTBOX_H
#define NITRO_TEXTBOX_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x2022
typedef struct cv64_ovl_nitrotxt {
    ObjectHeader header;
    u8 field_0x20[20];
    s32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactable;
    u32 textbox_is_active;
    u8 field_0x44[8];
    s32 mandragora_amount_until_max_capacity;
    s32 nitro_amount_until_max_capacity;
    u32 message_display_time;
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    Vec3f position;
    ActorConfig* settings;
} cv64_ovl_nitrotxt_t;

void cv64_ovl_nitrotxt_entrypoint(cv64_ovl_nitrotxt_t* self);
void cv64_ovl_nitrotxt_init(cv64_ovl_nitrotxt_t* self);
void cv64_ovl_nitrotxt_idle(cv64_ovl_nitrotxt_t* self);
void cv64_ovl_nitrotxt_prepare_msg(cv64_ovl_nitrotxt_t* self);
void cv64_ovl_nitrotxt_yes_no(cv64_ovl_nitrotxt_t* self);
void cv64_ovl_nitrotxt_close(cv64_ovl_nitrotxt_t* self);
void cv64_ovl_nitrotxt_destroy(cv64_ovl_nitrotxt_t* self);

typedef enum cv64_ovl_nitrotxt_func_id {
    NITRO_TEXTBOX_INIT,
    NITRO_TEXTBOX_IDLE,
    NITRO_TEXTBOX_PREPARE_MESSAGE,
    NITRO_TEXTBOX_SELECT_OPTION,
    NITRO_TEXTBOX_CLOSE_TEXTBOX,
    NITRO_TEXTBOX_DESTROY
} cv64_ovl_nitrotxt_func_id_t;

typedef void (*cv64_ovl_nitrotxt_func_t)(cv64_ovl_nitrotxt_t*);

#endif
