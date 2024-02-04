#ifndef WINDOW_H
#define WINDOW_H

// Textbox / option selection background window

#include "gfx/camera.h"
#include "struct_78.h"
#include <ultra64.h>

typedef struct {
    u32 flags;
    camera* display_camera;
    vec3f position;
    f32 width;
    f32 height;
    f32 field_0x1C;
    f32 field_0x20;
    f32 window_closing_speed;
    u8 field_0x28[8];
    cv64_rgba_t primitive_color;
    vec3f size;
    struct_78* field_0x40;
} window_work;

#endif
