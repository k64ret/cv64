#ifndef EXPLOSIVE_WALL_SPOT_H
#define EXPLOSIVE_WALL_SPOT_H

#include "actor.h"
#include "objects/menu/mfds.h"

#define WALL_TYPE_MAIN_MAP                0
#define WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP 1

// ID: 0x2024
typedef struct cv64_ovl_explwalltxt {
    ObjectHeader header;
    u8 field_0x20[20];
    u32 state;
    u8 field_0x38[4];
    u32 interacting_with_interactable;
    u32 textbox_is_active;
    s8 set_nitro_text_ID;
    s8 set_mandragora_text_ID;
    s8 default_description_text_ID;
    s8 item_already_set_text_ID;
    s8 nitro_set_text_ID;
    s8 mandragora_set_text_ID;
    s8 ready_for_blasting_text_ID;
    u8 field_0x4B;
    s16 nitro_amount_until_max_capacity;
    u8 field_0x4E[4];
    s16 mandragora_amount_until_max_capacity;
    s32 wall_type;
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    Vec3f position;
    ActorConfig* settings;
} cv64_ovl_explwalltxt_t;

void cv64_ovl_explwalltxt_entrypoint(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_init(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_idle(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_determine_msg(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_item_prepare_msg(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_item_idle(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_item_determine_next_txt(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_item_no(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_ready_for_blast(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_nitro_is_set(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_mandragora_is_set(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_default_desc(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_item_already_set(cv64_ovl_explwalltxt_t* self);
void cv64_ovl_explwalltxt_destroy(cv64_ovl_explwalltxt_t* self);

typedef enum cv64_ovl_explwalltxt_func_id {
    EXPLOSIVE_WALL_SPOT_INIT,
    EXPLOSIVE_WALL_SPOT_IDLE,
    EXPLOSIVE_WALL_SPOT_DETERMINE_MESSAGE,
    EXPLOSIVE_WALL_SPOT_SETITEMTEXT_PREPAREMESSAGE,
    EXPLOSIVE_WALL_SPOT_SETITEMTEXT_IDLE,
    EXPLOSIVE_WALL_SPOT_SETITEMTEXT_DETERMINENETTEXTBOX,
    EXPLOSIVE_WALL_SPOT_SETITEMTEXT_CLOSE,
    EXPLOSIVE_WALL_SPOT_READY_FOR_BLASTING,
    EXPLOSIVE_WALL_SPOT_NITRO_IS_SET,
    EXPLOSIVE_WALL_SPOT_MANDRAGORA_IS_SET,
    EXPLOSIVE_WALL_SPOT_ITEM_ALREADY_SET,
    EXPLOSIVE_WALL_SPOT_DEFAULT_DESCRIPTION,
    EXPLOSIVE_WALL_SPOT_DESTROY
} cv64_ovl_explwalltxt_func_id_t;

typedef void (*cv64_ovl_explwalltxt_func_t)(cv64_ovl_explwalltxt_t*);

#endif
