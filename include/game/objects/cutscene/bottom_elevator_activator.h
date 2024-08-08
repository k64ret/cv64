#ifndef BOTTOM_ELEVATOR_ACTIVATOR_H
#define BOTTOM_ELEVATOR_ACTIVATOR_H

#include "actor.h"
#include "objects/menu/mfds.h"

// ID: 0x2025
typedef struct cv64_ovl_bottomelevatoractivatortextbox {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    u32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    u8 field_0x44[20];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} cv64_ovl_bottomelevatoractivatortextbox_t;

void cv64_ovl_bottomelevatoractivatortextbox_entrypoint(
    cv64_ovl_bottomelevatoractivatortextbox_t* self
);
void cv64_ovl_bottomelevatoractivatortextbox_init(cv64_ovl_bottomelevatoractivatortextbox_t* self);
void cv64_ovl_bottomelevatoractivatortextbox_idle(cv64_ovl_bottomelevatoractivatortextbox_t* self);
void cv64_ovl_bottomelevatoractivatortextbox_prep_msg(
    cv64_ovl_bottomelevatoractivatortextbox_t* self
);
void cv64_ovl_bottomelevatoractivatortextbox_yes_no(cv64_ovl_bottomelevatoractivatortextbox_t* self
);
void cv64_ovl_bottomelevatoractivatortextbox_close(cv64_ovl_bottomelevatoractivatortextbox_t* self);
void cv64_ovl_bottomelevatoractivatortextbox_destroy(cv64_ovl_bottomelevatoractivatortextbox_t* self
);

typedef enum cv64_ovl_bottomelevatoractivatortextbox_func_id {
    BOTTOM_ELEVATOR_ACTIVATOR_INIT,
    BOTTOM_ELEVATOR_ACTIVATOR_IDLE,
    BOTTOM_ELEVATOR_ACTIVATOR_PREPARE_MESSAGE,
    BOTTOM_ELEVATOR_ACTIVATOR_SELECT_OPTION,
    BOTTOM_ELEVATOR_ACTIVATOR_CLOSE_TEXTBOX,
    BOTTOM_ELEVATOR_ACTIVATOR_DESTROY
} cv64_ovl_bottomelevatoractivatortextbox_func_id_t;

typedef void (*cv64_ovl_bottomelevatoractivatortextbox_func_t)(cv64_ovl_bottomelevatoractivatortextbox_t*);

#endif
