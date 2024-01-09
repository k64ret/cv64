#ifndef ROSE_VENTILATOR_H
#define ROSE_VENTILATOR_H

#include "actor.h"
#include "gfx/model_info.h"

typedef struct cv64_ovl_rose_ventilator_cfg {
    u32 time_until_changing_max_speed;
    u32 current_speed;
    u32 max_speed;
} cv64_ovl_rose_ventilator_cfg_t;

typedef struct cv64_ovl_rose_ventilator {
    cv64_obj_hdr_t header;
    u8 field_0x4[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    cv64_ovl_rose_ventilator_cfg_t speed_settings;
    u8 field_0x40[48];
    cv64_actor_settings_t* settings;
} cv64_ovl_rose_ventilator_t;

typedef void (*cv64_ovl_rose_ventilator_func_t)(cv64_ovl_rose_ventilator_t*);

void cv64_ovl_rose_ventilator_entrypoint(cv64_ovl_rose_ventilator_t* self);
extern void cv64_ovl_rose_ventilator_init(cv64_ovl_rose_ventilator_t* self);
extern void cv64_ovl_rose_ventilator_loop(cv64_ovl_rose_ventilator_t* self);

extern cv64_ovl_rose_ventilator_func_t cv64_ovl_rose_ventilator_funcs[];

extern const u32 VENTILATOR_DOOR_DL;

#endif // ROSE_VENTILATOR_H
