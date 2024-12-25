#include "objects/menu/pause_menu.h"
#include "memory.h"
#include "sound.h"
#include "gfx/figure.h"
#include "system_work.h"

extern u16 item_descriptions[];

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

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createMainMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcMainMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_checkScrollObjExists.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcItemList.s")

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

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createSoundMenuWork.s")

// clang-format on

void func_0F001BF0() {}

// TODO: Remove when linking .rodata
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
    scroll->flags &= ~0x80;
    scroll->flags |= 0x40;
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
