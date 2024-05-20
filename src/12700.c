/**
 * @file 12700.c
 */

#include "cv64.h"
#include "math.h"

f32 f32_trunc(f32 value) {
    return (s32) value;
}

f32 f32_simple_round_nearest(f32 value) {
    return (s32) (value += value < 0.0f ? -0.5 : 0.5);
}

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

f32 f32_clamp(f32 value, f32 min, f32 max) {
    if (value < min) {
        return min;
    }

    if (max < value) {
        return max;
    }

    return value;
}

// https://decomp.me/scratch/yVAbQ
s32 func_80011C6C_1286C(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        arg1 = -arg1;
    }

    if (arg0 < 0) {
        arg0 = -arg0 % arg1;
        if (arg0 != 0) {
            arg0 = arg1 - arg0;
        }
    } else {
        arg0 %= arg1;
    }

    return arg0;
}
