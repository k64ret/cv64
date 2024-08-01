/**
 * @file mandragora_textbox.c
 *
 * Handles the textbox that grants the Mandragora item to the player.
 */

#include "objects/cutscene/mandragora_textbox.h"

// clang-format off

mandragoraTextbox_func_t mandragoraTextbox_functions[] = {
    mandragoraTextbox_init,
    mandragoraTextbox_idle,
    mandragoraTextbox_prepareMessage,
    mandragoraTextbox_selectOption,
    mandragoraTextbox_closeTextbox,
    mandragoraTextbox_destroy
};

// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_idle.s")

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_prepareMessage.s"            \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_selectOption.s"              \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_closeTextbox.s"              \
)

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/mandragora_textbox/mandragoraTextbox_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/mandragora_textbox/mandragoraIsPlacedInWall.s")
