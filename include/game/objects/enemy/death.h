#ifndef DEATH_H
#define DEATH_H

#include "actor.h"

typedef enum DeathAnimId {
    DEATH_ANIM_0  = 0,
    DEATH_ANIM_3  = 3,
    DEATH_ANIM_12 = 12
} DeathAnimId;

typedef struct DeathData {
    u8 field_0x00[4];
    actorVisualData visual_data;
    u8 field_0x44;
    u8 field_0x45;
    u8 field_0x46;
    u8 field_0x47;
    s16 field_0x48;
    s16 field_0x4A;
    s16 field_0x4C;
    s16 field_0x4E;
    f32 field_0x50;
    Vec3f field_0x54;
    u8 state;
    u8 substate;
    u8 field_0x62[2];
    f32 field_0x64;
    Vec3f field_0x68;
    u8 field_0x74[2];
    s16 angle;
    s16 field_0x78;
    s16 field_0x7A;
    s16 field_0x7C;
    u8 field_0x7E[2];
    u8 field_0x80;
    u8 field_0x81;
    u8 field_0x82;
    u8 field_0x83;
    u8 field_0x84[9];
    u8 field_0x8D;
    u8 number_of_scythes;
    s8 animation_ID;
    s32 anim_state;
    void* field_0x94;
    void* field_0x98;
    u8 field_0x9C;
    u8 field_0x9D;
    u8 field_0x9E[10];
} DeathData;

// ID: 0x2095
typedef struct Death {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    DeathData* data;
    modelLighting* model_lighting;
    u8 field_0x30[40];
    void* slash_gfx; // SlashGfx*
    u8 field_0x5C[20];
    ActorConfig* settings;
} Death;

extern void
func_0F00EB78(u8 animation_ID, f32 anim_speed, actorVisualData* visual_data, DeathData* data);
extern void func_0F00EBFC(DeathData* data, Model* model, animationMgr* anim_mgr);
extern void
Death_CreateMultipleScythes(Death* self, DeathData* data, u8, u8, u8 num_scythes, s16 angle, f32);

#endif
