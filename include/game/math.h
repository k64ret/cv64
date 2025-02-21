#ifndef MATH_H
#define MATH_H

#include <ultra64.h>

/**
 * Converts a fixed point angle into degrees
 */
#define FIXED_TO_DEG(fixed) (f32)(fixed * (360.0f / 65536.0f))

/**
 * Converts an angle in degrees into fixed point
 */
#define DEG_TO_FIXED(degrees) (u16)((degrees) * 65536.0f / 360.0f)

typedef struct Vec2 {
    s16 x, y;
} Vec2;

typedef struct Vec2f {
    f32 x, y;
} Vec2f;

typedef struct Vec3 {
    s16 x, y, z;
} Vec3;

typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

typedef struct Angle {
    s16 pitch, yaw, roll;
} Angle;

typedef f32 Mat4f[4][4];

extern f32 atan2f(f32 arg1, f32 arg2);
extern s16 atan2s(s16 y, s16 x);

f32 func_80011310_11F10(f32 src);
f32 func_80011370_11F70(f32 src);
f32 vec3f_distance(Vec3f* src1, Vec3f* src2);
f32 vec3f_magnitude(Vec3f* src);
f32 vec3f_80011440(Vec3f* dest, Vec3f* src, f32 scalar);
void vec3f_add(Vec3f* dest, Vec3f* src1, Vec3f* src2);
void vec3f_substract(Vec3f* dest, Vec3f* src1, Vec3f* src2);
void vec3f_copy(Vec3f* dest, Vec3f* src);
void vec3f_swap(Vec3f* dest, Vec3f* src);
void vec3f_multiplyScalar(Vec3f* dest, Vec3f* src, f32 scalar);
void vec3f_percentage(Vec3f* dest, Vec3f* src, f32 percent);
void vec3f_complement(Vec3f* dest, Vec3f* src);
f32 vec3f_80011614(Vec3f* dest, Vec3f* src);
f32 vec3f_dotProduct(Vec3f* src1, Vec3f* src2);
void vec3f_crossProduct(Vec3f* dest, Vec3f* src1, Vec3f* src2);
f32 vec3f_80011710(Vec3f* arg0, Vec3f* arg1);
void vec3f_set(Vec3f* vec, f32 x, f32 y, f32 z);
void vec3f_multiplyByOne(Vec3f* dest);
void vec3f_800117a4(Vec3f* dest, Vec3f* src1, Vec3f* src2, f32 scalar);
void vec3f_80011808(Vec3f* dest, Vec3f* src1, Vec3f* src2);
void func_80011880(Vec3f* dest, Vec3f* src, Mat4f* mtx);
void func_80011914_12514(Vec3f* dest, Vec3f* src, Vec3f* rotation, s32 angle);
void func_80011984_12584(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2);
void func_800119F0_125F0(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3);
extern void vec3f_substractFloats(f32*, f32*, f32*);

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
