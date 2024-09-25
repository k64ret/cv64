#include "objects/cutscene/demo60.h"

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Init.s")

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_CreateCutsceneCamera.s"             \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_GetPlayerModelAndSetBorders.s"      \
)

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Destroy.s")

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_PlayPlayerBlessingAnim.s"           \
)
