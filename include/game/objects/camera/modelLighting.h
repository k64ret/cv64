#ifndef MODEL_LIGHTING_H
#define MODEL_LIGHTING_H

#include "math.h"
#include "objects/camera/pointLight.h"
#include "gfx/light.h"

#define SIZE_AND_LIST_INDEX(size, index) (((size) << 0x10) | ((index) & 0x0F))

typedef struct {
    u32 field_0x00;
    u32 field_0x04[2]; // Some light indices
} light_list_t;

typedef struct {
    Vec3f* target_position;      // The position where the point light target is located at
    pointLight* point_lights[7]; // See 0x80010F5C
} point_light_list_t;

// ID: 0x006E
typedef struct modelLighting {
    ObjectHeader header;
    u8 field_0x20[4];
    FigureLight* model_light;
    u8 field_0x28[12];
    union {
        light_list_t light_list;
        point_light_list_t point_light_list;
    };
} modelLighting;

extern modelLighting* modelLighting_create(void* parent);
extern s32
modelLighting_createList(modelLighting* self, u32 size_and_index, Vec3f* target_position);

#endif
