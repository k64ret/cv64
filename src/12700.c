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
        var_a0 = value < 0.0f ? -1 : 1;
        temp_f4 += var_a0;
    }

    return temp_f4;
}

f32 f32_normalize(f32 value, f32 min, f32 max) {
    value = (value - min) / (max - min);

    if (value < 0.0f) {
        return 0.0f;
    }

    if (value > 1.0f) {
        return 1.0f;
    }

    return value;
}

#pragma GLOBAL_ASM("../asm/nonmatchings/12700/f32_clamp.s")

// https://decomp.me/scratch/D2hli
#pragma GLOBAL_ASM("../asm/nonmatchings/12700/func_80011C6C_1286C.s")
