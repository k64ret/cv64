/**
 * @file vec3f.c
 *
 * Contains code for different math-related operations, as well as operations with vectors.
 */

#include "math.h"

f32 func_80011310_11F10(f32 src) {
    f32 src_squared;
    f32 sqrt;

    src_squared = src * src;
    sqrt        = (src_squared > 1.0f) ? 0.0f : sqrtf(1.0f - src_squared);

    return atan2f(sqrt, src);
}

f32 func_80011370_11F70(f32 src) {
    f32 src_squared;
    f32 sqrt;

    src_squared = src * src;
    sqrt        = (src_squared > 1.0f) ? 0.0f : sqrtf(1.0f - src_squared);

    return atan2f(src, sqrt);
}

f32 vec3f_distance(Vec3f* src1, Vec3f* src2) {
    Vec3f dest;

    vec3f_substract(&dest, src1, src2);
    return vec3f_magnitude(&dest);
}

f32 vec3f_magnitude(Vec3f* src) {
    return sqrtf((src->z * src->z) + ((src->x * src->x) + (src->y * src->y)));
}

// Possibly scaleVectorPreservingDirection
f32 vec3f_80011440(Vec3f* dest, Vec3f* src, f32 scalar) {
    f32 magn;

    magn = vec3f_magnitude(src);
    if (magn != 0.0f) {
        vec3f_multiplyScalar(dest, src, scalar / magn);
    } else {
        vec3f_set(dest, 0.0f, 0.0f, 0.0f);
    }

    return magn;
}

void vec3f_add(Vec3f* dest, Vec3f* src1, Vec3f* src2) {
    dest->x = src2->x + src1->x;
    dest->y = src2->y + src1->y;
    dest->z = src2->z + src1->z;
}

void vec3f_substract(Vec3f* dest, Vec3f* src1, Vec3f* src2) {
    dest->x = src1->x - src2->x;
    dest->y = src1->y - src2->y;
    dest->z = src1->z - src2->z;
}

