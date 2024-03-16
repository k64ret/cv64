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

f32 vec3f_distance(vec3f* src1, vec3f* src2) {
    vec3f dest;

    vec3f_substract(&dest, src1, src2);
    return vec3f_magnitude(&dest);
}

f32 vec3f_magnitude(vec3f* src) {
    return sqrtf((src->z * src->z) + ((src->x * src->x) + (src->y * src->y)));
}

// Possibly scaleVectorPreservingDirection
f32 vec3f_80011440(vec3f* dest, vec3f* src, f32 scalar) {
    f32 magn;

    magn = vec3f_magnitude(src);
    if (magn != 0.0f) {
        vec3f_multiplyScalar(dest, src, scalar / magn);
    } else {
        vec3f_set(dest, 0.0f, 0.0f, 0.0f);
    }

    return magn;
}

void vec3f_add(vec3f* dest, vec3f* src1, vec3f* src2) {
    dest->x = src2->x + src1->x;
    dest->y = src2->y + src1->y;
    dest->z = src2->z + src1->z;
}

void vec3f_substract(vec3f* dest, vec3f* src1, vec3f* src2) {
    dest->x = src1->x - src2->x;
    dest->y = src1->y - src2->y;
    dest->z = src1->z - src2->z;
}

void vec3f_copy(vec3f* dest, vec3f* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

void vec3f_swap(vec3f* dest, vec3f* src) {
    vec3f temp;

    vec3f_copy(&temp, dest);
    vec3f_copy(dest, src);
    vec3f_copy(src, &temp);
}

void vec3f_multiplyScalar(vec3f* dest, vec3f* src, f32 scalar) {
    dest->x = src->x * scalar;
    dest->y = src->y * scalar;
    dest->z = src->z * scalar;
}

void vec3f_percentage(vec3f* dest, vec3f* src, f32 percent) {
    percent = 1.0f / percent;
    dest->x = src->x * percent;
    dest->y = src->y * percent;
    dest->z = src->z * percent;
}

void vec3f_complement(vec3f* dest, vec3f* src) {
    dest->x = -src->x;
    dest->y = -src->y;
    dest->z = -src->z;
}

// Possibly calculateVectorMagnitudePercentages
f32 vec3f_80011614(vec3f* dest, vec3f* src) {
    f32 magn;

    magn = vec3f_magnitude(src);
    if (magn != 0.0f) {
        vec3f_percentage(dest, src, magn);
    }

    return magn;
}

f32 vec3f_dotProduct(vec3f* src1, vec3f* src2) {
    return (src2->z * src1->z) + ((src1->x * src2->x) + (src1->y * src2->y));
}

void vec3f_crossProduct(vec3f* dest, vec3f* src1, vec3f* src2) {
    f32 temp1 = (src1->y * src2->z) - (src2->y * src1->z);
    f32 temp2 = (src1->z * src2->x) - (src2->z * src1->x);
    f32 temp3 = (src1->x * src2->y) - (src2->x * src1->y);

    dest->x = temp1;
    dest->y = temp2;
    dest->z = temp3;
}

// Possibly `vec3f_angle_between`
f32 vec3f_80011710(vec3f* arg0, vec3f* arg1) {
    f32 temp1 = vec3f_dotProduct(arg0, arg1);
    f32 temp2 = vec3f_magnitude(arg0);
    f32 temp3 = vec3f_magnitude(arg1);
    return func_80011310_11F10(temp1 / (temp2 * temp3));
}

void vec3f_set(vec3f* vec, f32 x, f32 y, f32 z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

// Possibly `vec3f_identity`
void vec3f_multiplyByOne(vec3f* dest) {
    vec3f_multiplyScalar(dest, dest, 1.0f);
}

// Possibly `vec3f_lerp`
void vec3f_800117a4(vec3f* dest, vec3f* src1, vec3f* src2, f32 scalar) {
    vec3f temp1;
    vec3f temp2;

    vec3f_multiplyScalar(&temp1, src1, 1.0f - scalar);
    vec3f_multiplyScalar(&temp2, src2, scalar);
    vec3f_add(dest, &temp1, &temp2);
}

// Possibly `vec3f_reflect`
void vec3f_80011808(vec3f* dest, vec3f* src1, vec3f* src2) {
    vec3f temp;

    vec3f_multiplyScalar(
        &temp, src2, (vec3f_dotProduct(src1, src2) / vec3f_dotProduct(src2, src2)) * 2
    );
    vec3f_substract(dest, src1, &temp);
}

// Possibly transformVectorByMatrix
// https://decomp.me/scratch/jpCsM
void func_80011880(vec3f* dest, vec3f* src, Matrix44F* mtx) {
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

void func_80011914_12514(vec3f* dest, vec3f* src, vec3f* rotation, s32 angle) {
    Matrix44F mtx;

    guAlignF(mtx, ANGLE_FIXED_POINT_TO_DEGREES(angle), rotation->x, rotation->y, rotation->z);
    func_80011880(dest, src, mtx);
}

// Possibly subtractProjectedVector
void func_80011984_12584(vec3f* arg0, vec3f* arg1, vec3f* arg2) {
    vec3f sp24;

    vec3f_multiplyScalar(&sp24, arg2, vec3f_dotProduct(arg1, arg2) / vec3f_dotProduct(arg2, arg2));
    vec3f_substract(arg0, arg1, &sp24);
}

// Either calculatePointProjectionOnLineSegment or projectedVectorFromLine
void func_800119F0_125F0(vec3f* arg0, vec3f* arg1, vec3f* arg2, vec3f* arg3) {
    f32 var_fv1;
    vec3f sp30;
    vec3f sp24;
    vec3f sp18;

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
