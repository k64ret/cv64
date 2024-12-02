/**
 * @file explosive_wall_spot.c
 *
 * Handles the textbox associated to the spots in front of the breakable walls in Castle Center
 * where the player has to drop the Magical Nitro and Mandragora.
 */

#include "objects/cutscene/explosive_wall_spot.h"
#include "objects/menu/gameplayMenuMgr.h"
#include "system_work.h"

// clang-format off

cv64_ovl_explwalltxt_func_t cv64_ovl_explwalltxt_funcs[] = {
    cv64_ovl_explwalltxt_init,
    cv64_ovl_explwalltxt_idle,
    cv64_ovl_explwalltxt_determine_msg,
    cv64_ovl_explwalltxt_item_prepare_msg,
    cv64_ovl_explwalltxt_item_idle,
    cv64_ovl_explwalltxt_item_determine_next_txt,
    cv64_ovl_explwalltxt_item_no,
    cv64_ovl_explwalltxt_ready_for_blast,
    cv64_ovl_explwalltxt_nitro_is_set,
    cv64_ovl_explwalltxt_mandragora_is_set,
    cv64_ovl_explwalltxt_item_already_set,
    cv64_ovl_explwalltxt_default_desc,
    cv64_ovl_explwalltxt_destroy
};

// clang-format on

void cv64_ovl_explwalltxt_entrypoint(cv64_ovl_explwalltxt_t* self) {
    ENTER(self, cv64_ovl_explwalltxt_funcs);
}

