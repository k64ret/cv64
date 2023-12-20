#include "cv64.h"
#include <ultra64.h>

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_isValid.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/clearAllObjects.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_allocate.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/updateObjectListFreeSlot.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_create.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_createAndSetChild.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_findFirstObjectByID.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/objectList_findFirstObjectByID.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_findObjectBetweenIDRange.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/objectList_findObjectBetweenRange.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_findObjectByIDAndType.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/objectList_findObjectByIDAndType.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001BE4_27E4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001CA0_28A0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001DD4_29D4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001EB4_2AB4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/findNextMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/findFirstMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_8000211C_2D1C.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_allocEntryInList.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_allocEntryInListAndClear.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80002264_2E64.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800022BC_2EBC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/GameStateMgr_execute.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_executeChildObject.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_execute.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80002570_3170.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800026D8_32D8.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_destroyChildrenAndModelInfo.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/GameStateMgr_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800027BC_33BC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_8000287C_347C.s")
