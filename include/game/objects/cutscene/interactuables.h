#ifndef INTERACTUABLES_H
#define INTERACTUABLES_H

#include "gfx/model_info.h"
#include "objects/effect/pickableItemFlash.h"
#include "objects/menu/mfds.h"
#include "actor.h"
#include "item.h"

#define ITEM_FADE_TIMER self->header.timer

#define INTERACTUABLES_SETTINGS_TYPE_ITEM      1
#define INTERACTUABLES_SETTINGS_TYPE_TEXT_SPOT 2

typedef enum cv64_interactuables_settings_flag {
    ITEM_VANISH                                = 0x0001,
    TEXT_SPOT_DESTROY_AFTER_INTERACTION        = 0x0002,
    TEXT_SPOT_DESTROY_IF_EVENT_FLAG_IS_SET     = 0x0004,
    TEXT_SPOT_DISABLE_IF_EVENT_FLAG_IS_NOT_SET = 0x0008,
    /**
     * Yes / No selection textbox
     */
    TEXT_SPOT_DO_ACTION_AFTER_SELECTING_OPTION = 0x0010,
    TEXT_SPOT_IF_YES_START_CUTSCENE            = 0x0020,
    TEXT_SPOT_IF_YES_ACTIVATE_LEVER            = 0x0040,
    TEXT_SPOT_IF_YES_SET_EVENT_FLAG            = 0x0080,
    /**
     * Yes / No selection textbox
     */
    TEXT_SPOT_IF_YES_PULL_LEVER = 0x0100,
    ITEM_DOES_NOT_FLASH         = 0x0400,
    ITEM_INVISIBLE              = 0x0800
} cv64_interactuables_settings_flag_t;

typedef struct {
    u16 type;
    union {
        u16 item;
        u16 text_ID;
    };
    u16 flags;
    u8 field_0x06[2];
    u32 event_flag;
    union {
        u16 cutscene_ID;
        u16 actor_ID;
        u16 pickable_item_flash_height;
    };
    u16 actor_variable_1;
    u16 trigger_size; // Only used for text spots
    u8 field_0x12[2];
} interactuables_settings;

// ID: 0x0027
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x04[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    f32 height;
    /**
     * ID in `interactuable_settings_table`
     */
    u16 table_index;
    u8 field_0x3A[2];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    union {
        u16 item_doesnt_vanish;
        u16 item_doesnt_flash;
    };
    u16 item_falling_height_multiplier;
    u16 current_flash_inactive_time;
    u8 field_0x4A[2];
    u32 time_when_flash_appears_over_item;
    cv64_rgba_t primitive_color;
    u16 map_event_flag_ID;
    u16 item_model_settings_flags;
    u32 event_flag; // Save event flag that gets set when interacting with the item
    s16 trigger_X_size;
    s16 trigger_Z_size;
    union {
        pickableItemFlash* flash;
        mfds_state* textbox;
    };
    vec3f position;
    cv64_actor_settings_t* settings;
} interactuables;

void interactuables_entrypoint(interactuables* self);
void interactuables_init(interactuables* self);
void interactuables_main(interactuables* self);
void interactuables_initCheck(interactuables* self);
void interactuables_selectTextboxOption(interactuables* self);
void interactuables_stopCheck(interactuables* self);
void interactuables_destroy(interactuables* self);
void interactuables_stopInteraction(interactuables* self);

typedef enum cv64_interactuables_func_id {
    INTERACTUABLES_INIT,
    INTERACTUABLES_MAIN,
    INTERACTUABLES_INIT_CHECK,
    INTERACTUABLES_SELECT_TEXTBOX_OPTION,
    INTERACTUABLES_STOP_CHECK,
    INTERACTUABLES_DESTROY
} cv64_interactuables_func_id_t;

typedef void (*cv64_interactuables_func_t)(interactuables*);

extern interactuables_settings interactuables_settings_table[125];

#endif
