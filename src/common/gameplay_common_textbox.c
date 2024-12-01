/**
 * @file gameplay_common_textbox.c
 *
 * This file contains code that operates with the gameplay common textbox
 * (aka the `gameplayMenuMgr` textbox, as it is created by said object).
 *
 * This textbox displays most of the messages seen during gameplay, including
 * item names, text spot messages, etc.
 */

#include "objects/menu/gameplayMenuMgr.h"
#include "item.h"
#include "system_work.h"

u16 YOU_CANNOT_CARRY_MORE_ITEMS_TEXT[] = {
#include "objects/menu/gameplay_common_textbox.msg"
};

MfdsState* gameplayCommonTextbox_getIfClosed() {
    MfdsState* common_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        common_textbox = gameplay_menu_mgr->common_textbox;
    } else {
        // Empty `else` needed for matching.
    }

    if (common_textbox != NULL) {
        if (common_textbox->flags & MFDS_FLAG_OPEN_TEXTBOX) {
            return NULL;
        }
        return common_textbox;
    }
}

MfdsState* gameplayCommonTextbox_close() {
    MfdsState* common_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        common_textbox = gameplay_menu_mgr->common_textbox;
    } else {
        // Empty `else` needed for matching.
    }

    if (common_textbox != NULL) {
        if (!(common_textbox->flags & MFDS_FLAG_CLOSE_TEXTBOX)) {
            common_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
        }
        return common_textbox;
    }
    return NULL;
}

ObjMfds* gameplayCommonTextbox_displayMessage(
    u16* text_ptr,
    u32 flags,
    u8 line,
    u16 width,
    u8 color_palette,
    s16 X_pos,
    s16 Y_pos,
    u8 display_time
) {
    MfdsState* common_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;
    u32 temp_t0;
    u32 temp_t2;
    u32 temp_v0;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        common_textbox = gameplay_menu_mgr->common_textbox;
    } else {
        // Empty `else` needed for matching.
    }

    if (common_textbox != NULL) {
        if (common_textbox->flags & MFDS_FLAG_OPEN_TEXTBOX) {
            if (!(common_textbox->flags & MFDS_FLAG_CLOSE_TEXTBOX)) {
                common_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            }
            return NULL;
        }

        common_textbox->flags &=
            ~(MFDS_FLAG_SLOW_TEXT_SPEED |
              (MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED));
        common_textbox->flags |= MFDS_FLAG_SLOW_TEXT_SPEED;
        common_textbox->flags |= (MFDS_FLAG_OPEN_LENS | MFDS_FLAG_OPEN_TEXTBOX) | flags;
        (*textbox_setPos)(common_textbox, X_pos, Y_pos, 1);
        (*textbox_setDimensions)(common_textbox, line, width, 0, 0);
        (*textbox_setMessagePtr)(common_textbox, text_ptr, NULL, 0);
        common_textbox->palette      = color_palette % 4;
        common_textbox->display_time = display_time;
        return common_textbox;
    }
}

MfdsState* gameplayCommonTextbox_displayItemName(s32 item) {
    MfdsState* common_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        common_textbox = gameplay_menu_mgr->common_textbox;
    } else {
        // Empty `else` needed for matching.
    }

    if (common_textbox != NULL) {
        if (common_textbox->flags & MFDS_FLAG_OPEN_TEXTBOX) {
            if (!(common_textbox->flags & MFDS_FLAG_CLOSE_TEXTBOX)) {
                common_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            }
            return NULL;
        }
        common_textbox->flags |= (MFDS_FLAG_OPEN_LENS | MFDS_FLAG_OPEN_TEXTBOX);
        common_textbox->flags &=
            ~(MFDS_FLAG_SLOW_TEXT_SPEED |
              (MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED));
        if (item_addAmountToInventory(item, 1) < 0) {
            common_textbox->flags |= MFDS_FLAG_ALLOW_VARIABLE_SPEED;
            textbox_setPos(common_textbox, 38, 160, 1);
            textbox_setDimensions(common_textbox, 3, 240, 0, 0);
            common_textbox->display_time = 60;
            textbox_setMessagePtr(
                common_textbox,
                text_getMessageFromPool(&YOU_CANNOT_CARRY_MORE_ITEMS_TEXT, 0),
                NULL,
                0
            );
            common_textbox->palette = 2;
            return (MfdsState*) -1;
        }
        if (item == ITEM_ID_WHITE_JEWEL) {
            common_textbox->flags |= MFDS_FLAG_ALLOW_VARIABLE_SPEED;
            textbox_setPos(common_textbox, 38, 140, 1);
            textbox_setDimensions(common_textbox, 4, 240, 0, 0);
            common_textbox->display_time = 0;
        } else {
            common_textbox->flags |= (MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED);
            textbox_setPos(common_textbox, 40, 170, 1);
            textbox_setDimensions(common_textbox, 1, 150, 0, 0);
            common_textbox->display_time = 90;
        }
        textbox_setMessagePtr(
            common_textbox, text_getMessageFromPool(&item_pickables_names, item - 1), NULL, 0
        );
        common_textbox->palette = 2;
        return common_textbox;
    }
}

