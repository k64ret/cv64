/**
 * @file pause_menu.c
 *
 * This file contains the code that handles the Pause menu (officially known as "Status").
 *
 * @note Some parts of the pause menu are controlled by other entities
 *       (for example, the `scroll` handles part of the item selection logic).
 */

#include "objects/menu/pause_menu.h"
#include "memory.h"
#include "sound.h"
#include "gfx/figure.h"
#include "system_work.h"

// clang-format off

u16 item_descriptions[] = {
#include "objects/menu/pause_menu_item_description_text.msg"
};

u16 options_text[] = {
#include "objects/menu/pause_menu_options_text.msg"
};

u16 item_usage_text[] = {
#include "objects/menu/pause_menu_item_usage_text.msg"
};

u16 confirmation_text[] = {
#include "objects/menu/pause_menu_confirmation_text.msg"
};

u16 selection_arrow_character[] = {
#include "objects/menu/pause_menu_arrow_selection_char.msg"
};

/**
 * This array holds what items can be used in the item menu, and what effects they
 * do to the player
 */
ItemUseSettings item_use_settings_array[] = {
    {ITEM_ID_HEALING_KIT, PLAYER_STATUS_TO_REMOVE(PLAYER_FLAG_POISON | PLAYER_FLAG_VAMP), 100},
    {ITEM_ID_ROAST_BEEF, PLAYER_STATUS_TO_REMOVE(0), 80},
    {ITEM_ID_ROAST_CHICKEN, PLAYER_STATUS_TO_REMOVE(0), 50},
    {ITEM_ID_PURIFYING, PLAYER_STATUS_TO_REMOVE(PLAYER_FLAG_VAMP), 0},
    {ITEM_ID_CURE_AMPOULE, PLAYER_STATUS_TO_REMOVE(PLAYER_FLAG_POISON), 0},
    {ITEM_ID_SUN_CARD, TIME_CARD, 6},
    {ITEM_ID_MOON_CARD, TIME_CARD, 18}
};

s32 sound_volume_decreased = FALSE;

PauseMenuFuncs pauseMenu_functions[] = {
    pauseMenu_decreaseSoundVolume,
    pauseMenu_init,
    pauseMenu_createMainMenu,
    pauseMenu_calcMainMenu,
    pauseMenu_createItemList,
    pauseMenu_calcItemList,
    pauseMenu_calcItemSelectedMenu,
    pauseMenu_destroy,
    pauseMenu_calcQuitMenu,
    object_doNothing
};

// clang-format on

// TODO: `extern const u32` for the dlists
u32 character_portraits[NUM_CHARACTERS] = {0x06013988, 0x06015360};

u32 D_0F002FBC[NUM_CHARACTERS] = {10, 10};

const char pauseMenu_unusedString1[] = "Status: Now In!!\n";

void pauseMenu_entrypoint(PauseMenu* self) {
    ENTER(self, pauseMenu_functions);
}

/**
 * Decrease the sound volume when entering the menu
 */
