#include "c64.h"
#include <ultra64.h>

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_isValid.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/clearAllModules.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_allocate.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/updateModuleListFreeSlot.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_create.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_createAndSetChild.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_findFirstModuleByID.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/module/moduleList_findFirstModuleByID.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_findModuleBetweenIDRange.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/module/moduleList_findModuleBetweenRange.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_findModuleByIDAndType.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/module/moduleList_findModuleByIDAndType.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001BE4_27E4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001CA0_28A0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001DD4_29D4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001EB4_2AB4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/findNextMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/findFirstMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_8000211C_2D1C.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_allocEntryInList.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_allocEntryInListAndClear.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80002264_2E64.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_800022BC_2EBC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/GameStateMgr_execute.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_executeChildModule.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_execute.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80002570_3170.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_800026D8_32D8.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_destroyChildrenAndModelInfo.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/module/GameStateMgr_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_800027BC_33BC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_8000287C_347C.s")
