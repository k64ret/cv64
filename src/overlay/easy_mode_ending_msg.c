/**
 * File: easy_mode_ending_msg.c
 * Description: Displays the ending message when you beat Easy Mode
 * Associated modules: 0x2140
 *
 * osMapTLB'd? = Yes
 * Entrypoint address = 0x0F000000
 * Associated files ptr = 0x800963C0
 * Associated files:
 *   0xBB (Overlay)
 */

#include "objects/menu/easy_mode_ending_msg.h"
#include "sound.h"

void cv64_ovl_easymode_entrypoint(cv64_ovl_easyending_t* self) {
    ENTER(self, cv64_ovl_easyending_funcs);
}

// Initializes the textbox
// https://decomp.me/scratch/Gr6E6
void cv64_ovl_easyending_init(cv64_ovl_easyending_t* self) {
    mfds_state* new_textbox;
    s32 text_ptr;

    // Sound ID "10" is silent in the final game
    (*play_sound)(10);
    // Create textbox and initialize variables
    new_textbox = (*textbox_create)(self, common_cameras_array.HUD,
                                    (OPEN_TEXTBOX | FAST_TEXT_TRANSITION));
    self->ending_textbox = new_textbox;
    (*textbox_setPos)(new_textbox, 30, 110, 1);
    (*textbox_setDimensions)(new_textbox, 6, 250, 0, 0);
    new_textbox->color_palette = 0;
    new_textbox->display_time = 0;
    /*
     * Get the offset within the overlay where the text is located.
     * Don't grab the most significant byte (& 0xFFFFFF). self removes the
     * "0x0F" part from the address.
     */
    text_ptr =
        (s32) (*text_getMessageFromPool)(cv64_ovl_easyending_msg, 0) & 0xFFFFFF;
    (*textbox_setMessagePtr)(new_textbox,
                             (s32) endingMessage_fileBuffer + text_ptr, 0, 0);
    (*textbox_8012cda4)(new_textbox, 0x40035, 30);
    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function,
                                                 &self->header.functionInfo_ID);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/easy_mode_ending_msg/cv64_ovl_easyending_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/easy_mode_ending_msg/cv64_ovl_easyending_destroy.s")

// clang-format on
