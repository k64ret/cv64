/**
 * @file difficulty_and_character_select.c
 *
 * Handles both the character selection screen when selecting a new game,
 * as well as the difficulty selection menu that shows up when accessing a save file
 * without a controller pak inserted in.
 */

#include "objects/menu/mfds.h"
#include "objects/effect/distortion.h"
#include "objects/menu/characterSelect.h"
#include "system_work.h"

u16 level_select_text[] = {
#include "objects/menu/characterSelect.msg"
};

// Position of the lens when highlighting a character
Vec2f lens_pos[NUM_CHARACTERS] = {{-82.0f, 52.0f}, {23.0f, 52.0f}};

characterSelect_func_t characterSelect_functions[] = {
    difficultySelect_loop,
    characterSelect_areStructsCreated,
    characterSelect_init,
    characterSelect_openScroll,
    characterSelect_createLens,
    characterSelect_selectOption,
    characterSelect_optionSelected,
    characterSelect_destroy
};

// Unused
u32 D_0F001300_E59C90[NUM_CHARACTERS] = {10, 10};

const char characterSelect_unused_str_1[] = "Step %d\n";
const char characterSelect_unused_str_2[] = "pc_select_init!\n";

void characterSelect_entrypoint(characterSelect* self) {
    ENTER(self, characterSelect_functions);
}

void difficultySelect_loop(characterSelect* self) {
    miniScroll* mini_scroll;
    MfdsState* difficulty_text;
    characterSelectInner* inner = &self->inner;
    u8 option;

    // If 1 or more Controller Paks are plugged in, skip the difficulty select
    // and go to the character selection screen
    if (sys.contPak_file_no > -1) {
        option = self->header.function_info_ID;
        if (option) {
        }
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
        return;
    }
    switch (self->inner.difficulty_select_state) {
        // Create the scroll and open it
        case CREATE_SCROLL:
            mini_scroll        = (*miniScroll_create)(self, NULL, 0, 0);
            inner->mini_scroll = mini_scroll;
            (*miniScroll_setPosition)(inner->mini_scroll, 0.0f, 53.0f, 80.0f);
            (*miniScroll_setWidth)(inner->mini_scroll, 1.1599999666214f, 0.689999997615814f, 1.0f);
            (*miniScroll_setState)(inner->mini_scroll, MINISCROLL_STATE_OPEN);
            if (BITS_HAS(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HARD_MODE_UNLOCKED)) {
                inner->difficulty_select_state = CREATE_TEXT_HARD_MODE;
            } else {
                inner->difficulty_select_state = CREATE_TEXT_NON_HARD_MODE;
            }
            break;
        // Draw the Easy and Normal text strings
        case CREATE_TEXT_NON_HARD_MODE:
            difficulty_text = (*textbox_create)(
                self,
                common_camera_HUD,
                (MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED
                )
            );
            inner->difficulty_text = difficulty_text;
            (*textbox_setDimensions)(inner->difficulty_text, 5, 128, 0, 0);
            (*textbox_setScaleParameters)(
                inner->difficulty_text, 2, 2, 81.0f, 1.0f, 1.0f, FALSE, FALSE
            );
            (*textbox_setMessagePtr)(
                inner->difficulty_text,
                (*text_getMessageFromPool)(
                    GET_UNMAPPED_ADDRESS(NI_OVL_CHARACTER_SELECT, &level_select_text), 0
                ),
                NULL,
                0
            );
            (*textbox_setPos)(inner->difficulty_text, 103, 96, 0);
            inner->difficulty_select_state = WAIT_UNTIL_SCROLL_IS_OPENED;
            break;
        // Draw the Easy, Normal and Hard text strings
        case CREATE_TEXT_HARD_MODE:
            difficulty_text = (*textbox_create)(
                self,
                common_camera_HUD,
                (MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED
                )
            );
            inner->difficulty_text = difficulty_text;
            (*textbox_setDimensions)(inner->difficulty_text, 5, 128, 0, 0);
            (*textbox_setScaleParameters)(
                inner->difficulty_text, 2, 2, 81.0f, 1.0f, 1.0f, FALSE, FALSE
            );
            (*textbox_setMessagePtr)(
                inner->difficulty_text,
                (*text_getMessageFromPool)(
                    GET_UNMAPPED_ADDRESS(NI_OVL_CHARACTER_SELECT, &level_select_text), 1
                ),
                NULL,
                0
            );
            (*textbox_setPos)(inner->difficulty_text, 101, 87, 0);
            inner->difficulty_select_state = WAIT_UNTIL_SCROLL_IS_OPENED;
            break;
        // Wait until scroll is opened
        case WAIT_UNTIL_SCROLL_IS_OPENED:
            if ((*miniScroll_checkFlags)(inner->mini_scroll, MINISCROLL_FLAG_OPENED)) {
                inner->difficulty_select_state++;
            }
            break;
        // Select a difficulty option
        case SELECT_OPTION:
            option = inner->difficulty_text->textbox_option;
            switch (option) {
                case TEXTBOX_OPTION_IDLE:
                    return;
                // Easy
                case 1:
                    BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_EASY),
                        BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_NORMAL),
                        BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HARD);
                    break;
                // Normal
                case 2:
                    BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_EASY),
                        BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_NORMAL),
                        BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HARD);
                    break;
                // Hard
                case 3:
                    BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_EASY),
                        BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_NORMAL),
                        BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HARD);
                    break;
            }
            inner->difficulty_select_state++;
            break;
        // Exit to the character selection screen
        case EXIT:
            (*miniScroll_setState)(inner->mini_scroll, MINISCROLL_STATE_DESTROY);
            BITS_SET(inner->difficulty_text->flags, MFDS_FLAG_CLOSE_TEXTBOX);
            inner->difficulty_select_state = CREATE_SCROLL;
            inner->difficulty_text         = NULL;
            inner->mini_scroll             = NULL;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            break;
    }
}

