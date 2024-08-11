#ifndef MANDRAGORA_TEXTBOX_H
#define MANDRAGORA_TEXTBOX_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x2021
typedef struct cv64_ovl_mandragoratextbox {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    s32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 field_0x44[8];
    s32 nitro_amount_until_max_capacity;
    s32 mandragora_amount_until_max_capacity;
    u8 field_0x54[4];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} cv64_ovl_mandragoratextbox_t;

void cv64_ovl_mandragoratextbox_entrypoint(cv64_ovl_mandragoratextbox_t* self);
void cv64_ovl_mandragoratextbox_init(cv64_ovl_mandragoratextbox_t* self);
void cv64_ovl_mandragoratextbox_idle(cv64_ovl_mandragoratextbox_t* self);
void cv64_ovl_mandragoratextbox_prep_msg(cv64_ovl_mandragoratextbox_t* self);
void cv64_ovl_mandragoratextbox_yes_no(cv64_ovl_mandragoratextbox_t* self);
void cv64_ovl_mandragoratextbox_close(cv64_ovl_mandragoratextbox_t* self);
void cv64_ovl_mandragoratextbox_destroy(cv64_ovl_mandragoratextbox_t* self);

typedef enum cv64_ovl_mandragoratextbox_func_id {
    MANDRAGORA_TEXTBOX_INIT,
    MANDRAGORA_TEXTBOX_IDLE,
    MANDRAGORA_TEXTBOX_PREPARE_MESSAGE,
    MANDRAGORA_TEXTBOX_SELECT_OPTION,
    MANDRAGORA_TEXTBOX_CLOSE_TEXTBOX,
    MANDRAGORA_TEXTBOX_DESTROY
} cv64_ovl_mandragoratextbox_func_id_t;

typedef void (*cv64_ovl_mandragoratextbox_func_t)(cv64_ovl_mandragoratextbox_t*);

#endif
