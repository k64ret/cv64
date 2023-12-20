#include "c64.h"
#include <ultra64.h>

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/gamestate_create.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/gamestate_change.s")

void func_80000534(void) {}

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/GameStateMgr_calc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/gamestate_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/setup_frame.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/end_frame.s")
