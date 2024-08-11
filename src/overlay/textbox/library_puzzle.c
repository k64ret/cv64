/**
 * @file library_puzzle.c
 *
 * Handles the puzzle from Castle Center's library.
 */

#include "objects/cutscene/library_puzzle.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

libraryPuzzle_func_t libraryPuzzle_functions[] = {
    libraryPuzzle_init,
    libraryPuzzle_idle,
    libraryPuzzle_showFirstTextbox,
    libraryPuzzle_puzzle_prepare,
    libraryPuzzle_puzzle_selectOption,
    libraryPuzzle_puzzle_fail,
    libraryPuzzle_puzzle_success,
    libraryPuzzle_destroy
};

// clang-format on

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_idle.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_showFirstTextbox.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_puzzle_prepare.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_puzzle_selectOption.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_puzzle_fail.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_puzzle_success.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_printSelectedOptions.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_selectNextOption.s")

// clang-format on
