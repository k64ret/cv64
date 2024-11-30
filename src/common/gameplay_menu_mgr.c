/**
 * @file gameplay_menu_mgr.c
 *
 * This file contains the code for the `gameplayMenuMgr`,
 * which handles accessing menus during gameplay.
 */

#include "objects/menu/gameplayMenuMgr.h"
#include "objects/engine/DMAMgr.h"
#include "memory.h"
#include "sound.h"
#include "gamestate.h"
#include "system_work.h"

gameplayMenuMgrFuncs gameplayMenuMgr_functions[] = {
    gameplayMenuMgr_initMainStructs,
    gameplayMenuMgr_initHUDParams,
    gameplayMenuMgr_outsideMenuLoop,
    gameplayMenuMgr_initMenu,
    gameplayMenuMgr_insideMenuLoop,
    gameplayMenuMgr_exitMenu,
    object_doNothing
};

u32 selection_text_button_pressed      = 0;
u32 selection_text_joystick_input_held = 0;
u32 selection_text_idle_time           = 0;

/**
 * The character display system has been started. (%p)\n
 */
const char gameplayMenuMgr_unusedString1[] = "文字侮ｦシステムを起動しました。(%p)\n";
/**
 * etc_ctrl : No. %02d Unknown screen request.\nEntering standby mode.\n
 */
const char gameplayMenuMgr_unusedString2[] =
    "etc_ctrl : No. %02d 不明な画面要求がありました。\n待機モードに移行します。\n";
const char gameplayMenuMgr_unusedString3[] = "etc_ctrl : alloc trunc size = 0x%08x!!\n";
const char gameplayMenuMgr_unusedString4[] = "etc_ctrl : Call Status!!\n";
const char gameplayMenuMgr_unusedString5[] = "etc_ctrl : Call Item Shop!!\n";
const char gameplayMenuMgr_unusedString6[] = "etc_ctrl : Call Gameover!!\n";
const char gameplayMenuMgr_unusedString7[] = "etc_ctrl : Return to GAME!!\n";
const char gameplayMenuMgr_unusedString8[] = "etc_ctrl : Call Title!!\n";

/**
 * After `gameplayMenuMgr` has created its main structs, there's a small delay
 * of 10 frames
 */
u32 initialize_hud_params_delay_timer;

void gameplayMenuMgr_entrypoint(gameplayMenuMgr* self) {
    ENTER(self, gameplayMenuMgr_functions);
}

