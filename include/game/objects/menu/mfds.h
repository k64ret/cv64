#ifndef MFSD_H
#define MFSD_H

// Textbox structs

#include "gfx/camera.h"
#include "gfx/model_info.h"
#include "objects/menu/lens.h"
#include "objects/menu/textboxAdvanceArrow.h"
#include "window.h"
#include <ultra64.h>

typedef struct {
    u8 field_0x00;
    u8 transition_time[4];
    u8 field_0x05[4];
    u8 transition_point[4];
    u8 field_0x0D[3];
    mfds_color_anim_data* color_anim_data[4];
    u8 max_transition_time[4];
} mfds_color_animation_state;

typedef struct {
    u16* text;
    u8 field_0x04[2];
    s16 field_0x06;
    s16 field_0x08;
    u8 scroll_timer;
    u8 pallete;
    u8 field_0x0C[2];
    s16 field_0x0E;
    u8 flags;
    u8 field_0x11;
    vec2s position;
    vec2s field_0x16;
    u8 field_0x1A;
    u8 field_0x1B;
    u8 field_0x1C[18];
    u8 display_time;
    u8 field_0x2F;
    mfds_color_animation_state* color_animation_state;
} mfds_work;

// TODO: Fill This
typedef struct {
    u8 field_0x00[0x2B2];
} mfds_tex_buffer;

// TODO: Fill This
typedef struct {
    u8 text_char;
    u8 field_0x01[519];
} mfds_ltex_buffer;

typedef struct {
    u32 field_0x00;
    u32 field_0x04;
    u32 field_0x08;
} mfds_dl_size;

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

typedef struct {
    u16 color;
    u16 time;
} mfds_color_anim_data;

// TODO: Fill This
typedef struct {
    u8 field_0x00[0x1A];
} mfds_number_work;

typedef struct {
    u32 flags;
    camera* display_camera;
    u16* text; // Officially called "str1"
    u16* item_amount_text;
    s32 field_0x10;
    vec2s position;
    f32 position_Z;
    vec2f scale;
    s32 number;
    s32 field_0x28;
    u16 width;
    u8 field_0x2E;
    u8 textbox_option;
    u8 line;
    u8 field_0x31;
    u8 character_spacing;
    u8 field_0x33;
    u8 pallete;
    u8 menu_text_ID; // ID in the menu text pool that starts at 0x8016CEB8
    u8 field_0x36;
    u8 field_0x37[3];
    u8 visual_flags;
    u8 display_time;
    s8 field_0x3C;
    u8 field_0x3D[19];
    u8 field_0x50;
    u8 field_0x51;
    u8 field_0x52[2];
    u32 window_flags;
    f32 window_closing_speed;
    lens_obj* lens;
} mfds_state;

// ID: 0x0127
// Real name: obj_mfds
typedef struct {
    cv64_object_hdr_t header;
    u16 field_0x20;
    u16 field_0x22;
    u8 field_0x24[4];
    cv64_model_inf_t* model;
    u8 field_0x2C[8];
    Gfx** mfds_double;
    void* field_0x38;
    void* field_0x3C;
    textboxAdvanceArrow* advance_arrow;
    void* field_0x44;
    void* field_0x48;
    void* field_0x4C;
    u16* mfds_menu_string_and_mfds_item_form; // This may be a union?
    mfds_number_work* number;
    mfds_color_animation_state* color_animation_state;
    window_work* window;
    mfds_dl_size* dl_size;
    mfds_ltex_buffer* ltex_buffer;
    mfds_tex_buffer* tex_buffer;
    mfds_work* work;
    mfds_state* state;
} obj_mfds;

#endif