void cv64_ovl_explwalltxt_init(cv64_ovl_explwalltxt_t* self) {
    ActorConfig* settings = self->settings;

    if (ptr_PlayerData == NULL)
        return;

    self->position.x     = settings->position.x;
    self->position.y     = settings->position.y;
    self->position.z     = settings->position.z;
    self->trigger_size_X = settings->variable_2;
    self->trigger_size_Z = settings->variable_3;
    self->wall_type      = settings->variable_1;

    if (self->wall_type == WALL_TYPE_MAIN_MAP) {
        self->set_nitro_text_ID           = CASTLE_CENTER_MAIN_SET_NITRO;
        self->set_mandragora_text_ID      = CASTLE_CENTER_MAIN_SET_MANDRAGORA;
        self->default_description_text_ID = CASTLE_CENTER_MAIN_WALL_INFO;
        self->item_already_set_text_ID    = CASTLE_CENTER_MAIN_ITEM_ALREADY_SET;
        self->nitro_set_text_ID           = CASTLE_CENTER_MAIN_NITRO_SET;
        self->mandragora_set_text_ID      = CASTLE_CENTER_MAIN_MANDRAGORA_SET;
        self->ready_for_blasting_text_ID  = CASTLE_CENTER_MAIN_READY_FOR_BLASTING;
    }

    if (self->wall_type == WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP) {
        self->set_nitro_text_ID           = CASTLE_CENTER_3F_SET_NITRO;
        self->set_mandragora_text_ID      = CASTLE_CENTER_3F_SET_MANDRAGORA;
        self->default_description_text_ID = CASTLE_CENTER_3F_WALL_INFO;
        self->item_already_set_text_ID    = CASTLE_CENTER_3F_ITEM_ALREADY_SET;
        self->nitro_set_text_ID           = CASTLE_CENTER_3F_NITRO_SET;
        self->mandragora_set_text_ID      = CASTLE_CENTER_3F_MANDRAGORA_SET;
        self->ready_for_blasting_text_ID  = CASTLE_CENTER_3F_READY_FOR_BLASTING;
    }

    self->header.timer = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_explwalltxt_idle(cv64_ovl_explwalltxt_t* self) {
    // If we're interacting with the wall and it hasn't been blown up yet
    if ((self->interacting_with_interactable == TRUE) &&
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

void cv64_ovl_explwalltxt_determine_msg(cv64_ovl_explwalltxt_t* self) {
    // If we don't have the Nitro or the Mandragora
    if ((self->nitro_amount_until_max_capacity > 0) &&
        (self->mandragora_amount_until_max_capacity > 0)) {
        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            EXPLOSIVE_WALL_SPOT_DEFAULT_DESCRIPTION
        );
        return;
    }

    // If we have Nitro on the inventory
    if (self->nitro_amount_until_max_capacity <= 0) {
        switch (self->wall_type) {
            // Check if Nitro is already placed in the wall
            case WALL_TYPE_MAIN_MAP:
                if (CHECK_EVENT_FLAGS(
                        EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                        EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL
                    )) {
                    (*object_curLevel_goToFunc)(
                        self->header.current_function,
                        &self->header.function_info_ID,
                        EXPLOSIVE_WALL_SPOT_ITEM_ALREADY_SET
                    );
                    return;
                }
                break;
            case WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP:
                if (CHECK_EVENT_FLAGS(
                        EVENT_FLAG_ID_CASTLE_CENTER_3F,
                        EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL
                    )) {
                    (*object_curLevel_goToFunc)(
                        self->header.current_function,
                        &self->header.function_info_ID,
                        EXPLOSIVE_WALL_SPOT_ITEM_ALREADY_SET
                    );
                    return;
                }
                break;
        }
    }

    // If we have Mandragora on the inventory
    if (self->mandragora_amount_until_max_capacity <= 0) {
        switch (self->wall_type) {
            // Check if Mandragora is already placed in the wall
            case WALL_TYPE_MAIN_MAP:
                if (CHECK_EVENT_FLAGS(
                        EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                        EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL
                    )) {
                    (*object_curLevel_goToFunc)(
                        self->header.current_function,
                        &self->header.function_info_ID,
                        EXPLOSIVE_WALL_SPOT_ITEM_ALREADY_SET
                    );
                    return;
                }
                break;
            case WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP:
                if (CHECK_EVENT_FLAGS(
                        EVENT_FLAG_ID_CASTLE_CENTER_3F,
                        EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL
                    )) {
                    (*object_curLevel_goToFunc)(
                        self->header.current_function,
                        &self->header.function_info_ID,
                        EXPLOSIVE_WALL_SPOT_ITEM_ALREADY_SET
                    );
                    return;
                }
                break;
        }
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_explwalltxt_item_prepare_msg(cv64_ovl_explwalltxt_t* self) {
    // clang-format off
    MfdsState* message = (self->nitro_amount_until_max_capacity <= 0)
        ? (*gameplayCommonTextbox_getMapMessage)(self->set_nitro_text_ID, 0)
        : (*gameplayCommonTextbox_getMapMessage)(self->set_mandragora_text_ID, 0);
    // clang-format on

    if (message == NULL)
        return;

    self->message_textbox = message;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_explwalltxt_item_idle(cv64_ovl_explwalltxt_t* self) {
    MfdsState* textbox = self->message_textbox;
    u8 textbox_option  = textbox->textbox_option;

    switch (textbox_option) {
        case TEXTBOX_OPTION_IDLE:
            return;
        case TEXTBOX_OPTION_YES:
            if (self->nitro_amount_until_max_capacity <= 0) {
                (*item_removeAmountFromInventory)(ITEM_ID_MAGICAL_NITRO, 1);
                BITS_UNSET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_CAN_EXPLODE_ON_JUMPING);
                switch (self->wall_type) {
                    case WALL_TYPE_MAIN_MAP:
                        SET_EVENT_FLAGS(
                            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                            EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL
                        );
                        break;
                    case WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP:
                        SET_EVENT_FLAGS(
                            EVENT_FLAG_ID_CASTLE_CENTER_3F,
                            EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL
                        );
                        break;
                }
            } else {
                (*item_removeAmountFromInventory)(ITEM_ID_MANDRAGORA, 1);
                switch (self->wall_type) {
                    case WALL_TYPE_MAIN_MAP:
                        SET_EVENT_FLAGS(
                            EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                            EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL
                        );
                        break;
                    case WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP:
                        SET_EVENT_FLAGS(
                            EVENT_FLAG_ID_CASTLE_CENTER_3F,
                            EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL
                        );
                        break;
                }
            }
            break;
        case TEXTBOX_OPTION_NO:
            (*object_curLevel_goToFunc)(
                self->header.current_function,
                &self->header.function_info_ID,
                EXPLOSIVE_WALL_SPOT_SETITEMTEXT_CLOSE
            );
            return;
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_explwalltxt_item_determine_next_txt(cv64_ovl_explwalltxt_t* self) {
    switch (self->wall_type) {
        case WALL_TYPE_MAIN_MAP:
            // Both the Nitro and Mandragora have been set. The wall is ready for blasting
            if ((CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                    EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL
                )) &&
                (CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                    EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL
                ))) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    EXPLOSIVE_WALL_SPOT_READY_FOR_BLASTING
                );
                return;
            }
            // Nitro was put into the floor successfully
            if (CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                    EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL
                )) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    EXPLOSIVE_WALL_SPOT_NITRO_IS_SET
                );
                return;
            }
            // Mandragora was put into the floor successfully
            if (CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_MAIN,
                    EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL
                )) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    EXPLOSIVE_WALL_SPOT_MANDRAGORA_IS_SET
                );
                return;
            }
            break;
        case WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP:
            // Both the Nitro and Mandragora have been set. The wall is ready for blasting
            if ((CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_3F, EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL
                )) &&
                (CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_3F,
                    EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL
                ))) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    EXPLOSIVE_WALL_SPOT_READY_FOR_BLASTING
                );
                return;
            }
            // Nitro was put into the floor successfully
            if (CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_3F, EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL
                )) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    EXPLOSIVE_WALL_SPOT_NITRO_IS_SET
                );
                return;
            }
            // Mandragora was put into the floor successfully
            if (CHECK_EVENT_FLAGS(
                    EVENT_FLAG_ID_CASTLE_CENTER_3F,
                    EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL
                )) {
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.function_info_ID,
                    EXPLOSIVE_WALL_SPOT_MANDRAGORA_IS_SET
                );
                return;
            }
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

