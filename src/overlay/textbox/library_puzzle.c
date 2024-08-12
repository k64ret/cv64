/**
 * @file library_puzzle.c
 *
 * Handles the puzzle from Castle Center's library.
 */

#include "objects/cutscene/library_puzzle.h"
#include "memory.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

libraryPuzzle_func_t libraryPuzzle_functions[] = {
    libraryPuzzle_init,
    libraryPuzzle_idle,
    libraryPuzzle_showFirstTextbox,
    libraryPuzzle_puzzle_prepare,
    libraryPuzzle_puzzle_selectOption,
    libraryPuzzle_puzzle_fail,
    libraryPuzzle_puzzle_success,
    libraryPuzzle_destroy
};

// clang-format on

void libraryPuzzle_entrypoint(libraryPuzzle* self) {
    ENTER(self, libraryPuzzle_functions);
}

void libraryPuzzle_init(libraryPuzzle* self) {
    cv64_actor_settings_t* settings = self->settings;

    if (ptr_PlayerData != NULL) {
        if (CHECK_EVENT_FLAGS(11, 0x01000000)) {
            self->header.destroy(self);
            return;
        }
        self->position.x     = settings->position.x;
        self->position.y     = settings->position.y;
        self->position.z     = settings->position.z;
        self->trigger_size_X = 10;
        self->trigger_size_Z = 10;
        (*object_allocEntryInListAndClear)(
            self, HEAP_KIND_MULTIPURPOSE, sizeof(libraryPuzzleData), 0
        );
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void libraryPuzzle_idle(libraryPuzzle* self) {
    mfds_state* message;

    if (self->interacting_with_interactuable == TRUE) {
        message = (*map_getMessageFromPool)(7, 0);
        if (message != NULL) {
            sys.FREEZE_PLAYER  = TRUE;
            sys.FREEZE_ENEMIES = TRUE;
            (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, TRUE);
            self->message_textbox = message;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

void libraryPuzzle_showFirstTextbox(libraryPuzzle* self) {
    mfds_state* options_textbox;
    libraryPuzzleData* data;
    window_work* lens;
    mfds_state* textbox = self->message_textbox;

    switch (textbox->textbox_option) {
        case TEXTBOX_OPTION_IDLE:
            return;
        case TEXTBOX_OPTION_YES:
            data                       = self->data;
            data->selected_options_IDs = 0;
            data->highlighted_option   = 0;
            data->message_textbox =
                (*textbox_create)(self, common_camera_HUD, (0x08000000 | 0x00200000 | 0x00000008));
            options_textbox = data->message_textbox;
            if (options_textbox != NULL) {
                (*textbox_setPos)(options_textbox, 50, 50, 1);
                (*textbox_setDimensions)(options_textbox, 1, 255, 0, 8);
                options_textbox->display_time = 0;
                libraryPuzzle_printSelectedOptions(data->options_text, 0);
                (*textbox_setMessagePtr)(options_textbox, data->options_text, NULL, 0);
            }
            lens = (*lens_create)(
                self,
                common_camera_HUD,
                (0x00000080 | 0x00000020 | 0x00000010 | 0x00000004 | 0x00000001),
                -125.0f,
                58.0f,
                10.0f,
                1.0f,
                1.0f,
                20.0f
            );
            data->lens_window_work = lens;
            lens->flags &= ~0x100;
            lens->flags |= 0x200;
            self->message_textbox = (*map_getMessageFromPool)(8, 0);
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
        case TEXTBOX_OPTION_NO:
            sys.FREEZE_PLAYER  = FALSE;
            sys.FREEZE_ENEMIES = FALSE;
            (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
            self->header.timer                   = 0;
            self->textbox_is_active              = FALSE;
            self->interacting_with_interactuable = FALSE;
            (*object_curLevel_goToFunc)(
                self->header.current_function, &self->header.function_info_ID, LIBRARY_PUZZLE_IDLE
            );
    }
}

void libraryPuzzle_puzzle_prepare(libraryPuzzle* self) {
    mfds_state* textbox;
    u16* message_ptr;

    textbox = (*textbox_create)(self, common_camera_HUD, (0x08000000 | 0x00400000 | 0x00200000));
    self->message_textbox = textbox;
    if (textbox != NULL) {
        message_ptr = (*text_getMessageFromPool)(GET_MAP_MESSAGE_POOL_PTR(), 8);
        (*textbox_setPos)(textbox, 30, 140, 1);
        (*textbox_setDimensions)(textbox, 4, 255, 0, 0);
        (*textbox_setMessagePtr)(textbox, message_ptr, NULL, 0);
        (*textbox_enableLens)(
            textbox, (0x00040000 | 0x00000020 | 0x00000010 | 0x00000004 | 0x00000001), 40.0f
        );
    }
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_puzzle_selectOption.s")

void libraryPuzzle_puzzle_fail(libraryPuzzle* self) {
    libraryPuzzleData* data = self->data;
    mfds_state* textbox = self->message_textbox;
    s32 temp[2];

    if (textbox == NULL) {
        textbox = (*map_getMessageFromPool)(11, 0);
        self->message_textbox = textbox;
        return;
    }
    if ((*lensAreClosed)()) {
        (*cutscene_setActorStateIfMatchingVariable1)(0x01D6, 0, 0);
        (*cutscene_setActorStateIfMatchingVariable1)(0x01D6, 1, 0);
        (*cutscene_setActorStateIfMatchingVariable1)(0x01D6, 2, 0);
        self->header.timer = 0;
        self->first_option = 0;
        self->second_option = 0;
        self->third_option = 0;
        self->number_of_options_selected = 0;
        self->option_selected = 0;
        self->textbox_is_active = 0;
        self->interacting_with_interactuable = 0;
        data->lens_window_work->flags |= 0x300;
        textbox = data->message_textbox;
        textbox->flags |= 0x04000000;
        sys.FREEZE_ENEMIES = 0;
        sys.FREEZE_PLAYER = 0;
        (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
        (*object_curLevel_goToFunc)(self->header.current_function, &self->header.function_info_ID, LIBRARY_PUZZLE_IDLE);
    }
}

void libraryPuzzle_puzzle_success(libraryPuzzle* self) {
    libraryPuzzleData* data = self->data;

    sys.cutscene_ID = 0x13;
    SET_EVENT_FLAGS(11, 0x01000000);
    data->lens_window_work->flags |= 0x300;
    data->message_textbox->flags |= 0x04000000;
    sys.FREEZE_ENEMIES = 0;
    sys.FREEZE_PLAYER = 0;
    (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
}

void libraryPuzzle_destroy(libraryPuzzle* self) {
    self->header.destroy(self);
}

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_printSelectedOptions.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/textbox/library_puzzle/libraryPuzzle_selectNextOption.s")

// clang-format on
