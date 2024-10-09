#ifndef LIGHT_H
#define LIGHT_H

#include "gfx/color.h"
#include <ultra64.h>

// TODO: Fill this
typedef struct {
    u8 field_0x00[0x78];
} struct_48;

typedef struct {
    RGBA color;
    /**
     * X [0]
     * Y [1]
     * Z [2]
     */
    s8 direction[3];
    /**
     * Starting from 1. Index of the current light in the list.
     */
    u8 index;
} light_parameters;

/**
 * @note Can't `typedef` this struct defintion as `Light` because there is a conflicting
 * `union` definition in libultra, so we decided to rename it to `FigureLight`.
 */
typedef struct FigureLight {
    s16 type;
    u16 flags;
    struct FigureLight* prev;
    struct FigureLight* sibling;
    struct FigureLight* next;
    struct FigureLight* parent;
    u8 field1_0x14[28];
    struct FigureLight* field2_0x30;
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
    RGBA ambient_color;
    u8 field_0x6C[3];
    u8 field_0x6F; // See 0x800109B0
    /**
     * Light list
     */
    light_parameters lights[7];
} FigureLight;

extern FigureLight* light_create(u16 type);
extern FigureLight* map_lights[3];
extern FigureLight* ptr_master_light;

extern void light_setAmbientColor(FigureLight* self, u32 ambient_color);
extern void light_setColorAndDirection(FigureLight* self, s32 index, u32 color, u32 direction);
extern s32 light_addColorAndDirection(FigureLight* self, u32 color, u32 direction);
extern s32 light_addColorAndDirectionOrSetAmbientColorIfListIsEmpty(
    FigureLight* self, u32 ambient_color, u32 direction
);

#endif
