#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H

#include "gfx/light.h"
#include "gfx/model_info.h"
#include "objects/menu/mfds.h"
#include "objects/menu/mark.h"

typedef enum pc_select_work_flags {
    ENABLE_REINHARDT = 0x01,
    ENABLE_CARRIE    = 0x02
} pc_select_work_flags;

typedef struct {
    light* field_0x00;
    light* field_0x04;
    light* field_0x08;
    u8 flags;
    u8 field_0x0D[3];
    vec3f field_0x10;
    u8 field_0x1C;
    u8 number_of_characters;
    /**
    * The character ID that's going to be set into the SaveStruct +1
    */
    u8 player_character;
    s8 lens_not_moving;
    /**
    * Always set to 0, and copied to `lens_not_moving` when selecting a character
    */
    s8 field_0x20;
    u8 field_0x21;
    s16 current_character_option;
    s16 max_cursor_transition_delay;
    s16 current_cursor_transition_delay;
    u8 field_0x28[12];
    s8 previous_character_option;
    u8 field_0x35[7];
} pc_select_work;

// ID: 0x212E
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* character_portraits[2];
    u8 field_0x2C[8];
    union {
        u32 difficulty_select_state;
        void* scroll_state; // scroll_state*
    };
    union {
        void* miniScroll; // miniScroll*
        lens_obj* lens;
    };
    mfds_state* character_names[2];
    u8 field_0x44[8];
    mark_work* mark;
    u8 field_0x50[20];
    f32 lens_pos_multiplier;
    vec2f lens_pos;
    pc_select_work* work;
} characterSelect;

void characterSelect_entrypoint(characterSelect* self);
void difficultySelect_loop(characterSelect* self);
void characterSelect_areStructsCreated(characterSelect* self);
void characterSelect_init(characterSelect* self);
void characterSelect_showScroll(characterSelect* self);
void characterSelect_createLens(characterSelect* self);
void characterSelect_selectOption(characterSelect* self);
void characterSelect_optionSelected(characterSelect* self);
void characterSelect_destroy(characterSelect* self);
void characterSelect_determineCharacterToSelect(characterSelect* self);

typedef void (*characterSelect_func_t)(characterSelect*);

#endif // CHARACTER_SELECT_H
