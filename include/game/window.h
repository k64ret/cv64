#ifndef WINDOW_H
#define WINDOW_H

// Textbox / option selection background window

#include "bit.h"
#include "gfx/camera.h"
#include "struct_78.h"
#include <ultra64.h>

typedef enum WindowFlag {
    WINDOW_FLAG_OPEN_RIGHT = BIT(0),
    WINDOW_FLAG_OPEN_LEFT  = BIT(1),
    WINDOW_FLAG_OPEN_DOWN  = BIT(2),
    WINDOW_FLAG_OPEN_UP    = BIT(3),
    /**
     * This flag combined with `WINDOW_FLAG_OPEN_DOWN_RIGHT` makes the lens open from the upper-left
     * corner to the lower-right one.
     */
    WINDOW_FLAG_OPEN_RIGHT_DOWN = BIT(4),
    /**
     * This flag combined with `WINDOW_FLAG_OPEN_RIGHT_DOWN` makes the lens open from the upper-left
     * corner to the lower-right one.
     */
    WINDOW_FLAG_OPEN_DOWN_RIGHT = BIT(5),
    WINDOW_FLAG_40              = BIT(6),
    WINDOW_FLAG_80              = BIT(7),
    WINDOW_CLOSING              = BIT(8),
    WINDOW_OPENING              = BIT(9),
    WINDOW_OPENED_X             = BIT(12),
    WINDOW_OPENED_Y             = BIT(13),
    WINDOW_FLAG_4000            = BIT(14),
    WINDOW_FLAG_8000            = BIT(15),
    WINDOW_FLAG_40000           = BIT(18),
    WINDOW_HIDE                 = BIT(19),
    WINDOW_FLAG_200000          = BIT(21),
    /**
     * Seems to enable lens distortion, similar to `WINDOW_FLAG_ENABLE_DISTORTION_EFFECT`
     */
    WINDOW_FLAG_400000                   = BIT(22),
    WINDOW_FLAG_ENABLE_DISTORTION_EFFECT = BIT(23)
} WindowFlag;

typedef struct WindowWork {
    u32 flags;
    Camera* display_camera;
    Vec3f position;
    f32 width;
    f32 height;
    f32 field_0x1C;
    f32 field_0x20;
    f32 window_closing_speed;
    u8 field_0x28[8];
    RGBA primitive_color;
    Vec3f size;
    struct_78* field_0x40;
} WindowWork;

extern void WindowWork_setParams(
    WindowWork* work,
    u32 flags,
    u8 param_3,
    u8 param_4,
    f32 distortion_size,
    f32 param_6,
    void* param_7
);

#endif
