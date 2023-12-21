#ifndef MATH_H
#define MATH_H

#include <ultra64.h>

typedef struct {
    s16 x, y;
} vec2s;

typedef struct {
    f32 x, y;
} vec2f;

typedef struct {
    s16 x, y, z;
} vec3s;

typedef struct {
    f32 x, y, z;
} vec3f;

typedef struct {
    s16 pitch, yaw, roll;
} angle_t;

#endif
