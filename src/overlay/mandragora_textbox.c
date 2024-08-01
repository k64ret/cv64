/**
 * @file mandragora_textbox.c
 *
 * Handles the textbox that grants the Mandragora item to the player.
 */

#include "objects/cutscene/mandragora_textbox.h"
#include "system_work.h"

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

void mandragoraTextbox_entrypoint(mandragoraTextbox* self) {
    ENTER(self, mandragoraTextbox_functions);
}

void mandragoraTextbox_init(mandragoraTextbox* self) {
    cv64_actor_settings_t* settings = self->settings;

    if (ptr_PlayerData != NULL) {
        self->position.x     = settings->position.x;
        self->position.y     = settings->position.y;
        self->position.z     = settings->position.z;
        self->trigger_size_X = settings->variable_2;
        self->trigger_size_Z = settings->variable_3;
        self->header.timer   = 0;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void mandragoraTextbox_idle(mandragoraTextbox* self) {
    int temp[2];

    if (self->interacting_with_interactuable == TRUE) {
        sys.FREEZE_GAMEPLAY = TRUE;
        (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, TRUE);
        self->nitro_amount_until_max_capacity =
            (*item_getAmountUntilMaxCapacity)(ITEM_ID_MAGICAL_NITRO);
        self->mandragora_amount_until_max_capacity =
            (*item_getAmountUntilMaxCapacity)(ITEM_ID_MANDRAGORA);
        self->text_ID = 0;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void mandragoraTextbox_prepareMessage(mandragoraTextbox* self) {
    mfds_state* message;

    // Both walls are blown up
    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        ) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        self->text_ID = CASTLE_CENTER_MANDRAGORA_INFO;
        // Mandragora is not on the inventory
    } else if (self->mandragora_amount_until_max_capacity != 0) {
        // Nitro is not on the inventory
        if (self->nitro_amount_until_max_capacity != 0) {
            if (shouldNotGiveMandragora()) {
                self->text_ID = CASTLE_CENTER_MANDRAGORA_INFO;
            } else {
                self->text_ID = CASTLE_CENTER_TAKE_MANDRAGORA;
            }
            // Try getting Mandragora when Nitro is already on the inventory
        } else {
            self->text_ID = CASTLE_CENTER_TRY_HAVING_MANDRAGORA_AND_NITRO_SAME_TIME;
        }
        // Already have Mandragora on the inventory
    } else {
        self->text_ID = CASTLE_CENTER_MANDRAGORA_INFO;
    }
    message = (*map_getMessageFromPool)(self->text_ID, 0);
    if (message != NULL) {
        self->message_textbox   = message;
        self->header.timer      = 0;
        self->textbox_is_active = FALSE;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void mandragoraTextbox_selectOption(mandragoraTextbox* self) {
    mfds_state* textbox = self->message_textbox;

    if (self->text_ID == CASTLE_CENTER_TAKE_MANDRAGORA) {
        switch (textbox->textbox_option) {
            case 0:
                return;
            // Yes
            case 1:
                self->text_ID = CASTLE_CENTER_OBTAINED_MANDRAGORA;
                (*item_addAmountToInventory)(ITEM_ID_MANDRAGORA, 1);
                // Fallthrough
            // No
            case 2:
            default:
                break;
        }
    }
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void mandragoraTextbox_closeTextbox(mandragoraTextbox* self) {
    mfds_state* message_textbox;

    if (self->text_ID == CASTLE_CENTER_OBTAINED_MANDRAGORA) {
        message_textbox = (*map_getMessageFromPool)(self->text_ID, 0);
        if (message_textbox != NULL) {
            self->message_textbox = message_textbox;
        } else {
            return;
        }
    }
    self->text_ID = 0;
    if ((*lensAreClosed)()) {
        self->header.timer                   = 0;
        self->textbox_is_active              = FALSE;
        self->interacting_with_interactuable = FALSE;
        sys.FREEZE_GAMEPLAY                  = FALSE;
        (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, MANDRAGORA_TEXTBOX_IDLE
        );
    }
}

void mandragoraTextbox_destroy(mandragoraTextbox* self) {
    self->header.destroy(self);
}

s32 shouldNotGiveMandragora() {
    // There's Mandragora at both walls
    if ((CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN, EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL
        )) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F, EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL
        )) {
        return TRUE;
    }

    // The lower wall has a Mandragora and the upper wall is blown up
    if ((CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN, EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL
        )) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        return TRUE;
    }

    // The upper wall has a Mandragora and the lower wall is blown up
    if ((CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F, EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL
        )) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        )) {
        return TRUE;
    }
    return FALSE;
}
