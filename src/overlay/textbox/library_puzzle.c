/**
 * @file library_puzzle.c
 *
 * Handles the puzzle from Castle Center's library.
 */

#include "objects/cutscene/library_puzzle.h"
#include "objects/map/honmaru_4f_minami/library_piece.h"
#include "objects/menu/gameplayMenuMgr.h"
#include "memory.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

cv64_ovl_librarypuzzletxt_func_t cv64_ovl_librarypuzzletxt_funcs[] = {
    cv64_ovl_librarypuzzletxt_init,
    cv64_ovl_librarypuzzletxt_idle,
    cv64_ovl_librarypuzzletxt_show,
    cv64_ovl_librarypuzzletxt_prepare_msg,
    cv64_ovl_librarypuzzletxt_select,
    cv64_ovl_librarypuzzletxt_fail,
    cv64_ovl_librarypuzzletxt_success,
    cv64_ovl_librarypuzzletxt_destroy
};

// clang-format on

void cv64_ovl_librarypuzzletxt_entrypoint(cv64_ovl_librarypuzzletxt_t* self) {
    ENTER(self, cv64_ovl_librarypuzzletxt_funcs);
}

static void print_selected_options(u16*, u16);
static s32 select_next_option(s32*, u16*, u16*);

void cv64_ovl_librarypuzzletxt_init(cv64_ovl_librarypuzzletxt_t* self) {
    ActorConfig* settings = self->settings;

    if (ptr_PlayerData == NULL)
        return;

    // Destroy if the puzzle was already solved
    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN,
            EVENT_FLAG_CASTLE_CENTER_4F_AND_MAZE_GARDEN_LIBRARY_PUZZLE_SOLVED
        )) {
        self->header.destroy(self);
        return;
    }

    self->position.x = settings->position.x;
    self->position.y = settings->position.y;
    self->position.z = settings->position.z;
    /**
     * The trigger sizes below are unused, since `Player_getActorCurrentlyInteractingWith`
     * uses other hardcoded trigger sizes when the player checks out the puzzle's trigger
     */
    self->trigger_size_X = 10;
    self->trigger_size_Z = 10;
    (*object_allocEntryInListAndClear)(
        self, HEAP_KIND_MULTIPURPOSE, sizeof(cv64_ovl_librarypuzzledata_t), 0
    );
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_librarypuzzletxt_idle(cv64_ovl_librarypuzzletxt_t* self) {
    MfdsState* message;

    if (self->interacting_with_interactable != TRUE)
        return;

    // Freeze player and ask the user if they want to do the puzzle
    message =
        (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_DESCRIPTION, 0);
    if (message == NULL)
        return;

    sys.FREEZE_PLAYER  = TRUE;
    sys.FREEZE_ENEMIES = TRUE;
    (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, TRUE);
    self->message_textbox = message;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

/**
 * Shows the initial textbox in the Library Puzzle interaction
 */
void cv64_ovl_librarypuzzletxt_show(cv64_ovl_librarypuzzletxt_t* self) {
    MfdsState* options_textbox;
    cv64_ovl_librarypuzzledata_t* data;
    WindowWork* lens;
    MfdsState* textbox = self->message_textbox;

    switch (textbox->textbox_option) {
        case TEXTBOX_OPTION_IDLE:
            return;
        case TEXTBOX_OPTION_YES:
            data                       = self->data;
            data->selected_options_IDs = 0;

            // Highlight the number 1 by default
            data->highlighted_option = PUZZLE_OPTION(1);

            // Create and setup the textbox that holds the 1, 2, 3, etc. options
            data->options_textbox = (*textbox_create)(
                self,
                common_camera_HUD,
                (MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_00000008)
            );
            options_textbox = data->options_textbox;
            if (options_textbox != NULL) {
                (*textbox_setPos)(options_textbox, 50, 50, 1);
                (*textbox_setDimensions)(options_textbox, 1, 255, 0, 8);
                options_textbox->display_time = 0;
                print_selected_options(data->options_text, 0);
                (*textbox_setMessagePtr)(options_textbox, data->options_text, NULL, 0);
            }

            // Create and setup the selection lens
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
            BITS_UNSET(lens->flags, WINDOW_CLOSING);
            BITS_SET(lens->flags, WINDOW_OPENING);

            /**
             * This isn't used in practice, since the piece text is written into a new
             * textbox, and not to gameplayMenuMgr's common textbox, which closes after
             * said message displays
             */
            self->message_textbox = (*gameplayCommonTextbox_getMapMessage)(
                CASTLE_CENTER_4F_LIBRARY_PUZZLE_GOLD_PIECE, 0
            );

            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
        case TEXTBOX_OPTION_NO:
            // Go back to normal gameplay
            sys.FREEZE_PLAYER  = FALSE;
            sys.FREEZE_ENEMIES = FALSE;
            (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
            SELECTION_DELAY_TIMER(self)         = 0;
            self->textbox_is_active             = FALSE;
            self->interacting_with_interactable = FALSE;
            (*object_curLevel_goToFunc)(
                self->header.current_function, &self->header.function_info_ID, LIBRARY_PUZZLE_IDLE
            );
    }
}

void cv64_ovl_librarypuzzletxt_prepare_msg(cv64_ovl_librarypuzzletxt_t* self) {
    MfdsState* textbox;
    u16* message_ptr;

    /**
     * Create and setup the "Is the X piece in place?" textbox,
     * and display it for the gold piece first
     */
    textbox = (*textbox_create)(
        self,
        common_camera_HUD,
        (MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED)
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

/**
 * Allows the player to select the goddesses for the Library Puzzle
 */
void cv64_ovl_librarypuzzletxt_select(cv64_ovl_librarypuzzletxt_t* self) {
    cv64_ovl_librarypuzzledata_t* data;
    WindowWork* lens;
    MfdsState* textbox = self->message_textbox;
    s32 set_piece      = 0;

    if (BITS_HAS(textbox->flags, MFDS_FLAG_TEXT_IS_PARSED)) {
        data = self->data;
        if (self->option_selected == FALSE) {
            set_piece = select_next_option(
                &data->highlighted_option, &SELECTION_DELAY_TIMER(self), &data->selected_options_IDs
            );
            // Update the selection lens's horizontal position
            lens             = data->lens;
            lens->position.x = (s32) (data->highlighted_option * 25) - 101;
        }

        // An option was selected
        if (set_piece > 0) {
            print_selected_options(data->options_text, data->selected_options_IDs);
            (*textbox_setMessagePtr)(data->options_textbox, data->options_text, NULL, 0);
            BITS_SET(data->options_textbox->flags, MFDS_FLAG_UPDATE_STRING);
            self->option_selected = TRUE;
            self->number_of_options_selected++;
            (*play_sound)(SD_LIBRARY_PIECE_SET);
            return;
        }

        /**
         * Set each piece to the position indicated by the selected option
         * and update the message displayed to reflect
         * the next piece
         */
        if (self->option_selected) {
            switch (self->number_of_options_selected) {
                /**
                 * Red piece
                 */
                case 1:
                    (*textbox_setMessagePtr)(
                        textbox,
                        (*text_getMessageFromPool)(
                            GET_MAP_MESSAGE_POOL_PTR(), CASTLE_CENTER_4F_LIBRARY_PUZZLE_RED_PIECE
                        ),
                        NULL,
                        0
                    );
                    BITS_UNSET(textbox->flags, MFDS_FLAG_HIDE_TEXTBOX);
                    BITS_SET(textbox->flags, MFDS_FLAG_UPDATE_STRING);
                    self->first_option = data->highlighted_option;
                    (*cutscene_setActorStateIfMatchingVariable1)(
                        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE,
                        YELLOW_PIECE,
                        self->first_option + 1
                    );
                    self->message_textbox = textbox;
                    self->option_selected = FALSE;
                    break;

                /**
                 * Blue piece
                 */
                case 2:
                    (*textbox_setMessagePtr)(
                        textbox,
                        (*text_getMessageFromPool)(
                            GET_MAP_MESSAGE_POOL_PTR(), CASTLE_CENTER_4F_LIBRARY_PUZZLE_BLUE_PIECE
                        ),
                        NULL,
                        0
                    );
                    BITS_UNSET(textbox->flags, MFDS_FLAG_HIDE_TEXTBOX);
                    BITS_SET(textbox->flags, MFDS_FLAG_UPDATE_STRING);
                    self->second_option = data->highlighted_option;
                    (*cutscene_setActorStateIfMatchingVariable1)(
                        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE,
                        RED_PIECE,
                        self->second_option + 1
                    );
                    self->message_textbox = textbox;
                    self->option_selected = FALSE;
                    break;

                /**
                 * All pieces have been put
                 */
                case 3:
                    self->third_option = data->highlighted_option;
                    BITS_SET(textbox->flags, MFDS_FLAG_CLOSE_TEXTBOX);
                    (*cutscene_setActorStateIfMatchingVariable1)(
                        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE,
                        BLUE_PIECE,
                        self->third_option + 1
                    );
                    break;
            }
        }
    }

    // Check the puzzle code
    if (self->number_of_options_selected != LIBRARY_PUZZLE_MAX_SELECTED_OPTIONS)
        return;

    if ((self->first_option == PUZZLE_OPTION(2)) && (self->second_option == PUZZLE_OPTION(4)) &&
        (self->third_option == PUZZLE_OPTION(8))) {
        // Success
        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            LIBRARY_PUZZLE_PUZZLE_SUCCESS
        );
        return;
    }

    // Fail
    self->message_textbox =
        (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_FAIL, 0);
    SELECTION_DELAY_TIMER(self) = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_librarypuzzletxt_fail(cv64_ovl_librarypuzzletxt_t* self) {
    cv64_ovl_librarypuzzledata_t* data = self->data;
    MfdsState* textbox                 = self->message_textbox;
    s32 temp[2];

    // Open up the common textbox again, and display the failed message
    if (textbox == NULL) {
        textbox = (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_4F_LIBRARY_PUZZLE_FAIL, 0);
        self->message_textbox = textbox;
        return;
    }

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    // Close the message and go back to normal

    // Put all the pieces back in the pedestal
    (*cutscene_setActorStateIfMatchingVariable1)(
        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, BLUE_PIECE, 0
    );
    (*cutscene_setActorStateIfMatchingVariable1)(
        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, YELLOW_PIECE, 0
    );
    (*cutscene_setActorStateIfMatchingVariable1)(
        STAGE_OBJECT_HONMARU_4F_MINAMI_LIBRARY_PIECE, RED_PIECE, 0
    );
    SELECTION_DELAY_TIMER(self)         = 0;
    self->first_option                  = 0;
    self->second_option                 = 0;
    self->third_option                  = 0;
    self->number_of_options_selected    = 0;
    self->option_selected               = FALSE;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    BITS_SET(data->lens->flags, WINDOW_CLOSING | WINDOW_OPENING);
    textbox = data->options_textbox;
    BITS_SET(textbox->flags, MFDS_FLAG_CLOSE_TEXTBOX);
    sys.FREEZE_ENEMIES = FALSE;
    sys.FREEZE_PLAYER  = FALSE;
    (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, LIBRARY_PUZZLE_IDLE
    );
}

void cv64_ovl_librarypuzzletxt_success(cv64_ovl_librarypuzzletxt_t* self) {
    cv64_ovl_librarypuzzledata_t* data = self->data;

    /**
     * Start the puzzle solved cutscene,
     * set the appropiate event flags and go back to normal
     */
    sys.cutscene_ID = CUTSCENE_ID_LIBRARY_PUZZLE_SOLVED;
    SET_EVENT_FLAGS(
        EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN,
        EVENT_FLAG_CASTLE_CENTER_4F_AND_MAZE_GARDEN_LIBRARY_PUZZLE_SOLVED
    );
    BITS_SET(data->lens->flags, WINDOW_CLOSING | WINDOW_OPENING);
    BITS_SET(data->options_textbox->flags, MFDS_FLAG_CLOSE_TEXTBOX);
    sys.FREEZE_ENEMIES = FALSE;
    sys.FREEZE_PLAYER  = FALSE;
    (*cameraMgr_setLockCameraAtPointState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_librarypuzzletxt_destroy(cv64_ovl_librarypuzzletxt_t* self) {
    self->header.destroy(self);
}

/**
* `number + ASCII_TO_CV64('0')` takes a variable number and converts it to
* the game's custom text format.
*/
void print_selected_options(u16* text, u16 selected_options_IDs) {
    u16* string = text;
    u16 i;
    u16 number;

    // Iterate through all the options
    for (i = 1, number = 1; i < LIBRARY_PUZZLE_NUM_OPTIONS; i++) {
        number = i;

        // Check that an option was selected
        if (BITS_HAS(selected_options_IDs, BIT(number + 0x1F))) {
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

/**
 * Check controller inputs to move the selection lens.
 * There is normally a small delay of 4 frames between selections.
 *
 * @return
 *  0: Default, nothing happened
 *  1: A new option was selected
 * -1: The B button was pressed. No code checks for this output in practice
 */
s32 select_next_option(
    s32* highlighted_option, u16* selection_delay_timer, u16* selected_options_IDs
) {
    s32 ret = 0;

    // All options are selected (impossible to perform in practice)
    if (*selected_options_IDs ==
        (OPTION_1 | OPTION_2 | OPTION_3 | OPTION_4 | OPTION_5 | OPTION_6 | OPTION_7 | OPTION_8 |
         OPTION_9)) {
        return 0;
    }

    /**
     * Remove selection delay if pressing any of the D-Pad buttons
     * except for the D-Pad Down (probably a mistake since Up is checked twice)
     */
    if ((CONT_BTNS_PRESSED(CONT_0, U_JPAD)) || (CONT_BTNS_PRESSED(CONT_0, U_JPAD)) ||
        (CONT_BTNS_PRESSED(CONT_0, L_JPAD)) || (CONT_BTNS_PRESSED(CONT_0, R_JPAD))) {
        *selection_delay_timer = 0;
    }

    /**
     * Move cursor to the left or to the right
     *
     * `*selected_options_IDs & (1 << (*highlighted_option))` makes sure
     * to skip selecting the already-selected options
     */
    if ((CONT_BTNS_PRESSED(CONT_0, L_JPAD)) || (sys.controllers[0].joy_x < -25)) {
        if (*selection_delay_timer == 0) {
            *selection_delay_timer = LIBRARY_PUZZLE_SELECTION_DELAY;
            do {
                (*highlighted_option)--;
                if ((*highlighted_option) < PUZZLE_OPTION(1)) {
                    *highlighted_option = PUZZLE_OPTION(9);
                }
            } while (BITS_HAS(*selected_options_IDs, BIT(*highlighted_option)));
        } else {
            (*selection_delay_timer)--;
        }
    } else if ((CONT_BTNS_PRESSED(CONT_0, R_JPAD)) || (sys.controllers[0].joy_x >= 26)) {
        if (*selection_delay_timer == 0) {
            *selection_delay_timer = LIBRARY_PUZZLE_SELECTION_DELAY;
            do {
                (*highlighted_option)++;
                if ((*highlighted_option) > PUZZLE_OPTION(9)) {
                    *highlighted_option = PUZZLE_OPTION(1);
                }
            } while (BITS_HAS(*selected_options_IDs, BIT(*highlighted_option)));
        } else {
            (*selection_delay_timer)--;
        }
    }

    /**
     * Move the lens forwards one place after selecting an option to avoid
     * being able to select the previous option again
     */
    if (BITS_HAS(*selected_options_IDs, BIT(*highlighted_option))) {
        ret = 1;
        do {
            (*highlighted_option)++;
            if ((*highlighted_option) > PUZZLE_OPTION(9)) {
                *highlighted_option = PUZZLE_OPTION(1);
            }
        } while (BITS_HAS(*selected_options_IDs, BIT(*highlighted_option)));
    }

    if (ret != 0) {
        return 0;
    }

    /**
     * Option selected
     */
    if ((CONT_BTNS_PRESSED(CONT_0, A_BUTTON))) {
        BITS_SET(*selected_options_IDs, BIT(*highlighted_option));
        ret = 1;
        /**
     * Pressed the B button. This does nothing in practice.
     * It could've been used to exit the puzzle earlier in development,
     * but in the final game, the puzzle doesn't finish until all options are selected
     */
    } else if ((CONT_BTNS_PRESSED(CONT_0, B_BUTTON))) {
        ret = -1;
    }

    return ret;
}
