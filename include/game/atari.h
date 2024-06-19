#ifndef ATARI_WORK_H
#define ATARI_WORK_H

// Collider structs

#include "gfx/model_info.h"
#include <ultra64.h>

typedef enum atari_work_flags_t {
    DONT_UPDATE_POSITIONAL_DATA            = 0x20,
    UPDATE_ATTACKER_TARGET_POSITIONAL_DATA = 0x40,
    INFLICT_DAMAGE                         = 0x100,
    ENABLE_PUSH_BACK_FORCE                 = 0x800,
    TYPE_DATA                              = 0x1000,
    TYPE_BASE                              = 0x2000,
    ATARI_WORK_DESTROY                     = 0x8000
} atari_work_flags_t;

typedef enum atari_work_damage_type_t {
    DAMAGE_BLOOD   = 0x01, // Red sparkles
    REGULAR_HIT    = 0x02, // Displays orange sparkles
    BURNING_DAMAGE = 0x04,
    POISON_DAMAGE  = 0x10,
    ELECTRIFIED    = 0x20,
    GRABBED        = 0x40,
    /**
     * Except for being frozen
     */
    INVINCIBLE = 0x80,
    /**
     * Also used in 0x80030350
     */
    GRABBED_AND_LAUNCHED = 0x400,
    GEAR_SINK_DEATH      = 0x800,
    /**
     * Plays weird animation
     */
    ATARI_WORK_DAMAGE_TYPE_1000 = 0x1000,
    HIT_LAUNCH                  = 0x2000,
    FALLS_OVER                  = 0x4000,
    /**
     * Spreads the damage effect throught the whole body
     */
    CREATE_SPARKLES_ON_EVERY_ATARI_DATA = 0x8000
} atari_work_damage_type_t;

typedef struct {
    /**
     * The lowest 3-bits are a function ID in the array at 0x80098600
     */
    u16 flags;
    s16 damage_type;
    /**
     * Seems to only be used for deciding whether or not
     * to draw the damage effect. See createDamageEffect()
     */
    s16 ignored_damage_type;
    s16 damage;
    s16 max_damage_received;
    s16 field_0x0A;
    s16 damage_sound_ID;
    s16 field_0x0E;
    u8 field_0x10[2];
    angle_t direction;
    vec3f center_point;
    vec2f size;
    cv64_model_inf_t* attached_model;
    /**
     * The "atari_base" struct it's attached to
     */
    struct atari_data_work* atari_work[2];
    f32 field_0x38;
    f32 field_0x3C;
    vec3f position;
    vec3f field_0x4C;
    vec3f field_0x58;
    f32 field_0x64;
    cv64_model_inf_t* field_0x68;
    struct atari_data_work* collider_attacker;
    vec3f damage_effect_position;
    vec3f damage_effect_scale;
    f32 field_0x88;
    f32 field_0x8C;
    s16 field_0x90;
    s16 received_damage_type;
    s16 field_0x94;
    s16 field_0x96;
    u8 field_0x98[4];
} atari_data_work;

typedef struct {
    u16 flags;
    s16 damage_type;
    /**
     * Seems to only be used for deciding whether or not
     * to draw the damage effect. See createDamageEffect()
     */
    s16 ignored_damage_type;
    s16 field_0x06;
    s16 health;
    s16 field_0x0A;
    u8 field_0x0C;
    u8 field_0x0D;
    s16 push_back_divisor;
    vec3f push_back_force;
    atari_data_work* attacker_atari_data;
    /**
     * Associated colider that was hit by attacker_atari_data
     */
    atari_data_work* collider_hit;
    vec3f damage_effect_pos;
    vec3f damage_effect_scale;
    /**
     * Unused? Copies to field 0x4 of `struct_97`
     */
    f32 field_0x3C;
    /**
     * Unused? Copies to field 0x8 of `struct_97`
     */
    f32 field_0x40;
    s16 field_0x44;
    s16 field_0x46;
    u16 received_damage_type;
    u16 damage_received;
    u32 damaged_by_attacker_flags;
    s32 field_0x50;
    u32 hit_target_flags;
    cv64_model_inf_t* attached_model;
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
    s16 damage_type;
    /**
     * Seems to only be used for deciding whether or not
     * to draw the damage effect. See createDamageEffect()
     */
    s16 ignored_damage_type;
    s16 damage;
    s16 max_damage_received;
    s16 field_0x0A;
    u8 field_0x0C;
    u8 on_hit_SFX_set_slot;
    s16 field_0x0E;
    vec3f push_back_on_collider_contact;
    atari_data_work* collider_hit;
    vec3f damage_effect_position;
    vec3f damage_effect_scale;
    f32 field_0x38;
    f32 field_0x3C;
    s16 field_0x40;
    s16 field_0x42;
    s16 received_damage_type;
    union {
        s16 damage_received;
        s16 victim_boss_life;
    };
    s16 field_0x48;
    /**
     * Received damage from an attacker
     */
    u8 damaged_by_attacker;
    /**
     * Hit a target
     */
    u8 hit_target;
    u8 field_0x4C;
    u8 field_0x4D;
    s16 angle;
    s16 field_0x50;
    s16 field_0x52;
    vec3f center_point;
    vec2f size;
    cv64_model_inf_t* damage_effect_model;
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
