#ifndef NITRO_DISPOSAL_TEXTBOX_H
#define NITRO_DISPOSAL_TEXTBOX_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x2023
typedef struct cv64_ovl_nitrodisposaltextbox {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    u32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 field_0x44[4];
    u32 has_nitro_text_ID;
    u32 no_nitro_text_ID;
    u32 nitro_amount_until_max_capacity;
    u8 field_0x54[4];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} cv64_ovl_nitrodisposaltextbox_t;

void cv64_ovl_nitrodisposaltextbox_entrypoint(cv64_ovl_nitrodisposaltextbox_t* self);
void cv64_ovl_nitrodisposaltextbox_init(cv64_ovl_nitrodisposaltextbox_t* self);
void cv64_ovl_nitrodisposaltextbox_idle(cv64_ovl_nitrodisposaltextbox_t* self);
void cv64_ovl_nitrodisposaltextbox_prep_msg(cv64_ovl_nitrodisposaltextbox_t* self);
void cv64_ovl_nitrodisposaltextbox_yes_no(cv64_ovl_nitrodisposaltextbox_t* self);
void cv64_ovl_nitrodisposaltextbox_close(cv64_ovl_nitrodisposaltextbox_t* self);
void cv64_ovl_nitrodisposaltextbox_destroy(cv64_ovl_nitrodisposaltextbox_t* self);

typedef enum cv64_ovl_nitrodisposaltextbox_func_id {
    NITRO_DISPOSAL_TEXTBOX_INIT,
    NITRO_DISPOSAL_TEXTBOX_IDLE,
    NITRO_DISPOSAL_TEXTBOX_PREPARE_MESSAGE,
    NITRO_DISPOSAL_TEXTBOX_SELECT_OPTION,
    NITRO_DISPOSAL_TEXTBOX_CLOSE_TEXTBOX,
    NITRO_DISPOSAL_TEXTBOX_DESTROY
} cv64_ovl_nitrodisposaltextbox_func_id_t;

typedef void (*cv64_ovl_nitrodisposaltextbox_func_t)(cv64_ovl_nitrodisposaltextbox_t*);

#endif
