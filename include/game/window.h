#ifndef WINDOW_H
#define WINDOW_H

// Textbox / option selection background window

#include "gfx/camera.h"
#include "struct_78.h"
#include <ultra64.h>

typedef enum cv64_window_flag {
    WINDOW_FLAG_1 = CV64_BIT(0),
    WINDOW_FLAG_4 = CV64_BIT(2),
    WINDOW_FLAG_10 = CV64_BIT(4),
    WINDOW_FLAG_20 = CV64_BIT(5),
    WINDOW_FLAG_40 = CV64_BIT(6),
    WINDOW_FLAG_80 = CV64_BIT(7),
    WINDOW_CLOSING = CV64_BIT(8),
    WINDOW_OPENING = CV64_BIT(9),
    WINDOW_OPENED_X = CV64_BIT(12),
    WINDOW_OPENED_Y = CV64_BIT(13),
    WINDOW_FLAG_4000 = CV64_BIT(14),
    WINDOW_FLAG_8000 = CV64_BIT(15),
    WINDOW_FLAG_40000 = CV64_BIT(18),
    WINDOW_HIDE = CV64_BIT(19),
    WINDOW_FLAG_800000 = CV64_BIT(23)
} cv64_window_flag_t;

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

extern void windowWork_setParams(
    window_work* window_work,
    u32 flags,
    u8 param_3,
    u8 param_4,
    f32 distortion_size,
    f32 param_6,
    void* param_7
);

#endif
