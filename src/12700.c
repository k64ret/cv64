#include "cv64.h"
#include "math.h"

f32 f32_trunc(f32 value) {
    return (s32) value;
}

// https://decomp.me/scratch/dG8bd
#pragma GLOBAL_ASM("../asm/nonmatchings/12700/f32_simple_round_nearest.s")

f32 f32_round_nearest_with_sign(f32 value) {
    s32 temp_f4 = value;
    s32 var_v0  = temp_f4;
    s32 var_a0;

    if (value != temp_f4) {
        if (value < 0.0f) {
            var_a0 = -1;
        } else {
            var_a0 = 1;
        }
        temp_f4 += var_a0;
    }

    return temp_f4;
}

#pragma GLOBAL_ASM("../asm/nonmatchings/12700/f32_normalize.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/12700/f32_clamp.s")

// https://decomp.me/scratch/D2hli
#pragma GLOBAL_ASM("../asm/nonmatchings/12700/func_80011C6C_1286C.s")
