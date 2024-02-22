#ifndef CV64_EFFECT_H
#define CV64_EFFECT_H

#include "gfx/model_info.h"
#include "gfx/camera.h"
#include "actor.h"
#include "object.h"

#define EFFECT_ID_1 1

// Generic effect struct
typedef struct cv64_effect {
    cv64_object_hdr_t header;
    u8 padding1[4];
    cv64_model_inf_t* model;
    u8 field_0x28[OBJECT_SIZE - 0x28];
    cv64_actor_settings_t* settings;
} cv64_effect_t;

extern cv64_effect_t* createEffectObjectUnderEffectMgr(
    u16 effect_obj_info_array_index, camera* param_2, u32 param_3
);
extern void
effect_setPosition(cv64_effect_t* self, f32 x, f32 y, f32 z, u16 param_5);
extern void
effect_setScale(cv64_effect_t* self, f32 x, f32 y, f32 z, u16 param_5);
extern void func_8005B78C(cv64_effect_t* self, u16 param_5);

#endif // CV64_EFFECT_H
