#ifndef LIGHT_H
#define LIGHT_H

#include "gfx/color.h"
#include <ultra64.h>

// TODO: Fill this
typedef struct {
    u8 field_0x00[0x78];
} struct_48;

typedef struct {
    cv64_rgba_t color;
    /**
     * X, Y, Z
     */
    s8 direction[3];
    /**
     * Starting from 1. Index of the current light in the list.
     */
    u8 index;
} light_parameters;

// TODO: Figure this out better
typedef struct {
    s16 type;
    u16 flags;
    struct light* prev;
    struct light* sibling;
    struct light* next;
    struct light* parent;
    u8 field1_0x14[28];
    struct light* field2_0x30;
    /**
     * The actual data starts at +0x10
     */
    struct_48* field3_0x34;
    u8 field4_0x38[4];
    /**
     * Current total number of lights in the light list
     */
    s32 number_of_lights;
    u8 field6_0x40[40];
    cv64_rgba_t ambient_color;
    u8 field_0x6C[3];
    u8 field_0x6F; // See 0x800109B0
    /**
     * Light list
     */
    light_parameters lights[7];
} light;

extern light* light_create(u16 type);
extern light* map_lights[3];
extern light* ptr_master_light;

#endif
