#include "cv64.h"
#include "objects/cutscene/cutsceneMgr.h"
#include "cutscene_ID.h"
#include "system_work.h"

cv64_cutscenemgr_func_t cutsceneMgr_functions[] = {
    cutsceneMgr_main,
    cutsceneMgr_createCutscene,
    cutsceneMgr_setCameraClippingAndScissoring,
    cutsceneMgr_loop,
    cutsceneMgr_stopCutscene
};

void cutsceneMgr_entrypoint(cutsceneMgr* self) {
    ENTER(self, cutsceneMgr_functions);
}

void cutsceneMgr_main(cutsceneMgr* self) {
    actorVisualData* visual_data;

    if (sys.cutscene_ID == CUTSCENE_ID_NONE)
        return;

    // Cutscenes 1 (Opening) and 2 (Malus Playing Violin) don't happen during gameplay,
    // so `ptr_PlayerData` is not initialized by then.
    // This check is here so that those cutscenes can play outside of the gameplay state.
    if (sys.cutscene_ID < 3) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    } else if (ptr_PlayerData != NULL) {
        visual_data = &ptr_PlayerData->visualData;

        if ((visual_data->flags & DEAD) ||
            (sys.SaveStruct_gameplay.player_status & DEAD)) {
            sys.entrance_cutscene_ID = CUTSCENE_ID_NONE;
            sys.cutscene_ID = CUTSCENE_ID_NONE;
        } else {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
        }
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_createCutscene.s")

// clang-format on

void cutsceneMgr_setCameraClippingAndScissoring(cutsceneMgr* self) {
    if (cutscene_settings[self->cutscene_ID].overlay &
        CUTSCENE_OVERLAY_WIDESCREEN_BORDERS) {
        if (sys.cutscene_flags & CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS) {
            cutscene_setCameraClippingAndScissoring(WIDESCREEN_BORDERS);
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
        }
    } else {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

void cutsceneMgr_loop(cutsceneMgr* self) {
    if (objectList_findFirstObjectByID(
            cutscene_settings[self->cutscene_ID].object_ID
        ) == NULL) {
        if (cutscene_settings[self->cutscene_ID].overlay &
            CUTSCENE_OVERLAY_FILM_REEL) {
            sys.cutscene_flags &= ~CUTSCENE_FLAG_FILM_REEL_EFFECT;
        }
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
        return;
    }
    if ((sys.controllers[0].buttons_pressed & (START_BUTTON | RECENTER_BUTTON)
        ) &&
        (2 < sys.cutscene_ID)) {
        cutscene* cutscene_obj = self->cutscene_object;
        cutscene_obj->skip_cutscene = TRUE;
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_stopCutscene.s")

// clang-format on
