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

void Fire_Entrypoint(Fire* self) {
    ENTER(self, Fire_functions);
}

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Loop.s")

void Fire_Destroy(Fire* self) {
    self->header.destroy(self);
}