void characterSelect_areStructsCreated(characterSelect* self) {
    if (((*objectList_findFirstObjectByID)(CUTSCENE_DISTORTION) == NULL) &&
        (self->inner.work != NULL)) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

// Real name: `pc_select_init`
void characterSelect_init(characterSelect* self) {
    Model* character_portrait;
    MfdsState* character_name;
    s32 temp1;
    scroll_state* scroll_state;
    s32 temp2;
    characterSelectInner* inner = &self->inner;
    pc_select_work* work        = inner->work;

    // Create Reinhardt's portrait
    character_portrait = (*Model_createAndSetChild)(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HUD_ELEMENT, work->scroll_elements_light
    );
    self->character_portraits[REINHARDT] = character_portrait;
    character_portrait->material_dlist   = &REINHARDT_PORTRAIT_MATERIAL_DL;
    character_portrait->dlist =
        FIG_APPLY_VARIABLE_TEXTURE_AND_PALETTE((u32) &REINHARDT_PORTRAIT_DL);
    character_portrait->assets_file = NI_ASSETS_CHARACTER_SELECTION_SCREEN;
    BITS_SET(character_portrait->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    BITS_SET(character_portrait->flags, FIG_FLAG_0080);
    character_portrait->primitive_color.integer = RGBA(255, 255, 255, 255);
    character_portrait->size.x                  = 0.6999999881f;
    character_portrait->size.y                  = 0.6999999881f;
    character_portrait->size.z                  = 0.6999999881f;
    character_portrait->position.x              = -50.0f;
    character_portrait->position.y              = 10.0f;
    character_portrait->position.z              = 67.0f;
    if (BITS_HAS(work->flags, ENABLE_REINHARDT)) {
        character_portrait->palette = ENABLED_PALETTE;
    } else {
        character_portrait->palette = DISABLED_PALETTE;
    }

    // Create Carrie's portrait
    character_portrait = (*Model_createAndSetChild)(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HUD_ELEMENT, character_portrait
    );
    self->character_portraits[CARRIE]  = character_portrait;
    character_portrait->material_dlist = &CARRIE_PORTRAIT_MATERIAL_DL;
    character_portrait->dlist = FIG_APPLY_VARIABLE_TEXTURE_AND_PALETTE((u32) &CARRIE_PORTRAIT_DL);
    character_portrait->assets_file = NI_ASSETS_CHARACTER_SELECTION_SCREEN;
    BITS_SET(character_portrait->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    BITS_SET(character_portrait->flags, FIG_FLAG_0080);
    character_portrait->primitive_color.integer = RGBA(255, 255, 255, 255);
    character_portrait->size.x                  = 0.6999999881f;
    character_portrait->size.y                  = 0.6999999881f;
    character_portrait->size.z                  = 0.6999999881f;
    character_portrait->position.x              = 50.0f;
    character_portrait->position.y              = 10.0f;
    character_portrait->position.z              = 67.0f;
    if (BITS_HAS(work->flags, ENABLE_CARRIE)) {
        character_portrait->palette = ENABLED_PALETTE;
    } else {
        character_portrait->palette = DISABLED_PALETTE;
    }

    // Create scroll
    sys.background_color.integer = RGBA(0, 0, 0, 255);
    scroll_state                 = (*createScrollState)(
        self,
        work->scroll_dowels_light,
        work->scroll_elements_light,
        SCROLL_STATE_FLAG_02,
        SCROLL_STATE_PARAMS_PLAYER_SELECT,
        0.0f,
        60.0f,
        67.0f,
        30.0f,
        NULL
    );
    if (scroll_state == NULL) {
        self->header.destroy(self);
        return;
    }
    self->inner.scrollState = scroll_state;

    // Create Reinhardt's name text string
    character_name = (*textbox_create)(
        self,
        work->scroll_elements_light,
        MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED |
            MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP | MFDS_FLAG_00000008 |
            MFDS_FLAG_MENU_TEXT_ID_PRINTS_MENU_STRING
    );
    if (character_name == NULL) {
        self->header.destroy(self);
        return;
    }
    self->inner.character_names[REINHARDT] = character_name;
    (*textbox_setPos)(character_name, 70, 170, 1);
    (*textbox_setDimensions)(character_name, 1, 100, 0, 0);
    character_name->palette                       = TEXT_COLOR_BEIGE;
    character_name->misc_text_IDs[0].menu_text_ID = MENU_TEXT_REINHARDT;
    (*textbox_setMessagePtr)(character_name, NULL, NULL, 0);
    (*textbox_setScaleParameters)(character_name, 2, 2, 67.0f, 1.0f, 1.0f, TRUE, TRUE);

    // Create Carrie's name text string
    character_name = (*textbox_create)(
        self,
        work->scroll_elements_light,
        MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED |
            MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP | MFDS_FLAG_00000008 |
            MFDS_FLAG_MENU_TEXT_ID_PRINTS_MENU_STRING
    );
    if (character_name == NULL) {
        self->header.destroy(self);
        return;
    }
    self->inner.character_names[CARRIE] = character_name;
    (*textbox_setPos)(character_name, 185, 170, 1);
    (*textbox_setDimensions)(character_name, 1, 100, 0, 0);
    character_name->palette                       = TEXT_COLOR_BEIGE;
    character_name->misc_text_IDs[0].menu_text_ID = MENU_TEXT_CARRIE;
    (*textbox_setMessagePtr)(character_name, NULL, NULL, 0);
    (*textbox_setScaleParameters)(character_name, 2, 2, 67.0f, 1.0f, 1.0f, TRUE, TRUE);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void characterSelect_openScroll(characterSelect* self) {
    scroll_state* scroll_state = self->inner.scrollState;

    if (scroll_state->position.y > 0.0f) {
        scroll_state->position.y -= 6.0f;
        return;
    }
    BITS_UNSET(scroll_state->flags, SCROLL_STATE_FLAG_CLOSING);
    BITS_SET(scroll_state->flags, SCROLL_STATE_FLAG_OPENING);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void characterSelect_createLens(characterSelect* self) {
    pc_select_work* work       = self->inner.work;
    scroll_state* scroll_state = self->inner.scrollState;
    WindowWork* lens;

    if ((s8) work->lens_not_moving) {
        /**
         * Make it so that the character selection menu can be accessed during gameplay. In the
         * final game, only the Button Config menu can be accessed during gameplay (through the
         * Pause Menu)
         */
        if ((*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR) != NULL) {
            self->inner.lens = (*lens_create)(
                self,
                work->lens_light,
                WINDOW_FLAG_80 | WINDOW_FLAG_OPEN_DOWN_RIGHT | WINDOW_FLAG_OPEN_RIGHT_DOWN |
                    WINDOW_FLAG_OPEN_DOWN | WINDOW_FLAG_OPEN_RIGHT,
                lens_pos[REINHARDT].x,
                lens_pos[REINHARDT].y,
                0.0f,
                96.0f,
                68.0f,
                30.0f
            );
            lens = self->inner.lens;
        } else {
            self->inner.lens = (*lens_create)(
                self,
                work->lens_light,
                WINDOW_FLAG_ENABLE_DISTORTION_EFFECT | WINDOW_FLAG_80 |
                    WINDOW_FLAG_OPEN_DOWN_RIGHT | WINDOW_FLAG_OPEN_RIGHT_DOWN |
                    WINDOW_FLAG_OPEN_DOWN | WINDOW_FLAG_OPEN_RIGHT,
                lens_pos[REINHARDT].x,
                lens_pos[REINHARDT].y,
                0.0f,
                96.0f,
                68.0f,
                30.0f
            );
            lens = self->inner.lens;
            (*WindowWork_setParams)(lens, WINDOW_FLAG_200000, 9, 9, 6.0f, 3.299999952f, NULL);
        }
        // Open the lens
        BITS_UNSET(lens->flags, WINDOW_CLOSING);
        BITS_SET(lens->flags, WINDOW_OPENING);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
        return;
    }
    if (BITS_HAS(scroll_state->flags, SCROLL_STATE_FLAG_OPENED)) {
        work->lens_not_moving = TRUE;
    }
}

void characterSelect_selectOption(characterSelect* self) {
    Model* character_portrait;
    characterSelect* self_temp;
    WindowWork* lens;
    mark_work* mark;
    characterSelectInner* inner;
    pc_select_work* work;
    s32 i;

    character_portrait = self->character_portraits[0];
    inner              = &self->inner;
    work               = inner->work;
    lens               = self->inner.lens;
    // Iterate through all the enabled characters and lower their brightness
    // if they're not highlighted by the lens
    if (character_portrait->primitive_color.integer >= RGBA(51, 51, 52, 0)) {
        for (self_temp = self, i = 0; i != NUM_CHARACTERS; i++,
            self_temp          = (u32*) self_temp + 1,
            character_portrait = self_temp->character_portraits[0]) {
            if (BITS_HAS(work->flags, BIT(i))) {
                character_portrait->primitive_color.integer -= RGBA(17, 17, 17, 0);
            }
        }
    }

    if ((s8) work->lens_not_moving) {
        // Player has not selected a new character
        if (work->current_character_option == work->previous_character_option) {
            // Moving the lens to the left
            if ((work->current_character_option == work->previous_character_option) &&
                (CONT_BTNS_PRESSED(CONT_0, L_JPAD) || (sys.controllers[0].joy_x < -25))) {
                work->current_character_option--;
            }
            // Moving the lens to the right
            if ((work->current_character_option == work->previous_character_option) &&
                (CONT_BTNS_PRESSED(CONT_0, R_JPAD) || (sys.controllers[0].joy_x >= 26))) {
                work->current_character_option++;
            }
            characterSelect_determineCharacterToSelect(
                work, work->current_character_option - work->previous_character_option
            );
            // Character is selected
            if (CONT_BTNS_PRESSED(CONT_0, A_BUTTON) ||
                CONT_BTNS_PRESSED(CONT_0, (START_BUTTON | RECENTER_BUTTON))) {
                // Apply alternate costume if moving up + if the appropiate Special jewels were obtained
                if (CONT_BTNS_PRESSED(CONT_0, U_JPAD) || (sys.controllers[0].joy_y >= 26)) {
                    // Make sure the player has finished the game before trying to assign the alternate costume
                    if (((BITS_HAS(
                              sys.SaveStruct_gameplay.flags, SAVE_FLAG_REINDHART_GOOD_ENDING
                          ) ||
                          BITS_HAS(sys.SaveStruct_gameplay.flags, SAVE_FLAG_CARRIE_GOOD_ENDING)) ||
                         BITS_HAS(sys.SaveStruct_gameplay.flags, SAVE_FLAG_REINDHART_BAD_ENDING)) ||
                        BITS_HAS(sys.SaveStruct_gameplay.flags, SAVE_FLAG_CARRIE_BAD_ENDING)) {
                        // Reinhardt is selected
                        if (((u32) work->previous_character_option == REINHARDT) &&
                            BITS_HAS(
                                sys.SaveStruct_gameplay.flags, SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME
                            )) {
                            sys.alternate_costume = TRUE;
                            BITS_SET(
                                sys.SaveStruct_gameplay.flags, SAVE_FLAG_COSTUME_IS_BEING_USED
                            );
                        }
                        // Carrie is selected
                        if (((u32) work->previous_character_option == CARRIE) &&
                            BITS_HAS(
                                sys.SaveStruct_gameplay.flags, SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME
                            )) {
                            sys.alternate_costume = TRUE;
                            BITS_SET(
                                sys.SaveStruct_gameplay.flags, SAVE_FLAG_COSTUME_IS_BEING_USED
                            );
                        }
                    }
                }
                // Increase the character portrait's brightness when selected
                switch ((u32) work->previous_character_option) {
                    case REINHARDT:
                        character_portrait = self->character_portraits[REINHARDT];
                        break;
                    case CARRIE:
                        character_portrait = self->character_portraits[CARRIE];
                        break;
                }
                character_portrait->primitive_color.integer = RGBA(255, 255, 255, 255);
                // Close lens
                BITS_UNSET(lens->flags, WINDOW_OPENING);
                BITS_SET(lens->flags, WINDOW_CLOSING);
                // Display a red circle on the selected character
                mark = (*markWork_create)(
                    self,
                    work->scroll_elements_light,
                    MARK_FLAG_DRAW_CIRCLE,
                    character_portrait->position.x,
                    character_portrait->position.y,
                    67.0f,
                    1.0f,
                    1.0f,
                    1.0f,
                    20.0f
                );
                self->inner.mark = mark;
                BITS_SET(mark->flags, MARK_FLAG_DISPLAY);
                work->lens_not_moving = work->field_0x20 = FALSE;
                (*object_curLevel_goToNextFuncAndClearTimer)(
                    self->header.current_function, &self->header.function_info_ID
                );
                return;
            }
            // Back out of the menu
            if (CONT_BTNS_PRESSED(CONT_0, B_BUTTON)) {
                // Close lens
                BITS_UNSET(lens->flags, WINDOW_OPENING);
                BITS_SET(lens->flags, WINDOW_CLOSING);
                // Display a red cross on the center of the screen
                mark = (*markWork_create)(
                    self,
                    work->scroll_elements_light,
                    MARK_FLAG_DRAW_CROSS,
                    0.0f,
                    0.0f,
                    67.0f,
                    3.0f,
                    3.0f,
                    3.0f,
                    20.0f
                );
                self->inner.mark = mark;
                BITS_SET(mark->flags, MARK_FLAG_DISPLAY);
                work->lens_not_moving = work->field_0x20 = FALSE;
                work->current_character_option           = -1;
                (*object_curLevel_goToNextFuncAndClearTimer)(
                    self->header.current_function, &self->header.function_info_ID
                );
                return;
            }
        } else { // Player has selected a new character
            work->lens_not_moving           = FALSE;
            self->inner.lens_pos_multiplier = 0.0f;
            self->inner.lens_pos.x          = lens_pos[work->current_character_option].x -
                lens_pos[work->previous_character_option].x;
            self->inner.lens_pos.y = lens_pos[work->current_character_option].y -
                lens_pos[work->previous_character_option].y;
            work->max_cursor_transition_delay     = 3;
            work->current_cursor_transition_delay = 0;
        }
    } else {
        self->inner.lens_pos_multiplier = ((f32) work->current_cursor_transition_delay) /
            ((f32) work->max_cursor_transition_delay);
        if (self->inner.lens_pos_multiplier >= 1.0) {
            work->lens_not_moving           = TRUE;
            self->inner.lens_pos_multiplier = 1.0f;
        }
        lens->position.x = (s32) (lens_pos[work->previous_character_option].x +
                                  (self->inner.lens_pos.x * self->inner.lens_pos_multiplier));
        lens->position.y = (s32) (lens_pos[work->previous_character_option].y +
                                  (self->inner.lens_pos.y * self->inner.lens_pos_multiplier));
        work->current_cursor_transition_delay++;

        if ((s8) work->lens_not_moving) {
            work->previous_character_option = work->current_character_option;
        }
    }
}

void characterSelect_optionSelected(characterSelect* self) {
    pc_select_work* work       = self->inner.work;
    scroll_state* scroll_state = self->inner.scrollState;
    WindowWork* lens_temp1     = self->inner.lens;
    WindowWork* lens_temp2     = lens_temp1;
    mark_work* mark            = self->inner.mark;

    if ((s8) work->lens_not_moving == FALSE) {
        if (lens_temp2 != NULL) {
            // TODO: (WINDOW_CLOSING | WINDOW_OPENING) represents flag 0x300.
            // However, we don't know if that specific flag represents something
            // not related to opening / closing the lens
            if ((BITS_MASK(lens_temp2->flags, 0x300) >> 8) == FALSE) {
                if (1) {
                }
                BITS_SET(lens_temp2->flags, 0x300);
                self->inner.lens = NULL;
            }
        } else if ((BITS_MASK(mark->flags, MARK_FLAG_DISPLAY) >> 2) == FALSE) {
            BITS_UNSET(scroll_state->flags, SCROLL_STATE_FLAG_OPENING);
            BITS_SET(scroll_state->flags, SCROLL_STATE_FLAG_CLOSING);
            work->lens_not_moving = TRUE;
        }
    } else if ((self->inner.scrollState != NULL) && BITS_NOT_HAS(scroll_state->flags, SCROLL_STATE_FLAG_HIDE)) {
        if (1) {
        }
        if (scroll_state->position.y > 60.0f) {
            if (lens_temp1 && self->inner.lens) {
            }
            BITS_UNSET(mark->flags, MARK_FLAG_DISPLAY);
            BITS_SET(mark->flags, MARK_FLAG_DESTROY);
            BITS_SET(self->inner.character_names[REINHARDT]->flags, MFDS_FLAG_CLOSE_TEXTBOX);
            if (1) {
            }
            BITS_SET(self->inner.character_names[CARRIE]->flags, MFDS_FLAG_CLOSE_TEXTBOX);
            scroll_state->flags     = SCROLL_STATE_FLAG_HIDE;
            self->inner.scrollState = NULL;
            work->player_character  = work->current_character_option + 1;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
        }
        if (1) {
        }
        scroll_state->position.y += 6.0f;
    }
}

void characterSelect_destroy(characterSelect* self) {
    if ((*objectList_findFirstObjectByID)(MENU_LENS) == NULL) {
        self->header.destroy(self);
    }
}

void characterSelect_determineCharacterToSelect(
    pc_select_work* work, s8 new_character_option_offset
) {
    s32 character;

    while (TRUE) {
        // Clamp `work->current_character_option`
        if (work->current_character_option >= work->number_of_characters) {
            // Make sure the character option is always positive.
            if (new_character_option_offset >= 0) {
                character = new_character_option_offset;
            } else {
                character = -new_character_option_offset;
            }
            // Hardcoded check for selecting Reinhardt if attempting to
            // select a character past Carrie.
            // This makes the game unable to select more than 2 characters.
            if (character == CARRIE) {
                work->current_character_option = REINHARDT;
            } else {
                // Clamp `work->current_character_option`
                work->current_character_option =
                    work->current_character_option % work->number_of_characters;
            }
        }
        // @bug? If the `work->current_character_option` is larger than `work->number_of_characters`,
        // it will still assign a negative value. This value will eventually go up until it
        // reaches a positive value after some time.
        if (work->current_character_option < 0) {
            work->current_character_option =
                work->number_of_characters + work->current_character_option;
        }
        // Check if the characters are disabled. If not, don't select them.
        if (BITS_NOT_HAS(work->flags, BIT(work->current_character_option))) {
            work->current_character_option =
                work->current_character_option + new_character_option_offset;
            new_character_option_offset = (u8) new_character_option_offset;
        } else {
            return;
        }
    }
}
