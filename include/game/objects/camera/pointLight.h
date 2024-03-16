#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "actor.h"

typedef struct {
    u8 field_0x00[8];
    u32 field_0x08;
} struct_15;

typedef struct {
    u8 field_0x00[2];
    s16 field_0x02;
    vec3f position;
    vec2f max_light_distance;
    cv64_rgba_t color;
    struct_15 field_0x1C;
} pointLightData;

// ID: 0x006F
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    pointLightData data;
    u8 field_0x5C[20];
    cv64_actor_settings_t* settings;
} pointLight;

extern void pointLight_entrypoint(pointLight* self);

#endif
