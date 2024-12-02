/**
 * @file nitro_disposal.c
 *
 * Handles the textbox associated to the Magical Nitro disposal spots.
 */

#include "objects/cutscene/nitro_disposal_textbox.h"
#include "objects/menu/gameplayMenuMgr.h"
#include "system_work.h"

// clang-format off

cv64_ovl_nitrodisposaltxt_func_t cv64_ovl_nitrodisposaltxt_funcs[] = {
    cv64_ovl_nitrodisposaltxt_init,
    cv64_ovl_nitrodisposaltxt_idle,
    cv64_ovl_nitrodisposaltxt_prepare_msg,
    cv64_ovl_nitrodisposaltxt_yes_no,
    cv64_ovl_nitrodisposaltxt_close,
    cv64_ovl_nitrodisposaltxt_destroy
};

// clang-format on

void cv64_ovl_nitrodisposaltxt_entrypoint(cv64_ovl_nitrodisposaltxt_t* self) {
    ENTER(self, cv64_ovl_nitrodisposaltxt_funcs);
}

void cv64_ovl_nitrodisposaltxt_init(cv64_ovl_nitrodisposaltxt_t* self) {
    ActorConfig* settings = self->settings;

    if (ptr_PlayerData == NULL)
        return;

    self->position.x     = settings->position.x;
    self->position.y     = settings->position.y;
    self->position.z     = settings->position.z;
    self->trigger_size_X = settings->variable_2;
    self->trigger_size_Z = settings->variable_3;
    switch (settings->variable_1) {
        case NITRO_DISPOSAL_TEXTBOX_BOTTOM_ELEVATOR:
            self->has_nitro_text_ID = CASTLE_CENTER_1F_DISPOSAL_WITH_NITRO;
            self->no_nitro_text_ID  = CASTLE_CENTER_1F_DISPOSAL_WITHOUT_NITRO;
            break;
        case NITRO_DISPOSAL_TEXTBOX_GEARS:
            self->has_nitro_text_ID = CASTLE_CENTER_2F_DISPOSAL_WITH_NITRO;
            self->no_nitro_text_ID  = CASTLE_CENTER_2F_DISPOSAL_WITHOUT_NITRO;
            break;
        case NITRO_DISPOSAL_TEXTBOX_FRIENDLY_LIZARD_MAN:
            self->has_nitro_text_ID = CASTLE_CENTER_3F_DISPOSAL_WITH_NITRO;
            self->no_nitro_text_ID  = CASTLE_CENTER_3F_DISPOSAL_WITHOUT_NITRO;
            break;
    }
    self->header.timer = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrodisposaltxt_idle(cv64_ovl_nitrodisposaltxt_t* self) {
    if (self->interacting_with_interactable != TRUE)
        return;

    sys.FREEZE_GAMEPLAY = TRUE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, TRUE);
    self->nitro_amount_until_max_capacity =
        (*item_getAmountUntilMaxCapacity)(ITEM_ID_MAGICAL_NITRO);
    self->text_ID = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrodisposaltxt_prepare_msg(cv64_ovl_nitrodisposaltxt_t* self) {
    MfdsState* message;

    // Both walls have been blown up already
    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        ) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        self->text_ID = self->no_nitro_text_ID;
        // Nitro is not on the inventory
    } else if (self->nitro_amount_until_max_capacity != 0) {
        self->text_ID = self->no_nitro_text_ID;
        // Nitro is on the inventory
    } else {
        self->text_ID = self->has_nitro_text_ID;
    }

    message = (*gameplayCommonTextbox_getMapMessage)(self->text_ID, 0);
    if (message == NULL)
        return;

    self->message_textbox   = message;
    self->header.timer      = 0;
    self->textbox_is_active = FALSE;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrodisposaltxt_yes_no(cv64_ovl_nitrodisposaltxt_t* self) {
    MfdsState* textbox = self->message_textbox;

    if (self->has_nitro_text_ID == self->text_ID) {
        switch (textbox->textbox_option) {
            case TEXTBOX_OPTION_IDLE:
                return;
            case TEXTBOX_OPTION_YES:
                (*item_removeAmountFromInventory)(ITEM_ID_MAGICAL_NITRO, 1);
                BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_CAN_EXPLODE_ON_JUMPING);
                // Fallthrough
            case TEXTBOX_OPTION_NO:
            default:
                break;
        }
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrodisposaltxt_close(cv64_ovl_nitrodisposaltxt_t* self) {
    self->text_ID = 0;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, NITRO_DISPOSAL_TEXTBOX_IDLE
    );
}

void cv64_ovl_nitrodisposaltxt_destroy(cv64_ovl_nitrodisposaltxt_t* self) {
    self->header.destroy(self);
}
