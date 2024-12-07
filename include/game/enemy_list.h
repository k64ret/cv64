#ifndef ENEMY_LIST_H
#define ENEMY_LIST_H

#include "actor.h"

#define MAX_NUM_ENEMIES_SPAWNED 32

/**
 * Flags indicating the current state of the enemy
 */
typedef enum EnemyListEntryFlag {
    ENEMY_ALIVE           = BIT(0),
    ENEMY_ACTIVE          = BIT(1),
    ENEMY_ATTACKING       = BIT(2),
    ENEMY_DAMAGED         = BIT(3),
    ENEMY_DYING           = BIT(4), // Set when they're hit one last time before they eventually die
    ENEMY_GRABBING_PLAYER = BIT(5)
} EnemyListEntryFlag;

typedef struct EnemyListEntry {
    u16 flags;
    u16 field_0x02;
    Actor* enemy;
} EnemyListEntry;

typedef struct EnemyList {
    s32 num_enemies;
    EnemyListEntry enemies[MAX_NUM_ENEMIES_SPAWNED];
} EnemyList;

void EnemyList_init();
EnemyListEntry* EnemyList_addOrModifyEntry(Actor* actor, u16 flags);
void EnemyList_removeEntry(Actor* actor);
void func_8003E98C_3F58C();
void EnemyList_printEnemyState(u16 flags, char* string);
void func_8003EA7C_3F67C();
void func_8003EA84_3F684(void* arg0);
void EnemyList_clearEntry(EnemyListEntry* entry);
s32 EnemyList_getNumberOfActiveEnemies();
s32 EnemyList_isAnyEnemyWithinRange(Vec3f* position, f32 max_XZ_distance, f32 max_height);
s32 EnemyList_getTimeOfDay();

extern EnemyList enemy_list;
extern s32 D_800D80C4;

#endif