void gameplayMenuMgr_initMainStructs(gameplayMenuMgr* self) {
    MfdsState* common_textbox;
    HUD* obj_hud;

    initialize_hud_params_delay_timer = 0;

    obj_hud = (*objectList_findFirstObjectByID)(MENU_HUD);
    if (obj_hud != NULL) {
        self->HUD_params = obj_hud->params;
    } else {
        self->HUD_params = NULL;
    }

    if (self->HUD_params == NULL) {
        if ((*objectList_findFirstObjectByID)(MENU_HUD) == NULL) {
            self->obj_hud = (*object_createAndSetChild)(self, MENU_HUD);
        }
        self->HUD_params = NULL;
    }

    common_textbox = textbox_create(
        self, common_camera_HUD, MFDS_FLAG_GAMEPLAYMENUMGR_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED
    );
    self->common_textbox = common_textbox;
    if (1) {
    }
    common_textbox->palette = TEXT_COLOR_WHITE;
    textbox_setPos(common_textbox, 30, 150, 1);
    textbox_setDimensions(common_textbox, 4, 255, 0, 0);
    textbox_enableLens(
        common_textbox,
        WINDOW_FLAG_40000 | WINDOW_FLAG_OPEN_DOWN_RIGHT | WINDOW_FLAG_OPEN_RIGHT_DOWN |
            WINDOW_FLAG_OPEN_DOWN | WINDOW_FLAG_OPEN_RIGHT,
        20.0f
    );
    textbox_setMessagePtr(common_textbox, NULL, NULL, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void gameplayMenuMgr_initHUDParams(gameplayMenuMgr* self) {
    HUD* obj_hud;

    if (initialize_hud_params_delay_timer < 10) {
        initialize_hud_params_delay_timer++;
        return;
    }

    initialize_hud_params_delay_timer = 0;

    obj_hud = (*objectList_findFirstObjectByID)(MENU_HUD);
    if (obj_hud != NULL) {
        self->HUD_params = obj_hud->params;
    } else {
        self->HUD_params = NULL;
    }

    if (self->HUD_params != NULL) {
        self->menu_state                        = 0;
        self->update_assets_heap_block_max_size = FALSE;
        self->flags                             = IN_GAMEPLAY;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void gameplayMenuMgr_outsideMenuLoop(gameplayMenuMgr* self) {
    if (ptr_PlayerData != NULL) {
        self->current_opened_menu = sys.current_opened_menu;

        // Checks for determining if the pause menu should open or not.
        // If pressed Start...
        if ((CONT_BTNS_PRESSED(CONT_0, START_BUTTON | RECENTER_BUTTON)) &&
            // If we're in gameplay and there's no cutscene playing...
            !(sys.cutscene_flags & CUTSCENE_FLAG_PLAYING) && (sys.map_is_setup) &&
            // If the player nor the gameplay are frozen (for example, when reading textboxes)
            (sys.FREEZE_PLAYER == FALSE) && (sys.FREEZE_GAMEPLAY == FALSE)) {
            // If the player is idling or moving
            if ((sys.ptr_PlayerObject->header.current_function[0].function == PLAYER_IDLE) ||
                (sys.ptr_PlayerObject->header.current_function[0].function == PLAYER_MOVING)) {
                sys.current_opened_menu = MENU_ID_PAUSE;
            }
        }

        // Make sure to close the common textbox if entering a menu
        if (self->current_opened_menu != MENU_ID_NOT_ON_MENU) {
            if (self->common_textbox->flags & MFDS_FLAG_OPEN_TEXTBOX) {
                self->hide_common_textbox_window = TRUE;
                gameplayMenuMgr_closeCommonTextbox();
                self->common_textbox->flags |= MFDS_FLAG_HIDE_TEXTBOX;
            } else {
                self->hide_common_textbox_window = FALSE;
            }

            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

void gameplayMenuMgr_initMenu(gameplayMenuMgr* self) {
    HUD* obj_hud;
    HUDParams* hud_params;

    if (self->hide_common_textbox_window) {
        if (lensAreClosed() == FALSE) {
            getGameplayMenuMgrTextboxObjectFromList()->window->flags |= WINDOW_HIDE;
        }
        self->hide_common_textbox_window = FALSE;
    }

    (*heap_init)(
        HEAP_KIND_MENU_DATA,
        (HeapBlockHeader*) &HEAP_MENU_DATA_START,
        HEAP_MENU_DATA_SIZE,
        HEAP_WRITE_BACK_CACHE_TO_RAM
    );

    switch (self->current_opened_menu) {
        case MENU_ID_PAUSE:
            self->menu_state |= ENTERING_PAUSE_MENU;
            self->assets_file_buffer_start_ptr =
                (*heap_alloc)(HEAP_KIND_MENU_DATA, NI_ASSETS_MENU_BUFFER_SIZE);
            self->update_assets_heap_block_max_size = TRUE;
            DMAMgr_loadNisitenmaIchigoFile(
                ptr_DMAMgr,
                NI_ASSETS_MENU,
                self->assets_file_buffer_start_ptr,
                &self->assets_file_buffer_end_ptr
            );
            NisitenmaIchigo_checkAndStoreLoadedFile(NI_ASSETS_MENU);
            NisitenmaIchigo_checkAndStoreLoadedFile(NI_ASSETS_MENU);
            break;

        case MENU_ID_RENON_SHOP:
            self->menu_state |= ENTERING_RENON_SHOP;

            obj_hud = (*objectList_findFirstObjectByID)(MENU_HUD);
            if (obj_hud != NULL) {
                hud_params = obj_hud->params;
            } else {
                hud_params = NULL;
            }
            self->HUD_params = hud_params;

            if (hud_params != NULL) {
                hud_params->flags |= HUD_PARAMS_HIDE_HUD;
            }

            self->assets_file_buffer_start_ptr =
                (*heap_alloc)(HEAP_KIND_MENU_DATA, NI_ASSETS_MENU_BUFFER_SIZE);
            self->update_assets_heap_block_max_size = TRUE;
            DMAMgr_loadNisitenmaIchigoFile(
                ptr_DMAMgr,
                NI_ASSETS_MENU,
                self->assets_file_buffer_start_ptr,
                &self->assets_file_buffer_end_ptr
            );
            NisitenmaIchigo_checkAndStoreLoadedFile(NI_ASSETS_MENU);
            break;

        case MENU_ID_GAME_OVER:
            self->menu_state |= ENTERING_GAME_OVER;

            obj_hud = (*objectList_findFirstObjectByID)(MENU_HUD);
            if (obj_hud != NULL) {
                hud_params = obj_hud->params;
            } else {
                hud_params = NULL;
            }
            self->HUD_params = hud_params;

            if (hud_params != NULL) {
                hud_params->flags |= HUD_PARAMS_HIDE_HUD;
            }

            (*heap_free)(HEAP_KIND_MENU_DATA);
            break;

        default:
            (*heap_free)(HEAP_KIND_MENU_DATA);
            sys.current_opened_menu = MENU_ID_NOT_ON_MENU;
            (*object_curLevel_goToPrevFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
    }

    self->background_color.integer = sys.background_color.integer;
    sys.background_color.integer   = RGBA(0, 0, 0, 255);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

// clang-format off
void gameplayMenuMgr_insideMenuLoop(gameplayMenuMgr* self) {
    s32 temp[2];

    if ((self->assets_file_buffer_end_ptr != NULL) && (self->update_assets_heap_block_max_size)) {
        heapBlock_updateBlockMaxSize(self->assets_file_buffer_start_ptr, (u32) self->assets_file_buffer_end_ptr - (u32) self->assets_file_buffer_start_ptr);
        self->update_assets_heap_block_max_size = FALSE;
    }

    if ((*Fade_IsFading)() == FALSE) {
        sys.background_color.integer = RGBA(0, 0, 0, 255);
        if (self->flags & IN_GAMEPLAY) {
            if (self->menu_state & ENTERING_PAUSE_MENU) {
                if (objectList_findFirstObjectByID(MENU_PAUSE) == NULL) {
                    object_createAndSetChild(self, MENU_PAUSE);
                    self->menu_state &= ~ENTERING_PAUSE_MENU; self->flags &= ~IN_GAMEPLAY; self->flags |= IN_PAUSE_MENU;
                    if ((*Fade_IsFading)() == FALSE) {
                        (*Fade_SetSettings)(FADE_IN, 22, 0, 0, 0);
                    }
                    if (self->HUD_params != NULL) {
                        self->HUD_params->flags ^= HUD_PARAMS_ENTERED_PAUSE_MENU;
                    }
                }
            }
            else if (self->menu_state & ENTERING_RENON_SHOP) {
                if (objectList_findFirstObjectByID(MENU_RENON_SHOP) == NULL) {
                    object_createAndSetChild(self, MENU_RENON_SHOP);
                    if (1) {}
                    self->menu_state &= ~ENTERING_RENON_SHOP; self->flags &= ~IN_GAMEPLAY; self->flags |= IN_RENON_SHOP;
                    sys.cutscene_flags |= CUTSCENE_FLAG_PLAYING;
                }
            }
            else if (self->menu_state & ENTERING_GAME_OVER) {
                if (objectList_findFirstObjectByID(ENGINE_GAME_OVER) == NULL) {
                    object_createAndSetChild(self, ENGINE_GAME_OVER);
                    self->menu_state &= ~ENTERING_GAME_OVER; self->flags &= ~IN_GAMEPLAY; self->flags |= IN_GAME_OVER;
                    if ((*Fade_IsFading)() == FALSE) {
                        (*Fade_SetSettings)(FADE_IN, 15, 0, 0, 0);
                    }
                    sys.cutscene_flags |= CUTSCENE_FLAG_PLAYING;
                }
            }
        }
        else if (self->flags & IN_PAUSE_MENU) {
            if (objectList_findFirstObjectByID(MENU_PAUSE) == NULL) {
                if (self->menu_state & ENTERING_FILE_SELECT) {
                    if (objectList_findFirstObjectByID(MENU_FILE_SELECT_CONTROLLER) == NULL) {
                        object_createAndSetChild(self, MENU_FILE_SELECT_CONTROLLER);
                        self->menu_state &= ~ENTERING_FILE_SELECT; self->flags &= ~IN_PAUSE_MENU; self->flags |= IN_FILE_SELECT;
                        (*Fade_SetSettings)(FADE_IN, 45, 0, 0, 0);
                        sys.cutscene_flags |= CUTSCENE_FLAG_PLAYING;
                        return;
                    }
                }
                else if (self->menu_state & ENTERING_OPTION) {
                    if (objectList_findFirstObjectByID(MENU_OPTIONS_CONTROLLER) == NULL) {
                        object_createAndSetChild(self, MENU_OPTIONS_CONTROLLER);
                        self->menu_state &= ~ENTERING_OPTION; self->flags &= ~IN_PAUSE_MENU; self->flags |= IN_OPTIONS_MENU;
                        (*Fade_SetSettings)(FADE_IN, 60, 0, 0, 0);
                        sys.cutscene_flags |= CUTSCENE_FLAG_PLAYING;
                    }
                }
                else if (self->menu_state & EXIT_MENU) {
                    if (objectList_findFirstObjectByID(MENU_PAUSE) == NULL) {
                        if (self->HUD_params != NULL) {
                            self->HUD_params->flags ^= HUD_PARAMS_ENTERED_PAUSE_MENU;
                        }
                        (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
                    }
                }
                else if (self->menu_state & QUIT_GAME) {
                    if (objectList_findFirstObjectByID(MENU_PAUSE) == NULL) {
                        (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
                    }
                }
            }
        }
        else if (self->flags & IN_FILE_SELECT) {
            if (self->menu_state & ENTERING_PAUSE_MENU) {
                if ((objectList_findFirstObjectByID(MENU_FILE_SELECT_CONTROLLER) == NULL) && (objectList_findFirstObjectByID(MENU_PAUSE) == NULL)) {
                    object_createAndSetChild(self, MENU_PAUSE);
                    self->menu_state &= ~ENTERING_PAUSE_MENU; self->flags &= ~IN_FILE_SELECT; self->flags |= IN_PAUSE_MENU;
                    (*Fade_SetSettings)(FADE_IN, 15, 0, 0, 0);
                }
            }
            else if (self->menu_state & INIT_NEW_GAME) {
                if ((objectList_findFirstObjectByID(MENU_FILE_SELECT_CONTROLLER) == NULL) && (objectList_findFirstObjectByID(MENU_PAUSE) == NULL)) {
                    object_createAndSetChild(self, MENU_PAUSE);
                    self->menu_state &= ~ENTERING_PAUSE_MENU; self->flags &= ~IN_FILE_SELECT; self->flags |= IN_PAUSE_MENU;
                    (*Fade_SetSettings)(FADE_IN, 15, 0, 0, 0);
                }
            }
            else if (self->menu_state & MENU_STATE_100) {
                if ((objectList_findFirstObjectByID(MENU_FILE_SELECT_CONTROLLER) == NULL) && (objectList_findFirstObjectByID(MENU_PAUSE) == NULL)) {
                    object_createAndSetChild(self, MENU_PAUSE);
                    self->menu_state &= ~ENTERING_PAUSE_MENU; self->flags &= ~IN_FILE_SELECT; self->flags |= IN_PAUSE_MENU;
                    (*Fade_SetSettings)(FADE_IN, 15, 0, 0, 0);
                }
            }
        }
        else if (self->flags & IN_OPTIONS_MENU) {
            if (self->menu_state & ENTERING_PAUSE_MENU) {
                if ((objectList_findFirstObjectByID(MENU_OPTIONS_CONTROLLER) == NULL) && (objectList_findFirstObjectByID(MENU_PAUSE) == NULL)) {
                    object_createAndSetChild(self, MENU_PAUSE);
                    self->menu_state &= ~ENTERING_PAUSE_MENU; self->flags &= ~IN_OPTIONS_MENU; self->flags |= IN_PAUSE_MENU;
                    (*Fade_SetSettings)(FADE_IN, 15, 0, 0, 0);
                }
            }
        }
        else if (self->flags & IN_RENON_SHOP) {
            if (self->menu_state & EXIT_MENU) {
                if (objectList_findFirstObjectByID(MENU_RENON_SHOP) == NULL) {
                    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
                }
            }
        }
        else if (self->flags & IN_GAME_OVER) {
            if (self->menu_state & EXIT_MENU) {
                if (objectList_findFirstObjectByID(MENU_PAUSE) == NULL) {
                    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
                }
            }
            else if (self->menu_state & QUIT_GAME) {
                if (objectList_findFirstObjectByID(MENU_PAUSE) == NULL) {
                    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
                }
            }
        }
    }
}
// clang-format off

void gameplayMenuMgr_exitMenu(gameplayMenuMgr* self) {
    if ((*Fade_IsFading)() == FALSE) {
        (*heap_free)(HEAP_KIND_MENU_DATA);

        if (self->menu_state & EXIT_MENU) {
            // clang-format off
            self->menu_state &= ~EXIT_MENU; self->flags &= ~IN_PAUSE_MENU; self->flags |= IN_GAMEPLAY;
            // clang-format on
            sys.current_opened_menu      = sys.NOT_ON_MENU;
            sys.background_color.integer = self->background_color.integer;
            sys.cutscene_flags &= ~CUTSCENE_FLAG_PLAYING;
        } else if (self->menu_state & QUIT_GAME) {
            // clang-format off
            self->menu_state &= ~QUIT_GAME; self->flags &= ~IN_PAUSE_MENU; self->flags |= IN_QUIT_GAME;
            // clang-format on
            (*play_sound)(SD_CTRL_RESET_AUDIO_TRACK_STATE);
            gamestate_change(GAMESTATE_KONAMI_LOGO);
            (*Fade_SetSettings)(FADE_IN, 30, 0, 0, 0);
            sys.current_opened_menu = sys.NOT_ON_MENU;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
        }

        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            GAMEPLAYMENUMGR_OUTSIDE_MENU_LOOP
        );
    }
}

u32 moveSelectionCursor(u32 button) {
    u32 selection_input = 0;

    if (selection_text_idle_time != sys.global_timer_capped) {
        if (GET_CONTROLLER(CONT_0).joy_y > 40) {
            selection_input = U_JPAD;
        }
        if (GET_CONTROLLER(CONT_0).joy_y < -40) {
            selection_input |= D_JPAD;
        }
        if (GET_CONTROLLER(CONT_0).joy_x > 40) {
            selection_input |= R_JPAD;
        }
        if (GET_CONTROLLER(CONT_0).joy_x < -40) {
            selection_input |= L_JPAD;
        }

        selection_text_button_pressed =
            (selection_text_joystick_input_held ^ selection_input) & selection_input;
        selection_text_joystick_input_held = selection_input;

        if (selection_input & (U_JPAD | D_JPAD | R_JPAD | L_JPAD)) {
            selection_text_button_pressed =
                (GET_CONTROLLER(CONT_0).btns_pressed & ~(U_JPAD | D_JPAD | R_JPAD | L_JPAD)) |
                selection_text_button_pressed;
        } else {
            selection_text_button_pressed =
                GET_CONTROLLER(CONT_0).btns_pressed | selection_text_button_pressed;
        }

        selection_text_idle_time = sys.global_timer_capped;
    }

    if (selection_text_button_pressed) {
    }
    return selection_text_button_pressed & button;
}
