#ifndef ROSE_DOOR_H
#define ROSE_DOOR_H

#include "actor.h"
#include "gfx/model_info.h"
#include "map_actor_model.h"

// Variable 1 = Don't close door
#define ROSE_DOOR_DONT_CLOSE settings->variable_1

typedef struct cv64_ovl_rose_door_cfg {
    f32 initial_height;
    f32 height;
    f32 closing_speed;
} cv64_ovl_rose_door_cfg_t;

// ID: 0x1221
typedef struct cv64_ovl_rose_door {
    cv64_object_hdr_t header;
    u8 field_0x4[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    cv64_ovl_rose_door_cfg_t height_settings;
    u8 field_0x40[40];
    cv64_map_actor_model_t* map_actor_model;
    u8 field_0x6C[4];
    ActorConfig* settings;
} cv64_ovl_rose_door_t;

typedef void (*cv64_ovl_rose_door_func_t)(cv64_ovl_rose_door_t*);

void cv64_ovl_rose_door_entrypoint(cv64_ovl_rose_door_t* self);
void cv64_ovl_rose_door_init(cv64_ovl_rose_door_t* self);
void cv64_ovl_rose_door_loop(cv64_ovl_rose_door_t* self);

typedef enum cv64_ovl_rose_door_state_func_id {
    ROSE_DOOR_STATE_START_CLOSING,
    ROSE_DOOR_STATE_CLOSING,
    ROSE_DOOR_STATE_IDLE
} cv64_ovl_rose_door_state_func_id_t;

void cv64_ovl_rose_door_state_startClosing(cv64_ovl_rose_door_t* self);
void cv64_ovl_rose_door_state_closing(cv64_ovl_rose_door_t* self);
void cv64_ovl_rose_door_state_idle(cv64_ovl_rose_door_t* self);

extern const u32 ROSE_DOOR_DL;

#endif // ROSE_DOOR_H
