#ifndef LIBRARY_PUZZLE_H
#define LIBRARY_PUZZLE_H

#include "actor.h"
#include "objects/menu/mfds.h"

typedef enum cv64_ovl_librarypuzzledata_opt_id {
    OPTION_1 = CV64_BIT(0),
    OPTION_2 = CV64_BIT(1),
    OPTION_3 = CV64_BIT(2),
    OPTION_4 = CV64_BIT(3),
    OPTION_5 = CV64_BIT(4),
    OPTION_6 = CV64_BIT(5),
    OPTION_7 = CV64_BIT(6),
    OPTION_8 = CV64_BIT(7),
    OPTION_9 = CV64_BIT(8)
} cv64_ovl_librarypuzzledata_opt_id_t;

typedef struct cv64_ovl_librarypuzzledata {
    mfds_state* message_textbox;
    window_work* lens_window_work;
    u16 options_text[16];
    u8 field_0x28[8];
    u16 selected_options_IDs;
    u8 field_0x32[2];
    /**
     * Starts from 0, so option 1 is represented as 0
     */
    u32 highlighted_option;
} cv64_ovl_librarypuzzledata_t;

// ID: 0x2026
typedef struct cv64_ovl_librarypuzzletxt {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    cv64_ovl_librarypuzzledata_t* data;
    u8 field_0x38[4];
    u32 interacting_with_interactuable;
    u32 textbox_is_active;
    s32 first_option;
    s32 second_option;
    s32 third_option;
    u32 number_of_options_selected;
    s32 option_selected;
    u8 field_0x58[4];
    s16 trigger_size_X;
    s16 trigger_size_Z;
    mfds_state* message_textbox;
    vec3f position;
    cv64_actor_settings_t* settings;
} cv64_ovl_librarypuzzletxt_t;

void cv64_ovl_librarypuzzletxt_entrypoint(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_init(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_idle(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_show(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_prep_msg(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_select(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_fail(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_success(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_destroy(cv64_ovl_librarypuzzletxt_t* self);
void cv64_ovl_librarypuzzletxt_print_selected(u16* text, u16 selected_options_IDs);
s32 cv64_ovl_librarypuzzletxt_select_next(
    s32* highlighted_option, u16* selection_delay_timer, u16* selected_options_IDs
);

typedef enum cv64_ovl_librarypuzzletxt_func_id {
    LIBRARY_PUZZLE_INIT,
    LIBRARY_PUZZLE_IDLE,
    LIBRARY_PUZZLE_SHOW_FIRST_TEXTBOX,
    LIBRARY_PUZZLE_PUZZLE_PREPARE,
    LIBRARY_PUZZLE_PUZZLE_SELECT_OPTION,
    LIBRARY_PUZZLE_PUZZLE_FAIL,
    LIBRARY_PUZZLE_PUZZLE_SUCCESS,
    LIBRARY_PUZZLE_DESTROY
} cv64_ovl_librarypuzzletxt_func_id_t;

typedef void (*cv64_ovl_librarypuzzletxt_func_t)(cv64_ovl_librarypuzzletxt_t*);

#endif
