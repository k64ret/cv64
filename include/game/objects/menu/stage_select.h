#ifndef STAGE_SELECT_H
#define STAGE_SELECT_H

#include "object.h"
#include "gfx/model_info.h"
#include "objects/menu/mfds.h"
#include "objects/menu/lens.h"

#define STAGE_SELECT_NUM_OPTIONS 8

/**
* Time since the current option was selected.
* This is never updated, so it's always 0
* in practice.
*/
#define OPTION_SELECTION_TIMER self->header.timer

typedef enum stage_select_option_enum {
    FOREST            = 0,
    INSIDE_OF_RAMPART = 1,
    COURTYARD         = 2,
    EXECUTION_TOWER   = 3,
    CLOCK_TOWER       = 4,
    VS_DEATH          = 5,
    VS_ACTRIESE       = 6,
    VS_BEHIMOS        = 7
} stage_select_option_enum_t;

typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[8];
    Model* red_background_model;
    u8 field_0x2C[8];
    mfds_state** textboxes;
    u8 field_0x38[24];
    window_work* lens;
    u8* assets_file_start;
    u8* assets_file_end;
    s8 text_ID;
    s8 next_text_ID;
    u8 field_0x5E;
    s8 lens_are_moving;
    s8 previous_option;
    u8 field_0x61[3];
    s32 current_option;
    f32 lens_transition_rate;
    f32 lens_move_offset;
    s16 lens_move_vertical_difference;
    u8 field_0x72[2];
} stageSelect;

typedef void (*cv64_stage_select_func_t)(stageSelect*);

void stageSelect_entrypoint(stageSelect* self);     // 0x8012A520
void stageSelect_loadAssetsFile(stageSelect* self); // 0x8012A590
void stageSelect_initGraphics(stageSelect* self);   // 0x8012A688
void stageSelect_initLens(stageSelect* self);       // 0x8012A904
void stageSelect_moveLens(stageSelect* self);       // 0x8012AA60
void stageSelect_warpToStage(stageSelect* self);    // 0x8012AC04
void stageSelect_closeTextboxes(stageSelect* self); // 0x8012AEA0

#endif