void pauseMenu_decreaseSoundVolume(PauseMenu* self) {
    if (sys.file_load_array_ID == 0) {
        sound_volume_decreased = FALSE;
        if ((*isSoundVolumeDecreased)() == FALSE) {
            (*decreaseSoundVolume)(TRUE);
            sound_volume_decreased = TRUE;
        }
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void pauseMenu_init(PauseMenu* self) {
    u32 character_portraits_dlists[2] = character_portraits;
    FigureLight* light;
    s32 scroll_bg_model_type;
    MfdsState* textbox;
    Model* model;
    s32 temp[2];
    gameplayMenuMgr* gameplay_menu_mgr;

    /**
     * Get gameplayMenuMgr instance
     */
    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        if (gameplay_menu_mgr->assets_file_buffer_end_ptr != NULL) {
            self->gameplay_menu_mgr = gameplay_menu_mgr;
        } else {
            return;
        }
    }

    /**
     * Create and setup the display cameras
     */
    (*Camera_SetParams)(common_camera_8009B448, 3);
    common_camera_8009B448->position.x          = 0.0f;
    common_camera_8009B448->position.y          = 0.0f;
    common_camera_8009B448->position.z          = 300.0f;
    common_camera_8009B448->look_at_direction.x = 0.0f;
    common_camera_8009B448->look_at_direction.y = 0.0f;
    common_camera_8009B448->look_at_direction.z = 0.0f;
    common_camera_8009B448->look_at_direction.y = 0.0f;

    (*Camera_SetParams)(common_camera_8009B44C, 3);
    common_camera_8009B44C->position.x          = 0.0f;
    common_camera_8009B44C->position.y          = 0.0f;
    common_camera_8009B44C->position.z          = 300.0f;
    common_camera_8009B44C->look_at_direction.x = 0.0f;
    common_camera_8009B44C->look_at_direction.y = 0.0f;
    common_camera_8009B44C->look_at_direction.z = 0.0f;
    common_camera_8009B44C->look_at_direction.y = 0.0f;

    /**
     * Create and setup the lights
     */
    light                       = (*light_create)(FIG_TYPE_LIGHT);
    self->scrolls_borders_light = light;
    (*figure_setChild)(light, common_camera_8009B44C);
    light->ambient_color.r = light->ambient_color.g = light->ambient_color.b = 160;
    light->number_of_lights                                                  = 1;
    light->lights[0].color.r                                                 = 207;
    light->lights[0].color.g                                                 = 207;
    light->lights[0].color.b                                                 = 207;
    light->lights[0].direction[0]                                            = 240;
    light->lights[0].direction[1]                                            = 0;
    light->lights[0].direction[2]                                            = 16;

    scroll_bg_model_type           = FIG_TYPE_HUD_ELEMENT;
    light                          = (*light_create)(FIG_TYPE_LIGHT);
    self->scrolls_background_light = light;
    (*figure_setChild)(light, common_camera_8009B448);
    light->ambient_color.r        = 160;
    light->ambient_color.g        = 160;
    light->ambient_color.b        = 160;
    light->number_of_lights       = 1;
    light->lights[0].color.r      = 207;
    light->lights[0].color.g      = 207;
    light->lights[0].color.b      = 207;
    light->lights[0].direction[0] = 240;
    light->lights[0].direction[1] = 16;
    light->lights[0].direction[2] = 16;

    /**
     * Create and setup the scroll background model
     */
    model = (*Model_createAndSetChild)(scroll_bg_model_type, common_camera_8009B444);
    self->scroll_background_model = model;
    model->dlist                  = (u32) &PAUSE_SCROLL_BG_MODEL_DL;
    model->assets_file            = NI_ASSETS_GAMEPLAY_HUD;
    model->flags |= FIG_FLAG_APPLY_PRIMITIVE_COLOR;
    model->primitive_color.integer = RGBA(80, 80, 80, 255);
    model->position.x              = 0.0f;
    model->position.y              = 0.0f;
    model->position.z              = 0.0f;
    model->size.x                  = 1.1f;
    model->size.y                  = 1.1f;
    model->size.z                  = 1.1f;

    /**
     * Create and setup the character portrait
     */
    model = (*Model_createAndSetChild)(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HUD_ELEMENT, model
    );
    self->character_portrait = model;
    model->material_dlist    = (u32) &PAUSE_CHARACTER_PORTRAIT_MATERIAL_DL;
    model->dlist             = FIG_APPLY_VARIABLE_TEXTURE_AND_PALETTE(
        character_portraits_dlists[sys.SaveStruct_gameplay.character]
    );
    model->assets_file = NI_ASSETS_GAMEPLAY_HUD;
    model->flags |= FIG_FLAG_APPLY_PRIMITIVE_COLOR;
    model->primitive_color.integer = RGBA(255, 255, 255, 255);
    model->texture                 = 0;
    model->palette                 = 0;
    model->position.z              = 0.0f;
    model->size.x                  = 5.0f;
    model->size.y                  = 5.0f;
    model->size.z                  = 5.0f;
    model->position.x              = -105.0f;
    model->position.y              = 75.0f;

    /**
     * Create and setup the character name's text
     */
    textbox = (*textbox_create)(
        self,
        common_camera_HUD,
        MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED |
            MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP | MFDS_FLAG_00000008 |
            MFDS_FLAG_MENU_TEXT_ID_PRINTS_MENU_STRING
    );
    if (textbox == NULL) {
        self->header.destroy(self);
    }
    self->character_name_textbox = textbox;
    textbox->palette             = TEXT_COLOR_BEIGE;
    (*textbox_setPos)(textbox, 85, 17, 1);
    (*textbox_setDimensions)(textbox, 1, 96, 0, 0);
    textbox->misc_text_IDs[0].menu_text_ID =
        MENU_TEXT_REINHARDT + sys.SaveStruct_gameplay.character;
    (*textbox_setMessagePtr)(textbox, NULL, NULL, 0);
    (*textbox_setScaleParameters)(textbox, 2, 2, 10.0f, 0.89999998f, 0.89999998f, FALSE, TRUE);

    /**
     * Create and setup the digital clock's text
     */
    textbox = (*textbox_create)(
        self,
        common_camera_HUD,
        MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED |
            MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP | MFDS_FLAG_00000008
    );
    if (textbox == NULL) {
        self->header.destroy(self);
    }
    self->digital_clock_textbox = textbox;
    textbox->palette            = TEXT_COLOR_BEIGE;
    (*textbox_setPos)(textbox, 90, 60, 1);
    (*textbox_setDimensions)(textbox, 1, 32, 0, 0);
    (*allocStructInObjectEntryList)("Digital_Clock", self, sizeof(DigitalClock), 12);
    if (self->digital_clock_text != NULL) {
        pauseMenu_updateDigitalClockDisplay(self);
    } else {
        self->header.destroy(self);
    }
    (*textbox_setMessagePtr)(textbox, self->digital_clock_text->clock_text, NULL, 0);

    self->delay_before_being_able_to_select_option = 7;
    sys.background_color.integer                   = RGBA(0, 0, 0, 255);
    self->field_0x51                               = TRUE;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

const char pauseMenu_unusedString2[] = "Status: Exit!!\n";
const char pauseMenu_unusedString3[] = "Status: Item Use Incomplete Support!!\n";
const char pauseMenu_unusedString4[] = "Status: Option Call!!\n";
const char pauseMenu_unusedString5[] = "Status: Title Return!!\n";
const char pauseMenu_unusedString6[] = "Status: Exit!!\n";
const char pauseMenu_unusedString7[] = "wait scroll to end\n";
const char pauseMenu_unusedString8[] = "i_no : %d\n";

void pauseMenu_createMainMenu(PauseMenu* self) {
    scroll_state* scroll;
    MfdsState* textbox;

    if (1) {
    }
    if (1) {
    }

    if ((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) {
        scroll = (*createScrollState)(
            self,
            self->scrolls_borders_light,
            self->scrolls_background_light,
            SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02,
            0,
            -6.0f,
            -3.0f,
            10.0f,
            50.0f,
            NULL
        );
        scroll->width.x = 0.5f;
        scroll->width.y = 0.5f;
        scroll->width.z = 0.44999999f;
        scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
        scroll->flags |= SCROLL_STATE_FLAG_OPENING;
        self->options_scroll = scroll;

        textbox = (*textbox_create)(
            self,
            self->scrolls_borders_light,
            MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED |
                MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP
        );
        self->options_textbox = textbox;
        if (textbox) {
        }
        textbox->palette = TEXT_COLOR_WHITE;
        (*textbox_setPos)(textbox, 95, 90, 1);
        (*textbox_setDimensions)(textbox, 5, 100, 0, 0);
        (*textbox_setScaleParameters)(textbox, 2, 2, 11.0f, 1.0f, 1.0f, FALSE, TRUE);
        (*textbox_setMessagePtr)(
            textbox, GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &options_text), NULL, 0
        );
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void pauseMenu_calcMainMenu(PauseMenu* self) {
    s32 temp[2];
    scroll_state* options_scroll;
    MfdsState* options_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;
    Model* scroll_background_model;
    s32 textbox_option;

    options_textbox = self->options_textbox;
    options_scroll  = self->options_scroll;

    /**
     * Exit back to gameplay after pressing B
     * (wait until the scroll is opened before being able to back out)
     */
    if (CONT_BTNS_PRESSED(CONT_0, CONT_B) && (options_scroll->flags & SCROLL_STATE_FLAG_OPENED)) {
        gameplay_menu_mgr =
            (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
        if (gameplay_menu_mgr != NULL) {
            gameplay_menu_mgr->menu_state |= EXIT_MENU;
        }

        (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
        options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
        self->options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, PAUSE_MENU_DESTROY
        );
        return;
    }

    textbox_option = options_textbox->textbox_option;

    if (textbox_option == TEXTBOX_OPTION_IDLE) {
        return;
    }
    switch (textbox_option) {
        /**
         * Go to Item menu
         */
        case PAUSE_MENU_ITEM:
            options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            break;

        /**
         * Go to Option menu (leaving the pause menu entirely)
         */
        case PAUSE_MENU_OPTION:
            gameplay_menu_mgr =
                (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
            if (gameplay_menu_mgr != NULL) {
                gameplay_menu_mgr->menu_state |= ENTERING_OPTION;
            }

            (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
            options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*object_curLevel_goToFunc)(
                self->header.current_function, &self->header.function_info_ID, PAUSE_MENU_DESTROY
            );
            break;

        /**
         * Go to Quit menu
         */
        case PAUSE_MENU_QUIT:
            scroll_background_model = self->scroll_background_model;
            (*memory_clear)(
                scroll_background_model->matrix, sizeof(scroll_background_model->matrix)
            );
            (*object_curLevel_goToFunc)(
                self->header.current_function,
                &self->header.function_info_ID,
                PAUSE_MENU_CALC_QUIT_MENU
            );
            break;

        /**
         * Exit back to gameplay
         */
        case PAUSE_MENU_BACK:
            gameplay_menu_mgr =
                (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
            if (gameplay_menu_mgr != NULL) {
                gameplay_menu_mgr->menu_state |= EXIT_MENU;
            }

            options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
            (*object_curLevel_goToFunc)(
                self->header.current_function, &self->header.function_info_ID, PAUSE_MENU_DESTROY
            );
            break;
    }
}

/**
 * Requests the creation of the Item menu
 */
void pauseMenu_createItemList(PauseMenu* self) {
    if ((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) {
        pauseMenu_createPauseItemMenuWork(
            self, 2, self->scrolls_borders_light, self->scrolls_background_light, 0
        );
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void pauseMenu_calcItemList(PauseMenu* self) {
    MfdsState* textbox;
    Model* item_model;
    s32 temp[2];
    PauseItemMenuWork* item_menu;
    s32 selected_item_in_item_list;
    scroll_state* item_scroll;
    scroll_state* options_scroll;

    item_menu = self->item_menu;
    if (item_menu != NULL) {
        selected_item_in_item_list = item_menu->selected_item_in_item_list;

        /**
         * If an non-empty item was selected...
         */
        if (selected_item_in_item_list != ITEM_ID_NOTHING) {

            // Go back to the main menu if selecting an invalid item
            if (selected_item_in_item_list == 0xFF) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    PAUSE_MENU_CREATE_MAIN_MENU
                );
                return;
            }

            /**
             * Create the selected item submenu
             */
            self->selected_item = selected_item_in_item_list;
            pauseMenu_createItemDescription(self);

            // Create the item model scroll
            item_scroll = (*createScrollState)(
                self,
                self->scrolls_borders_light,
                self->scrolls_background_light,
                SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02,
                0,
                -55.0f,
                5.0f,
                120.0f,
                30.0f,
                NULL
            );
            item_scroll->width.x = 0.6f;
            item_scroll->width.y = 0.3f;
            item_scroll->width.z = 0.27f;
            item_scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
            item_scroll->flags |= SCROLL_STATE_FLAG_OPENING;
            self->item_model_scroll = item_scroll;

            // Create the options text scroll
            options_scroll = (*createScrollState)(
                self,
                self->scrolls_borders_light,
                self->scrolls_background_light,
                SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02,
                0,
                45.0f,
                5.0f,
                120.0f,
                30.0f,
                NULL
            );
            options_scroll->width.x = 0.69999999f;
            options_scroll->width.y = 0.3f;
            options_scroll->width.z = 0.27f;
            options_scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
            options_scroll->flags |= SCROLL_STATE_FLAG_OPENING;
            self->options_text_scroll = options_scroll;

            // Create and setup the options text
            textbox = (*textbox_create)(
                self,
                self->scrolls_background_light,
                MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED |
                    MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP
            );
            self->options_textbox = textbox;
            if (textbox) {
            }
            textbox->palette = TEXT_COLOR_BEIGE;
            (*textbox_setPos)(textbox, 165, 100, 1);
            (*textbox_setDimensions)(textbox, 3, 100, 0, 0);
            (*textbox_setMessagePtr)(
                textbox, GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &item_usage_text), NULL, 0
            );
            (*textbox_setScaleParameters)(textbox, 2, 2, 120.0f, 0.8f, 0.8f, TRUE, TRUE);

            // Create and setup the options selection arrow
            textbox = (*textbox_create)(
                self,
                self->scrolls_background_light,
                MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED |
                    MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP
            );
            self->selection_arrow_textbox = textbox;
            if (textbox) {
            }
            textbox->palette = TEXT_COLOR_RED;
            (*textbox_setPos)(textbox, 160, 100, 1);
            (*textbox_setDimensions)(textbox, 1, 16, 0, 0);
            (*textbox_setMessagePtr)(
                textbox,
                GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &selection_arrow_character),
                NULL,
                0
            );
            (*textbox_setScaleParameters)(textbox, 2, 2, 120.0f, 0.8f, 0.8f, TRUE, TRUE);

            self->outside_item_selected_menu = FALSE;
            self->selected_item_in_item_list = item_menu->selected_item_in_item_list;

            // Create and setup the selected item model
            item_model =
                (*createItemModel)(self->selected_item_in_item_list, common_camera_HUD, "item");
            self->item_model                               = item_model;
            self->field_0x51                               = FALSE;
            self->delay_before_being_able_to_select_option = 0;
            self->option_selection_inside_selected_item    = 0;
            self->target_health                            = 0;
            self->target_hour                              = 0;
            item_model->position.x                         = -80.0f;
            item_model->position.y                         = -10.0f;

            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            return;
        }
    }

    self->selected_item_can_be_used = FALSE;
}

const char pauseMenu_unusedString9[]  = "Sub NG(%d)!!\n";
const char pauseMenu_unusedString10[] = "no.%d , st.%x , force.%d\n";
const char pauseMenu_unusedString11[] = "Cure Item Used(%d)!!\n";
const char pauseMenu_unusedString12[] = "Cure Item Non Used(%d)!!\n";
const char pauseMenu_unusedString13[] = "Time Item Non Used(%d)!!\n";
const char pauseMenu_unusedString14[] = "Time Item Used(%d)!!\n";
const char pauseMenu_unusedString15[] = "Sub Ok(%d)!!\n";
const char pauseMenu_unusedString16[] = "Scroll On Status Menu\n";
const char pauseMenu_unusedString17[] = "YS step :%d\n";

void pauseMenu_calcItemSelectedMenu(PauseMenu* self) {
    MfdsState* options_textbox;
    MfdsState* selection_arrow_textbox;
    scroll_state* item_model_scroll;
    scroll_state* options_text_scroll;
    scroll_state* item_description_scroll;
    Model* item_model;
    MfdsState* item_description;
    s32 item_amount;
    s32 temp;

    selection_arrow_textbox = self->selection_arrow_textbox;
    item_model_scroll       = self->item_model_scroll;
    options_text_scroll     = self->options_text_scroll;
    item_description_scroll = self->item_description_scroll;
    item_model              = self->item_model;
    temp                    = pauseMenu_checkIfItemCanBeUsed(self);
    options_textbox         = self->options_textbox;

    /**
     * If the selected item cannot be used, assign the "Cannot use item" text.
     */
    if (temp) {
        (*textbox_setMessagePtr)(
            options_textbox,
            GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, (*text_getMessageFromPool)(item_usage_text, 1)),
            NULL,
            0
        );
        (*textbox_setPos)(options_textbox, 153, 90, 1);
        (*textbox_setPos)(selection_arrow_textbox, 176, 119, 1);
        /**
         * Otherwise assign the text the Yes / No options text.
         */
    } else {
        (*textbox_setMessagePtr)(
            options_textbox,
            GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, (*text_getMessageFromPool)(item_usage_text, 0)),
            NULL,
            0
        );
        (*textbox_setPos)(options_textbox, 165, 100, 1);
    }
    // Display the options text set above
    if (temp != self->selected_item_can_be_used) {
        options_textbox->flags |= MFDS_FLAG_UPDATE_STRING;
        self->selected_item_can_be_used = temp;
    }

    if (options_text_scroll->flags & SCROLL_STATE_FLAG_OPENED) {
        item_description = self->item_description;

        /**
         * Go back to the item list submenu
         */
        if (self->outside_item_selected_menu) {
            if (!(item_model_scroll->flags & SCROLL_STATE_FLAG_CLOSING) &&
                !(options_text_scroll->flags & SCROLL_STATE_FLAG_CLOSING) &&
                !(item_description_scroll->flags & SCROLL_STATE_FLAG_CLOSING)) {
                item_model_scroll->flags       = SCROLL_STATE_FLAG_HIDE;
                options_text_scroll->flags     = SCROLL_STATE_FLAG_HIDE;
                item_description_scroll->flags = SCROLL_STATE_FLAG_HIDE;
                item_description->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
                self->options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
                selection_arrow_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
                pauseMenu_createPauseItemMenuWork(
                    self, 2, self->scrolls_borders_light, self->scrolls_background_light, 0
                );
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    PAUSE_MENU_CALC_ITEM_LIST
                );
            }
        } else {
            /**
             * Display the item model
             */
            (*figure_showModelAndChildren)(item_model, 0);

            /**
             * If an option was selected, or the cursor is moving...
             */
            if (self->delay_before_being_able_to_select_option != 0) {
                if (self->target_health != 0) {
                    /**
                     * If we're done filling the player's health, stop healing
                     */
                    if (sys.SaveStruct_gameplay.life >= self->target_health) {
                        self->target_health = 0;
                    }
                } else {
                    /**
                     * Update the clock advancing if requested (i.e. if `target_hour` != 0)
                     *
                     * @note Due to the `!= 0` check, time cards cannot be used to advance the time
                     *       to 0:00
                     */
                    if (self->target_hour != 0) {
                        pauseMenu_updateClock(self);
                        return;
                    }

                    /**
                     * Otherwise just decrease the delay timer
                     */
                    self->delay_before_being_able_to_select_option--;
                }
            } else {
                /**
                 * Move the selection cursor between the Yes / No options
                 */
                if (temp == 0) {
                    if ((*moveSelectionCursor)(U_JPAD)) {
                        self->delay_before_being_able_to_select_option = 4;
                        self->option_selection_inside_selected_item++;
                    } else if ((*moveSelectionCursor)(D_JPAD)) {
                        self->delay_before_being_able_to_select_option = 4;
                        self->option_selection_inside_selected_item--;
                    }
                    if (self->option_selection_inside_selected_item >= 2) {
                        self->option_selection_inside_selected_item = 0;
                    }
                    if (self->option_selection_inside_selected_item < 0) {
                        self->option_selection_inside_selected_item = 1;
                    }
                    (*textbox_setPos)(
                        selection_arrow_textbox,
                        160,
                        (self->option_selection_inside_selected_item * 14) + 101,
                        1
                    );
                } else {
                    self->option_selection_inside_selected_item = 1;
                }

                /**
                 * Option selected
                 */
                if (CONT_BTNS_PRESSED(CONT_0, A_BUTTON) &&
                    (self->delay_before_being_able_to_select_option == 0)) {
                    self->delay_before_being_able_to_select_option = 3;

                    /**
                     * If either "No" was selected, or the item cannot be used,
                     * go back to the item menu
                     */
                    if ((self->option_selection_inside_selected_item != 0) ||
                        CONT_BTNS_PRESSED(CONT_0, B_BUTTON)) {
                        item_model_scroll->flags &= ~SCROLL_STATE_FLAG_OPENING;
                        item_model_scroll->flags |= SCROLL_STATE_FLAG_CLOSING;
                        options_text_scroll->flags &= ~SCROLL_STATE_FLAG_OPENING;
                        options_text_scroll->flags |= SCROLL_STATE_FLAG_CLOSING;
                        item_description_scroll->flags &= ~SCROLL_STATE_FLAG_OPENING;
                        item_description_scroll->flags |= SCROLL_STATE_FLAG_CLOSING;
                        (*figure_destroySelfAndChildren_2)(item_model, 0);
                        self->outside_item_selected_menu = TRUE;
                        return;
                    }

                    /**
                     * If we have any ammo for the selected item...
                     */
                    item_amount = sys.SaveStruct_gameplay.items.array[self->selected_item - 1];
                    if (item_amount > 0) {
                        /**
                         * Obtain the selected item's usage parameters
                         * from `item_use_settings_array`
                         */
                        self->target_health = 0;
                        self->target_hour   = 0;
                        self->item_use_settings_array_entry =
                            getItemUseArrayEntry(self->selected_item);
                        self->item_effect =
                            item_use_settings_array[self->item_use_settings_array_entry]
                                .item_effect;
                        self->item_use_settings_target_value =
                            item_use_settings_array[self->item_use_settings_array_entry]
                                .target_value;

                        if (self->item_use_settings_array_entry >= 0) {
                            /**
                             * If the selected item is a healing item, and we don't have max health
                             * or we have a status that can be cured, proceed to healing
                             */
                            if ((self->item_effect & HEALING) &&
                                ((temp = CURABLE_STATUS_TO_PLAYER_FLAG(self->item_effect) &
                                      sys.SaveStruct_gameplay.player_status,
                                  ((sys.SaveStruct_gameplay.life < 100))) ||
                                 (temp))) {

                                /**
                                 * Play the health recovered voice clip when curing a status
                                 */
                                if (temp) {
                                    if (sys.SaveStruct_gameplay.character == REINHARDT) {
                                        (*prepareSoundForPlay_defaultSettings)(
                                            SD_REINHARDT_HEALTH_RECOVERY
                                        );
                                    } else {
                                        (*prepareSoundForPlay_defaultSettings)(
                                            SD_CARRIE_HEALTH_RECOVERY
                                        );
                                    }
                                }

                                /**
                                 * Set the `SAVE_FLAG_VAMP_CURED_USING_ITEM` save flag when curing
                                 * the VAMP status
                                 */
                                if ((self->item_effect &
                                     CURABLE_FLAG_TO_PLAYER_FLAG(PLAYER_FLAG_VAMP)) &&
                                    (sys.SaveStruct_gameplay.player_status & PLAYER_FLAG_VAMP)) {
                                    sys.SaveStruct_gameplay.flags |=
                                        SAVE_FLAG_VAMP_CURED_USING_ITEM;
                                }

                                /**
                                 * Fill the player's health
                                 */
                                (*HUDParams_FillPlayerHealth)(
                                    self->item_use_settings_target_value,
                                    CURABLE_STATUS_TO_PLAYER_FLAG(self->item_effect),
                                    FALSE
                                );

                                /**
                                 * Determine the new health value that will be applied after using the item
                                 */
                                self->target_health = self->item_use_settings_target_value +
                                    sys.SaveStruct_gameplay.life;
                                if (self->target_health > 100) {
                                    self->target_health = 100;
                                }

                                (*item_removeAmountFromInventory)(self->selected_item, 1);
                            }

                            /**
                             * If using an time card...
                             */
                            if ((self->item_effect & TIME_CARD) &&
                                ((self->item_use_settings_target_value !=
                                  sys.SaveStruct_gameplay.hour) ||
                                 (sys.SaveStruct_gameplay.minute != 0) ||
                                 (sys.SaveStruct_gameplay.seconds != 0))) {
                                /**
                                 * Play the clock ticking sound and request the clock to begin advancing
                                 */
                                (*play_sound)(SD_CLOCK_TICKING);
                                self->target_hour = self->item_use_settings_target_value;

                                (*item_removeAmountFromInventory)(self->selected_item, 1);
                            }
                        }
                    }
                }
                /**
                 * Go back to the item list if pressing B or when the amount for the selected item goes back to 0
                 *
                 * Close the scroll, textboxes and remove the item model
                 */
                else if (CONT_BTNS_PRESSED(CONT_0, B_BUTTON) || (self->option_selection_inside_selected_item < 0) || (sys.SaveStruct_gameplay.items.array[self->selected_item - 1] == 0)) {
                    item_model_scroll->flags &= ~SCROLL_STATE_FLAG_OPENING;
                    item_model_scroll->flags |= SCROLL_STATE_FLAG_CLOSING;
                    options_text_scroll->flags &= ~SCROLL_STATE_FLAG_OPENING;
                    options_text_scroll->flags |= SCROLL_STATE_FLAG_CLOSING;
                    item_description_scroll->flags &= ~SCROLL_STATE_FLAG_OPENING;
                    item_description_scroll->flags |= SCROLL_STATE_FLAG_CLOSING;
                    (*figure_destroySelfAndChildren_2)(item_model, 0);
                    self->outside_item_selected_menu = TRUE;
                }
            }
        }
    }
}

void pauseMenu_destroy(PauseMenu* self) {
    if (((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) && ((*Fade_IsFading)() == FALSE)) {
        // Increase sound volume back
        if (sound_volume_decreased) {
            (*decreaseSoundVolume)(FALSE);
        }

        sys.background_color.integer = RGBA(0, 0, 0, 255);
        self->header.destroy(self);
    }
}

void pauseMenu_calcQuitMenu(PauseMenu* self) {
    s32 temp;
    Model* scroll_background_model;
    MfdsState* textbox;
    gameplayMenuMgr* gameplay_menu_mgr;
    MfdsState* options_textbox;
    MiniScrollParameters* mini_scroll_params;
    miniScroll* mini_scroll;

    scroll_background_model = self->scroll_background_model;
    options_textbox         = self->options_textbox;
    mini_scroll_params      = &scroll_background_model->mini_scroll_params;

    switch (mini_scroll_params->state) {
        /**
         * Create the Quit submenu scroll
         */
        case PAUSE_QUIT_STATE_CREATE_SCROLL:
            mini_scroll = (*miniScroll_create)(self, self->scrolls_borders_light, 0, 0);
            mini_scroll_params->scroll = mini_scroll;
            (*miniScroll_setPosition)(mini_scroll_params->scroll, -6.0f, 26.0f, 100.0f);
            (*miniScroll_setWidth)(mini_scroll_params->scroll, 0.7f, 0.36f, 1.0f);
            (*miniScroll_setScrollingParams)(mini_scroll_params->scroll, 50.0f, 1);
            (*miniScroll_setState)(mini_scroll_params->scroll, MINISCROLL_STATE_OPEN);
            mini_scroll_params->state++;
            break;

        /**
         * Wait 5 frames for the scroll to initialize
         */
        case PAUSE_QUIT_STATE_WAIT_FOR_SCROLL_INIT:
            mini_scroll_params->scroll_init_delay_timer++;
            if (mini_scroll_params->scroll_init_delay_timer >= 5) {
                mini_scroll_params->scroll_init_delay_timer = 0;
                mini_scroll_params->state++;
                break;
            }
            break;

        /**
         * Create and setup the submenu's textbox
         */
        case PAUSE_QUIT_STATE_CREATE_TEXTBOX:
            textbox = (*textbox_create)(
                self,
                self->scrolls_borders_light,
                MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED
            );
            mini_scroll_params->textbox = textbox;
            (*textbox_setDimensions)(textbox, 3, 128, 0, 0);
            (*textbox_setScaleParameters)(
                mini_scroll_params->textbox, 2, 2, 101.0f, 0.8f, 0.8f, FALSE, FALSE
            );
            (*textbox_setMessagePtr)(
                mini_scroll_params->textbox,
                GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &confirmation_text),
                NULL,
                0
            );
            (*textbox_setPos)(mini_scroll_params->textbox, 104, 103, 0);
            mini_scroll_params->state++;
            break;

        case PAUSE_QUIT_STATE_OPEN_SCROLL:
            if ((*miniScroll_checkFlags)(mini_scroll_params->scroll, MINISCROLL_FLAG_OPENED)) {
                options_textbox->flags |= MINISCROLL_FLAG_CLOSED;
                mini_scroll_params->state++;
                break;
            }
            break;

        case PAUSE_QUIT_STATE_IDLE:
            if (mini_scroll_params->textbox->textbox_option != TEXTBOX_OPTION_IDLE) {
                /**
                 * After selecting an option, close the scroll and determine what to do next
                 */
                (*miniScroll_setState)(mini_scroll_params->scroll, MINISCROLL_STATE_CLOSE);
                mini_scroll_params->textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
                switch (mini_scroll_params->textbox->textbox_option - 1) {
                    // Yes
                    case 0:
                        mini_scroll_params->state = PAUSE_QUIT_STATE_QUIT_GAME;
                        break;

                    // No
                    case 1:
                        mini_scroll_params->state = PAUSE_QUIT_STATE_CLOSE_QUIT_SUBMENU;
                        break;
                }
            }
            break;

        /**
         * Go back to the Konami / KCEK logo screen
         */
        case PAUSE_QUIT_STATE_QUIT_GAME:
            gameplay_menu_mgr =
                (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
            if (gameplay_menu_mgr != NULL) {
                gameplay_menu_mgr->menu_state |= QUIT_GAME;
            }

            textbox = mini_scroll_params->textbox;
            textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;

            self->options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
            (*player_status_init)();

            mini_scroll_params->after_quit_state = PAUSE_MENU_DESTROY;
            mini_scroll_params->state            = PAUSE_QUIT_STATE_DESTROY_SCROLL;
            break;

        /**
         * Close the Quit submenu and go back to the main menu
         */
        case PAUSE_QUIT_STATE_CLOSE_QUIT_SUBMENU:
            mini_scroll_params->after_quit_state = PAUSE_MENU_CALC_MAIN_MENU;
            textbox                              = (*textbox_create)(
                self,
                self->scrolls_borders_light,
                MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED |
                    MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP
            );
            self->options_textbox = textbox;
            textbox->palette      = TEXT_COLOR_WHITE;
            options_textbox       = textbox;
            if (options_textbox) {
            }
            (*textbox_setPos)(textbox, 95, 90, 1);
            (*textbox_setDimensions)(options_textbox, 5, 100, 0, 0);
            if (options_textbox) {
            }
            (*textbox_setScaleParameters)(options_textbox, 2, 2, 11.0f, 1.0f, 1.0f, FALSE, TRUE);
            (*textbox_setMessagePtr)(
                options_textbox, GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &options_text), NULL, 0
            );
            mini_scroll_params->state = PAUSE_QUIT_STATE_DESTROY_SCROLL;
            break;

        /**
         * Destroy the scroll and switch the pause menu state to what was set in `after_quit_state`
         */
        case PAUSE_QUIT_STATE_DESTROY_SCROLL:
            if ((*miniScroll_checkFlags)(mini_scroll_params->scroll, MINISCROLL_FLAG_CLOSED)) {
                (*miniScroll_editFlags)(mini_scroll_params->scroll, MINISCROLL_STATE_DESTROY, -1);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    mini_scroll_params->after_quit_state
                );
            }
            break;
    }
}

/**
 * Updates the digital clock text with the internal time values
 */
void pauseMenu_updateDigitalClockDisplay(PauseMenu* self) {
    DigitalClock* digital_clock = self->digital_clock_text;
    s8 first_digit;
    s32 second_digit;

    // Hours
    first_digit                  = sys.SaveStruct_gameplay.hour / 10;
    digital_clock->clock_text[0] = PIXEL_HUD_0 + first_digit;
    digital_clock->clock_text[1] = PIXEL_HUD_0 + sys.SaveStruct_gameplay.hour - (first_digit * 10);

    // Colon
    digital_clock->clock_text[2] = ASCII_TO_CV64(':');

    // Minutes
    (u8*) digital_clock += 0x0A;
    first_digit                   = sys.SaveStruct_gameplay.minute / 10;
    digital_clock->clock_text[-2] = PIXEL_HUD_0 + first_digit;
    digital_clock->clock_text[-1] =
        PIXEL_HUD_0 + sys.SaveStruct_gameplay.minute - (first_digit * 10);

    // Null terminator
    digital_clock->clock_text[0] = 0;
}

/**
 * Creates `PauseItemMenuWork`, which contains parameters used while inside the Item menu
 *
 * @note The devs probably made a mistake as this struct is set to be called `sound_menu_work`,
 *       when `sound_menu_work` in reality corresponds to the struct that contains parameters
 *       that are used in the Options's Sound menu.
 */
PauseItemMenuWork* pauseMenu_createPauseItemMenuWork(
    PauseMenu* self, u8 ptrs_array_index, modelLighting* arg2, modelLighting* arg3, s32 arg4
) {
    PauseItemMenuWork* work;
    scroll_state* scroll;

    if (self != NULL) {
        (*allocStructInObjectEntryList)(
            "sound_menu_work", self, sizeof(PauseItemMenuWork), ptrs_array_index
        );
        work = ((Object*) self)->alloc_data[ptrs_array_index];
        if (work != NULL) {
            work->current_page               = 1;
            work->field_0x05                 = 0;
            work->number_of_pages_to_advance = 0;
            work->highlighted_option         = 0;
            work->selected_item_in_item_list = ITEM_ID_NOTHING;

            scroll = (*createScrollState)(
                self,
                arg2,
                arg3,
                SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02,
                9,
                0.0f,
                -30.0f,
                90.0f,
                30.0f,
                work
            );
            scroll->width.z = 0.6f;
            scroll->width.y = 0.6f;
            scroll->width.x = 1.5f;
            scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
            scroll->flags |= SCROLL_STATE_FLAG_OPENING;
            work->scroll = scroll;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
    return work;
}

const char pauseMenu_unusedString18[] = "Sub NG(%d)!!\n";

void func_0F001BF0() {}

/**
 * Creates the item description text when selecting an item
 */
void pauseMenu_createItemDescription(PauseMenu* self) {
    scroll_state* scroll;
    MfdsState* textbox;

    /**
     * Create and setup the text's background scroll
     */
    scroll = (*createScrollState)(
        self,
        self->scrolls_borders_light,
        self->scrolls_background_light,
        SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02,
        0,
        0.0f,
        -55.0f,
        100.0f,
        30.0f,
        NULL
    );
    scroll->width.x = 1.5f;
    scroll->width.y = 0.5f;
    scroll->width.z = 0.33f;
    scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
    scroll->flags |= SCROLL_STATE_FLAG_OPENING;
    self->item_description_scroll = scroll;

    /**
     * Create and setup the item description textbox
     */
    textbox = (*textbox_create)(
        self,
        self->scrolls_background_light,
        MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED |
            MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP
    );
    self->item_description = textbox;
    if (textbox) {
    }
    textbox->palette = TEXT_COLOR_BROWN;
    (*textbox_setPos)(textbox, 30, 157, 1);
    (*textbox_setDimensions)(textbox, 3, 255, 0, 0);
    (*textbox_setMessagePtr)(
        textbox,
        (*text_getMessageFromPool)(
            GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &item_descriptions), self->selected_item - 1
        ),
        NULL,
        0
    );
    (*textbox_setScaleParameters)(textbox, 2, 2, 100.0f, 0.8f, 0.8f, TRUE, TRUE);
}

/**
 * Given an item, it returns the index in `item_use_settings_array`
 * corresponding to the entry that belongs to said item.
 *
 * Returns -1 if it can't be found.
 */
s32 getItemUseArrayEntry(s32 item) {
    s32 entry_idx;

    for (entry_idx = 0; item_use_settings_array[entry_idx].item != ITEM_ID_NOTHING; entry_idx++) {
        if (item == item_use_settings_array[entry_idx].item) {
            return entry_idx;
        }
    }
    return -1;
}

/**
 * Update the clock while it's spinning after using a time card
 */
void pauseMenu_updateClock(PauseMenu* self) {
    sys.SaveStruct_gameplay.minute += 5.0f;
    if (sys.SaveStruct_gameplay.minute >= 60) {
        sys.SaveStruct_gameplay.minute -= 60;
        sys.SaveStruct_gameplay.hour++;
        if (sys.SaveStruct_gameplay.hour >= 24) {
            sys.SaveStruct_gameplay.hour = 0;
            sys.SaveStruct_gameplay.day++;
            if (sys.SaveStruct_gameplay.day >= 7) {
                sys.SaveStruct_gameplay.day = 0;
                sys.SaveStruct_gameplay.week++;
            }
        }

        /**
         * Stop the clock spin when it reaches the target hour
         */
        if (self->target_hour == sys.SaveStruct_gameplay.hour) {
            (*play_sound)(STOP_SOUND(SD_CLOCK_TICKING));
            sys.SaveStruct_gameplay.minute  = 0;
            sys.SaveStruct_gameplay.seconds = 0;
            self->target_hour               = 0;
        }
    }

    /**
     * Update the digital clock text with the new time values
     */
    pauseMenu_updateDigitalClockDisplay(self);
    (*textbox_setMessagePtr)(self->digital_clock_textbox, self->digital_clock_text, NULL, 0);
    self->digital_clock_textbox->flags |= MFDS_FLAG_UPDATE_STRING;
}

/**
 * Returns 0 if the selected item can be used. Otherwise returns -1
 */
s32 pauseMenu_checkIfItemCanBeUsed(PauseMenu* self) {
    s32 item_amount;
    s32 curable_statuses;
    s32 temp;

    /**
     * Don't use the item if the player doesn't have any amount of it
     */
    item_amount = sys.SaveStruct_gameplay.items.array[self->selected_item - 1];
    if (item_amount <= 0) {
        return -1;
    }

    /**
     * Get the item usage parameters for the selected item.
     * If the entry is invalid (-1), don't use the item
     */
    self->item_use_settings_array_entry = getItemUseArrayEntry(self->selected_item);
    self->item_effect = item_use_settings_array[self->item_use_settings_array_entry].item_effect;
    temp              = self->item_use_settings_array_entry;
    self->item_use_settings_target_value =
        item_use_settings_array[self->item_use_settings_array_entry].target_value;
    if (temp < 0) {
        return -1;
    }

    /**
     * If the selected item is a healing item...
     */
    if (self->item_effect & HEALING) {
        /**
         * Get the statuses that items can cure (VAMP, POISON and STO in practice),
         * then check if the player has that status (`temp`)
         */
        curable_statuses = MASK_CURABLE_STATUSES(self->item_effect);
        temp             = MASKED_CURABLE_STATUS_TO_PLAYER_FLAG(curable_statuses) &
            sys.SaveStruct_gameplay.player_status;

        /**
         * If the player doesn't have max health or if it has any of the curable statuses set,
         * allow the Healing Kit to be used
         */
        if ((self->selected_item == ITEM_ID_HEALING_KIT) &&
            ((sys.SaveStruct_gameplay.life < 100) || (temp))) {
            return 0;
        }

        /**
         * Don't allow the player to use any healing item (except for the Healing Kit)
         * if under the VAMP status
         */
        if ((self->item_use_settings_target_value != 0) &&
            (sys.SaveStruct_gameplay.player_status & PLAYER_FLAG_VAMP)) {
            return -1;
        }

        /**
         * If the selected item can cure any of the curable statuses, but the player
         * isn't under any of those statuses,then don't allow the item to be used
         */
        if ((curable_statuses) && (temp == FALSE)) {
            return -1;
        }

        /**
         * Don't use a healing item if the player already has max health
         */
        if ((sys.SaveStruct_gameplay.life >= 100) && (self->item_use_settings_target_value != 0)) {
            return -1;
        }
        /**
     * If the selected item is a Sun or Moon card...
     */
    } else if (self->item_effect & TIME_CARD) {
        /**
         * Don't allow using a card if we're already in the target hour o'clock
         */
        if ((self->item_use_settings_target_value == sys.SaveStruct_gameplay.hour) &&
            (sys.SaveStruct_gameplay.minute == 0) && (sys.SaveStruct_gameplay.seconds == 0)) {
            return -1;
        }
    } else {
        return -1;
    }

    /**
     * Allow the item to be used
     */
    return 0;
}
