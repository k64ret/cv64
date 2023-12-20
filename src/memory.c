#include "c64.h"
#include <ultra64.h>

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_clear.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_copy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_writebackDCache.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/initHeaps.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80000D68.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80000D74.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_alloc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_allocWithAlignment.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_updateBlockMaxSize.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001008.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001080.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800010A0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800010C8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001110.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001148.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800011AC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800011DC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001228.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001260.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012C0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012D8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012F4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001338.s")

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
