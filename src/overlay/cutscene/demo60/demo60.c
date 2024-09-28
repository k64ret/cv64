/**
 * @file demo60.c
 *
 * This file contains the code that handles the following cutscene:
 * - Forest of Silence's Intro (`CUTSCENE_ID_FOREST_INTRO`)
 */

#include "cv64.h"
#include "objects/cutscene/demo60.h"
#include "memory.h"
#include "sound.h"
#include "system_work.h"

#include "animations/reinhardt/blessing.inc.h"
#include "animations/carrie/blessing.inc.h"

#include "camera_data/D_0E001190.inc.h"
#include "camera_data/D_0E0011E8.inc.h"
#include "camera_data/D_0E001284.inc.h"

Demo60Func Demo60_functions[] = {
    Demo60_Init,
    Demo60_CreateCutsceneCamera,
    Demo60_GetPlayerModelAndSetBorders,
    Demo60_Loop,
    Demo60_Destroy
};

void Demo60_Entrypoint(Demo60* self) {
    ENTER(self, Demo60_functions);
}

void Demo60_Init(Demo60* self) {
    Demo60Data* data;

    (*Fade_SetSettings)(FADE_OUT, 1, 0, 0, 0);
    self->state = DEMO60_FADE_IN;
    data        = (Demo60Data*) (*object_allocEntryInListAndClear)(
        self, HEAP_KIND_MULTIPURPOSE, sizeof(Demo60Data), 1
    );
    self->skip_cutscene = FALSE;
    data->game_camera   = common_camera_game_view;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void Demo60_CreateCutsceneCamera(Demo60* self) {
    s32 temp;
    Camera* cutscene_camera;
    Demo60Data* data = self->data;

    cutscene_camera =
        (Camera*) (*Model_createAndSetChild)(FIG_TYPE_CAMERA_CUTSCENE, data->game_camera);
    data->cutscene_camera                      = cutscene_camera;
    self->cutscene_camera                      = cutscene_camera;
    data->current_camera_movement.cam_position = &data->cutscene_camera->position;
    if (1) {
    }
    data->current_camera_movement.cam_angle                = &data->cutscene_camera->field36_0x4c;
    data->current_camera_movement.cam_look_at_dir_offset.y = 0.0f;
    data->current_camera_movement.cam_look_at_dir_offset.x = 0.0f;
    data->current_camera_movement.cam_look_at_dir_offset.z = 0.0f;

    (*Cutscene_UpdateCameraLookAtDir)(data->game_camera, &data->current_camera_movement);
    self->current_time = 0;
    self->max_time     = 380;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void Demo60_GetPlayerModelAndSetBorders(Demo60* self) {
    Demo60Data* data = self->data;
    Model* player_model;

    if ((sys.map_is_setup) && (ptr_PlayerData != NULL)) {
        if (ptr_PlayerData->visualData.model != NULL) {
            player_model       = ptr_PlayerData->visualData.model;
            data->player_model = player_model;
            sys.cutscene_flags &= ~CUTSCENE_FLAG_IS_ENTRANCE_CUTSCENE;
            sys.cutscene_flags |= CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

void Demo60_Loop(Demo60* self) {
    s32 temp[4];
    CutsceneCoordinatesConfig* coords;
    Demo60Data* data = self->data;
    s32 current_time;
    u32 i;

    if (self->skip_cutscene) {
        if (self->state == DEMO60_RUNNING) {
            (*Fade_SetSettings)(FADE_OUT, 10, 0, 0, 0);
            self->state = DEMO60_FADE_OUT;
        }

        if (self->state == DEMO60_SET_MAP_CAMERA_PARAMETERS) {
            (*Map_SetCameraParams)();
        }

        if (self->state == DEMO60_RESET_BORDERS) {
            sys.cutscene_flags &= ~CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS;
            (*cutscene_setCameraClippingAndScissoring)(DL_SCISSORING_FULLSCREEN);
            self->current_time = self->max_time - 1;
            self->state        = DEMO60_SET_MAP_CAMERA_PARAMETERS;
        }

        if ((self->state == DEMO60_FADE_OUT) && ((*Fade_IsFading)() == FALSE)) {
            self->state = DEMO60_RESET_BORDERS;
        }
    }

    for (coords = ARRAY_START(D_0E0011E8); coords < ARRAY_END(D_0E0011E8); coords++) {
        if ((self->current_time >= coords->start_time) &&
            (coords->end_time >= self->current_time)) {
            (*func_801299A4)(
                self->current_time, data->cutscene_camera, coords, &data->cam_mov_state_init, 0
            );
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_0E001190); i++) {
        coords = &D_0E001190[i];
        if ((self->current_time >= coords->start_time) &&
            (coords->end_time >= self->current_time)) {
            switch (coords->field_0x00) {
                case 5:
                case 6:
                    (*func_80128D20)(
                        self->current_time,
                        data->game_camera,
                        data->cutscene_camera,
                        coords,
                        &data->cam_mov_state_turn_and_move_to_player,
                        0
                    );
                    break;
                default:
                    (*func_801299A4)(
                        self->current_time,
                        data->game_camera,
                        coords,
                        &data->cam_mov_state_turn_and_move_to_player,
                        0
                    );
                    break;
            }
            (*Cutscene_UpdateCameraLookAtDir)(data->game_camera, &data->current_camera_movement);
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_0E001284); i++) {
        coords = &D_0E001284[i];
        if ((self->current_time >= coords->start_time) &&
            (coords->end_time >= self->current_time)) {
            if (coords->player_anims_array_index == 2) {
                switch (coords->field_0x00) {
                    case 0:
                    case 1:
                        (*func_801299A4)(
                            self->current_time,
                            data->player_model,
                            coords,
                            &data->cam_mov_state_blessing,
                            1
                        );
                        break;
                }
                Demo60_PlayPlayerBlessingAnim(self, coords);
            } else {
                (*func_8012A130)(
                    self,
                    data->player_model,
                    ARRAY_START(D_0E001284),
                    &data->cam_mov_state_blessing,
                    ARRAY_COUNT(D_0E001284),
                    1
                );
            }
        }
    }

    current_time = self->current_time;
    if ((current_time == (D_0E001284[2].start_time + 75)) &&
        (sys.SaveStruct_gameplay.character == REINHARDT)) {
        (*play_sound)(SD_REINHARDT_BLESSING);
    }

    current_time = self->current_time;
    if ((current_time == (D_0E001284[2].start_time + 60)) &&
        (sys.SaveStruct_gameplay.character == CARRIE)) {
        (*play_sound)(SD_CARRIE_BLESSING);
    }

    if (self->state == DEMO60_FADE_IN) {
        (*Fade_SetSettings)(FADE_IN, 10, 0, 0, 0);
        self->state = DEMO60_WAIT_UNTIL_FADE_IN_IS_OVER;
    }

    if (self->state == DEMO60_WAIT_UNTIL_FADE_IN_IS_OVER) {
        if ((*Fade_IsFading)() == FALSE) {
            self->state = DEMO60_RUNNING;
        } else {
            return;
        }
    }

    if (self->max_time >= self->current_time) {
        self->current_time++;
    }

    if (self->max_time < self->current_time) {
        (*Map_SetCameraParams)();
        if (self->skip_cutscene) {
            (*Fade_SetSettings)(FADE_IN, 25, 0, 0, 0);
            (*Cutscene_SetCameraPosToEndCoords)(ARRAY_END(D_0E001190) - 1, data->game_camera);
            (*Cutscene_SetCameraPosToEndCoords)(ARRAY_END(D_0E0011E8) - 1, data->cutscene_camera);
            (*Cutscene_UpdateCameraLookAtDir)(data->game_camera, &data->current_camera_movement);
            (*Cutscene_SetEndCoordsToActor)(ARRAY_END(D_0E001284) - 1, data->player_model);
        }
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void Demo60_Destroy(Demo60* self) {
    sys.entrance_cutscene_ID = CUTSCENE_ID_NONE;
    self->header.destroy(self);
}

void Demo60_PlayPlayerBlessingAnim(Demo60* self, CutsceneCoordinatesConfig* coords) {
    Demo60Data* data            = self->data;
    actorVisualData* visualData = &ptr_PlayerData->visualData;
    s32 temp;

    if (coords->player_anims_array_index == 2) {
        switch (sys.SaveStruct_gameplay.character) {
            case REINHARDT:
                (*Actor_updateAnimParamsWhenDiffRotationPtrs)(
                    visualData, &trans_Reindhart_blessing, &rot_Reindhart_blessing, 1.0f
                );
                break;
            case CARRIE:
                (*Actor_updateAnimParamsWhenDiffRotationPtrs)(
                    visualData, &trans_Carrie_blessing, &rot_Carrie_blessing, 1.0f
                );
                break;
        }
    }

    if ((*animationMgr_animateFrame)(&visualData->animMgr, data->player_model) == -2) {
        (*animationMgr_unsetSmoothEndAnimationFlag)(&visualData->animMgr);
    }
}
