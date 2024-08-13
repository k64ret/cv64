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
        if (CHECK_EVENT_FLAGS(
                EVENT_FLAG_ID_CASTLE_WALL_LIBRARY_AND_MAZE_GARDEN,
                EVENT_FLAG_CASTLE_WALL_LIBRARY_AND_MAZE_GARDEN_LIBRARY_PUZZLE_SOLVED
            )) {
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
        message = (*map_getMessageFromPool)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_DESCRIPTION, 0);
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
            data->highlighted_option   = PUZZLE_OPTION(1);
            data->message_textbox      = (*textbox_create)(
                self, common_camera_HUD, (OPEN_TEXTBOX | FAST_TEXT_TRANSITION | MFDS_FLAG_00000008)
            );
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
                (WINDOW_FLAG_80 | WINDOW_FLAG_OPEN_DOWN_RIGHT | WINDOW_FLAG_OPEN_RIGHT_DOWN |
                 WINDOW_FLAG_OPEN_DOWN | WINDOW_FLAG_OPEN_RIGHT),
                -125.0f,
                58.0f,
                10.0f,
                1.0f,
                1.0f,
                20.0f
            );
            data->lens = lens;
            lens->flags &= ~WINDOW_CLOSING;
            lens->flags |= WINDOW_OPENING;
            self->message_textbox =
                (*map_getMessageFromPool)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_GOLD_PIECE, 0);
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
        case TEXTBOX_OPTION_NO:
            sys.FREEZE_PLAYER  = FALSE;
            sys.FREEZE_ENEMIES = FALSE;
            (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
            SELECTION_DELAY_TIMER(self)          = 0;
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

    textbox = (*textbox_create)(
        self, common_camera_HUD, (OPEN_TEXTBOX | FAST_TEXT_TRANSITION | MFDS_FLAG_400000)
    );
    self->message_textbox = textbox;
    if (textbox != NULL) {
        message_ptr = (*text_getMessageFromPool)(
            GET_MAP_MESSAGE_POOL_PTR(), CASTLE_CENTER_4F_LIBRARY_PUZZLE_GOLD_PIECE
        );
        (*textbox_setPos)(textbox, 30, 140, 1);
        (*textbox_setDimensions)(textbox, 4, 255, 0, 0);
        (*textbox_setMessagePtr)(textbox, message_ptr, NULL, 0);
        (*textbox_enableLens)(
            textbox,
            (WINDOW_FLAG_40000 | WINDOW_FLAG_OPEN_DOWN_RIGHT | WINDOW_FLAG_OPEN_RIGHT_DOWN |
             WINDOW_FLAG_OPEN_DOWN | WINDOW_FLAG_OPEN_RIGHT),
            40.0f
        );
    }
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void libraryPuzzle_puzzle_selectOption(libraryPuzzle* self) {
    libraryPuzzleData* data;
    window_work* lens;
    mfds_state* textbox       = self->message_textbox;
    s32 update_option_strings = 0;

    if (textbox->flags & TEXT_IS_PARSED) {
        data = self->data;
        if (self->option_selected == FALSE) {
            update_option_strings = libraryPuzzle_selectNextOption(
                &data->highlighted_option, &SELECTION_DELAY_TIMER(self), &data->selected_options_IDs
            );
            lens             = data->lens;
            lens->position.x = (s32) (data->highlighted_option * 25) - 101;
        }
        if (update_option_strings > 0) {
            libraryPuzzle_printSelectedOptions(data->options_text, data->selected_options_IDs);
            (*textbox_setMessagePtr)(data->message_textbox, data->options_text, NULL, 0);
            data->message_textbox->flags |= UPDATE_STRING;
            self->option_selected = TRUE;
            self->number_of_options_selected++;
            (*play_sound)(SD_LIBRARY_PIECE_SET);
            return;
        }
        if (self->option_selected) {
            switch (self->number_of_options_selected) {
                case 1:
                    (*textbox_setMessagePtr)(
                        textbox,
                        (*text_getMessageFromPool)(
                            GET_MAP_MESSAGE_POOL_PTR(), CASTLE_CENTER_4F_LIBRARY_PUZZLE_RED_PIECE
                        ),
                        NULL,
                        0
                    );
                    textbox->flags &= ~HIDE_TEXTBOX;
                    textbox->flags |= UPDATE_STRING;
                    self->first_option = data->highlighted_option;
                    (*cutscene_setActorStateIfMatchingVariable1)(
                        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, 1, self->first_option + 1
                    );
                    self->message_textbox = textbox;
                    self->option_selected = FALSE;
                    break;
                case 2:
                    (*textbox_setMessagePtr)(
                        textbox,
                        (*text_getMessageFromPool)(
                            GET_MAP_MESSAGE_POOL_PTR(), CASTLE_CENTER_4F_LIBRARY_PUZZLE_BLUE_PIECE
                        ),
                        NULL,
                        0
                    );
                    textbox->flags &= ~HIDE_TEXTBOX;
                    textbox->flags |= UPDATE_STRING;
                    self->second_option = data->highlighted_option;
                    (*cutscene_setActorStateIfMatchingVariable1)(
                        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, 2, self->second_option + 1
                    );
                    self->message_textbox = textbox;
                    self->option_selected = FALSE;
                    break;
                case 3:
                    self->third_option = data->highlighted_option;
                    textbox->flags |= CLOSE_TEXTBOX;
                    (*cutscene_setActorStateIfMatchingVariable1)(
                        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, 0, self->third_option + 1
                    );
                    break;
            }
        }
    }
    if (self->number_of_options_selected == 3) {
        if ((self->first_option == PUZZLE_OPTION(2)) && (self->second_option == PUZZLE_OPTION(4)) &&
            (self->third_option == PUZZLE_OPTION(8))) {
            (*object_curLevel_goToFunc)(
                self->header.current_function,
                &self->header.function_info_ID,
                LIBRARY_PUZZLE_PUZZLE_SUCCESS
            );
            return;
        }
        self->message_textbox = (*map_getMessageFromPool)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_FAIL, 0);
        SELECTION_DELAY_TIMER(self) = 0;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void libraryPuzzle_puzzle_fail(libraryPuzzle* self) {
    libraryPuzzleData* data = self->data;
    mfds_state* textbox     = self->message_textbox;
    s32 temp[2];

    if (textbox == NULL) {
        textbox               = (*map_getMessageFromPool)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_FAIL, 0);
        self->message_textbox = textbox;
        return;
    }
    if ((*lensAreClosed)()) {
        (*cutscene_setActorStateIfMatchingVariable1)(
            STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, 0, 0
        );
        (*cutscene_setActorStateIfMatchingVariable1)(
            STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, 1, 0
        );
        (*cutscene_setActorStateIfMatchingVariable1)(
            STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, 2, 0
        );
        SELECTION_DELAY_TIMER(self)          = 0;
        self->first_option                   = 0;
        self->second_option                  = 0;
        self->third_option                   = 0;
        self->number_of_options_selected     = 0;
        self->option_selected                = FALSE;
        self->textbox_is_active              = FALSE;
        self->interacting_with_interactuable = FALSE;
        data->lens->flags |= (WINDOW_CLOSING | WINDOW_OPENING);
        textbox = data->message_textbox;
        textbox->flags |= CLOSE_TEXTBOX;
        sys.FREEZE_ENEMIES = FALSE;
        sys.FREEZE_PLAYER  = FALSE;
        (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, LIBRARY_PUZZLE_IDLE
        );
    }
}

void libraryPuzzle_puzzle_success(libraryPuzzle* self) {
    libraryPuzzleData* data = self->data;

    sys.cutscene_ID = CUTSCENE_ID_LIBRARY_PUZZLE_SOLVED;
    SET_EVENT_FLAGS(
        EVENT_FLAG_ID_CASTLE_WALL_LIBRARY_AND_MAZE_GARDEN,
        EVENT_FLAG_CASTLE_WALL_LIBRARY_AND_MAZE_GARDEN_LIBRARY_PUZZLE_SOLVED
    );
    data->lens->flags |= (WINDOW_CLOSING | WINDOW_OPENING);
    data->message_textbox->flags |= CLOSE_TEXTBOX;
    sys.FREEZE_ENEMIES = FALSE;
    sys.FREEZE_PLAYER  = FALSE;
    (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void libraryPuzzle_destroy(libraryPuzzle* self) {
    self->header.destroy(self);
}

/**
* `number + ASCII_TO_CV64('0')` takes a variable number and converts it to
* the game's custom text format.
*/
void libraryPuzzle_printSelectedOptions(u16* text, u16 selected_options_IDs) {
    u16* string = text;
    u16 i;
    u16 number;

    for (i = 1, number = 1; i < 10; i++) {
        number = i;
        if (selected_options_IDs & (1 << (number + 0x1F))) {
            // Print selected options in red
            string[0] = CTRL_SET_COLOR(TEXT_COLOR_RED);
            string[1] = number + ASCII_TO_CV64('0');
            // Print the following chars in white by default
            string[2] = CTRL_SET_COLOR(TEXT_COLOR_WHITE);
            string += 3;
        } else {
            // Just print the number, don't change its color
            string[0] = number + ASCII_TO_CV64('0');
            string += 1;
        }
    }
    *string = 0;
}

s32 libraryPuzzle_selectNextOption(
    s32* highlighted_option, u16* selection_delay_timer, u16* selected_options_IDs
) {
    s32 ret = 0;

    if (*selected_options_IDs ==
        (OPTION_1 | OPTION_2 | OPTION_3 | OPTION_4 | OPTION_5 | OPTION_6 | OPTION_7 | OPTION_8 |
         OPTION_9)) {
        return 0;
    }

    if ((CONT_BTNS_PRESSED(CONT_0, U_JPAD)) || (CONT_BTNS_PRESSED(CONT_0, U_JPAD)) ||
        (CONT_BTNS_PRESSED(CONT_0, L_JPAD)) || (CONT_BTNS_PRESSED(CONT_0, R_JPAD))) {
        *selection_delay_timer = 0;
    }

    if ((CONT_BTNS_PRESSED(CONT_0, L_JPAD)) || (sys.controllers[0].joystick_x < -25)) {
        if (*selection_delay_timer == 0) {
            *selection_delay_timer = 4;
            do {
                (*highlighted_option)--;
                if ((*highlighted_option) < 0) {
                    *highlighted_option = 8;
                }
            } while (*selected_options_IDs & (1 << (*highlighted_option)));
        } else {
            (*selection_delay_timer)--;
        }
    } else if ((CONT_BTNS_PRESSED(CONT_0, R_JPAD)) || (sys.controllers[0].joystick_x >= 26)) {
        if (*selection_delay_timer == 0) {
            *selection_delay_timer = 4;
            do {
                (*highlighted_option)++;
                if ((*highlighted_option) >= 9) {
                    *highlighted_option = 0;
                }
            } while (*selected_options_IDs & (1 << (*highlighted_option)));
        } else {
            (*selection_delay_timer)--;
        }
    }

    if (*selected_options_IDs & (1 << (*highlighted_option))) {
        ret = 1;
        do {
            (*highlighted_option)++;
            if ((*highlighted_option) >= 9) {
                *highlighted_option = 0;
            }
        } while (*selected_options_IDs & (1 << (*highlighted_option)));
    }

    if (ret != 0) {
        return 0;
    }

    if ((CONT_BTNS_PRESSED(CONT_0, A_BUTTON))) {
        *selected_options_IDs |= (1 << (*highlighted_option));
        ret = 1;
    } else if ((CONT_BTNS_PRESSED(CONT_0, B_BUTTON))) {
        ret = -1;
    }

    return ret;
}
