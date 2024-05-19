/**
 * @file overlay_BA.c
 *
 * This actor can be found in the main area of Castle Wall, and its purpose
 * is to play sound `SD_2E9` when falling off the platform where you encounter
 * Dracula.
 *
 * Sound `SD_2E9` appears to be silent, so it's unknown how it would have sound
 * like. For some reason, it's grouped under the "Menu" objects.
*/

#include "objects/menu/object_213F.h"
#include "objects/player/player.h"
#include "sound.h"
#include "system_work.h"

// 0x0F0001A0
cv64_ovl_obj213F_func_t cv64_ovl_obj213F_funcs[] = {
    obj213F_isDraculaCutsceneWatched,
    obj213F_isPlayerDroppingDown,
    obj213F_playSound,
    obj213F_destroy
};

void obj213F_entrypoint(object_213F* self) {
    ENTER(self, cv64_ovl_obj213F_funcs);
}

void obj213F_isDraculaCutsceneWatched(object_213F* self) {
    cv64_model_inf_t* player_model;

    if ((ptr_PlayerData != NULL) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_WALL_MAIN, EVENT_FLAG_CASTLE_WALL_MAIN_WATCHED_DRACULA_CUTSCENE
        )) {
        player_model = ptr_PlayerData->visualData.model;

        if (300.0f < player_model->position.y) {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

void obj213F_isPlayerDroppingDown(object_213F* self) {
    cv64_model_inf_t* model = ptr_PlayerData->visualData.model;

    if (model->position.y < 300.0f) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void obj213F_playSound(object_213F* self) {
    (*play_sound)(SD_2E9);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void obj213F_destroy(object_213F* self) {
    self->header.destroy(self);
}
