#ifndef COLLISION_H
#define COLLISION_H

#include "math.h"
#include <ultra64.h>

// NOTE: "type" and "variable" could actually be a union, since IIRC there's
// code that loads both as u16
typedef struct cv64_collision_triangle {
    u8 type;
    u8 variable; // For example, footstep_sfx. If 0x80, fall death. If 0xA2,
                 // lava death
    vec3s vtx_pos[3]; // Vertices positions
} cv64_collision_triangle_t;

#endif
