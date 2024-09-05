/**
 * @file controller_pak.c
 *
 * This file contains functions used to wrap functionality with the controller pak,
 * used for saving the game in the western versions of the game.
 */

#include "cv64.h"

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_getInsertedStatus.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_initAllPaks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_initPak.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_allocateFile.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_deleteFile.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_findFile.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_getFileState.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_getNumFiles.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_getFreeBlocks.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_IsPlug.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_readFile.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_writeFile.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_checkRumblePak.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_checkInsertedStatus.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_8001aaa8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_8001ab18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/controller_pak/contPak_repairID.s")
