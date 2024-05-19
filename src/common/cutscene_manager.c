/**
 * @file cutscene_manager.c
 *
 * Handles global aspects of cutscenes, such as initializing a cutscene's object,
 * setting up common cutscene camera parameters, checking if the player has pressed
 * START to skip the cutscene, etc.
 */

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
            self->header.current_function, &self->header.function_info_ID
        );
    } else if (ptr_PlayerData != NULL) {
        visual_data = &ptr_PlayerData->visualData;

        if (BITS_HAS(visual_data->flags, DEAD) ||
            BITS_HAS(sys.SaveStruct_gameplay.player_status, DEAD)) {
            sys.entrance_cutscene_ID = CUTSCENE_ID_NONE;
            sys.cutscene_ID          = CUTSCENE_ID_NONE;
        } else {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

void cutsceneMgr_createCutscene(cutsceneMgr* self) {
    s16 i;
    u16 cutscene_overlay;
    u32* cutscene_ID_ptr;
    u32 cutscene_flags;

    self->cutscene_ID = CUTSCENE_ID_NONE;

    for (i = 0; i < ARRAY_COUNT(cutscene_settings); i++) {
        if (sys.cutscene_ID == cutscene_settings[i].cutscene_ID) {
            self->cutscene_ID = i + 1;
        }
    }

    if (self->cutscene_ID == CUTSCENE_ID_NONE) {
        sys.cutscene_ID = CUTSCENE_ID_NONE;
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, CUTSCENEMGR_MAIN
        );
        return;
    }

    cutscene_overlay = cutscene_settings[self->cutscene_ID - 1].overlay;
    if (BITS_HAS(cutscene_overlay, CUTSCENE_OVERLAY_FADE)) {
        (*fade_setSettings)(FADE_OUT, 10, 0, 0, 0);
    }

    cutscene_overlay = cutscene_settings[self->cutscene_ID - 1].overlay;
    cutscene_ID_ptr  = &self->cutscene_ID;
    cutscene_flags   = sys.cutscene_flags;
    if (BITS_HAS(cutscene_overlay, CUTSCENE_OVERLAY_FILM_REEL)) {
        sys.cutscene_flags = cutscene_flags | CUTSCENE_FLAG_FILM_REEL_EFFECT;
        if ((self && self) && self) {
        }
        self->csFilmReel = object_createAndSetChild(&self->header, CUTSCENE_CSFILMREEL);
    }

    self->cutscene_object = object_createAndSetChild(
        &self->header, cutscene_settings[(*cutscene_ID_ptr) - 1].object_ID
    );
    if (self->cutscene_object != NULL) {
        BITS_SET(sys.cutscene_flags, CUTSCENE_FLAG_PLAYING);
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cutsceneMgr_setCameraClippingAndScissoring(cutsceneMgr* self) {
    if (BITS_HAS(
            cutscene_settings[self->cutscene_ID - 1].overlay, CUTSCENE_OVERLAY_WIDESCREEN_BORDERS
        )) {
        if (BITS_HAS(sys.cutscene_flags, CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS)) {
            cutscene_setCameraClippingAndScissoring(WIDESCREEN_BORDERS);
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    } else {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cutsceneMgr_loop(cutsceneMgr* self) {
    if (objectList_findFirstObjectByID(cutscene_settings[self->cutscene_ID - 1].object_ID) ==
        NULL) {
        if (BITS_HAS(
                cutscene_settings[self->cutscene_ID - 1].overlay, CUTSCENE_OVERLAY_FILM_REEL
            )) {
            BITS_UNSET(sys.cutscene_flags, CUTSCENE_FLAG_FILM_REEL_EFFECT);
        }
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    } else if (BITS_HAS(sys.controllers[0].buttons_pressed, START_BUTTON | RECENTER_BUTTON) && (2 < sys.cutscene_ID)) {
        cutscene* cutscene_obj      = self->cutscene_object;
        cutscene_obj->skip_cutscene = TRUE;
    }
}

void cutsceneMgr_stopCutscene(cutsceneMgr* self) {
    cutscene_parameters* settings;

    if (objectList_findFirstObjectByID(CUTSCENE_CSFILMREEL) != NULL) {
        return;
    }

    if (BITS_NOT_HAS(sys.cutscene_flags, CUTSCENE_FLAG_10) &&
        BITS_HAS(
            cutscene_settings[self->cutscene_ID - 1].overlay, CUTSCENE_OVERLAY_WIDESCREEN_BORDERS
        )) {
        cutscene_setCameraClippingAndScissoring(FULLSCREEN);
    }

    if ((sys.cutscene_ID != CUTSCENE_ID_NONE) &&
        (sys.cutscene_ID == cutscene_settings[self->cutscene_ID - 1].cutscene_ID) &&
        (sys.cutscene_ID != CUTSCENE_ID_NONE)) {
        sys.cutscene_ID = CUTSCENE_ID_NONE;
    }

    if (BITS_NOT_HAS(sys.cutscene_flags, CUTSCENE_FLAG_20)) {
        BITS_UNSET(sys.cutscene_flags, CUTSCENE_FLAG_PLAYING);
        if (BITS_NOT_HAS(sys.cutscene_flags, CUTSCENE_FLAG_10)) {
            BITS_UNSET(sys.cutscene_flags, CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS);
        }
    }

    settings = &cutscene_settings[self->cutscene_ID - 1];
    if (BITS_HAS(settings->overlay, CUTSCENE_OVERLAY_FADE)) {
        (*fade_setSettings)(FADE_IN, 10, 0, 0, 0);
    }

    settings = &cutscene_settings[self->cutscene_ID - 1];
    if (settings->make_player_idle_after_cutscene) {
        (*object_curLevel_goToFuncInLevel)(
            sys.ptr_PlayerObject->header.current_function,
            &sys.ptr_PlayerObject->header.function_info_ID,
            0,
            PLAYER_IDLE
        );
    }

    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, CUTSCENEMGR_MAIN
    );
}
