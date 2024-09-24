#ifndef PLAYER_H
#define PLAYER_H

#include "actor.h"
#include "gfx/model_info.h"
#include "math.h"
#include "objects/player/attackMgr.h"
#include "objects/player/player_flags.h"
#include "objects/player/enemyTargetGfx.h"
#include <ultra64.h>

typedef struct {
    s16 field0_0x0;
    u8 field1_0x2;
    u8 field2_0x3;
    u8 field3_0x4;
    u8 field4_0x5;
    u8 field5_0x6;
    u8 field6_0x7;
    f32 field7_0x8;
    f32 field8_0xc;
    f32 field9_0x10;
    f32 field10_0x14;
    f32 ledge_moving_speed_multiplier;
    f32 field12_0x1c;
    f32 max_jogging_XZ_speed;
    f32 max_running_XZ_speed;
    f32 jump_height;
    f32 jump_gravity_accel;
    f32 field17_0x30;
    f32 field18_0x34;
    Vec3f field19_0x38;
    s16 damage_received;
    s16 current_health_depletion_rate_while_poisoned;
    u8 field22_0x48;
    u8 field23_0x49;
    u8 player_invincibility_time;
    u8 damage_type; // Type of damage received by the player from an enemy
    u8 field26_0x4c;
    u8 field27_0x4d;
    u8 field28_0x4e;
    u8 field29_0x4f;
    u8 field30_0x50;
    u8 field31_0x51;
    u8 field32_0x52;
    u8 field33_0x53;
    u8 field34_0x54;
    u8 field35_0x55;
    u8 field36_0x56;
    u8 field37_0x57;
    u8 field38_0x58;
    u8 field39_0x59;
    u8 field40_0x5a;
    u8 field41_0x5b;
    u8 field42_0x5c;
    u8 field43_0x5d;
    u8 field44_0x5e;
    u8 field45_0x5f;
    u8 field46_0x60;
    u8 field47_0x61;
    u8 field48_0x62;
    u8 field49_0x63;
    u8 field50_0x64;
    u8 field51_0x65;
    u8 field52_0x66;
    u8 field53_0x67;
    u8 field54_0x68;
    u8 field55_0x69;
    u8 field56_0x6a;
    u8 field57_0x6b;
    u8 field58_0x6c;
    u8 field59_0x6d;
    u8 field60_0x6e;
    u8 field61_0x6f;
    u8 field62_0x70;
    u8 field63_0x71;
    u8 field64_0x72;
    u8 field65_0x73;
} playerParams;

// Todo: Double check this
typedef union {
    Vec3f player_hit_launch_velocity;
    u32 openingLightDoor;
} unk_union_playerData;

typedef struct {
    u8 field_0x00[4];
    actorVisualData visualData;
    playerParams* params;
    u32 additionalFlags;
    u32 field_0x4C;
    u16 idleTimer;
    s16 field_0x52;
    s16 field_0x54;
    s16 damage_anim_array_index;
    unk_union_playerData field_0x58;
    u16 field_0x64;
    u16 field_0x66;
    u8 field_0x68[12];
    Vec3f speed;
    f32 field_0x80;
    f32 gravity_accel;
    attackManager* attackMgr;
    enemyTargetData_t* enemyTargetData;
    u8 unable_to_jump_timer;
    u8 unable_to_throw_subweapon_timer;
    u8 field_0x92;
    u8 field_0x93;
    u32 field_0x94;   // map_object_actor_collision_union ?
    void* field_0x98; // roomMgr* ?
    f32 water_source_closeness;
    s16 currently_stepping_coll_type_and_variable;
    u8 field_0xA2[6];
} playerData;

typedef struct {
    u8 field0_0x0;
    u8 field1_0x1;
    u8 field2_0x2;
    u8 field3_0x3;
    u32 field4_0x4;
    u8 field5_0x8;
    u8 field6_0x9;
    u8 field7_0xa;
    u8 field8_0xb;
    u8 field9_0xc;
    u8 field10_0xd;
    s16 field11_0xe;
    u8 field12_0x10;
    u8 field13_0x11;
    u8 field14_0x12;
    u8 field15_0x13;
    u8 field16_0x14;
    u8 field17_0x15;
    u8 field18_0x16;
    u8 field19_0x17;
    s16 field20_0x18;
    u8 field21_0x1a;
    u8 field22_0x1b;
    animationMgr field23_0x1c;
    s32 field24_0x4c;
    s16 field25_0x50;
    s16 field26_0x52;
    animationMgr field27_0x54;
    s32 field28_0x84;
    u8 field29_0x88;
    u8 field30_0x89;
    u8 field31_0x8a;
    u8 field32_0x8b;
    u8 field33_0x8c;
    u8 field34_0x8d;
    u8 field35_0x8e;
    u8 field36_0x8f;
    u8 field37_0x90;
    u8 field38_0x91;
    u8 field39_0x92;
    u8 field40_0x93;
    u8 field41_0x94;
    u8 field42_0x95;
    u8 field43_0x96;
    u8 field44_0x97;
    u8 field45_0x98;
    u8 field46_0x99;
    u8 field47_0x9a;
    u8 field48_0x9b;
    u8 field49_0x9c;
    u8 field50_0x9d;
    u8 field51_0x9e;
    u8 field52_0x9f;
    u8 field53_0xa0;
    u8 field54_0xa1;
    u8 field55_0xa2;
    u8 field56_0xa3;
    u8 field57_0xa4;
    u8 field58_0xa5;
    u8 field59_0xa6;
    u8 field60_0xa7;
} playerMovingAttack;

// Generic player actor struct
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    Model* model;
    playerData* data;
    playerMovingAttack* movingAttack;
    u8 field_0x30[OBJECT_SIZE - 0x30];
} Player;

typedef enum cv64_player_state_funcs_id {
    PLAYER_INIT,
    PLAYER_IDLE,
    PLAYER_DAMAGE,
    PLAYER_JUMP,
    PLAYER_ATTACK,
    PLAYER_ACTION,
    PLAYER_MOVING,
    PLAYER_LEDGE_MOVEMENT,
    PLAYER_FALLING,
    PLAYER_SLIDE,
    PLAYER_ENEMY_LOCK,
    PLAYER_DEAD,
    PLAYER_FROZEN,
    PLAYER_FROZEN_GRAB
} cv64_player_state_funcs_id_t;

extern playerData* ptr_PlayerData;

extern s32 getAngleBetweenPlayerAndInteractable(
    f32 player_pos_X, f32 player_pos_Z, f32 actor_pos_X, f32 actor_pos_Z
);

#endif
