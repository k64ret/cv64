/**
 * File: difficulty_and_character_select.c
 * Description:
 *   Handles both the character selection screen when selecting a new game,
 *   as well as the difficulty selection.
 * Associated objects: 0x212E
 *
 * Mapped by the TLB? = Yes
 */

#include "objects/menu/mfds.h"
#include "objects/effect/distortion.h"
#include "objects/menu/characterSelect.h"
#include "system_work.h"

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/difficultySelect_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_areStructsCreated.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_showScroll.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_createLens.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_selectOption.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_optionSelected.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/difficulty_and_character_select/characterSelect_determineCharacterToSelect.s")

// clang-format on
