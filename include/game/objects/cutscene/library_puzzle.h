#ifndef LIBRARY_PUZZLE_H
#define LIBRARY_PUZZLE_H

#include "actor.h"
#include "objects/menu/mfds.h"

typedef enum libraryPuzzleData_optionIDs {
    OPTION_1 = CV64_BIT(0),
    OPTION_2 = CV64_BIT(1),
    OPTION_3 = CV64_BIT(2),
    OPTION_4 = CV64_BIT(3),
    OPTION_5 = CV64_BIT(4),
    OPTION_6 = CV64_BIT(5),
    OPTION_7 = CV64_BIT(6),
    OPTION_8 = CV64_BIT(7),
    OPTION_9 = CV64_BIT(8)
} libraryPuzzleData_optionIDs;

typedef struct libraryPuzzleData {
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
} libraryPuzzleData;

// ID: 0x2026
typedef struct libraryPuzzle {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    libraryPuzzleData* data;
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
} libraryPuzzle;

void libraryPuzzle_entrypoint(libraryPuzzle* self);
void libraryPuzzle_init(libraryPuzzle* self);
void libraryPuzzle_idle(libraryPuzzle* self);
void libraryPuzzle_showFirstTextbox(libraryPuzzle* self);
void libraryPuzzle_puzzle_prepare(libraryPuzzle* self);
void libraryPuzzle_puzzle_selectOption(libraryPuzzle* self);
void libraryPuzzle_puzzle_fail(libraryPuzzle* self);
void libraryPuzzle_puzzle_success(libraryPuzzle* self);
void libraryPuzzle_destroy(libraryPuzzle* self);
void libraryPuzzle_printSelectedOptions(libraryPuzzle* self);
void libraryPuzzle_selectNextOption(libraryPuzzle* self);

typedef enum libraryPuzzle_func_id {
    LIBRARY_PUZZLE_INIT,
    LIBRARY_PUZZLE_IDLE,
    LIBRARY_PUZZLE_SHOW_FIRST_TEXTBOX,
    LIBRARY_PUZZLE_PUZZLE_PREPARE,
    LIBRARY_PUZZLE_PUZZLE_SELECT_OPTION,
    LIBRARY_PUZZLE_PUZZLE_FAIL,
    LIBRARY_PUZZLE_PUZZLE_SUCCESS,
    LIBRARY_PUZZLE_DESTROY
} libraryPuzzle_func_id_t;

typedef void (*libraryPuzzle_func_t)(libraryPuzzle*);

#endif
