#ifndef NITRO_DISPOSAL_TEXTBOX_H
#define NITRO_DISPOSAL_TEXTBOX_H

#include "actor.h"
#include "objects/menu/mfds.h"

#define NITRO_DISPOSAL_TEXTBOX_BOTTOM_ELEVATOR     0
#define NITRO_DISPOSAL_TEXTBOX_GEARS               1
#define NITRO_DISPOSAL_TEXTBOX_FRIENDLY_LIZARD_MAN 2

// ID: 0x2023
typedef struct cv64_ovl_nitrodisposaltxt {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    s32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactable;
    u32 textbox_is_active;
    u8 field_0x44[4];
    s32 has_nitro_text_ID;
    s32 no_nitro_text_ID;
    s32 nitro_amount_until_max_capacity;
    u8 field_0x54[4];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    Vec3f position;
    cv64_actor_settings_t* settings;
} cv64_ovl_nitrodisposaltxt_t;

void cv64_ovl_nitrodisposaltxt_entrypoint(cv64_ovl_nitrodisposaltxt_t* self);
void cv64_ovl_nitrodisposaltxt_init(cv64_ovl_nitrodisposaltxt_t* self);
void cv64_ovl_nitrodisposaltxt_idle(cv64_ovl_nitrodisposaltxt_t* self);
void cv64_ovl_nitrodisposaltxt_prepare_msg(cv64_ovl_nitrodisposaltxt_t* self);
void cv64_ovl_nitrodisposaltxt_yes_no(cv64_ovl_nitrodisposaltxt_t* self);
void cv64_ovl_nitrodisposaltxt_close(cv64_ovl_nitrodisposaltxt_t* self);
void cv64_ovl_nitrodisposaltxt_destroy(cv64_ovl_nitrodisposaltxt_t* self);

typedef enum cv64_ovl_nitrodisposaltxt_func_id {
    NITRO_DISPOSAL_TEXTBOX_INIT,
    NITRO_DISPOSAL_TEXTBOX_IDLE,
    NITRO_DISPOSAL_TEXTBOX_PREPARE_MESSAGE,
    NITRO_DISPOSAL_TEXTBOX_SELECT_OPTION,
    NITRO_DISPOSAL_TEXTBOX_CLOSE_TEXTBOX,
    NITRO_DISPOSAL_TEXTBOX_DESTROY
} cv64_ovl_nitrodisposaltxt_func_id_t;

typedef void (*cv64_ovl_nitrodisposaltxt_func_t)(cv64_ovl_nitrodisposaltxt_t*);

#endif
