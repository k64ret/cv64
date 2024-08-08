/**
 * @file nitro_disposal.c
 *
 * Handles the textbox that for the Magical Nitro disposal spot.
 */

#include "objects/cutscene/nitro_disposal_textbox.h"
#include "system_work.h"

// clang-format off

cv64_ovl_nitrodisposaltextbox_func_t cv64_ovl_nitrodisposaltextbox_funcs[] = {
    cv64_ovl_nitrodisposaltextbox_init,
    cv64_ovl_nitrodisposaltextbox_idle,
    cv64_ovl_nitrodisposaltextbox_prep_msg,
    cv64_ovl_nitrodisposaltextbox_yes_no,
    cv64_ovl_nitrodisposaltextbox_close,
    cv64_ovl_nitrodisposaltextbox_destroy
};

// clang-format on

void cv64_ovl_nitrodisposaltextbox_entrypoint(cv64_ovl_nitrodisposaltextbox_t* self) {
    ENTER(self, cv64_ovl_nitrodisposaltextbox_funcs);
}

void cv64_ovl_nitrodisposaltextbox_init(cv64_ovl_nitrodisposaltextbox_t* self) {
    cv64_actor_settings_t* settings = self->settings;

    if (ptr_PlayerData == NULL)
        return;

    self->position.x     = settings->position.x;
    self->position.y     = settings->position.y;
    self->position.z     = settings->position.z;
    self->trigger_size_X = settings->variable_2;
    self->trigger_size_Z = settings->variable_3;
    switch (settings->variable_1) {
        case 0:
            self->has_nitro_text_ID = 7;
            self->no_nitro_text_ID  = 8;
            break;
        case 1:
            self->has_nitro_text_ID = 2;
            self->no_nitro_text_ID  = 3;
            break;
        case 2:
            self->has_nitro_text_ID = 3;
            self->no_nitro_text_ID  = 4;
            break;
    }
    self->header.timer = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrodisposaltextbox_idle(cv64_ovl_nitrodisposaltextbox_t* self) {
    if (self->interacting_with_interactuable != TRUE)
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

void cv64_ovl_nitrodisposaltextbox_prep_msg(cv64_ovl_nitrodisposaltextbox_t* self) {
    mfds_state* message;

    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        ) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        self->text_ID = self->no_nitro_text_ID;
    } else if (self->nitro_amount_until_max_capacity != 0) {
        self->text_ID = self->no_nitro_text_ID;
    } else {
        self->text_ID = self->has_nitro_text_ID;
    }

    message = (*map_getMessageFromPool)(self->text_ID, 0);
    if (message == NULL)
        return;

    self->message_textbox   = message;
    self->header.timer      = 0;
    self->textbox_is_active = FALSE;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrodisposaltextbox_yes_no(cv64_ovl_nitrodisposaltextbox_t* self) {
    mfds_state* textbox = self->message_textbox;

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

void cv64_ovl_nitrodisposaltextbox_close(cv64_ovl_nitrodisposaltextbox_t* self) {
    self->text_ID = 0;

    if (!(*lensAreClosed)())
        return;

    self->header.timer                   = 0;
    self->textbox_is_active              = FALSE;
    self->interacting_with_interactuable = FALSE;
    sys.FREEZE_GAMEPLAY                  = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, NITRO_DISPOSAL_TEXTBOX_IDLE
    );
}

void cv64_ovl_nitrodisposaltextbox_destroy(cv64_ovl_nitrodisposaltextbox_t* self) {
    self->header.destroy(self);
}
