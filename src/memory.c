#include "c64.h"
#include <ultra64.h>

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_clear.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_copy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_writebackDCache.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/initHeaps.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80000D68_1968.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80000D74_1974.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_alloc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_allocWithAlignment.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_updateBlockMaxSize.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001008_1C08.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001080_1C80.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800010A0_1CA0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800010C8_1CC8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001110_1D10.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001148_1D48.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800011AC_1DAC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800011DC_1DDC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001228_1E28.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001260_1E60.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012C0_1EC0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012D8_1ED8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012F4_1EF4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001338_1F38.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_curLevel_goToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_prevLevel_goToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_nextLevel_goToNextFunc.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_curLevel_goToNextFuncAndClearTimer.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_curLevel_goToPrevFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_prevLevel_goToPrevFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_nextLevel_goToPrevFunc.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_curLevel_goToPrevFuncAndClearTimer.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_curLevel_goToFunc.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_curLevel_goToFuncInLevel.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_prevLevel_goToFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/module_nextLevel_goToFunc.s")
