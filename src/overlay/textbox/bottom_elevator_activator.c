/**
 * @file bottom_elevator_activator.c
 *
 * Handles the textbox associated to the bottom elevator activator in Castle Center.
 */

#include "objects/cutscene/bottom_elevator_activator.h"
#include "objects/menu/gameplayMenuMgr.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

cv64_ovl_elevatortxt_func_t cv64_ovl_elevatortxt_funcs[] = {
    cv64_ovl_elevatortxt_init,
    cv64_ovl_elevatortxt_idle,
    cv64_ovl_elevatortxt_prepare_msg,
    cv64_ovl_elevatortxt_yes_no,
    cv64_ovl_elevatortxt_close,
    cv64_ovl_elevatortxt_destroy
};

// clang-format on

void cv64_ovl_elevatortxt_entrypoint(cv64_ovl_elevatortxt_t* self) {
    ENTER(self, cv64_ovl_elevatortxt_funcs);
}

void cv64_ovl_elevatortxt_init(cv64_ovl_elevatortxt_t* self) {
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

void cv64_ovl_elevatortxt_idle(cv64_ovl_elevatortxt_t* self) {
    if (self->interacting_with_interactable != TRUE)
        return;

    sys.FREEZE_GAMEPLAY = TRUE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, TRUE);
    self->state = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_elevatortxt_prepare_msg(cv64_ovl_elevatortxt_t* self) {
    MfdsState* message;

    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
            EVENT_FLAG_CASTLE_CENTER_3F_RELEASED_BULL_ROOM_CRYSTAL_MAGIC
        )) {
        if (CHECK_EVENT_FLAGS(
                EVENT_FLAG_ID_CASTLE_CENTER_1F_2F, EVENT_FLAG_CASTLE_CENTER_1F_2F_ELEVATOR_ACTIVATED
            )) {
            message =
                (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_1F_ELEVATOR_ALREADY_USED, 0);
            self->state = BOTTOM_ELEVATOR_ACTIVATOR_STATE_ALREADY_USED;
        } else {
            message = (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_1F_ACTIVATE_ELEVATOR, 0);
            self->state = BOTTOM_ELEVATOR_ACTIVATOR_STATE_ACTIVATE_ELEVATOR;
        }
    } else {
        message =
            (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_1F_CANT_ACTIVATE_ELEVATOR_YET, 0);
    }

    if (message == NULL)
        return;

    self->message_textbox   = message;
    self->header.timer      = 0;
    self->textbox_is_active = FALSE;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_elevatortxt_yes_no(cv64_ovl_elevatortxt_t* self) {
    MfdsState* textbox = self->message_textbox;

    if (self->state == BOTTOM_ELEVATOR_ACTIVATOR_STATE_ACTIVATE_ELEVATOR) {
        switch (textbox->textbox_option) {
            case TEXTBOX_OPTION_IDLE:
                return;
            case TEXTBOX_OPTION_YES:
                SET_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_1F_2F,
                    EVENT_FLAG_CASTLE_CENTER_1F_2F_ELEVATOR_ACTIVATED
                );
                (*play_sound)(SD_TRIGGER_BOTTOM_ELEVATOR_ACTIVATOR);
                break;
            case TEXTBOX_OPTION_NO:
                self->state = BOTTOM_ELEVATOR_ACTIVATOR_STATE_DONT_ACTIVATE_YET;
                break;
        }
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_elevatortxt_close(cv64_ovl_elevatortxt_t* self) {
    MfdsState* message;

    if (self->state == BOTTOM_ELEVATOR_ACTIVATOR_STATE_ACTIVATE_ELEVATOR) {
        message = (*gameplayCommonTextbox_getMapMessage)(CASTLE_CENTER_1F_ELEVATOR_ACTIVATED, 0);
        if (message == NULL)
            return;

        self->message_textbox = message;
        self->state           = BOTTOM_ELEVATOR_ACTIVATOR_STATE_ELEVATOR_ACTIVATED;
    }

    if ((self->state != BOTTOM_ELEVATOR_ACTIVATOR_STATE_DONT_ACTIVATE_YET) &&
        !(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function,
        &self->header.function_info_ID,
        BOTTOM_ELEVATOR_ACTIVATOR_IDLE
    );
}

void cv64_ovl_elevatortxt_destroy(cv64_ovl_elevatortxt_t* self) {
    self->header.destroy(self);
}
