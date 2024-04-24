#ifndef SCROLL_H
#define SCROLL_H

#include "gfx/camera.h"
#include "gfx/model_info.h"
#include "objects/menu/mark.h"

typedef enum scroll_state_flags {
    WHITE_DOWELS = 0x10,
    OPENED       = 0x20,
    OPENING      = 0x40,
    CLOSING      = 0x80,
    HIDE         = 0xC0
} scroll_state_flags;

typedef enum scroll_state_params {
    DATA                 = 1,
    SELECT               = 2,
    COPY                 = 3,
    DELETE               = 4,
    PLAYER_SELECT        = 5,
    OPTION               = 6,
    BUTTON_CONFIG        = 7,
    SOUND_MODE           = 8,
    PAUSE_MENU_ITEM_LIST = 9,
    RENON_SHOP_ITEM_LIST = 10,
    WIDE                 = 0x80
} scroll_state_params;

typedef struct {
    u32 flags;
    camera* field_0x04;
    camera* display_camera;
    vec3f position;
    vec3f width;
    u8 open_close_speed;
    u8 params;
    s16 lower_dowel_pitch_angle;
    u8 field_0x28[4];
    f32 field_0x2C;
    f32 field_0x30;
    u8 field_0x34;
    u8 field_0x35[3];
    vec3f field_0x38;
    f32 open_close_max_speed;
    f32 open_close_current_speed;
    f32 dowel_angle_multiplier;
    // The following pointers are all function pointers actually
    void* field_0x50;
    void* field_0x54;
    void* field_0x58;
    void* field_0x5C;
    void* field_0x60;
    void* field_0x64;
    void* field_0x68;
    void* field_0x6C;
    void* destroy_function;
    u8 field_0x74[4];
} scroll_state;

// ID: 0x0132
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* both_dowels;
    cv64_model_inf_t* lower_dowel;
    cv64_model_inf_t* scroll_background;
    /**
     * Data, Player Select, etc textures
     */
    cv64_model_inf_t* header_texture;
    s32 field_0x34;
    void* btnConfigMenu; // buttonConfigMenu*
    u32 field_0x3C;
    u32 field_0x40;
    mark_work* markWork;
    u8 field_0x48[24];
    s32 field_0x60;
    u8 field_0x64[4];
    u32 number_of_items_in_scroll;
    /**
     * Can be menu works, like sound_menu_work_keycon_menu_work, etc
     * Might need a generic "menu work" struct
     */
    void* work;
    scroll_state* state;
} scroll;

extern scroll_state* createScrollState(
    void* parent,
    void* param_2,
    void* display_camera,
    u32 flags,
    u8 params,
    f32 pos_X,
    f32 pos_Y,
    f32 pos_Z,
    f32 open_close_speed,
    void* work
);

typedef void (*scroll_func_t)(scroll*);

#endif
