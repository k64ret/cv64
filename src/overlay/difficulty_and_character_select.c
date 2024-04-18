#include "cv64.h"

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
