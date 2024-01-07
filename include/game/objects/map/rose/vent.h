#include "actor.h"
#include "cv64.h"
#include "gfx/model_info.h"
#include "object.h"
#include <ultra64.h>

typedef struct cv64_ovl_rose_vent_cfg {
    u32 time_until_changing_max_speed;
    u32 current_speed;
    u32 max_speed;
} cv64_ovl_rose_vent_cfg_t;

typedef struct cv64_ovl_rose_vent {
    cv64_obj_hdr_t header;
    u8 field_0x4[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    cv64_ovl_rose_vent_cfg_t speed_settings;
    u8 field_0x40[48];
    cv64_actor_settings_t* settings;
} cv64_ovl_rose_vent_t;

typedef void (*cv64_ovl_rose_vent_func_t)(cv64_ovl_rose_vent_t*);

extern cv64_ovl_rose_vent_func_t cv64_ovl_rose_vent_funcs[];
