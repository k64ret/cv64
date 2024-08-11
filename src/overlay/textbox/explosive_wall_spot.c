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

void explosiveWallSpot_entrypoint(explosiveWallTextbox* self) {
    ENTER(self, explosiveWallSpot_functions);
}

void explosiveWallSpot_init(explosiveWallTextbox* self) {
    cv64_actor_settings_t* settings = self->settings;

    if (ptr_PlayerData != NULL) {
        self->position.x     = settings->position.x;
        self->position.y     = settings->position.y;
        self->position.z     = settings->position.z;
        self->trigger_size_X = settings->variable_2;
        self->trigger_size_Z = settings->variable_3;
        self->wall_type      = settings->variable_1;
        if (self->wall_type == WALL_TYPE_MAIN_MAP) {
            self->set_nitro_text_ID           = 0xE;
            self->set_mandragora_text_ID      = 0xF;
            self->default_description_text_ID = 2;
            self->item_already_set_text_ID    = 0x10;
            self->nitro_set_text_ID           = 0x11;
            self->mandragora_set_text_ID      = 0x12;
            self->ready_for_blasting_text_ID  = 0x13;
        }
        if (self->wall_type == WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP) {
            self->set_nitro_text_ID           = 0xC;
            self->set_mandragora_text_ID      = 0xD;
            self->default_description_text_ID = 0;
            self->item_already_set_text_ID    = 0xE;
            self->nitro_set_text_ID           = 0xF;
            self->mandragora_set_text_ID      = 0x10;
            self->ready_for_blasting_text_ID  = 0x11;
        }
        self->header.timer = 0;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void explosiveWallSpot_idle(explosiveWallTextbox* self) {
    if ((self->interacting_with_interactuable == TRUE) &&
        ((self->wall_type == WALL_TYPE_MAIN_MAP) &&
             !(CHECK_EVENT_FLAGS(
                 EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                 EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
             )) ||
         ((self->wall_type == WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP) &&
          !(CHECK_EVENT_FLAGS(
              EVENT_FLAG_ID_CASTLE_CENTER_3F,
              EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
          ))))) {
        sys.FREEZE_GAMEPLAY = TRUE;
        (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, TRUE);
        self->nitro_amount_until_max_capacity =
            (*item_getAmountUntilMaxCapacity)(ITEM_ID_MAGICAL_NITRO);
        self->mandragora_amount_until_max_capacity =
            (*item_getAmountUntilMaxCapacity)(ITEM_ID_MANDRAGORA);
        self->header.timer      = 0;
        self->state             = 0;
        self->textbox_is_active = FALSE;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

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
