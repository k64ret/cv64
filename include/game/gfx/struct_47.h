#ifndef STRUCT_47_H
#define STRUCT_47_H

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
    struct struct_47* prev;
    struct struct_47* sibling;
    struct struct_47* next;
    struct struct_47* parent;
    u8 field1_0x14[28];
    void* field2_0x30;
    struct_48* field3_0x34;
    u8 field4_0x38[4];
    s32 field5_0x3c;
    u8 field6_0x40[40];
    color_union primitive_color;
    color_union environment_color;
    color_union blend_color;
    color_union fog_color;
    u8 field11_0x78[48];
} struct_47;

extern struct_47* func_80004C40(u16 type);
extern void* func_80004CE8(void* current, void* prev);      // TODO: Put this in another header

#endif
