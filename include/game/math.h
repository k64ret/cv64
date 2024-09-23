#ifndef MATH_H
#define MATH_H

#include <ultra64.h>

#define ANGLE_FIXED_POINT_TO_DEGREES(angle) (angle * (360.0f / 65536))

typedef struct Vec2 {
    s16 x, y;
} Vec2;

typedef struct Vec2f {
    f32 x, y;
} Vec2f;

typedef struct Vec3 {
    s16 x, y, z;
} Vec3;

typedef struct {
    f32 x, y, z;
} vec3f;

typedef struct {
    s16 pitch, yaw, roll;
} angle_t;

typedef f32 Matrix44F[4][4];

extern f32 atan2f(f32 arg1, f32 arg2);
extern s16 atan2s(s16 y, s16 x);

f32 func_80011310_11F10(f32 src);
f32 func_80011370_11F70(f32 src);
f32 vec3f_distance(vec3f* src1, vec3f* src2);
f32 vec3f_magnitude(vec3f* src);
f32 vec3f_80011440(vec3f* dest, vec3f* src, f32 scalar);
void vec3f_add(vec3f* dest, vec3f* src1, vec3f* src2);
void vec3f_substract(vec3f* dest, vec3f* src1, vec3f* src2);
void vec3f_copy(vec3f* dest, vec3f* src);
void vec3f_swap(vec3f* dest, vec3f* src);
void vec3f_multiplyScalar(vec3f* dest, vec3f* src, f32 scalar);
void vec3f_percentage(vec3f* dest, vec3f* src, f32 percent);
void vec3f_complement(vec3f* dest, vec3f* src);
f32 vec3f_80011614(vec3f* dest, vec3f* src);
f32 vec3f_dotProduct(vec3f* src1, vec3f* src2);
void vec3f_crossProduct(vec3f* dest, vec3f* src1, vec3f* src2);
f32 vec3f_80011710(vec3f* arg0, vec3f* arg1);
void vec3f_set(vec3f* vec, f32 x, f32 y, f32 z);
void vec3f_multiplyByOne(vec3f* dest);
void vec3f_800117a4(vec3f* dest, vec3f* src1, vec3f* src2, f32 scalar);
void vec3f_80011808(vec3f* dest, vec3f* src1, vec3f* src2);
void func_80011880(vec3f* dest, vec3f* src, Matrix44F* mtx);
void func_80011914_12514(vec3f* dest, vec3f* src, vec3f* rotation, s32 angle);
void func_80011984_12584(vec3f* arg0, vec3f* arg1, vec3f* arg2);
void func_800119F0_125F0(vec3f* arg0, vec3f* arg1, vec3f* arg2, vec3f* arg3);

f32 f32_trunc(f32 value);
f32 f32_simple_round_nearest(f32 value);
f32 f32_round_nearest_with_sign(f32 value);
/**
 * Given a start and end value within a range,
 * returns the percentage of the relative position of value in that range.
 */
f32 f32_normalize(f32 value, f32 min, f32 max);
f32 f32_clamp(f32 value, f32 min, f32 max);
s32 func_80011C6C_1286C(s32 arg0, s32 arg1);

#endif
