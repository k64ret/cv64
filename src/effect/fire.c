/**
 * @file fire.c
 *
 * The common decorative fire effect seeing above candles and other elements.
 */

#include "objects/effect/fire.h"
#include "objects/effect/fire_sparkles.h"

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

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Loop.s")

// clang-format on

void Fire_Destroy(Fire* self) {
    self->header.destroy(self);
}
