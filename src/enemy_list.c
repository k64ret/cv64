/**
 * @file enemy_list.c
 *
 * Contains the code that handles the enemy list,
 * a record of the enemies currently loaded and their state
 */

#include "cv64.h"

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_addOrModifyEntry.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_removeEntry.s")

void func_8003e98c() {}

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/func_8003e994.s")

void func_8003ea7c() {}

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/func_8003ea84.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_clearEntry.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_getNumberOfActiveEnemies.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_isAnyEnemyWithinRange.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/enemy_list/EnemyList_getTimeOfDay.s")

// clang-format on
