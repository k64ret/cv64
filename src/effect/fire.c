/**
 * @file dma.c
 *
 * This file defines functions involved with direct memory access and retrieving data from the cartridge.
 */

#include "objects/effect/fire.h"

// clang-format off

FireFuncs Fire_functions[] = {
    Fire_Init,
    Fire_Loop,
    Fire_Destroy
};

// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Destroy.s")
