#ifndef LENS_H
#define LENS_H

#include "object.h"
#include "gfx/model.h"
#include "objects/effect/distortion.h"
#include "window.h"

// ID: 0x0128
typedef struct ObjLens {
    ObjectHeader header;
    u8 field_0x20[4];
    struct Model* model;
    struct Model* lower_left_corner;
    struct Model* upper_right_corner;
    struct Model* lower_right_corner;
    struct Model* upper_stripe;
    struct Model* left_stripe;
    struct Model* right_stripe;
    struct Model* lower_stripe;
    struct Model* lens_flash; // The flash seen in the upper right corner
    struct Model* lens_background;
    struct Model* lens_background_overlay; // Overlay color for the lens background
    void* field_0x50;
    void* field_0x54;
    void* field_0x58;
    void* field_0x5C;
    obj_distortion* distortion;
    struct_78* field_0x64;
    WindowWork* field_0x68;
    WindowWork* field_0x6C;
    WindowWork* main_window;
} ObjLens;

extern WindowWork* lens_create(
    void* parent,
    Camera* display_camera,
    u32 flags,
    f32 pos_X,
    f32 pos_Y,
    f32 pos_Z,
    f32 height,
    f32 width,
    f32 closing_speed
);

#endif
