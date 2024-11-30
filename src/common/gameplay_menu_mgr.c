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
//const char gameplayMenuMgr_unusedString1[] = "文字侮ｦシステムを起動しました。(%p)\n";
/**
 * etc_ctrl : No. %02d Unknown screen request.\nEntering standby mode.
 */
//const char gameplayMenuMgr_unusedString2[] = "etc_ctrl : No. %02d 不明な画面要求がありました。\n待機モードに移行します。";
//const char gameplayMenuMgr_unusedString3[] = "etc_ctrl : alloc trunc size = 0x%08x!!\n";
//const char gameplayMenuMgr_unusedString4[] = "etc_ctrl : Call Status!!\n";
//const char gameplayMenuMgr_unusedString5[] = "etc_ctrl : Call Item Shop!!\n";
//const char gameplayMenuMgr_unusedString6[] = "etc_ctrl : Call Gameover!!\n";
//const char gameplayMenuMgr_unusedString7[] = "etc_ctrl : Return to GAME!!\n";
//const char gameplayMenuMgr_unusedString8[] = "etc_ctrl : Call Title!!\n";

u32 gameplayMenuMgr_wait;

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_initMainStructs.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_initHUDParams.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_outsideMenuLoop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_initMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_insideMenuLoop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/gameplayMenuMgr_exitMenu.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr/moveSelectionCursor.s")
