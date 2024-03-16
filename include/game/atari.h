#ifndef ATARI_WORK_H
#define ATARI_WORK_H

#include "gfx/model_info.h"
#include <ultra64.h>

typedef struct {
    u16 flags;
    s16 field_0x02;
    s16 field_0x04;
    s16 damage;
    s16 field_0x08;
    s16 field_0x0A;
    s16 field_0x0C;
    s16 field_0x0E;
    u8 field_0x10[2];
    angle_t direction;
    vec3f center_point;
    vec2f size;
    cv64_model_inf_t* attached_bone;
    struct atari_data_work* field_0x30;
    struct atari_data_work* field_0x34;
    f32 field_0x38;
    f32 field_0x3C;
    vec3f position;
    vec3f field_0x4C;
    vec3f field_0x58;
    f32 field_0x64;
    cv64_model_inf_t* field_0x68;
    struct atari_data_work* field_0x6C;
    vec3f field_0x70;
    vec3f field_0x7C;
    f32 field_0x88;
    f32 field_0x8C;
    s16 field_0x90;
    s16 field_0x92;
    s16 field_0x94;
    s16 field_0x96;
    u8 field_0x98[4];
} atari_data_work;

typedef struct {
    u16 flags;
    s16 field_0x02;
    s16 field_0x04;
    s16 field_0x06;
    s16 field_0x08;
    s16 field_0x0A;
    u8 field_0x0C;
    u8 field_0x0D;
    s16 field_0x0E;
    vec3f field_0x10;
    atari_data_work* field_0x1C;
    atari_data_work* field_0x20;
    vec3f field_0x24;
    vec3f field_0x30;
    f32 field_0x3C;
    f32 field_0x40;
    s16 field_0x44;
    s16 field_0x46;
    u16 field_0x48;
    u16 damage_received;
    u32 field_0x4C;
    s32 field_0x50;
    s32 field_0x54;
    cv64_model_inf_t* attached_bone;
    atari_data_work* field_0x5C[4];
    atari_data_work* field_0x6C[4];
    s32 field_0x7C;
    u8 field_0x80;
    u8 field_0x81[3];
    s32 field_0x84;
    u8 field_0x88[8];
    s16 field_0x90;
    s16 field_0x92;
    s16 field_0x94;
    s16 field_0x96;
    u8 field_0x98[4];
} atari_base_work;

typedef struct {
    u16 flags;
    s16 field_0x02;
    s16 field_0x04;
    s16 damage_dealt;
    s16 field_0x08;
    s16 field_0x0A;
    u8 field_0x0C;
    u8 field_0x0D;
    s16 field_0x0E;
    vec3f push_back_on_collider_contact;
    atari_data_work* collider_hit;
    vec3f damage_SFX_position;
    vec3f field_0x2C;
    f32 field_0x38;
    f32 field_0x3C;
    s16 field_0x40;
    s16 field_0x42;
    s16 field_0x44;
    s16 damage_received;
    s16 field_0x48;
    u8 field_0x4A;
    u8 field_0x4B;
    u8 field_0x4C;
    u8 field_0x4D;
    s16 angle;
    s16 field_0x50;
    s16 field_0x52;
    vec3f center_point;
    vec2f size;
    cv64_model_inf_t* field_0x68;
    u8 field30_0x6C;
    u8 field31_0x6D;
    u8 field32_0x6E;
    u8 field33_0x6F;
    vec3f position;
    vec3f field_0x7C;
    vec3f field_0x88;
    f32 field_0x94;
    u8 field_0x98;
    u8 field_0x99;
    u8 field_0x9A;
    u8 field_0x9B;
} atari_only_work;

extern void atari_work_table_init();
extern atari_base_work* atariBaseWork_create(cv64_model_inf_t* attached_bone);
extern atari_data_work* atariDataWork_create(cv64_model_inf_t* attached_bone, u16 param_2);
extern atari_only_work*
atariOnlyWork_create(cv64_model_inf_t* attached_bone, u16 function, u16 param_3);
extern u32
atariBaseWork_attachCollider(atari_base_work* self, atari_data_work* collider, u32 param_3);

#endif
