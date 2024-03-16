#ifndef MFDS_H
#define MFDS_H

// Textbox structs

#include "cv64.h"
#include "gfx/camera.h"
#include "gfx/model_info.h"
#include "objects/menu/lens.h"
#include "objects/menu/textboxAdvanceArrow.h"
#include "window.h"

// clang-format off

#define TEXT_COLOR_WHITE 0
#define TEXT_COLOR_RED   1
#define TEXT_COLOR_BEIGE 2
#define TEXT_COLOR_BROWN 3

typedef enum cv64_textbox_flag {
    MENU_TEXT_ID_PRINTS_ITEM        = CV64_BIT(0),
    MENU_TEXT_ID_PRINTS_MENU_STRING = CV64_BIT(1),
    PRINT_NUMBER                    = CV64_BIT(4),
    DISPLAY_LENS                    = CV64_BIT(6),      // Aka enable window_work
    ALLOC_TEXTBOX_IN_MENU_DATA_HEAP = CV64_BIT(14),
    SLOW_TEXT_TRANSITION            = CV64_BIT(20),
    FAST_TEXT_TRANSITION            = CV64_BIT(21),
    MFDS_FLAG_400000                = CV64_BIT(22),
    UPDATE_STRING                   = CV64_BIT(24),
    MFDS_FLAG_2000000               = CV64_BIT(25),
    CLOSE_TEXTBOX                   = CV64_BIT(26),
    OPEN_TEXTBOX                    = CV64_BIT(27),
    CLOSE_LENS                      = CV64_BIT(28),
    MFDS_FLAG_20000000              = CV64_BIT(29),
    TEXTBOX_IS_ACTIVE               = CV64_BIT(30),     // TODO: Double-check this
    HIDE_TEXTBOX                    = CV64_BIT(31)
} cv64_textbox_flag_t;

// clang-format on

typedef struct {
    u16 color;
    u16 time;
} mfds_color_anim_data;

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
    u8 palette;
    u8 field_0x0C[2];
    s16 field_0x0E;
    u8 flags;
    u8 field_0x11;
    vec2s position;
    vec2s field_0x16;
    u8 field_0x1A;
    u8 num_options;
    u8 current_option;
    u8 field_0x1C[17];
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
    u8 palette;
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
    union {
        u16* mfds_menu_string;
        u16* mfds_item_form;
    };
    mfds_number_work* number;
    mfds_color_animation_state* color_animation_state;
    window_work* window;
    mfds_dl_size* dl_size;
    mfds_ltex_buffer* ltex_buffer;
    mfds_tex_buffer* tex_buffer;
    mfds_work* work;
    mfds_state* state;
} obj_mfds;

extern mfds_state* textbox_create(void* parent_object, camera* display_camera, u32 flags);
extern void
textbox_setDimensions(mfds_state* self, s8 height, s16 width, u8 param_4, u8 character_spacing);
extern void textbox_setPos(mfds_state* self, u16 x, u16 y, s32 unused);
extern void
textbox_setMessagePtr(mfds_state* self, u16* text, u16* item_amount_number_text, s16 number);
extern void textbox_enableLens(mfds_state* self, u32 window_work_flags, f32 window_closing_speed);
extern u16* text_getMessageFromPool(u16* message_pool_base_ptr, s32 id);
extern void textbox_setScaleAndSomethingElse(
    mfds_state* self,
    u8 param_2,
    u8 param_3,
    f32 position_Z,
    f32 scale_X,
    f32 scale_Y,
    u8 param_7,
    u8 param_8
);
extern void text_convertIntNumberToText(u32, u16*, u8, u32);
extern u16* text_findCharInString(u16* text, u16 char_to_find);
extern mfds_color_anim_data text_color_anim_data_table[4][8];
extern u16* convertUTF16ToCustomTextFormat(u16* text_buffer);
extern void textbox_setHeightAndWidth(mfds_state* self, u32 index, u8 text_height, u8 text_width);
extern mfds_state* map_getMessageFromPool(u32 text_ID, u32 textbox_display_time);

#endif
