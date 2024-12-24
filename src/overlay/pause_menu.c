#include "objects/menu/pause_menu.h"

extern PauseMenuFuncs pauseMenu_functions[];

void pauseMenu_entrypoint(PauseMenu* self) {
    ENTER(self, pauseMenu_functions);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_decreaseSoundVolume.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createMainMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcMainMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_checkScrollObjExists.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcItemList.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcItemSelectedMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_calcQuitMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_updateDigitalClockDisplay.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createSoundMenuWork.s")

void func_0F001BF0() {}

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_createItemDescription.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/getItemUseArrayEntry.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_updateClock.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/pause_menu/pauseMenu_checkIfItemCanBeUsed.s")

// clang-format on
