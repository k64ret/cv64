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

#pragma GLOBAL_ASM(                                                            \
    "../asm/nonmatchings/module/moduleList_findFirstModuleByID.s")

#pragma GLOBAL_ASM(                                                            \
    "../asm/nonmatchings/module/module_findModuleBetweenIDRange.s")

#pragma GLOBAL_ASM(                                                            \
    "../asm/nonmatchings/module/moduleList_findModuleBetweenRange.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_findModuleByIDAndType.s")

#pragma GLOBAL_ASM(                                                            \
    "../asm/nonmatchings/module/moduleList_findModuleByIDAndType.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001BE4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001CA0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001DD4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80001EB4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/findNextMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/findFirstMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_8000211C.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_allocEntryInList.s")

#pragma GLOBAL_ASM(                                                            \
    "../asm/nonmatchings/module/module_allocEntryInListAndClear.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80002264.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_800022BC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/GameStateMgr_execute.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_executeChildModule.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/module_execute.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_80002570.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_800026D8.s")

#pragma GLOBAL_ASM(                                                            \
    "../asm/nonmatchings/module/module_destroyChildrenAndModelInfo.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/GameStateMgr_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_800027BC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/module/func_8000287C.s")
