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

/**
 * @note State `ENEMY_GRABBING_PLAYER` is missing a unique letter.
 */
char EnemyList_enemyStates[] = {
    'P', 'C', 'A', 'D', 'O',
    '?', '?', '?', '?', '?',
    '?', '?', '?', '?', '?',
    '?'
};

u8 D_800985E0_991E0[4] = {0};

s32 Enemy_timeOfDayList[] = {
    TIME_EVENING_MORNING,
    TIME_DAY,
    TIME_EVENING_MORNING,
    TIME_NIGHT
};

// clang-format on

EnemyList enemy_list;
s32 D_800D80C4;
/**
 * @note `D_800D80D0` is `.bss` padding.
 *       It's unknown whether it was actually part of `enemy_list.c` or not.
 */
u8 D_800D80D0[128];

/**
 * Clears the enemy list
 */
void EnemyList_init() {
    memory_clear(&enemy_list, sizeof(enemy_list));
}

/**
 * Given an enemy actor and its state flags, this function either
 * - Adds an enemy and its state flags to `enemy_list` if not present
 * - Modifies its state flags if the enemy is already on said list
 */
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

    /**
     * If the enemy is not on the list, add it.
     * Otherwise just modify its state flags.
     */
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

/**
 * Given an enemy actor, this function removes it from the list if present
 */
void EnemyList_removeEntry(Actor* actor) {
    s32 i;
    EnemyListEntry* entry;
    EnemyListEntry* last_entry;

    entry = ARRAY_START(enemy_list.enemies);
    i     = 0;
    if (enemy_list.num_enemies > 0) {
        do {
            if (actor == entry->enemy) {
                // If the enemy found is the last one on the list
                if ((i + 1) == enemy_list.num_enemies) {
                    EnemyList_clearEntry(entry);
                    enemy_list.num_enemies--;
                }
                // Otherwise copy the last entry into the removed enemy's slot and clear the last entry
                else {
                    last_entry = &enemy_list.enemies[enemy_list.num_enemies - 1];
                    *entry     = *last_entry;
                    EnemyList_clearEntry(last_entry);
                    enemy_list.num_enemies--;
                }
                break;
            }
            i++;
            entry++;
        } while (i < enemy_list.num_enemies);
    }
}

void func_8003E98C_3F58C() {}

/**
 * Given a set of enemy state flags, this function would print into the destination string
 * a letter for each state flag that was set, and a space otherwise.
 * See `EnemyList_enemyStates` for all possible letters, one per `EnemyListEntryFlag` value, in order.
 *
 * For example, if the state flags `(ENEMY_ALIVE | ENEMY_ACTIVE | ENEMY_DAMAGED)` are passed,
 * the function would have printed the following into the destination string: "PC D "
 *
 * @bug The function can only print the first 5 states from `EnemyListEntryFlag`,
 *       despite `EnemyList_enemyStates` supporting more letters.
 *
 *       This means that the `ENEMY_GRABBING_PLAYER` state will be printed as a space,
 *       despite being a valid state.
 */
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

/**
 * Clears an enemy entry
 */
void EnemyList_clearEntry(EnemyListEntry* entry) {
    memory_clear(entry, sizeof(EnemyListEntry));
}

/**
 * Returns the total number of enemies that are currently alive and active
 */
s32 EnemyList_getNumberOfActiveEnemies() {
    EnemyListEntry* entry;
    s32 i;
    s32 num_active_enemies;

    for (num_active_enemies = 0, i = 0, entry = ARRAY_START(enemy_list.enemies);
         i < enemy_list.num_enemies;
         i++, entry++) {
        if (entry->flags & (ENEMY_ALIVE | ENEMY_ACTIVE)) {
            num_active_enemies++;
        }
    }

    return num_active_enemies;
}

/**
 * Given a position vector, this function returns `TRUE` if there's at least one active enemy
 * that's inside the radius delimited by the given X, Y and Z maximum distances.
 */
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

/**
 * Returns the current time of the day.
 *
 * See `Enemy_timeOfDayList` for all possible values
 */
s32 EnemyList_getTimeOfDay() {
    s16 adjusted_hour = sys.SaveStruct_gameplay.hour - 4;

    if (adjusted_hour < 0) {
        adjusted_hour += 24;
    }

    return Enemy_timeOfDayList[adjusted_hour / 6];
}
