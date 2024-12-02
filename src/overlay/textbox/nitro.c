/**
 * @file nitro.c
 *
 * Handles the textbox that grants the Magical Nitro item to the player.
 */

#include "objects/cutscene/nitro_textbox.h"
#include "objects/menu/gameplayMenuMgr.h"
#include "system_work.h"

// clang-format off

cv64_ovl_nitrotxt_func_t cv64_ovl_nitrotxt_funcs[] = {
    cv64_ovl_nitrotxt_init,
    cv64_ovl_nitrotxt_idle,
    cv64_ovl_nitrotxt_prepare_msg,
    cv64_ovl_nitrotxt_yes_no,
    cv64_ovl_nitrotxt_close,
    cv64_ovl_nitrotxt_destroy
};

// clang-format on

const char cv64_ovl_nitrotxt_unused_str[] = "OK\n";

static s32 cannot_collect_nitro(void);

void cv64_ovl_nitrotxt_entrypoint(cv64_ovl_nitrotxt_t* self) {
    ENTER(self, cv64_ovl_nitrotxt_funcs);
}

void cv64_ovl_nitrotxt_init(cv64_ovl_nitrotxt_t* self) {
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

void cv64_ovl_nitrotxt_idle(cv64_ovl_nitrotxt_t* self) {
    int temp[2];

    if (self->interacting_with_interactable != TRUE)
        return;

    sys.FREEZE_GAMEPLAY = TRUE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, TRUE);
    self->mandragora_amount_until_max_capacity =
        (*item_getAmountUntilMaxCapacity)(ITEM_ID_MANDRAGORA);
    self->nitro_amount_until_max_capacity =
        (*item_getAmountUntilMaxCapacity)(ITEM_ID_MAGICAL_NITRO);
    self->message_display_time = 0;

    // Both walls are blown up
    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        ) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        self->text_ID = CASTLE_CENTER_3F_NITRO_INFO;
        // Nitro is not on the inventory
    } else if (self->nitro_amount_until_max_capacity != 0) {
        // Mandragora is not on the inventory
        if (self->mandragora_amount_until_max_capacity != 0) {
            if (cannot_collect_nitro()) {
                self->text_ID = CASTLE_CENTER_3F_NITRO_INFO;
            } else {
                self->text_ID              = CASTLE_CENTER_3F_TAKE_NITRO;
                self->message_display_time = 0;
            }
            // Try getting Nitro when Mandragora is already on the inventory
        } else {
            self->text_ID = CASTLE_CENTER_TRY_HAVING_MANDRAGORA_AND_NITRO_SAME_TIME;
        }
        // Already have Nitro on the inventory
    } else {
        self->text_ID = CASTLE_CENTER_3F_NITRO_INFO;
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrotxt_prepare_msg(cv64_ovl_nitrotxt_t* self) {
    MfdsState* message;

    message = (*gameplayCommonTextbox_getMapMessage)(self->text_ID, self->message_display_time);
    if (message == NULL)
        return;

    self->message_textbox   = message;
    self->header.timer      = 0;
    self->textbox_is_active = FALSE;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_nitrotxt_yes_no(cv64_ovl_nitrotxt_t* self) {
    MfdsState* textbox = self->message_textbox;

    if (self->text_ID == CASTLE_CENTER_3F_TAKE_NITRO) {
        switch (textbox->textbox_option) {
            case TEXTBOX_OPTION_IDLE:
                return;
            case TEXTBOX_OPTION_YES:
                self->text_ID = CASTLE_CENTER_3F_NITRO_WARNING;
                (*item_addAmountToInventory)(ITEM_ID_MAGICAL_NITRO, 1);
                BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_CAN_EXPLODE_ON_JUMPING);
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

void cv64_ovl_nitrotxt_close(cv64_ovl_nitrotxt_t* self) {
    MfdsState* message_textbox;

    if (self->text_ID == CASTLE_CENTER_3F_NITRO_WARNING) {
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
        self->header.current_function, &self->header.function_info_ID, NITRO_TEXTBOX_IDLE
    );
}

void cv64_ovl_nitrotxt_destroy(cv64_ovl_nitrotxt_t* self) {
    self->header.destroy(self);
}

s32 cannot_collect_nitro(void) {
    // There's Nitro at both walls
    if ((CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN, EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL
        )) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F, EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL
        )) {
        return TRUE;
    }

    // The lower wall has a Nitro and the upper wall is blown up
    if ((CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN, EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL
        )) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION
        )) {
        return TRUE;
    }

    // The upper wall has a Nitro and the lower wall is blown up
    if ((CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_3F, EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL
        )) &&
        CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION
        )) {
        return TRUE;
    }

    return FALSE;
}
