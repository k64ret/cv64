#ifndef LENS_H
#define LENS_H

#include "object.h"
#include "gfx/model_info.h"
#include "objects/effect/distortion.h"
#include "window.h"

// ID: 0x0128
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    cv64_model_inf_t* lower_left_corner;
    cv64_model_inf_t* upper_right_corner;
    cv64_model_inf_t* lower_right_corner;
    cv64_model_inf_t* upper_stripe;
    cv64_model_inf_t* left_stripe;
    cv64_model_inf_t* right_stripe;
    cv64_model_inf_t* lower_stripe;
    cv64_model_inf_t* lens_flash; // The flash seen in the upper right corner
    cv64_model_inf_t* lens_background;
    cv64_model_inf_t*
        lens_background_overlay; // Overlay color for the lens background
    void* field_0x50;
    void* field_0x54;
    void* field_0x58;
    void* field_0x5C;
    distortion_obj* distortion;
    struct_78* field_0x64;
    window_work* field_0x68;
    window_work* field_0x6C;
    window_work* main_window;
} lens_obj;

extern window_work* lens_create(
    void* parent,
    camera* display_camera,
    u32 flags,
    f32 pos_X,
    f32 pos_Y,
    f32 pos_Z,
    f32 height,
    f32 width,
    f32 closing_speed
);

extern u32 lensAreClosed();

#endif
