#ifndef ATARI_WORK_H
#define ATARI_WORK_H

// Collider structs

#include "gfx/model.h"
#include <ultra64.h>

typedef enum atari_work_flag {
    ATARI_WORK_DONT_UPDATE_POSITIONAL_DATA            = 0x20,
    ATARI_WORK_UPDATE_ATTACKER_TARGET_POSITIONAL_DATA = 0x40,
    ATARI_WORK_INFLICT_DAMAGE                         = 0x100,
    ATARI_WORK_ENABLE_PUSH_BACK_FORCE                 = 0x800,
    ATARI_WORK_TYPE_DATA                              = 0x1000,
    ATARI_WORK_TYPE_BASE                              = 0x2000,
    ATARI_WORK_DESTROY                                = 0x8000
} atari_work_flag;

typedef enum atari_work_damage_kind {
    /**
     * Red sparkles
     */
    DAMAGE_KIND_BLOOD = 0x01,
    /**
     * Orange sparkles
     */
    DAMAGE_KIND_REGULAR_HIT = 0x02,
    DAMAGE_KIND_BURN        = 0x04,
    DAMAGE_KIND_POISON      = 0x10,
    DAMAGE_KIND_ELECTRICITY = 0x20,
    DAMAGE_KIND_GRAB        = 0x40,
    /**
     * Except for being frozen
     */
    DAMAGE_KIND_INVINCIBLE = 0x80,
    /**
     * Also used in 0x80030350
     */
    DAMAGE_KIND_GRAB_AND_LAUNCH = 0x400,
    DAMAGE_KIND_GEAR_SINK_DEATH = 0x800,
    /**
     * Plays weird animation
     */
    DAMAGE_KIND_1000       = 0x1000,
    DAMAGE_KIND_HIT_LAUNCH = 0x2000,
    DAMAGE_KIND_FALL_OVER  = 0x4000,
    /**
     * Spreads the damage effect throught the whole body
     */
    DAMAGE_KIND_CREATE_SPARKLES_ON_EVERY_ATARI_DATA = 0x8000
} atari_work_damage_kind;

typedef struct atari_data_work {
    /**
     * The lowest 3-bits are a function ID in the array at 0x80098600
     */
    s16 flags;
    s16 damage_type;
    /**
     * Seems to only be used for deciding whether or not
     * to draw the damage effect. See createDamageEffect()
     */
    s16 ignored_damage_type;
    s16 damage;
    s16 max_damage_received;
    u16 interaction_flags;
    s16 damage_sound_ID;
    s16 field_0x0E;
    u8 field_0x10[2];
    Angle direction;
    Vec3f center_point;
    Vec2f size;
    Model* attached_model;
    /**
     * The "atari_base" struct it's attached to
     */
    struct atari_data_work* atari_work[2];
    f32 field_0x38;
    f32 field_0x3C;
    Vec3f position;
    Vec3f field_0x4C;
    Vec3f field_0x58;
    f32 field_0x64;
    Model* field_0x68;
    struct atari_data_work* collider_attacker;
    Vec3f damage_effect_position;
    Vec3f damage_effect_scale;
    f32 field_0x88;
    f32 field_0x8C;
    s16 field_0x90;
    s16 received_damage_type;
    s16 field_0x94;
    s16 field_0x96;
    u8 field_0x98[4];
} atari_data_work;

typedef struct atari_base_work {
    s16 flags;
    s16 damage_type;
    /**
     * Seems to only be used for deciding whether or not
     * to draw the damage effect. See createDamageEffect()
     */
    s16 ignored_damage_type;
    s16 field_0x06;
    s16 health;
    u16 interaction_flags;
    u8 field_0x0C;
    u8 field_0x0D;
    s16 push_back_divisor;
    Vec3f push_back_force;
    atari_data_work* attacker_atari_data;
    /**
     * Associated colider that was hit by attacker_atari_data
     */
    atari_data_work* collider_hit;
    Vec3f damage_effect_pos;
    Vec3f damage_effect_scale;
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
    Model* attached_model;
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

typedef struct atari_only_work {
    s16 flags;
    s16 damage_type;
    /**
     * Seems to only be used for deciding whether or not to draw the damage effect.
     * See createDamageEffect()
     */
    s16 ignored_damage_type;
    s16 damage;
    s16 max_damage_received;
    u16 interaction_flags;
    u8 field_0x0C;
    u8 on_hit_SFX_set_slot;
    s16 field_0x0E;
    Vec3f push_back_on_collider_contact;
    atari_data_work* collider_hit;
    Vec3f damage_effect_position;
    Vec3f damage_effect_scale;
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
    Vec3f center_point;
    Vec2f size;
    Model* damage_effect_model;
    u8 field30_0x6C;
    u8 field31_0x6D;
    u8 field32_0x6E;
    u8 field33_0x6F;
    Vec3f position;
    Vec3f field_0x7C;
    Vec3f field_0x88;
    f32 field_0x94;
    u8 field_0x98;
    u8 field_0x99;
    u8 field_0x9A;
    u8 field_0x9B;
} atari_only_work;

extern void atari_work_table_init(void);
extern atari_base_work* atariBaseWork_create(Model* attached_bone);
extern atari_data_work* atariDataWork_create(Model* attached_bone, u16 param_2);
extern atari_only_work* atariOnlyWork_create(Model* attached_bone, u16 function, u16 param_3);
extern u32
atariBaseWork_attachCollider(atari_base_work* self, atari_data_work* collider, u32 param_3);
extern void atariWork_markForDeletion(atari_base_work* self);

#endif
