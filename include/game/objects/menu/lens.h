#ifndef LENS_H
#define LENS_H

#include "object.h"
#include "gfx/model.h"
#include "objects/effect/distortion.h"
#include "window.h"

// ID: 0x0128
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    Model* lower_left_corner;
    Model* upper_right_corner;
    Model* lower_right_corner;
    Model* upper_stripe;
    Model* left_stripe;
    Model* right_stripe;
    Model* lower_stripe;
    Model* lens_flash; // The flash seen in the upper right corner
    Model* lens_background;
    Model* lens_background_overlay; // Overlay color for the lens background
    void* field_0x50;
    void* field_0x54;
    void* field_0x58;
    void* field_0x5C;
    obj_distortion* distortion;
    struct_78* field_0x64;
    window_work* field_0x68;
    window_work* field_0x6C;
    window_work* main_window;
} lens_obj;

extern window_work* lens_create(
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

extern u32 lensAreClosed(void);

#endif
