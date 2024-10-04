/**
 * @file demo50.c
 *
 * This file contains the code that handles the following cutscene:
 * - Unused Death Cutscene (`CUTSCENE_ID_UNUSED_DEATH`)
 *
 * This cutscene appeared in prerelease material of the game
 * https://tcrf.net/Castlevania_(Nintendo_64)#Unused_Cutscene
 */

#include "objects/cutscene/demo50.h"
#include "memory.h"
#include "system_work.h"

Demo50Func Demo50_functions[] = {
    Demo50_Init,
    Demo50_CreateCutsceneCamera,
    Demo50_GetPlayerModelAndSetBorders,
    Demo50_Loop,
    Demo50_Restart
};

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_Entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_Init.s")

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_CreateCutsceneCamera.s"             \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_GetPlayerModelAndSetBorders.s"      \
)

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_Loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_Restart.s")

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_PlayDeathAnimations.s"              \
)
