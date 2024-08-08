/**
 * @file bottom_elevator_activator.c
 *
 * Handles the textbox associated to the bottom elevator activator in Castle Center.
 */

#include "objects/cutscene/bottom_elevator_activator.h"
#include "system_work.h"

// clang-format off

cv64_ovl_bottomelevatoractivatortextbox_func_t cv64_ovl_bottomelevatoractivatortextbox_funcs[] = {
    cv64_ovl_bottomelevatoractivatortextbox_init,
    cv64_ovl_bottomelevatoractivatortextbox_idle,
    cv64_ovl_bottomelevatoractivatortextbox_prep_msg,
    cv64_ovl_bottomelevatoractivatortextbox_yes_no,
    cv64_ovl_bottomelevatoractivatortextbox_close,
    cv64_ovl_bottomelevatoractivatortextbox_destroy
};

// clang-format on

void cv64_ovl_bottomelevatoractivatortextbox_entrypoint(
    cv64_ovl_bottomelevatoractivatortextbox_t* self
) {
    ENTER(self, cv64_ovl_bottomelevatoractivatortextbox_funcs);
}

void cv64_ovl_bottomelevatoractivatortextbox_init(cv64_ovl_bottomelevatoractivatortextbox_t* self) {
    cv64_actor_settings_t* settings = self->settings;

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

void cv64_ovl_bottomelevatoractivatortextbox_idle(cv64_ovl_bottomelevatoractivatortextbox_t* self) {
    if (self->interacting_with_interactuable != TRUE)
        return;

    sys.FREEZE_GAMEPLAY = TRUE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, TRUE);
    self->text_ID = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_bottomelevatoractivatortextbox_prep_msg(
    cv64_ovl_bottomelevatoractivatortextbox_t* self
) {
    mfds_state* message;

    if (CHECK_EVENT_FLAGS(13, 1)) {
        if (CHECK_EVENT_FLAGS(8, 2)) {
            message       = (*map_getMessageFromPool)(4, 0);
            self->text_ID = 2;
        } else {
            message       = (*map_getMessageFromPool)(1, 0);
            self->text_ID = 1;
        }
    } else {
        message = (*map_getMessageFromPool)(3, 0);
    }

    if (message == NULL)
        return;

    self->message_textbox   = message;
    self->header.timer      = 0;
    self->textbox_is_active = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_bottomelevatoractivatortextbox_yes_no(cv64_ovl_bottomelevatoractivatortextbox_t* self
) {
    mfds_state* textbox = self->message_textbox;

    if (self->text_ID == 1) {
        switch (textbox->textbox_option) {
            case TEXTBOX_OPTION_IDLE:
                return;
            case TEXTBOX_OPTION_YES:
                SET_EVENT_FLAGS(8, 2);
                (*play_sound)(0x119);
                break;
            case TEXTBOX_OPTION_NO:
                self->text_ID = 4;
                break;
        }
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_bottomelevatoractivatortextbox_close(cv64_ovl_bottomelevatoractivatortextbox_t* self
) {
    mfds_state* message;

    if (self->text_ID == 1) {
        message = (*map_getMessageFromPool)(2, 0);
        if (message == NULL)
            return;

        self->message_textbox = message;
        self->text_ID         = 5;
    }
    if ((self->text_ID == 4) || ((*lensAreClosed)())) {
        self->header.timer                   = 0;
        self->textbox_is_active              = FALSE;
        self->interacting_with_interactuable = FALSE;
        sys.FREEZE_GAMEPLAY                  = FALSE;
        (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            NITRO_DISPOSAL_TEXTBOX_IDLE
        );
    }
}

void cv64_ovl_bottomelevatoractivatortextbox_destroy(cv64_ovl_bottomelevatoractivatortextbox_t* self
) {
    self->header.destroy(self);
}
