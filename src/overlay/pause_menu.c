#include "objects/menu/pause_menu.h"
#include "memory.h"
#include "sound.h"
#include "gfx/figure.h"
#include "system_work.h"

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

void pauseMenu_destroy(PauseMenu* self) {
    if (((*objectList_findFirstObjectByID)(MENU_SCROLL) == NULL) && ((*Fade_IsFading)() == FALSE)) {
        if (sound_volume_decreased) {
            (*decreaseSoundVolume)(FALSE);
        }
        sys.background_color.integer = RGBA(0, 0, 0, 255);
        self->header.destroy(self);
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcQuitMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_updateDigitalClockDisplay.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createSoundMenuWork.s")

void func_0F001BF0() {}

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createItemDescription.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/getItemUseArrayEntry.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_updateClock.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_checkIfItemCanBeUsed.s")

// clang-format on
