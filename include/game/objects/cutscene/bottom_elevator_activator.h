#ifndef BOTTOM_ELEVATOR_ACTIVATOR_H
#define BOTTOM_ELEVATOR_ACTIVATOR_H

#include "actor.h"
#include "objects/menu/mfds.h"

#define BOTTOM_ELEVATOR_ACTIVATOR_STATE_ACTIVATE_ELEVATOR  1
#define BOTTOM_ELEVATOR_ACTIVATOR_STATE_ALREADY_USED       2
#define BOTTOM_ELEVATOR_ACTIVATOR_STATE_DONT_ACTIVATE_YET  4
#define BOTTOM_ELEVATOR_ACTIVATOR_STATE_ELEVATOR_ACTIVATED 5

// ID: 0x2025
typedef struct cv64_ovl_elevatortxt {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    /**
     * This field should be the text ID, just like with most of the
     * other special textboxes. However, it isn't used to retrieve messages this time,
     * and the text IDs assigned to this variables sometimes aren't coherent with the current
     * state.
     *
     * For example, after activating the elevator, this variable is set to 5, which if interpreted as
     * a text ID, it would be `CASTLE_CENTER_1F_ELEVATOR_NOT_MOVING`, which doesn't make sense, since the
     * elevator is already activated.
     */
    u32 state;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 field_0x44[20];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} cv64_ovl_elevatortxt_t;

void cv64_ovl_elevatortxt_entrypoint(cv64_ovl_elevatortxt_t* self);
void cv64_ovl_elevatortxt_init(cv64_ovl_elevatortxt_t* self);
void cv64_ovl_elevatortxt_idle(cv64_ovl_elevatortxt_t* self);
void cv64_ovl_elevatortxt_prepare_msg(cv64_ovl_elevatortxt_t* self);
void cv64_ovl_elevatortxt_yes_no(cv64_ovl_elevatortxt_t* self);
void cv64_ovl_elevatortxt_close(cv64_ovl_elevatortxt_t* self);
void cv64_ovl_elevatortxt_destroy(cv64_ovl_elevatortxt_t* self);

typedef enum cv64_ovl_elevatortxt_func_id {
    BOTTOM_ELEVATOR_ACTIVATOR_INIT,
    BOTTOM_ELEVATOR_ACTIVATOR_IDLE,
    BOTTOM_ELEVATOR_ACTIVATOR_PREPARE_MESSAGE,
    BOTTOM_ELEVATOR_ACTIVATOR_SELECT_OPTION,
    BOTTOM_ELEVATOR_ACTIVATOR_CLOSE_TEXTBOX,
    BOTTOM_ELEVATOR_ACTIVATOR_DESTROY
} cv64_ovl_elevatortxt_func_id_t;

typedef void (*cv64_ovl_elevatortxt_func_t)(cv64_ovl_elevatortxt_t*);

#endif
