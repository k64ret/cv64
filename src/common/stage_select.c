/**
 * @file stage_select.c
 *
 * This file contains the code that drives the unused Stage Select game state
 *
 * See this TCRF.net article for more information:
 * https://tcrf.net/Castlevania_(Nintendo_64)/Unused_Code#Stage_Select
 */

#include "cv64.h"
#include "memory.h"
#include "objects/engine/DMAMgr.h"
#include "gfx/camera.h"
#include "atari.h"
#include "gamestate.h"
#include "system_work.h"
#include "objects/menu/stage_select.h"

u16 stageselect_text[] = {
#include "objects/menu/stage_select.msg"
};

StageSelectFunc stageselect_funcs[] = {
    StageSelect_loadAssetsFile,
    StageSelect_initGraphics,
    StageSelect_initLens,
    StageSelect_moveLens,
    StageSelect_warpToStage,
    object_doNothing
};

const char stageselect_unused_str_1[] = "Model Trans OK!!\n";
const char stageselect_unused_str_2[] = "Mfds Set OK!!\n";
const char stageselect_unused_str_3[] = "Rens Set OK!!\n";
const char stageselect_unused_str_4[] = "Slect Stage : %02d\n";

void StageSelect_entrypoint(StageSelect* self) {
    ENTER(self, stageselect_funcs);
}

