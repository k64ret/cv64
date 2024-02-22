#ifndef STAGE_SELECT_H
#define STAGE_SELECT_H

#include "object.h"
#include "gfx/model_info.h"
#include "objects/menu/mfds.h"
#include "objects/menu/lens.h"

#define STAGE_SELECT_NUM_OPTIONS 8

typedef enum stage_select_option_enum {
    FOREST = 0,
    INSIDE_OF_RAMPART = 1,
    COURTYARD = 2,
    EXECUTION_TOWER = 3,
    CLOCK_TOWER = 4,
    VS_DEATH = 5,
    VS_ACTRIESE = 6,
    VS_BEHIMOS = 7
} stage_select_option_enum_t;

typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[8];
    cv64_model_inf_t* red_background_model;
    u8 field_0x2C[8];
    mfds_state** textboxes;
    u8 field_0x38[24];
    window_work* lens_window_work;
    u8* assets_file_start;
    u8* assets_file_end;
    s8 text_ID;
    s8 field_0x5D;
    s8 field_0x5E;
    s8 lens_are_moving;
    s8 previous_option;
    u8 field_0x61[3];
    u32 current_option;
    f32 lens_transition_rate;
    f32 lens_move_offset;
    s16 field_0x70;
    u8 field_0x72[2];
} stageSelect;

typedef void (*cv64_stage_select_func_t)(stageSelect*);

void stageSelect_entrypoint(stageSelect* self);     // 8012a520
void stageSelect_init(stageSelect* self);           // 8012a590
void stageSelect_initGraphics(stageSelect* self);   // 8012a688
void stageSelect_initMenuButton(stageSelect* self); // 8012a904
void stageSelect_moveButton(stageSelect* self);     // 8012aa60
void stageSelect_warpToStage(stageSelect* self);    // 8012ac04
void stageSelect_closeTextboxes(stageSelect* self); // 8012aea0

#endif
