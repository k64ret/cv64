#ifndef CV64_EFFECT_H
#define CV64_EFFECT_H

#include "gfx/model_info.h"
#include "actor.h"
#include "object.h"

// Generic effect struct
typedef struct cv64_effect {
    cv64_object_hdr_t header;
    u8 padding1[4];
    cv64_model_inf_t* model;
    u8 field_0x28[OBJECT_SIZE - 0x28];
    cv64_actor_settings_t* settings;
} cv64_effect_t;

#endif // CV64_EFFECT_H
