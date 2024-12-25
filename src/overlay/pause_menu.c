#include "objects/menu/pause_menu.h"
#include "memory.h"
#include "sound.h"
#include "gfx/figure.h"
#include "system_work.h"

extern u16 item_descriptions[];

extern u16 options_text[];

extern u16 item_usage_text[];

extern u16 selection_arrow_character[];

extern ItemUseSettings item_use_settings_array[];

extern s32 sound_volume_decreased;

extern PauseMenuFuncs pauseMenu_functions[];

extern u32 character_portraits[];

extern u32 D_0F002FBC[];

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

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_init.s")

// TODO: Remove `NON_MATCHING` label when linking .rodata
#ifdef NON_MATCHING
void pauseMenu_createMainMenu(PauseMenu* self) {
    scroll_state* scroll;
    MfdsState* textbox;

    if (1) {}
    if (1) {}
    if ((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) {
        scroll = (*createScrollState)(self, self->scrolls_borders_light, self->scrolls_background_light, SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02, 0, -6.0f, -3.0f, 10.0f, 50.0f, NULL);
        scroll->width.x = 0.5f;
        scroll->width.y = 0.5f;
        scroll->width.z = 0.44999999f;
        scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
        scroll->flags |= SCROLL_STATE_FLAG_OPENING;
        self->main_menu_options_scroll = scroll;

        textbox = (*textbox_create)(self, self->scrolls_borders_light, MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP);
        self->options_textbox = textbox;
        if (textbox) {}
        textbox->palette = TEXT_COLOR_WHITE;
        (*textbox_setPos)(textbox, 95, 90, 1);
        (*textbox_setDimensions)(textbox, 5, 100, 0, 0);
        (*textbox_setScaleParameters)(textbox, 2, 2, 11.0f, 1.0f, 1.0f, FALSE, TRUE);
        (*textbox_setMessagePtr)(textbox, GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &options_text), NULL, 0);
        (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
    }
}
#else
#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createMainMenu.s")
#endif

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcMainMenu.s")

void pauseMenu_checkScrollObjExists(PauseMenu* self) {
    if ((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) {
        pauseMenu_createSoundMenuWork(self, 2, self->scrolls_borders_light, self->scrolls_background_light, 0);
        (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
    }
}

// TODO: Remove `NON_MATCHING` label when linking .rodata
#ifdef NON_MATCHING
void pauseMenu_calcItemList(PauseMenu* self) {
    MfdsState* textbox;
    Model* item_model;
    s32 temp[2];
    SoundMenuWork* sound_menu;
    s32 selected_item_ID_in_item_list;
    scroll_state* item_scroll;
    scroll_state* options_scroll;

    sound_menu = self->sound_menu;
    if (sound_menu != NULL) {
        selected_item_ID_in_item_list = sound_menu->selected_item_ID_in_item_list;
        if (selected_item_ID_in_item_list != ITEM_ID_NOTHING) {
            if (selected_item_ID_in_item_list == 0xFF) {
                (*object_curLevel_goToFunc)(self->header.current_function, &self->header.function_info_ID, PAUSE_MENU_CREATE_MAIN_MENU);
                return;
            }
            self->selected_item_ID = selected_item_ID_in_item_list;
            pauseMenu_createItemDescription(self);

            item_scroll = (*createScrollState)(self, self->scrolls_borders_light, self->scrolls_background_light, SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02, 0, -55.0f, 5.0f, 120.0f, 30.0f, NULL);
            item_scroll->width.x = 0.6f;
            item_scroll->width.y = 0.3f;
            item_scroll->width.z = 0.27f;
            item_scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
            item_scroll->flags |= SCROLL_STATE_FLAG_OPENING;
            self->item_model_scroll = item_scroll;

            options_scroll = (*createScrollState)(self, self->scrolls_borders_light, self->scrolls_background_light, SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02, 0, 45.0f, 5.0f, 120.0f, 30.0f, NULL);
            options_scroll->width.x = 0.69999999f;
            options_scroll->width.y = 0.3f;
            options_scroll->width.z = 0.27f;
            options_scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
            options_scroll->flags |= SCROLL_STATE_FLAG_OPENING;
            self->options_text_scroll = options_scroll;

            textbox = (*textbox_create)(self, self->scrolls_background_light, MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP);
            self->options_textbox = textbox;
            if (textbox) {}
            textbox->palette = TEXT_COLOR_BEIGE;
            (*textbox_setPos)(textbox, 165, 100, 1);
            (*textbox_setDimensions)(textbox, 3, 100, 0, 0);
            (*textbox_setMessagePtr)(textbox, GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &item_usage_text), NULL, 0);
            (*textbox_setScaleParameters)(textbox, 2, 2, 120.0f, 0.8f, 0.8f, TRUE, TRUE);

            textbox = (*textbox_create)(self, self->scrolls_background_light, MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED | MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP);
            self->selection_arrow_textbox = textbox;
            if (textbox) {}
            textbox->palette = TEXT_COLOR_RED;
            (*textbox_setPos)(textbox, 160, 100, 1);
            (*textbox_setDimensions)(textbox, 1, 16, 0, 0);
            (*textbox_setMessagePtr)(textbox, GET_UNMAPPED_ADDRESS(NI_OVL_PAUSE_MENU, &selection_arrow_character), NULL, 0);
            (*textbox_setScaleParameters)(textbox, 2, 2, 120.0f, 0.8f, 0.8f, TRUE, TRUE);

            self->outside_item_selected_menu = FALSE;

            self->selected_item_ID_in_item_list = sound_menu->selected_item_ID_in_item_list;
            item_model = (*createItemModel)(self->selected_item_ID_in_item_list, common_camera_HUD, "item");
            self->item_model = item_model;
            self->field_0x51 = FALSE;
            self->delay_before_being_able_to_select_option = 0;
            self->option_selection_inside_selected_item = 0;
            self->target_health = 0;
            self->target_hour = 0;
            item_model->position.x = -80.0f;
            item_model->position.y = -10.0f;

            (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
            return;
        }
    }
    self->selected_item_can_be_used = FALSE;
}
#else
#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcItemList.s")
#endif

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

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcQuitMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_updateDigitalClockDisplay.s")

// TODO: Remove `NON_MATCHING` label when linking .rodata
#ifdef NON_MATCHING
SoundMenuWork* pauseMenu_createSoundMenuWork(PauseMenu* self, u8 ptrs_array_index, modelLighting* arg2, modelLighting* arg3, s32 arg4) {
    SoundMenuWork* work;
    scroll_state* scroll;

    if (self != NULL) {
        (*allocStructInObjectEntryList)("work_work", self, sizeof(SoundMenuWork), ptrs_array_index);
        work = ((Object*) self)->alloc_data[ptrs_array_index];
        if (work != NULL) {
            work->field_0x01 = 1;
            work->field_0x05 = 0;
            work->field_0x06 = 0;
            work->field_0x02 = 0;
            work->selected_item_ID_in_item_list = ITEM_ID_NOTHING;

            scroll = (*createScrollState)(self, arg2, arg3, SCROLL_STATE_FLAG_WHITE_DOWELS | SCROLL_STATE_FLAG_02, 9, 0.0f, -30.0f, 90.0f, 30.0f, work);
            scroll->width.z = 0.6f;
            scroll->width.y = 0.6f;
            scroll->width.x = 1.5f;
            scroll->flags &= ~SCROLL_STATE_FLAG_CLOSING;
            scroll->flags |= SCROLL_STATE_FLAG_OPENING;
            work->scroll = scroll;
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
    return work;
}
#else
#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createSoundMenuWork.s")
#endif

// clang-format on

void func_0F001BF0() {}

// TODO: Remove `NON_MATCHING` label when linking .rodata
#ifdef NON_MATCHING
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
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createItemDescription.s")
#endif

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

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_checkIfItemCanBeUsed.s")

// clang-format on