void StageSelect_loadAssetsFile(StageSelect* self) {
    if (((*Fade_IsFading)() != FALSE) || (ptr_DMAMgr->DMAChunkMgr == NULL))
        return;

    (*Fade_SetSettings)(FADE_IN, 30, 0, 0, 0);
    sys.cutscene_flags = 0;
    (*heap_init)(
        HEAP_KIND_MENU_DATA,
        &HEAP_MENU_DATA_START,
        HEAP_MENU_DATA_SIZE,
        HEAP_WRITE_BACK_CACHE_TO_RAM
    );
    self->assets_file_end   = NULL;
    self->assets_file_start = (*heap_alloc)(HEAP_KIND_MENU_DATA, NI_ASSETS_MENU_BUFFER_SIZE);
    DMAMgr_loadNisitenmaIchigoFile(
        ptr_DMAMgr, NI_ASSETS_MENU, (u32) self->assets_file_start, &self->assets_file_end
    );
    NisitenmaIchigo_checkAndStoreLoadedFile(NI_ASSETS_MENU);
    (*object_allocEntryInList)(self, HEAP_KIND_MULTIPURPOSE, sizeof(MfdsState* [10]), 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void StageSelect_initGraphics(StageSelect* self) {
    Model* bg_model;
    MfdsState** textbox_array = self->textboxes;

    if (self->assets_file_end == NULL)
        return;

    heapBlock_updateBlockMaxSize(
        self->assets_file_start, (u32) self->assets_file_end - (u32) self->assets_file_start
    );
    bg_model = Model_createAndSetChild(FIG_TYPE_HUD_ELEMENT, common_camera_8009B444);
    self->red_background_model = bg_model;
    bg_model->assets_file      = NI_ASSETS_MENU;
    bg_model->dlist            = &MENU_RED_BACKGROUND_DL;
    BITS_SET(bg_model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    bg_model->primitive_color.integer = RGBA(255, 255, 255, 255);
    bg_model->position.x              = 0.0f;
    bg_model->position.y              = 0.0f;
    bg_model->position.z              = 0.0f;
    bg_model->size.x                  = 1.0f;
    bg_model->size.y                  = 1.0f;
    bg_model->size.z                  = 1.0f;

    for (self->text_ID = 0; self->text_ID < STAGE_SELECT_NUM_OPTIONS + 1; self->text_ID++) {
        textbox_array[self->text_ID] = (*textbox_create)(
            self,
            common_camera_8009B444,
            (MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED)
        );

        if (textbox_array[self->text_ID] == 0)
            continue;

        textbox_array[self->text_ID]->palette = TEXT_COLOR_WHITE;
        if (self->text_ID != 0) {
            (*textbox_setPos)(textbox_array[self->text_ID], 30, (self->text_ID * 23) + 23, 1);
        } else {
            textbox_array[self->text_ID]->palette = TEXT_COLOR_BEIGE;
            (*textbox_setPos)(textbox_array[self->text_ID], 100, 10, 1);
            (*textbox_setHeightAndWidth)(textbox_array[self->text_ID], 1, 2, 1);
        }
        (*textbox_setDimensions)(textbox_array[self->text_ID], 1, 300, 0, 0);
        (*textbox_setMessagePtr)(
            textbox_array[self->text_ID],
            text_getMessageFromPool(stageselect_text, self->text_ID),
            NULL,
            0
        );
    }
    (*atari_work_table_init)();
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void StageSelect_initLens(StageSelect* self) {
    WindowWork* lens;
    MfdsState** textbox_array = self->textboxes;

    if ((*Fade_IsFading)() != FALSE)
        return;

    for (self->text_ID = 0; self->text_ID < STAGE_SELECT_NUM_OPTIONS + 1; self->text_ID++) {
        if (BITS_NOT_HAS(textbox_array[self->text_ID]->flags, MFDS_FLAG_TEXT_IS_PARSED)) {
            return;
        }
    }
    self->lens = (*lens_create)(
        self,
        common_camera_HUD,
        (WINDOW_FLAG_ENABLE_DISTORTION_EFFECT | WINDOW_FLAG_80 | WINDOW_FLAG_OPEN_DOWN_RIGHT |
         WINDOW_FLAG_OPEN_RIGHT_DOWN | WINDOW_FLAG_OPEN_DOWN | WINDOW_FLAG_OPEN_RIGHT),
        -120.0f,
        61.0f,
        10.0f,
        2.0f,
        240.0f,
        90.0f
    );
    if ((lens = self->lens) != NULL) {
        (*WindowWork_setParams)(lens, 0, 7, 5, 1.6f, 1.0f, NULL);
        BITS_UNSET(lens->flags, WINDOW_CLOSING);
        BITS_SET(lens->flags, WINDOW_OPENING);
    }
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void StageSelect_moveLens(StageSelect* self) {
    WindowWork* lens = self->lens;
    s32 current_option;
    s8 previous_option;

    if (self->lens_are_moving) {
        self->lens_move_offset = self->lens_transition_rate / 4;
        if (self->lens_move_offset >= 1.) {
            self->lens_are_moving  = FALSE;
            self->lens_move_offset = 1;
        }
        lens->position.y =
            (self->lens_move_offset * self->lens_move_vertical_difference) + self->text_ID;
        self->lens_transition_rate += 1.0;
        return;
    }
    current_option  = self->current_option;
    previous_option = self->previous_option;
    if (current_option == (u32) previous_option) {
        if (CONT_BTNS_PRESSED(CONT_0, A_BUTTON) ||
            CONT_BTNS_PRESSED(CONT_0, START_BUTTON | RECENTER_BUTTON)) {
            BITS_UNSET(lens->flags, WINDOW_OPENING);
            BITS_SET(lens->flags, WINDOW_CLOSING);
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        } else {
            (*menuButton_selectNextOption)(
                &self->current_option, &OPTION_SELECTION_TIMER, STAGE_SELECT_NUM_OPTIONS
            );
        }
        return;
    }
    self->lens_are_moving               = TRUE;
    self->previous_option               = current_option;
    self->text_ID                       = (61 - ((f64) previous_option * 23));
    self->next_text_ID                  = (61 - ((f64) current_option * 23));
    self->lens_transition_rate          = 0;
    self->lens_move_vertical_difference = self->next_text_ID - self->text_ID;
}

void StageSelect_warpToStage(StageSelect* self) {
    s16 i, j;
    WindowWork* lens = self->lens;

    if (!(BITS_MASK(lens->flags, WINDOW_FLAG_4000 | WINDOW_FLAG_8000) >> 0xE))
        return;

    StageSelect_closeTextboxes(self);

    sys.SaveStruct_gameplay.map           = MAP_NONE;
    sys.SaveStruct_gameplay.spawn         = -1;
    sys.SaveStruct_gameplay.life          = 100;
    sys.SaveStruct_gameplay.field_0x5C    = 100;
    sys.SaveStruct_gameplay.subweapon     = SUBWEAPON_NONE;
    sys.SaveStruct_gameplay.gold          = 0;
    sys.SaveStruct_gameplay.player_status = 0;

    // Remove inventory items
    // clang-format off
    for (i = 1; i < NUM_ITEMS + 1; i++) sys.SaveStruct_gameplay.items.array[i - 1] = 0;
    // clang-format on

    sys.SaveStruct_gameplay.week         = 0;
    sys.SaveStruct_gameplay.day          = 0;
    sys.SaveStruct_gameplay.hour         = 0;
    sys.SaveStruct_gameplay.minute       = 0;
    sys.SaveStruct_gameplay.seconds      = 0;
    sys.SaveStruct_gameplay.milliseconds = 0;

    // Clear event flags
    // clang-format off
    for (j = 0; j < NUM_EVENT_FLAGS; j++) sys.SaveStruct_gameplay.event_flags[j] = 0;
    // clang-format on

    sys.field89_0x2644c = 0;
    BITS_UNSET(sys.cutscene_flags, CUTSCENE_FLAG_PLAYING);
    sys.current_boss_actor_ID = 0;

    switch (self->current_option) {
        case FOREST:
            sys.entrance_cutscene_ID = CUTSCENE_ID_FOREST_INTRO;
            sys.map_fade_out_time    = 30;
            sys.map_fade_in_time     = 30;
            sys.map                  = MORI;
            sys.spawn                = 0;
            sys.map_fade_in_color.r  = 0;
            sys.map_fade_in_color.g  = 0;
            sys.map_fade_in_color.b  = 0;
            break;

        case INSIDE_OF_RAMPART:
            sys.entrance_cutscene_ID = CUTSCENE_ID_CASTLE_WALL_BRIDGE_RAISES;
            sys.map                  = TOUOKUJI;
            sys.map_fade_out_time    = 30;
            sys.map_fade_in_time     = 30;
            sys.spawn                = 0;
            sys.map_fade_in_color.r  = 0;
            sys.map_fade_in_color.g  = 0;
            sys.map_fade_in_color.b  = 0;
            break;

        case COURTYARD:
            BITS_SET(sys.cutscene_flags, CUTSCENE_FLAG_IS_ENTRANCE_CUTSCENE);
            sys.entrance_cutscene_ID = CUTSCENE_ID_ENTERING_VILLA;
            sys.map                  = NAKANIWA;
            sys.map_fade_out_time    = 30;
            sys.map_fade_in_time     = 30;
            sys.spawn                = 0;
            sys.map_fade_in_color.r  = 0;
            sys.map_fade_in_color.g  = 0;
            sys.map_fade_in_color.b  = 0;
            break;

        case EXECUTION_TOWER:
            sys.map                 = SHOKEI_TOU;
            sys.map_fade_out_time   = 30;
            sys.map_fade_in_time    = 30;
            sys.spawn               = 0;
            sys.map_fade_in_color.r = 0;
            sys.map_fade_in_color.g = 0;
            sys.map_fade_in_color.b = 0;
            break;

        case CLOCK_TOWER:
            sys.map                 = TOKEITOU_NAI;
            sys.map_fade_out_time   = 30;
            sys.map_fade_in_time    = 30;
            sys.spawn               = 0;
            sys.map_fade_in_color.r = 0;
            sys.map_fade_in_color.g = 0;
            sys.map_fade_in_color.b = 0;
            break;

        case VS_DEATH:
            // clang-format off
            sys.map = TURO_TOKEITOU, // Comma needed for matching
                sys.spawn = 1;
            // clang-format on
            sys.map_fade_out_time   = 30;
            sys.map_fade_in_time    = 30;
            sys.map_fade_in_color.r = 0;
            sys.map_fade_in_color.g = 0;
            sys.map_fade_in_color.b = 0;
            break;

        case VS_ACTRIESE:
            sys.map                 = TURO_TOKEITOU;
            sys.map_fade_out_time   = 30;
            sys.map_fade_in_time    = 30;
            sys.spawn               = 0;
            sys.map_fade_in_color.r = 0;
            sys.map_fade_in_color.g = 0;
            sys.map_fade_in_color.b = 0;
            break;

        case VS_BEHIMOS:
            sys.map                 = HONMARU_B1F;
            sys.map_fade_out_time   = 30;
            sys.map_fade_in_time    = 30;
            sys.spawn               = 0;
            sys.map_fade_in_color.r = 0;
            sys.map_fade_in_color.g = 0;
            sys.map_fade_in_color.b = 0;
            break;
    }

    gamestate_change(GAMESTATE_GAMEPLAY);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void StageSelect_closeTextboxes(StageSelect* self) {
    MfdsState** textbox_array = self->textboxes;

    // TODO: (WINDOW_CLOSING | WINDOW_OPENING) represents flag 0x300.
    // However, we don't know if that specific flag represents something
    // not related to opening / closing the lens
    BITS_SET(self->lens->flags, WINDOW_CLOSING | WINDOW_OPENING);
    for (self->text_ID = 0; self->text_ID < STAGE_SELECT_NUM_OPTIONS + 1; self->text_ID++) {
        BITS_SET(textbox_array[self->text_ID]->flags, MFDS_FLAG_CLOSE_TEXTBOX);
    }
    (*heap_free)(HEAP_KIND_MENU_DATA);
}