/**
 * Player selected the "NO" option in the
 * "Set X item?" textbox
 */
void cv64_ovl_explwalltxt_item_no(cv64_ovl_explwalltxt_t* self) {
    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, EXPLOSIVE_WALL_SPOT_IDLE
    );
}

void cv64_ovl_explwalltxt_ready_for_blast(cv64_ovl_explwalltxt_t* self) {
    MfdsState* message;

    if (self->state == 0) {
        message = (*gameplayCommonTextbox_getMapMessage)(self->ready_for_blasting_text_ID, 0);
    }

    if (message == NULL)
        return;

    self->state           = 1;
    self->message_textbox = message;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    switch (self->wall_type) {
        case WALL_TYPE_MAIN_MAP:
            sys.cutscene_ID = CUTSCENE_ID_BLOW_UP_WALL_IN_BULL_ARENA;
            break;
        case WALL_TYPE_FRIENDLY_LIZARD_MAN_MAP:
            sys.cutscene_ID = CUTSCENE_ID_BLOW_UP_WALL_TO_LIBRARY;
            break;
    }
    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, EXPLOSIVE_WALL_SPOT_IDLE
    );
}

void cv64_ovl_explwalltxt_nitro_is_set(cv64_ovl_explwalltxt_t* self) {
    MfdsState* message;

    if (self->state == 0) {
        message = (*gameplayCommonTextbox_getMapMessage)(self->nitro_set_text_ID, 0);
    }

    if (message == NULL)
        return;

    self->state           = 1;
    self->message_textbox = message;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, EXPLOSIVE_WALL_SPOT_IDLE
    );
}

void cv64_ovl_explwalltxt_mandragora_is_set(cv64_ovl_explwalltxt_t* self) {
    MfdsState* message;

    if (self->state == 0) {
        message = (*gameplayCommonTextbox_getMapMessage)(self->mandragora_set_text_ID, 0);
    }

    if (message == NULL)
        return;

    self->state           = 1;
    self->message_textbox = message;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, EXPLOSIVE_WALL_SPOT_IDLE
    );
}

void cv64_ovl_explwalltxt_default_desc(cv64_ovl_explwalltxt_t* self) {
    MfdsState* message;

    if (self->state == 0) {
        message = (*gameplayCommonTextbox_getMapMessage)(self->default_description_text_ID, 0);
    }

    if (message == NULL)
        return;

    self->state           = 1;
    self->message_textbox = message;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, EXPLOSIVE_WALL_SPOT_IDLE
    );
}

void cv64_ovl_explwalltxt_item_already_set(cv64_ovl_explwalltxt_t* self) {
    MfdsState* message;

    if (self->state == 0) {
        message = (*gameplayCommonTextbox_getMapMessage)(self->item_already_set_text_ID, 0);
    }

    if (message == NULL)
        return;

    self->state           = 1;
    self->message_textbox = message;

    if (!(*gameplayCommonTextbox_lensAreClosed)())
        return;

    self->header.timer                  = 0;
    self->textbox_is_active             = FALSE;
    self->interacting_with_interactable = FALSE;
    sys.FREEZE_GAMEPLAY                 = FALSE;
    (*cameraMgr_setReadingTextState)(sys.ptr_cameraMgr, FALSE);
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, EXPLOSIVE_WALL_SPOT_IDLE
    );
}

void cv64_ovl_explwalltxt_destroy(cv64_ovl_explwalltxt_t* self) {
    self->header.destroy(self);
}
