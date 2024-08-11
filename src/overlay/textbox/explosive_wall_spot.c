/**
 * @file explosive_wall_spot.c
 *
 * Handles the textbox associated to the spots in front of the breakable walls in Castle Center
 * where the player has to drop the Magical Nitro and Mandragora.
 */

#include "objects/cutscene/explosive_wall_spot.h"
#include "system_work.h"

// clang-format off

explosiveWallTextbox_func_t explosiveWallSpot_functions[] = {
    explosiveWallSpot_init,
    explosiveWallSpot_idle,
    explosiveWallSpot_determineMessage,
    explosiveWallSpot_setItemText_prepareMessage,
    explosiveWallSpot_setItemText_idle,
    explosiveWallSpot_setItemText_determineNextTextbox,
    explosiveWallSpot_setItemText_close,
    explosiveWallSpot_readyForBlasting,
    explosiveWallSpot_nitroIsSet,
    explosiveWallSpot_mandragoraIsSet,
    explosiveWallSpot_defaultDescription,
    explosiveWallSpot_itemAlreadySet,
    explosiveWallSpot_destroy
};

// clang-format on

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
