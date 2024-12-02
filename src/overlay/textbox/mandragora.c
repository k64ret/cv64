/**
 * @file mandragora.c
 *
 * Handles the textbox that grants the Mandragora item to the player.
 */

#include "objects/cutscene/mandragora_textbox.h"
#include "objects/menu/gameplayMenuMgr.h"
#include "system_work.h"

// clang-format off

cv64_ovl_mandragoratxt_func_t cv64_ovl_mandragoratxt_funcs[] = {
    cv64_ovl_mandragoratxt_init,
    cv64_ovl_mandragoratxt_idle,
    cv64_ovl_mandragoratxt_prepare_msg,
    cv64_ovl_mandragoratxt_yes_no,
    cv64_ovl_mandragoratxt_close,
    cv64_ovl_mandragoratxt_destroy
};

// clang-format on

static s32 cannot_collect_mandragora(void);

void cv64_ovl_mandragoratxt_entrypoint(cv64_ovl_mandragoratxt_t* self) {
    ENTER(self, cv64_ovl_mandragoratxt_funcs);
}

void cv64_ovl_mandragoratxt_init(cv64_ovl_mandragoratxt_t* self) {
    ActorConfig* settings = self->settings;

    if (ptr_PlayerData == NULL)
        return;

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

void cv64_ovl_mandragoratxt_idle(cv64_ovl_mandragoratxt_t* self) {
    int temp[2];

    if (self->interacting_with_interactable != TRUE)
        return;

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

void cv64_ovl_mandragoratxt_prepare_msg(cv64_ovl_mandragoratxt_t* self) {
    MfdsState* message;

    // Both walls are blown up
    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        ) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        self->text_ID = CASTLE_CENTER_MAIN_MANDRAGORA_INFO;
        // Mandragora is not on the inventory
    } else if (self->mandragora_amount_until_max_capacity != 0) {
        // Nitro is not on the inventory
        if (self->nitro_amount_until_max_capacity != 0) {
            // clang-format off
            self->text_ID = cannot_collect_mandragora()
                ? CASTLE_CENTER_MAIN_MANDRAGORA_INFO
                : CASTLE_CENTER_MAIN_TAKE_MANDRAGORA;
            // clang-format on
            // Try getting Mandragora when Nitro is already on the inventory
        } else {
            self->text_ID = CASTLE_CENTER_TRY_HAVING_MANDRAGORA_AND_NITRO_SAME_TIME;
        }
        // Already have Mandragora on the inventory
    } else {
        self->text_ID = CASTLE_CENTER_MAIN_MANDRAGORA_INFO;
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

void cv64_ovl_mandragoratxt_yes_no(cv64_ovl_mandragoratxt_t* self) {
    MfdsState* textbox = self->message_textbox;

    if (self->text_ID == CASTLE_CENTER_MAIN_TAKE_MANDRAGORA) {
        switch (textbox->textbox_option) {
            case TEXTBOX_OPTION_IDLE:
                return;
            case TEXTBOX_OPTION_YES:
                self->text_ID = CASTLE_CENTER_MAIN_OBTAINED_MANDRAGORA;
                (*item_addAmountToInventory)(ITEM_ID_MANDRAGORA, 1);
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

void cv64_ovl_mandragoratxt_close(cv64_ovl_mandragoratxt_t* self) {
    MfdsState* message_textbox;

    if (self->text_ID == CASTLE_CENTER_MAIN_OBTAINED_MANDRAGORA) {
        message_textbox = (*gameplayCommonTextbox_getMapMessage)(self->text_ID, 0);
        if (message_textbox == NULL)
            return;

        self->message_textbox = message_textbox;
    }

    self->text_ID = 0;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, MANDRAGORA_TEXTBOX_IDLE
    );
}

void cv64_ovl_mandragoratxt_destroy(cv64_ovl_mandragoratxt_t* self) {
    self->header.destroy(self);
}

s32 cannot_collect_mandragora(void) {
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
