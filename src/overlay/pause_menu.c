/**
 * @file pause_menu.c
 *
 * This file contains the code that handles the Pause menu.
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

ItemUseSettings item_use_settings_array[] = {
    {ITEM_ID_HEALING_KIT, PLAYER_STATUS_TO_REMOVE(PLAYER_FLAG_POISON | PLAYER_FLAG_VAMP), 100},
    {ITEM_ID_ROAST_BEEF, PLAYER_STATUS_TO_REMOVE(0), 80},
    {ITEM_ID_ROAST_CHICKEN, PLAYER_STATUS_TO_REMOVE(0), 50},
    {ITEM_ID_PURIFYING, PLAYER_STATUS_TO_REMOVE(PLAYER_FLAG_VAMP), 0},
    {ITEM_ID_CURE_AMPOULE, PLAYER_STATUS_TO_REMOVE(PLAYER_FLAG_POISON), 0},
    {ITEM_ID_SUN_CARD, ITEM_IS_CARD, 6},
    {ITEM_ID_MOON_CARD, ITEM_IS_CARD, 18}
};

s32 sound_volume_decreased = FALSE;

PauseMenuFuncs pauseMenu_functions[] = {
    pauseMenu_decreaseSoundVolume,
    pauseMenu_init,
    pauseMenu_createMainMenu,
    pauseMenu_calcMainMenu,
    pauseMenu_checkScrollObjExists,
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
    s32 temp;
    MfdsState* textbox;
    Model* model;
    s32 temp2[2];
    gameplayMenuMgr* gameplay_menu_mgr;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        if (gameplay_menu_mgr->assets_file_buffer_end_ptr != NULL) {
            self->gameplay_menu_mgr = gameplay_menu_mgr;
        } else {
            return;
        }
    }
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

    temp                           = FIG_TYPE_HUD_ELEMENT;
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

    model                         = (*Model_createAndSetChild)(temp, common_camera_8009B444);
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
        self->main_menu_options_scroll = scroll;

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
    scroll_state* main_menu_options_scroll;
    MfdsState* options_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;
    Model* scroll_background_model;
    s32 textbox_option;

    options_textbox          = self->options_textbox;
    main_menu_options_scroll = self->main_menu_options_scroll;

    if (CONT_BTNS_PRESSED(CONT_0, CONT_B) &&
        (main_menu_options_scroll->flags & SCROLL_STATE_FLAG_OPENED)) {
        gameplay_menu_mgr =
            (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
        if (gameplay_menu_mgr != NULL) {
            gameplay_menu_mgr->menu_state |= EXIT_MENU;
        }
        (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
        options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
        self->main_menu_options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
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
        case PAUSE_MENU_ITEM:
            options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->main_menu_options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
            break;

        case PAUSE_MENU_OPTION:
            gameplay_menu_mgr =
                (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
            if (gameplay_menu_mgr != NULL) {
                gameplay_menu_mgr->menu_state |= ENTERING_OPTION;
            }
            (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
            options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->main_menu_options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*object_curLevel_goToFunc)(
                self->header.current_function, &self->header.function_info_ID, PAUSE_MENU_DESTROY
            );
            break;

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

        case PAUSE_MENU_BACK:
            gameplay_menu_mgr =
                (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
            if (gameplay_menu_mgr != NULL) {
                gameplay_menu_mgr->menu_state |= EXIT_MENU;
            }
            options_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->main_menu_options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
            (*object_curLevel_goToFunc)(
                self->header.current_function, &self->header.function_info_ID, PAUSE_MENU_DESTROY
            );
            break;
    }
}

void pauseMenu_checkScrollObjExists(PauseMenu* self) {
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
    s32 selected_item_ID_in_item_list;
    scroll_state* item_scroll;
    scroll_state* options_scroll;

    item_menu = self->item_menu;
    if (item_menu != NULL) {
        selected_item_ID_in_item_list = item_menu->selected_item_ID_in_item_list;
        if (selected_item_ID_in_item_list != ITEM_ID_NOTHING) {
            if (selected_item_ID_in_item_list == 0xFF) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    PAUSE_MENU_CREATE_MAIN_MENU
                );
                return;
            }
            self->selected_item_ID = selected_item_ID_in_item_list;
            pauseMenu_createItemDescription(self);

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

            self->selected_item_ID_in_item_list = item_menu->selected_item_ID_in_item_list;
            item_model =
                (*createItemModel)(self->selected_item_ID_in_item_list, common_camera_HUD, "item");
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

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcItemSelectedMenu.s")

// clang-format on

void pauseMenu_destroy(PauseMenu* self) {
    if (((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) && ((*Fade_IsFading)() == FALSE)) {
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
    ModelUnk68* temp_s0;
    miniScroll* mini_scroll;

    scroll_background_model = self->scroll_background_model;
    options_textbox         = self->options_textbox;
    temp_s0                 = &scroll_background_model->field_0x68;

    switch (temp_s0->field_0x00) {
        case 0:
            mini_scroll         = (*miniScroll_create)(self, self->scrolls_borders_light, 0, 0);
            temp_s0->field_0x0C = mini_scroll;
            (*miniScroll_setPosition)(temp_s0->field_0x0C, -6.0f, 26.0f, 100.0f);
            (*miniScroll_setWidth)(temp_s0->field_0x0C, 0.7f, 0.36f, 1.0f);
            (*miniScroll_setScrollingParams)(temp_s0->field_0x0C, 50.0f, 1);
            (*miniScroll_setState)(temp_s0->field_0x0C, MINISCROLL_STATE_OPEN);
            temp_s0->field_0x00++;
            break;

        case 1:
            temp_s0->field_0x08++;
            if (temp_s0->field_0x08 >= 5) {
                temp_s0->field_0x08 = 0;
                temp_s0->field_0x00++;
                break;
            }
            break;

        case 2:
            textbox = (*textbox_create)(
                self,
                self->scrolls_borders_light,
                MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED
            );
            temp_s0->field_0x10 = textbox;
            (*textbox_setDimensions)(textbox, 3, 128, 0, 0);
            (*textbox_setScaleParameters)(
                temp_s0->field_0x10, 2, 2, 101.0f, 0.8f, 0.8f, FALSE, FALSE
            );
            (*textbox_setMessagePtr)(
                temp_s0->field_0x10,
                GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &confirmation_text),
                NULL,
                0
            );
            (*textbox_setPos)(temp_s0->field_0x10, 104, 103, 0);
            temp_s0->field_0x00++;
            break;

        case 3:
            if ((*miniScroll_checkFlags)(temp_s0->field_0x0C, MINISCROLL_FLAG_OPENED)) {
                options_textbox->flags |= MINISCROLL_FLAG_CLOSED;
                temp_s0->field_0x00++;
                break;
            }
            break;

        case 4:
            if (temp_s0->field_0x10->textbox_option != TEXTBOX_OPTION_IDLE) {
                (*miniScroll_setState)(temp_s0->field_0x0C, MINISCROLL_STATE_CLOSE);
                temp_s0->field_0x10->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
                switch (temp_s0->field_0x10->textbox_option - 1) {
                    case 0:
                        temp_s0->field_0x00 = 5;
                        break;
                    case 1:
                        temp_s0->field_0x00 = 6;
                        break;
                }
            }
            break;

        case 5:
            scroll_background_model = scroll_background_model;
            gameplay_menu_mgr =
                (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
            if (gameplay_menu_mgr != NULL) {
                gameplay_menu_mgr->menu_state |= QUIT_GAME;
            }
            textbox = temp_s0->field_0x10;
            textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            self->main_menu_options_scroll->flags = SCROLL_STATE_FLAG_HIDE;
            (*Fade_SetSettings)(FADE_OUT, 15, 0, 0, 0);
            (*player_status_init)();
            temp_s0->field_0x04 = PAUSE_MENU_DESTROY;
            temp_s0->field_0x00 = 7;
            break;

        case 6:
            temp_s0->field_0x04 = PAUSE_MENU_CALC_MAIN_MENU;
            textbox             = (*textbox_create)(
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
            temp_s0->field_0x00 = 7;
            break;

        case 7:
            if ((*miniScroll_checkFlags)(temp_s0->field_0x0C, MINISCROLL_FLAG_CLOSED)) {
                (*miniScroll_editFlags)(temp_s0->field_0x0C, MINISCROLL_STATE_DESTROY, -1);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    temp_s0->field_0x04
                );
            }
            break;
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_updateDigitalClockDisplay.s")

// clang-format on

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
            work->current_page                  = 1;
            work->field_0x05                    = 0;
            work->number_of_pages_to_advance    = 0;
            work->highlighted_option            = 0;
            work->selected_item_ID_in_item_list = ITEM_ID_NOTHING;

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

void pauseMenu_createItemDescription(PauseMenu* self) {
    scroll_state* scroll;
    MfdsState* textbox;

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
    self->description_text_scroll = scroll;

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
            GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &item_descriptions), self->selected_item_ID - 1
        ),
        NULL,
        0
    );
    (*textbox_setScaleParameters)(textbox, 2, 2, 100.0f, 0.8f, 0.8f, TRUE, TRUE);
}

s32 getItemUseArrayEntry(s32 item_ID) {
    s32 entry_ID;

    for (entry_ID = 0; item_use_settings_array[entry_ID].item != ITEM_ID_NOTHING; entry_ID++) {
        if (item_ID == item_use_settings_array[entry_ID].item) {
            return entry_ID;
        }
    }
    return -1;
}

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
        if (self->target_hour == sys.SaveStruct_gameplay.hour) {
            (*play_sound)(STOP_SOUND(SD_CLOCK_TICKING));
            sys.SaveStruct_gameplay.minute  = 0;
            sys.SaveStruct_gameplay.seconds = 0;
            self->target_hour               = 0;
        }
    }
    pauseMenu_updateDigitalClockDisplay(self);
    (*textbox_setMessagePtr)(self->digital_clock_textbox, self->digital_clock_text, NULL, 0);
    self->digital_clock_textbox->flags |= MFDS_FLAG_UPDATE_STRING;
}

s32 pauseMenu_checkIfItemCanBeUsed(PauseMenu* self) {
    ItemUseSettings* temp_a0;
    s32 item_amount;
    s32 temp_a0_2;
    s32 temp_a2_2;

    item_amount = sys.SaveStruct_gameplay.items.array[self->selected_item_ID - 1];
    if (item_amount <= 0) {
        return -1;
    }
    self->item_use_settings_array_entry = getItemUseArrayEntry(self->selected_item_ID);
    self->player_status_to_remove =
        item_use_settings_array[self->item_use_settings_array_entry].player_status_to_remove;
    temp_a0_2 = self->item_use_settings_array_entry;
    self->item_use_settings_amount_to_fill =
        item_use_settings_array[self->item_use_settings_array_entry].amount_to_fill;
    if (temp_a0_2 < 0) {
        return -1;
    }
    if (self->player_status_to_remove & 0x10) {
        temp_a2_2 = self->player_status_to_remove & 0xE;
        temp_a0_2 = (temp_a2_2 << 0x19) & sys.SaveStruct_gameplay.player_status;
        if ((self->selected_item_ID == ITEM_ID_HEALING_KIT) &&
            ((sys.SaveStruct_gameplay.life < 100) || (temp_a0_2))) {
            return 0;
        }
        if ((self->item_use_settings_amount_to_fill != 0) &&
            (sys.SaveStruct_gameplay.player_status & PLAYER_FLAG_VAMP)) {
            return -1;
        }
        if ((temp_a2_2) && (temp_a0_2 == 0)) {
            return -1;
        }
        if ((sys.SaveStruct_gameplay.life >= 100) &&
            (self->item_use_settings_amount_to_fill != 0)) {
            return -1;
        }
    } else if (self->player_status_to_remove & 1) {
        if ((self->item_use_settings_amount_to_fill == sys.SaveStruct_gameplay.hour) &&
            (sys.SaveStruct_gameplay.minute == 0) && (sys.SaveStruct_gameplay.seconds == 0)) {
            return -1;
        }
    } else {
        return -1;
    }
    return 0;
}
