#include "cv64.h"

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_main.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_createCutscene.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_setClippingAndScissoring.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_stopCutscene.s")

// clang-format on
