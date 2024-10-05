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

Demo50Func Demo50_functions[] = {
    Demo50_Init,
    Demo50_CreateCutsceneCamera,
    Demo50_GetPlayerModelAndSetBorders,
    Demo50_Loop,
    Demo50_Restart
};

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

void Demo50_CreateCutsceneCamera(Demo50* self) {
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

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_GetPlayerModelAndSetBorders.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo50/demo50/Demo50_Loop.s")

// clang-format on

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
