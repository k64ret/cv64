#ifndef LIGHT_H
#define LIGHT_H

#include "gfx/color.h"
#include <ultra64.h>

// TODO: Fill this
typedef struct {
    u8 field_0x00[0x78];
} struct_48;

// TODO: Figure this out better
typedef struct {
    s16 type;
    u16 flags;
    struct light* prev;
    struct light* sibling;
    struct light* next;
    struct light* parent;
    u8 field1_0x14[28];
    void* field2_0x30;
    struct_48* field3_0x34;
    u8 field4_0x38[4];
    s32 field5_0x3c;
    u8 field6_0x40[40];
    cv64_rgba_t primitive_color;
    cv64_rgba_t environment_color;
    cv64_rgba_t blend_color;
    cv64_rgba_t fog_color;
    u8 field11_0x78[48];
} light;

extern light* light_create(u16 type);
extern light* D_8018CDE0[3];

#endif
