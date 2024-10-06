/**
 * @file demo50.c
 *
 * This file contains the code that handles the following cutscene:
 * - Unused Death Cutscene (`CUTSCENE_ID_UNUSED_DEATH`)
 *
 * This cutscene appeared in prerelease material of the game
 * https://tcrf.net/Castlevania_(Nintendo_64)#Unused_Cutscene
 */

#include "objects/cutscene/demo50.h"
#include "memory.h"
#include "system_work.h"

#include "camera_data/D_0E000740.inc.h"
#include "camera_data/D_0E000784.inc.h"
#include "camera_data/D_0E00079C.inc.h"
#include "camera_data/D_0E0007E0.inc.h"

// clang-format off

Demo50Func Demo50_functions[] = {
    Demo50_Init,
    Demo50_SetupMainCutsceneParams,
    Demo50_SetupData,
    Demo50_Loop,
    Demo50_Restart
};

// clang-format on

void Demo50_Entrypoint(Demo50* self) {
    ENTER(self, Demo50_functions);
}

void Demo50_Init(Demo50* self) {
    Demo50Data* data;

    data = (Demo50Data*) (*object_allocEntryInListAndClear)(
        self, HEAP_KIND_MULTIPURPOSE, sizeof(Demo50Data), 0
    );

    if (1) {
    }

    self->skip_cutscene = FALSE;
    data->game_camera   = common_camera_game_view;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void Demo50_SetupMainCutsceneParams(Demo50* self) {
    s32 temp;
    Camera* cutscene_camera;
    Demo50Data* data;

    /**
     * @bug Restarting the cutscene at this point will make the game unable
     *      to initialize important data needed for it to work.
     *
     *      Although it appears that triggering this is not normally possible,
     *      even when trying to skip the cutscene as early as possible.
     */
    if (self->skip_cutscene) {
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, DEMO50_RESTART
        );
        return;
    }

    data = self->data;
    cutscene_camera =
        (Camera*) (*Model_createAndSetChild)(FIG_TYPE_CAMERA_CUTSCENE, data->game_camera);
    data->cutscene_camera                                  = cutscene_camera;
    self->cutscene_camera                                  = cutscene_camera;
    data->current_camera_movement.cam_position             = &data->cutscene_camera->position;
    data->current_camera_movement.cam_angle                = &data->cutscene_camera->field36_0x4c;
    data->current_camera_movement.cam_look_at_dir_offset.x = 0.0f;
    data->current_camera_movement.cam_look_at_dir_offset.z = 0.0f;
    data->current_camera_movement.cam_look_at_dir_offset.y = 18.0f;
    (*Cutscene_UpdateCameraLookAtDir)(data->game_camera, &data->current_camera_movement);
    self->death        = (Death*) (*object_createAndSetChild)(self, ENEMY_DEATH);
    self->current_time = 0;
    self->max_time     = 200;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void Demo50_SetupData(Demo50* self) {
    Model* death_model;
    Demo50Data* data;
    actorVisualData* death_visual_data;
    DeathData* death_data;

    data = self->data;
    if ((sys.map_is_setup) && (ptr_PlayerData != NULL)) {
        data->player_model = ptr_PlayerData->visualData.model;
        death_model        = self->death->model;

        if (death_model != NULL) {
            /**
             * Setup the death parameters on the cutscene's struct
             */
            data->death_model[0]    = death_model;
            data->death_data        = self->death->data;
            death_visual_data       = &data->death_data->visual_data;
            data->death_anim_mgr[0] = &death_visual_data->animMgr;

            (*mapOverlay)(self->death);
            (*Death_UpdateAnimParamsCutscene)(
                DEATH_ANIM_IDLE, 1.0f, death_visual_data, data->death_data
            );
            (*Death_AnimateFrameCutscene)(
                data->death_data, data->death_model[0], data->death_anim_mgr[0]
            );
            (*unmapOverlay)(self->death);

            sys.cutscene_flags |= CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

// https://decomp.me/scratch/JbQZ3
#ifdef NON_MATCHING
// clang-format off
    #pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_Loop.s")
// clang-format on
#else
void Demo50_Loop(Demo50* self) {
    CutsceneCoordinatesConfig* coords;
    DeathData* death_data;
    Demo50Data* data;
    Death* death;
    u32 i;

    data = self->data;

    /**
    * @bug Skipping the cutscene will make it stuck infinitely
    *      on the current frame, since it's not possible for `self->skip_cutscene`
    *      to become `FALSE` after it's been set to `TRUE`
    *
    *      This in turn prevents the cutscene's timer (`self->current_time`) to advance
    */
    if (self->skip_cutscene) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
        return;
    }

    for (i = 0; i < ARRAY_COUNT(D_0E000740); i++) {
        coords = &D_0E000740[i];
        if ((self->current_time >= coords->start_time) &&
            (coords->end_time >= self->current_time)) {
            (*func_8012A2B8)(
                self,
                data->death_model[coords->field_0x01],
                coords,
                &data->cam_mov_state_1[coords->field_0x01]
            );
            /**
            * None of the `CutsceneCoordinatesConfig` arrays for this cutscene
            * have `field_0x00` set to 4
            *
            * Setting any of the entries' `field_0x00` in `D_0E000740` to 4
            * will prevent updating Death's animations for that keyframe
            */
            if (coords->field_0x00 != 4) {
                Demo50_PlayDeathAnimations(self, coords);
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_0E00079C); i++) {
        coords = &D_0E00079C[i];
        if ((self->current_time >= coords->start_time) &&
            (coords->end_time >= self->current_time)) {
            (*func_801299A4)(
                self->current_time, data->cutscene_camera, coords, &data->cam_mov_state_3, 0
            );
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_0E000784); i++) {
        coords = &D_0E000784[i];
        if ((self->current_time >= coords->start_time) &&
            (coords->end_time >= self->current_time)) {
            (*func_801299A4)(
                self->current_time, data->game_camera, coords, &data->cam_mov_state_2, 0
            );
            (*Cutscene_UpdateCameraLookAtDir)(data->game_camera, &data->current_camera_movement);
        }
    }

    (*func_8012A130)(
        self,
        data->player_model,
        ARRAY_START(D_0E0007E0),
        &data->cam_mov_state_4,
        ARRAY_COUNT(D_0E0007E0),
        1
    );

    /**
    * @bug Because the cutscene repeats itself from the beginning over and over,
    *      the game will keep creating new scythes everytime, without destroying
    *      the previously spawned ones, leading to slowdowns
    */
    if ((self->current_time > 150.0f) && (self->current_time < 165.0f)) {
        death_data = data->death_data;
        if (death_data->anim_state != 0) {
            death_data->angle = data->death_model[0]->angle.yaw + DEG_TO_FIXED(90);
            death             = self->death;
            (*mapOverlay)(self->death);
            (*Death_CreateMultipleScythes)(death, death_data, 3, 2, 8, DEG_TO_FIXED(90), 20.0f);
            (*unmapOverlay)(self->death);
        }
    }

    if (self->max_time >= self->current_time) {
        self->current_time++;
    }

    if (self->max_time < self->current_time) {
        /**
        * Restart the cutscene
        */
        self->current_time = 0;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}
#endif

void Demo50_Restart(Demo50* self) {
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, DEMO50_LOOP
    );
}

void Demo50_PlayDeathAnimations(Demo50* self, CutsceneCoordinatesConfig* coords) {
    Demo50Data* data                   = self->data;
    actorVisualData* death_visual_data = &data->death_data->visual_data;

    /**
     * @note Death will only perform animations if `coords->field_0x01` is equal to 0,
     *       but the checks below (and the fact that there are various arrays of size 1
     *       in `Demo50Data`) suggests that there was originally more data that
     *       could be indexed by `coords->field_0x01` for this cutscene.
     */
    if ((coords->field_0x01 >= 0) && (coords->field_0x01 <= 0)) {
        (*mapOverlay)(self->death);
        switch (coords->player_anims_array_index) {
            case 0:
                (*Death_UpdateAnimParamsCutscene)(
                    DEATH_ANIM_IDLE, 1.0f, death_visual_data, data->death_data
                );
                break;
            case 3:
                (*Death_UpdateAnimParamsCutscene)(
                    DEATH_ANIM_FLYING_BACK, 1.0f, death_visual_data, data->death_data
                );
                break;
            case 7:
                (*Death_UpdateAnimParamsCutscene)(
                    DEATH_ANIM_THROW_MULTIPLE_SCYTHES, 1.0f, death_visual_data, data->death_data
                );
                break;
        }
        (*Death_AnimateFrameCutscene)(
            data->death_data,
            data->death_model[coords->field_0x01],
            data->death_anim_mgr[coords->field_0x01]
        );
        (*unmapOverlay)(self->death);
    }
}
