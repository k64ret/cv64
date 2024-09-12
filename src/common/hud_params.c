/**
 * @file hud_params.c
 *
 * This file has additional code used by the `HUD` object, all of which
 * handles different operations with the different health bars.
 */

#include "objects/menu/HUD.h"

#pragma GLOBAL_ASM("../asm/nonmatchings/common/hud_params/HUDParams_initBossBar.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/hud_params/HUDParams_removeBossCurrentLife.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/hud_params/HUDParams_increaseDamage.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/hud_params/HUDParams_resetPlayerLifeAndFlags.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/hud_params/HUDParams_fillPlayerHealth.s")
