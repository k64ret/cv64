#include "cv64.h"

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_entrypoint.s"          \
)

#pragma GLOBAL_ASM("asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_init.s")

#pragma GLOBAL_ASM("asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_idle.s")

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_determineMessage.s"    \
)

#pragma GLOBAL_ASM(                                                                                       \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_setItemText_prepareMessage.s" \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_setItemText_idle.s"    \
)

#pragma GLOBAL_ASM(                                                                                             \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_setItemText_determineNextTextbox.s" \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_setItemText_close.s"   \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_readyForBlasting.s"    \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_nitroIsSet.s"          \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_mandragoraIsSet.s"     \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_defaultDescription.s"  \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_itemAlreadySet.s"      \
)

#pragma GLOBAL_ASM(                                                                                \
    "asm/nonmatchings/overlay/textbox/explosive_wall_spot/explosiveWallSpot_destroy.s"             \
)
