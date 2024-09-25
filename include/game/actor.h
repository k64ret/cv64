#ifndef ACTOR_H
#define ACTOR_H

#include "gfx/model.h"
#include "object.h"
#include "atari.h"
#include "objects/camera/modelLighting.h"
#include "animation.h"
#include "actor_settings.h"
#include <ultra64.h>

// For "axis" argument from `checkIfOutsideEntityIsInsideMainEntityRadius`
#define AXIS_X   BIT(0)
#define AXIS_Y   BIT(1)
#define AXIS_Z   BIT(2)
#define AXIS_XYZ BIT(3)

typedef struct {
    u32 flags;
    cv64_atari_base_work_t* atari_base;
    Model* model;
    modelLighting* lighting;
    animationMgr animMgr;
} actorVisualData;

// Generic actor struct
typedef struct Actor {
    ObjectHeader header;
    u8 padding1[4];
    Model* model;
    u8 field_0x28[OBJECT_SIZE - 0x28];
    ActorConfig* settings;
} Actor;

extern void actor_model_set_pos(Actor* actor, Model* actor_model);
extern void actor_model_set_pos_and_angle(Actor* actor, Model* actor_model);
extern s32 actor_playerOutsideActorSpawnRadius(
    Actor* actor, f32 actor_pos_X, f32 actor_pos_Y, f32 actor_pos_Z
);
extern void func_801578FC(Actor* actor);
extern u32 checkIfOutsideEntityIsInsideMainEntityRadius(
    Model* player_model, Model* actor_model, f32 actor_spawn_radius, u32 axis
);
extern u8 Actor_getPosAndVariable1(Actor* actor, Vec3f* position, u16* variable_1);

#endif
