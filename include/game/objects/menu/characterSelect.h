#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H

#include "gfx/light.h"
#include "gfx/model.h"
#include "objects/menu/mfds.h"
#include "objects/menu/mark.h"
#include "objects/menu/scroll.h"
#include "objects/menu/miniScroll.h"
#include "system_work.h"

/**
 * In early versions of the game, it was possible for character slots
 * to be disabled / locked, preventing a character from being selected.
 * This would make their portraits colored in dark gold color
 * (https://tcrf.net/images/7/74/CV64_early_character_selection_screen.jpg)
 *
 * The final game still retains that functionality and even has the dark gold palettes
 * that would have been used to color the disabled icons.
 * However, those palettes belonged to an early rendition of the character portraits that's
 * no longer in the game, so enabling this feature will make the character portraits
 * look corrupted.
 */
#define ENABLED_PALETTE  0
#define DISABLED_PALETTE 1 // Unused

typedef enum pc_select_work_flags {
    ENABLE_REINHARDT       = 0x01,
    ENABLE_CARRIE          = 0x02,
    ENABLE_CORNELL         = 0x04, // Unused
    ENABLE_COLLER          = 0x08, // Unused
    PC_SELECT_WORK_FLAG_40 = 0x40  // Used, but never read from in practice
} pc_select_work_flags;

typedef enum difficulty_select_state_enum {
    CREATE_SCROLL               = 0, // Default state
    CREATE_TEXT_NON_HARD_MODE   = 1,
    CREATE_TEXT_HARD_MODE       = 2,
    WAIT_UNTIL_SCROLL_IS_OPENED = 3,
    SELECT_OPTION               = 4,
    EXIT                        = 5
} difficulty_select_state_enum;

typedef struct {
    FigureLight* scroll_dowels_light;
    FigureLight* scroll_elements_light;
    FigureLight* lens_light;
    u8 flags;
    u8 field_0x0D[3];
    Vec3f field_0x10;
    u8 field_0x1C;
    u8 number_of_characters;
    /**
    * The character ID that's going to be set into the SaveStruct +1
    */
    u8 player_character;
    u8 lens_not_moving;
    /**
    * Always set to FALSE, and copied to `lens_not_moving` when selecting a character
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

typedef struct {
    union {
        u32 difficulty_select_state;
        scroll_state* scrollState;
    };
    union {
        miniScroll* mini_scroll;
        WindowWork* lens;
    };
    union {
        MfdsState* character_names[NUM_CHARACTERS];
        MfdsState* difficulty_text;
    };
    u8 field_0x44[8];
    mark_work* mark;
    u8 field_0x50[20];
    f32 lens_pos_multiplier;
    Vec2f lens_pos;
    pc_select_work* work;
} characterSelectInner;

// ID: 0x212E
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* character_portraits[NUM_CHARACTERS];
    u8 field_0x2C[8];
    characterSelectInner inner;
} characterSelect;

void characterSelect_entrypoint(characterSelect* self);
void difficultySelect_loop(characterSelect* self);
void characterSelect_areStructsCreated(characterSelect* self);
void characterSelect_init(characterSelect* self);
void characterSelect_openScroll(characterSelect* self);
void characterSelect_createLens(characterSelect* self);
void characterSelect_selectOption(characterSelect* self);
void characterSelect_optionSelected(characterSelect* self);
void characterSelect_destroy(characterSelect* self);
void characterSelect_determineCharacterToSelect(
    pc_select_work* work, s8 new_character_option_offset
);

typedef void (*characterSelect_func_t)(characterSelect*);

extern const u32 REINHARDT_PORTRAIT_DL;
extern const u32 REINHARDT_PORTRAIT_MATERIAL_DL;
extern const u32 CARRIE_PORTRAIT_DL;
extern const u32 CARRIE_PORTRAIT_MATERIAL_DL;

#endif // CHARACTER_SELECT_H
