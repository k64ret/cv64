#include "cv64.h"

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_Entrypoint.s"         \
)

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_Init.s")

#pragma GLOBAL_ASM(                                                                                  \
    "../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_CreateCutsceneCamera.s" \
)

#pragma GLOBAL_ASM(                                                                                         \
    "../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_GetPlayerModelAndSetBorders.s" \
)

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_Loop.s")

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_Destroy.s"            \
)

#pragma GLOBAL_ASM(                                                                                    \
    "../asm/nonmatchings/overlay/cutscene/cutscene_60/cutscene_60/Cutscene60_PlayPlayerBlessingAnim.s" \
)
