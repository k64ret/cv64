/**
 * @file nitro_disposal_textbox.c
 *
 * Handles the textbox that for the Magical Nitro disposal spot.
 */

#include "objects/cutscene/nitro_disposal_textbox.h"

#pragma GLOBAL_ASM(                                                                                 \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_entrypoint.s" \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_init.s"      \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_idle.s"      \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_prep_msg.s"  \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_yes_no.s"    \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_close.s"     \
)

#pragma GLOBAL_ASM(                                                                                \
    "../asm/nonmatchings/overlay/textbox/nitro_disposal/cv64_ovl_nitrodisposaltextbox_destroy.s"   \
)
