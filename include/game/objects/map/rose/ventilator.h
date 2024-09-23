#ifndef ROSE_VENTILATOR_H
#define ROSE_VENTILATOR_H

#include "actor.h"
#include "gfx/model_info.h"

typedef struct cv64_ovl_rose_ventilator_cfg {
    s32 time_until_changing_max_speed;
    s32 current_speed;
    s32 max_speed;
} cv64_ovl_rose_ventilator_cfg_t;

// ID: 0x0220
typedef struct cv64_ovl_rose_ventilator {
    cv64_object_hdr_t header;
    u8 field_0x4[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    cv64_ovl_rose_ventilator_cfg_t speed_settings;
    u8 field_0x40[48];
    ActorConfig* settings;
} cv64_ovl_rose_ventilator_t;

typedef void (*cv64_ovl_rose_ventilator_func_t)(cv64_ovl_rose_ventilator_t*);

void cv64_ovl_rose_ventilator_entrypoint(cv64_ovl_rose_ventilator_t* self);
void cv64_ovl_rose_ventilator_init(cv64_ovl_rose_ventilator_t* self);
void cv64_ovl_rose_ventilator_loop(cv64_ovl_rose_ventilator_t* self);

extern const u32 ROSE_VENTILATOR_DL;

#endif // ROSE_VENTILATOR_H
