#include "cv64.h"
#include "debug.h"

void func_80019BC0_1A7C0(void) {}

void func_80019BC8_1A7C8(s32 arg0) {}

// Used in `func_80066400`. Maybe a stubbed debug print function
void func_80019BD0_1A7D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {}

// Maybe another stubbed debug print function, based on the number of arguments
void func_80019BE4_1A7E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {}

void func_80019BF8_1A7F8(void) {}

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_80019C00.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_setSizeDivisor.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_update.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_render.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_renderDivisions.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_renderBar.s")