MfdsState* gameplayCommonTextbox_displayMapMessage(u16 id, u8 display_time) {
    MfdsState* common_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        common_textbox = gameplay_menu_mgr->common_textbox;
    } else {
        // Empty `else` needed for matching.
    }

    if (common_textbox != NULL) {
        if (common_textbox->flags & MFDS_FLAG_OPEN_TEXTBOX) {
            if (!(common_textbox->flags & MFDS_FLAG_CLOSE_TEXTBOX)) {
                common_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            }
            return NULL;
        }
        common_textbox->flags &=
            ~(MFDS_FLAG_SLOW_TEXT_SPEED |
              (MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED));
        common_textbox->flags |= MFDS_FLAG_ALLOW_VARIABLE_SPEED;
        common_textbox->flags |= (MFDS_FLAG_OPEN_LENS | MFDS_FLAG_OPEN_TEXTBOX);
        textbox_setPos(common_textbox, 38, 140, 1);
        textbox_setDimensions(common_textbox, 4, 240, 0, 0);
        textbox_setMessagePtr(
            common_textbox,
            text_getMessageFromPool(GET_MAP_MESSAGE_POOL_PTR_NO_FUNC_PTR(), id),
            NULL,
            0
        );
        common_textbox->palette      = 0;
        common_textbox->display_time = display_time * 30.0f;
        return common_textbox;
    }
}

MfdsState*
gameplayCommonTextbox_displayMessageGivenPalette(u16* text_ptr, u8 id, u8 color_palette) {
    MfdsState* common_textbox;
    gameplayMenuMgr* gameplay_menu_mgr;

    gameplay_menu_mgr = (gameplayMenuMgr*) (*objectList_findFirstObjectByID)(MENU_GAMEPLAY_MENUMGR);
    if (gameplay_menu_mgr != NULL) {
        common_textbox = gameplay_menu_mgr->common_textbox;
    } else {
        // Empty `else` needed for matching.
    }

    if (common_textbox != NULL) {
        if (common_textbox->flags & MFDS_FLAG_OPEN_TEXTBOX) {
            if (!(common_textbox->flags & MFDS_FLAG_CLOSE_TEXTBOX)) {
                common_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
            }
            return NULL;
        }
        common_textbox->flags &=
            ~(MFDS_FLAG_SLOW_TEXT_SPEED |
              (MFDS_FLAG_FAST_TEXT_SPEED | MFDS_FLAG_ALLOW_VARIABLE_SPEED));
        common_textbox->flags |= MFDS_FLAG_ALLOW_VARIABLE_SPEED;
        common_textbox->flags |= (MFDS_FLAG_OPEN_LENS | MFDS_FLAG_OPEN_TEXTBOX);
        textbox_setPos(common_textbox, 38, 140, 1);
        textbox_setDimensions(common_textbox, 4, 240, 0, 0);
        textbox_setMessagePtr(common_textbox, (*text_getMessageFromPool)(text_ptr, id), NULL, 0);
        common_textbox->palette      = color_palette % 4;
        common_textbox->display_time = 0;
        return common_textbox;
    }
}

u32 gameplayCommonTextbox_lensAreOpened() {
    ObjMfds* common_textbox;
    WindowWork* lens;
    u32 flags;

    common_textbox = gameplayCommonTextbox_getFromList();
    lens           = common_textbox->window;
    if (lens != NULL) {
        flags = lens->flags;
        if ((((flags & 0xC000) >> 0xE) == 0) &&
            ((((flags & 0x3000) >> 0xC) != 0) || (((flags & 0x300) >> 8) != 0))) {
            return TRUE;
        }
        return FALSE;
    }
}

u32 gameplayCommonTextbox_lensAreClosed() {
    ObjMfds* common_textbox;
    WindowWork* lens;
    u32 flags;

    common_textbox = gameplayCommonTextbox_getFromList();
    lens           = common_textbox->window;
    if (lens != NULL) {
        flags = lens->flags;
        if ((((flags & 0xC000) >> 0xE) == 3) && (((flags & 0x3000) >> 0xC) == 3)) {
            return TRUE;
        }
        return FALSE;
    }
}

ObjMfds* gameplayCommonTextbox_get(s32 id, Object* current_object) {
    MfdsState* textbox;

    BITS_ASSIGN_MASK(id, 0x7FF);

    for (current_object++; current_object < ARRAY_END(objects_array); current_object++) {
        if (BITS_MASK(current_object->header.ID, 0x07FF) == id) {
            textbox = ((ObjMfds*) current_object)->state;
            if (textbox->flags & MFDS_FLAG_GAMEPLAYMENUMGR_TEXTBOX) {
                return current_object;
            }
        }
    }

    return NULL;
}

ObjMfds* gameplayCommonTextbox_getFromList() {
    return gameplayCommonTextbox_get(MENU_MFDS, ARRAY_START(objects_array) - 1);
}
