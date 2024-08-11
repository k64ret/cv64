#ifndef EXPLOSIVE_WALL_SPOT_H
#define EXPLOSIVE_WALL_SPOT_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x2024
typedef struct explosiveWallTextbox {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    u32 state;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 set_nitro_text_ID;
    u8 set_mandragora_text_ID;
    u8 default_description_text_ID;
    u8 item_already_set_text_ID;
    u8 nitro_set_text_ID;
    u8 mandragora_set_text_ID;
    u8 ready_for_blasting_text_ID;
    u8 field_0x4B;
    u16 nitro_amount_until_max_capacity;
    u8 field_0x4E[4];
    u16 mandragora_amount_until_max_capacity;
    u32 wall_type;
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} explosiveWallTextbox;

void explosiveWallSpot_entrypoint(explosiveWallTextbox* self);
void explosiveWallSpot_init(explosiveWallTextbox* self);
void explosiveWallSpot_idle(explosiveWallTextbox* self);
void explosiveWallSpot_determineMessage(explosiveWallTextbox* self);
void explosiveWallSpot_setItemText_prepareMessage(explosiveWallTextbox* self);
void explosiveWallSpot_setItemText_idle(explosiveWallTextbox* self);
void explosiveWallSpot_setItemText_determineNextTextbox(explosiveWallTextbox* self);
void explosiveWallSpot_setItemText_close(explosiveWallTextbox* self);
void explosiveWallSpot_readyForBlasting(explosiveWallTextbox* self);
void explosiveWallSpot_nitroIsSet(explosiveWallTextbox* self);
void explosiveWallSpot_mandragoraIsSet(explosiveWallTextbox* self);
void explosiveWallSpot_defaultDescription(explosiveWallTextbox* self);
void explosiveWallSpot_itemAlreadySet(explosiveWallTextbox* self);
void explosiveWallSpot_destroy(explosiveWallTextbox* self);

typedef enum explosiveWallTextbox_func_id {
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
    EXPLOSIVE_WALL_SPOT_DEFAULT_DESCRIPTION,
    EXPLOSIVE_WALL_SPOT_ITEM_ALREADY_SET,
    EXPLOSIVE_WALL_SPOT_DESTROY
} explosiveWallTextbox_func_id_t;

typedef void (*explosiveWallTextbox_func_t)(explosiveWallTextbox*);

#endif
