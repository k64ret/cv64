#ifndef ENEMY_TARGET_GFX_H
#define ENEMY_TARGET_GFX_H

#include "actor.h"

typedef enum enemyTargetData_flags {
    FACING_ENEMY         = 0x0001,
    RETICLE_TURNS_RED    = 0x0002,
    NOT_FACING_ENEMY     = 0x0004,
    RETICLE_TURNS_YELLOW = 0x0008,
    HIDE_RETICLE         = 0x8000
} enemyTargetData_flags;

typedef struct {
    u16 flags;
    Vec3 field_0x02;
    Vec3f field_0x08;
    f32 height_targetGfx_player; // The height difference between the enemy target gfx and the player
    f32 reticle_display_distance; // The maximum distance between the player and the enemy that makes the reticle appear. If you're beyond this distance, the reticle will hide
    animation_info spinning_anim_info;
    Actor* targeted_enemy_ptr; // The enemy that has the reticle over them
    s16 field_0x34;
    s16 field_0x36;
    Actor* red_targeted_enemy_ptr; // The enemy that has the red reticle over them
    Vec3f enemy_position;
    Vec3f distance_enemy_player; // The distance between the enemy and the player
    Actor* facing_enemy_ptr;     // The enemy you're facing
    Vec3f field_0x58;
    Actor* field_0x64; // This is written to, but never read from?
    Vec3f enemy_to_player_distance;
} enemyTargetData_t;

// ID: 0x007A
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[72];
    enemyTargetData_t* data;
} enemyTargetGfx;

extern void enemyTargetGfx_entrypoint(enemyTargetGfx* self);
extern void enemyTargetGfx_init(enemyTargetGfx* self);
extern void enemyTargetGfx_onTarget(enemyTargetGfx* self);
extern void func_800260F8_26CF8(enemyTargetGfx* self);
extern void enemyTargetGfx_hidden(enemyTargetGfx* self);

typedef void (*enemyTargetGfx_func_t)(enemyTargetGfx*);

typedef enum enemyTargetGfx_func_id {
    ENEMYTARGETGFX_INIT,
    ENEMYTARGETGFX_ON_TARGET,
    FUNC_800260F8,
    ENEMYTARGETGFX_HIDDEN
} enemyTargetGfx_func_id_t;

#endif
