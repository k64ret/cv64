#include "objects/cutscene/demo60.h"

// clang-format off

extern Demo60Func Demo60_functions[];

// clang-format on

void Demo60_Entrypoint(Demo60* self) {
    ENTER(self, Demo60_functions);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_CreateCutsceneCamera.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_GetPlayerModelAndSetBorders.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_PlayPlayerBlessingAnim.s")

// clang-format on
