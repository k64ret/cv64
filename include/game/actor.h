#ifndef ACTOR_H
#define ACTOR_H

#include "gfx/model_info.h"
#include "object.h"
#include "atari.h"
#include "objects/camera/modelLighting.h"
#include "animation.h"
#include "actor_settings.h"
#include <ultra64.h>

// For "axis" argument from checkIfOutsideEntityIsInsideMainEntityRadius()
#define AXIS_X   1
#define AXIS_Y   2
#define AXIS_Z   4
#define AXIS_XYZ 8

typedef struct {
    u32 flags;
    atari_base_work* atari_base;
    cv64_model_inf_t* model;
    modelLighting* lighting;
    animationMgr animMgr;
} actorVisualData;

// Generic actor struct
typedef struct cv64_actor {
    cv64_object_hdr_t header;
    u8 padding1[4];
    cv64_model_inf_t* model;
    u8 field_0x28[OBJECT_SIZE - 0x28];
    cv64_actor_settings_t* settings;
} cv64_actor_t;

extern void actor_model_set_pos(cv64_actor_t* actor, cv64_model_inf_t* actor_model);
extern void actor_model_set_pos_and_angle(cv64_actor_t* actor, cv64_model_inf_t* actor_model);
extern s32 actor_checkSpawn(cv64_actor_t* actor, f32 actor_pos_X, f32 actor_pos_Y, f32 actor_pos_Z);
extern void func_801578FC(cv64_actor_t* actor);
extern u32 checkIfOutsideEntityIsInsideMainEntityRadius(
    cv64_model_inf_t* player_model, cv64_model_inf_t* actor_model, f32 actor_spawn_radius, u32 axis
);
extern u8 Actor_getPosAndVariable1(cv64_actor_t* actor, vec3f* position, u16* variable_1);

#endif