void vec3f_copy(Vec3f* dest, Vec3f* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void vec3f_swap(Vec3f* dest, Vec3f* src) {
    Vec3f temp;

    vec3f_copy(&temp, dest);
    vec3f_copy(dest, src);
    vec3f_copy(src, &temp);
}

void vec3f_multiplyScalar(Vec3f* dest, Vec3f* src, f32 scalar) {
    dest->x = src->x * scalar;
    dest->y = src->y * scalar;
    dest->z = src->z * scalar;
}

void vec3f_percentage(Vec3f* dest, Vec3f* src, f32 percent) {
    percent = 1.0f / percent;
    dest->x = src->x * percent;
    dest->y = src->y * percent;
    dest->z = src->z * percent;
}

void vec3f_complement(Vec3f* dest, Vec3f* src) {
    dest->x = -src->x;
    dest->y = -src->y;
    dest->z = -src->z;
}

// Possibly calculateVectorMagnitudePercentages
f32 vec3f_80011614(Vec3f* dest, Vec3f* src) {
    f32 magn;

    magn = vec3f_magnitude(src);
    if (magn != 0.0f) {
        vec3f_percentage(dest, src, magn);
    }

    return magn;
}

f32 vec3f_dotProduct(Vec3f* src1, Vec3f* src2) {
    return (src2->z * src1->z) + ((src1->x * src2->x) + (src1->y * src2->y));
}

void vec3f_crossProduct(Vec3f* dest, Vec3f* src1, Vec3f* src2) {
    f32 temp1 = (src1->y * src2->z) - (src2->y * src1->z);
    f32 temp2 = (src1->z * src2->x) - (src2->z * src1->x);
    f32 temp3 = (src1->x * src2->y) - (src2->x * src1->y);

    dest->x = temp1;
    dest->y = temp2;
    dest->z = temp3;
}

// Possibly `vec3f_angle_between`
f32 vec3f_80011710(Vec3f* arg0, Vec3f* arg1) {
    f32 temp1 = vec3f_dotProduct(arg0, arg1);
    f32 temp2 = vec3f_magnitude(arg0);
    f32 temp3 = vec3f_magnitude(arg1);
    return func_80011310_11F10(temp1 / (temp2 * temp3));
}

void vec3f_set(Vec3f* vec, f32 x, f32 y, f32 z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

// Possibly `vec3f_identity`
void vec3f_multiplyByOne(Vec3f* dest) {
    vec3f_multiplyScalar(dest, dest, 1.0f);
}

// Possibly `vec3f_lerp`
void vec3f_800117a4(Vec3f* dest, Vec3f* src1, Vec3f* src2, f32 scalar) {
    Vec3f temp1;
    Vec3f temp2;

    vec3f_multiplyScalar(&temp1, src1, 1.0f - scalar);
    vec3f_multiplyScalar(&temp2, src2, scalar);
    vec3f_add(dest, &temp1, &temp2);
}

// Possibly `vec3f_reflect`
void vec3f_80011808(Vec3f* dest, Vec3f* src1, Vec3f* src2) {
    Vec3f temp;

    vec3f_multiplyScalar(
        &temp, src2, (vec3f_dotProduct(src1, src2) / vec3f_dotProduct(src2, src2)) * 2
    );
    vec3f_substract(dest, src1, &temp);
}

// Possibly transformVectorByMatrix
// https://decomp.me/scratch/jpCsM
void func_80011880(Vec3f* dest, Vec3f* src, Mat4f* mtx) {
    f32 temp_fa0 = ((mtx[0][0][0] * src->x) + (mtx[0][1][0] * src->y)) + (mtx[0][2][0] * src->z) +
        mtx[0][3][0];
    f32 temp_fa1 = ((mtx[0][0][1] * src->x) + (mtx[0][1][1] * src->y)) + (mtx[0][2][1] * src->z) +
        mtx[0][3][1];
    f32 temp_fv1 = ((mtx[0][0][2] * src->x) + (mtx[0][1][2] * src->y)) + (mtx[0][2][2] * src->z) +
        mtx[0][3][2];

    dest->x = temp_fa0;
    dest->y = temp_fa1;
    dest->z = temp_fv1;
}

void func_80011914_12514(Vec3f* dest, Vec3f* src, Vec3f* rotation, s32 angle) {
    Mat4f mtx;

    guAlignF(mtx, ANGLE_FIXED_POINT_TO_DEGREES(angle), rotation->x, rotation->y, rotation->z);
    func_80011880(dest, src, mtx);
}

// Possibly subtractProjectedVector
void func_80011984_12584(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2) {
    Vec3f sp24;

    vec3f_multiplyScalar(&sp24, arg2, vec3f_dotProduct(arg1, arg2) / vec3f_dotProduct(arg2, arg2));
    vec3f_substract(arg0, arg1, &sp24);
}

// Either calculatePointProjectionOnLineSegment or projectedVectorFromLine
void func_800119F0_125F0(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3) {
    f32 var_fv1;
    Vec3f sp30;
    Vec3f sp24;
    Vec3f sp18;

    vec3f_substract(&sp30, arg2, arg1);
    vec3f_substract(&sp24, arg3, arg1);
    var_fv1 = vec3f_dotProduct(&sp30, &sp30);
    if (var_fv1 != 0.0f) {
        var_fv1 = vec3f_dotProduct(&sp30, &sp24) / var_fv1;
    }
    if (var_fv1 < 0.0f) {
        vec3f_substract(arg0, arg1, arg3);
        return;
    }
    if (var_fv1 > 1.0f) {
        vec3f_substract(arg0, arg2, arg3);
        return;
    }
    vec3f_multiplyScalar(&sp18, &sp30, var_fv1);
    vec3f_add(&sp18, &sp18, arg1);
    vec3f_substract(arg0, &sp18, arg3);
}
