/**
 * @file gameplay_menu_mgr_textbox.c
 *
 * This file contains code that operates with the common gameplay textbox
 * (aka the `gameplayMenuMgr` textbox, as it is created by said object).
 *
 * This textbox displays most of the messages seen during gameplay, including
 * item names, text spot messages, etc.
 */

#include "cv64.h"

extern u16 YOU_CANNOT_CARRY_MORE_ITEMS_TEXT[];

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/gameplayMenuMgr_getCommonTextboxIfClosed.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/gameplayMenuMgr_closeCommonTextbox.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/func_8013B608_BE7F8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/item_prepareTextbox.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/map_getMessageFromPool.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/gameplayMenuMgr_setMessageAndColorPalette.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/lensAreOpened.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/lensAreClosed.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/getGameplayMenuMgrTextboxObject.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/gameplay_menu_mgr_textbox/getGameplayMenuMgrTextboxObjectFromList.s")

// clang-format on
