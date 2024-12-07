/**
 * @file enemy_list.c
 *
 * Contains the code that handles the enemy list,
 * a record of the enemies currently loaded and their state
 */

#include "enemy_list.h"
#include "memory.h"
#include "system_work.h"

// clang-format off

char EnemyList_enemyStates[] = {
    'P', 'C', 'A', 'D', 'O',
    '?', '?', '?', '?', '?',
    '?', '?', '?', '?', '?',
    '?', '\0', '\0', '\0', '\0'
};

s32 Enemy_timeOfDayList[] = {
    TIME_EVENING_MORNING,
    TIME_DAY,
    TIME_EVENING_MORNING,
    TIME_NIGHT
};

// clang-format on

// TODO: Temporarily commented out until we can fix .bss-related linker errors
// EnemyList enemy_list;
// s32 D_800D80C4;

void EnemyList_init() {
    memory_clear(&enemy_list, sizeof(enemy_list));
}

EnemyListEntry* EnemyList_addOrModifyEntry(Actor* actor, u16 flags) {
    s32 i;
    EnemyListEntry* entry;

    if (enemy_list.num_enemies >= MAX_NUM_ENEMIES_SPAWNED) {
        return NULL;
    }

    entry = ARRAY_START(enemy_list.enemies);
    i     = 0;
    if (enemy_list.num_enemies > 0) {
        do {
            if (actor == entry->enemy)
                break;
            i++;
            entry++;
        } while (i < enemy_list.num_enemies);
    }

    if (i == enemy_list.num_enemies) {
        EnemyList_clearEntry(entry);
        entry->flags = flags;
        entry->enemy = actor;
        enemy_list.num_enemies++;
    } else {
        entry->flags = flags;
    }

    return entry;
}

// https://decomp.me/scratch/7IsbK
#ifdef NON_MATCHING
void EnemyList_removeEntry(Actor* actor) {
    s32 i;
    EnemyListEntry* entry;
    EnemyListEntry* last_entry;

    entry = ARRAY_START(enemy_list.enemies);
    i     = 0;
    if (enemy_list.num_enemies > 0) {
        do {
            if (actor == entry->enemy) {
                if ((i + 1) == enemy_list.num_enemies) {
                    EnemyList_clearEntry(entry);
                    enemy_list.num_enemies--;
                    break;
                }
                last_entry   = &enemy_list.enemies[enemy_list.num_enemies - 1];
                entry->whole = last_entry->whole;
                entry->enemy = last_entry->enemy;
                EnemyList_clearEntry(last_entry);
                enemy_list.num_enemies--;
                break;
            }
            i++;
            entry++;
        } while (i < enemy_list.num_enemies);
    }
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_removeEntry.s")
#endif

void func_8003E98C_3F58C() {}

void EnemyList_printEnemyState(u16 flags, char* string) {
    s32 i;
    u16 j;

    for (i = 0, j = 1; i < 5; i++, j <<= 1) {
        if (flags & j) {
            string[i] = EnemyList_enemyStates[i];
        } else {
            string[i] = ' ';
        }
    }

    string[i] = '\0';
}

void func_8003EA7C_3F67C() {}

void func_8003EA84_3F684(void* arg0) {}

void EnemyList_clearEntry(EnemyListEntry* entry) {
    memory_clear(entry, sizeof(EnemyListEntry));
}

// https://decomp.me/scratch/DngTK
#ifdef NON_MATCHING
s32 EnemyList_getNumberOfActiveEnemies() {
    s32 i;
    EnemyListEntry* entry;
    s32 num_active_enemies;

    entry              = ARRAY_START(enemy_list.enemies);
    num_active_enemies = 0;
    i                  = 0;
    if (enemy_list.num_enemies > 0) {
        do {
            if (entry->flags & (ENEMY_ALIVE | ENEMY_ACTIVE)) {
                num_active_enemies++;
            }
            i++;
            entry++;
        } while (i < enemy_list.num_enemies);
    }

    return num_active_enemies;
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_getNumberOfActiveEnemies.s")
#endif

s32 EnemyList_isAnyEnemyWithinRange(Vec3f* position, f32 max_XZ_distance, f32 max_height) {
    s32 i;
    Vec3f pos_difference;
    EnemyListEntry* entry;
    f32 height_difference;
    Model* enemy_model;

    entry = ARRAY_START(enemy_list.enemies);
    i     = 0;
    if (enemy_list.num_enemies > 0) {
        do {
            if (entry->flags & (ENEMY_ALIVE | ENEMY_ACTIVE)) {
                enemy_model = entry->enemy->model;
                if (enemy_model != NULL) {
                    vec3f_substractFloats(&pos_difference, &enemy_model->position, position);
                    if (pos_difference.y < 0.0f) {
                        height_difference = -pos_difference.y;
                    } else {
                        height_difference = pos_difference.y;
                    }
                    if ((height_difference <= max_height) &&
                        (((pos_difference.z * pos_difference.z) +
                          (pos_difference.x * pos_difference.x)) <=
                         (max_XZ_distance * max_XZ_distance))) {
                        return TRUE;
                    }
                }
            }
            i++;
            entry++;
        } while (i < enemy_list.num_enemies);
    }
    return FALSE;
}

s32 EnemyList_getTimeOfDay() {
    s16 adjusted_hour = sys.SaveStruct_gameplay.hour - 4;

    if (adjusted_hour < 0) {
        adjusted_hour += 24;
    }

    return Enemy_timeOfDayList[adjusted_hour / 6];
}
