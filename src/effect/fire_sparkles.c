/**
 * @file fire_sparkles.c
 *
 * Fire sparkles, usually used in conjuction with the `Fire` effect.
 */

#include "objects/effect/fire_sparkles.h"
#include <ultra64.h>

// clang-format off

Gfx FireSparkles_material_dlist[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, TEXEL1, PRIMITIVE_ALPHA, TEXEL1, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0),
    gsSPEndDisplayList(),
};

FireSparklesFuncs FireSparkles_functions[] = {
    FireSparkles_Init,
    FireSparkles_Loop,
    FireSparkles_Destroy
};

// clang-format on

void FireSparkles_Entrypoint(FireSparkles* self) {
    ENTER(self, FireSparkles_functions);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire_sparkles/FireSparkles_Init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire_sparkles/FireSparkles_Loop.s")

// clang-format on

void FireSparkles_Destroy(FireSparkles* self) {
    self->header.destroy(self);
}
