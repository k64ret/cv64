/**
 * @file gameplay_common_textbox.c
 *
 * This file contains code that operates with the gameplay common textbox
 * (aka the `gameplayMenuMgr` textbox, as it is created by said object).
 *
 * This textbox displays most of the messages seen during gameplay, including
 * item names, text spot messages, etc.
 *
 * @note
 *     - Only the colors white, red, beige and brown can be passed to the gameplay common textbox
 *       using most of these functions, as they limit the palette ID range from 0 to 4, both inclusive.
 *       This means that you can't set animated colors to the text using these functions.
 *
 *     - Most of these functions will close the gameplay textbox if they're called while said textbox
 *       is already opened. The coder needs to ensure that the textbox is closed before trying to call
 *       those functions.
 *
 * @bug
 *      All of these functions are meant to return a value. However, many of these don't return
 *      a default value if the conditions said functions impose are not meant, leading to undefined behaviour.
 *      For example, `gameplayCommonTextbox_prepare` does not return anything if `common_textbox` is `NULL`
 *
 *      Other functions will attempt to use an unitialized variable if some conditions are not met.
 *      For example, in `gameplayCommonTextbox_prepare`, if the `gameplay_menu_mgr` variable is NULL,
 *      then the function will still use the `common_textbox` variable, which in this case is not initialized,
 *      leading to undefined behaviour.
 */

#include "objects/menu/gameplayMenuMgr.h"
#include "item.h"
#include "system_work.h"

u16 you_cannot_carry_more_items_text[] = {
#include "objects/menu/gameplay_common_textbox.msg"
};

/**
 * Returns the gameplay common textbox's instance if it's closed
 */
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

/**
 * Closes the gameplay common textbox
 */
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

/**
 * Opens the gameplay common textbox with the passed parameters
 */
MfdsState* gameplayCommonTextbox_prepare(
    u16* text_ptr, u32 flags, u8 line, u16 width, u8 palette, s16 X_pos, s16 Y_pos, u8 display_time
) {
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
        common_textbox->flags |= MFDS_FLAG_SLOW_TEXT_SPEED;
        common_textbox->flags |= (MFDS_FLAG_OPEN_LENS | MFDS_FLAG_OPEN_TEXTBOX) | flags;
        (*textbox_setPos)(common_textbox, X_pos, Y_pos, 1);
        (*textbox_setDimensions)(common_textbox, line, width, 0, 0);
        (*textbox_setMessagePtr)(common_textbox, text_ptr, NULL, 0);
        common_textbox->palette      = palette % 4;
        common_textbox->display_time = display_time;
        return common_textbox;
    }
}

/**
 * Adds +1 item to the inventory and opens the gameplay common textbox to display its name
 * (or the save prompt text if checking the white jewel)
 *
 * Returns -1 if the inventory for the specified item is full
 */
MfdsState* gameplayCommonTextbox_addItemAndPrepareName(s32 item) {
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

        /**
         * Add the given item to the inventory.
         *
         * If the inventory for that item is full,
         * display the "You cannot carry more items" text.
         */
        if (item_addAmountToInventory(item, 1) < 0) {
            common_textbox->flags |= MFDS_FLAG_ALLOW_VARIABLE_SPEED;
            textbox_setPos(common_textbox, 38, 160, 1);
            textbox_setDimensions(common_textbox, 3, 240, 0, 0);
            common_textbox->display_time = 60;
            textbox_setMessagePtr(
                common_textbox,
                text_getMessageFromPool(&you_cannot_carry_more_items_text, 0),
                NULL,
                0
            );
            common_textbox->palette = TEXT_COLOR_BEIGE;
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
            common_textbox, text_getMessageFromPool(&item_pickables_text, item - 1), NULL, 0
        );
        common_textbox->palette = TEXT_COLOR_BEIGE;
        return common_textbox;
    }
}

/**
 * Opens the gameplay common textbox to display a message
 * from the map assets file's text pool, given its ID within said pool
 */
MfdsState* gameplayCommonTextbox_getMapMessage(u16 id, u8 display_time) {
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
        common_textbox->palette      = TEXT_COLOR_WHITE;
        common_textbox->display_time = display_time * 30.0f;
        return common_textbox;
    }
}

/**
 * Opens the gameplay common textbox to display a message
 * from a specific text pool, given its ID within said pool.
 *
 * The fact that the common textbox's display time is set to 0
 * suggests that this function is supposed to be used for messages that
 * cannot be skipped automatically.
 * For example, those that prompt the player to make a selection, or to manually advance
 * the textbox.
 */
MfdsState* gameplayCommonTextbox_getMessageFromPool(u16* message_pool_ptr, u8 id, u8 palette) {
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
            common_textbox, (*text_getMessageFromPool)(message_pool_ptr, id), NULL, 0
        );
        common_textbox->palette      = palette % 4;
        common_textbox->display_time = 0;
        return common_textbox;
    }
}

/**
 * Returns `TRUE` if the gameplay common textbox's window is opened
 */
u32 gameplayCommonTextbox_lensAreOpened() {
    ObjMfds* common_textbox;
    WindowWork* lens;
    u32 flags;

    common_textbox = gameplayCommonTextbox_getObjectFromList();
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

/**
 * Returns `TRUE` if the gameplay common textbox's window is closed
 */
u32 gameplayCommonTextbox_lensAreClosed() {
    ObjMfds* common_textbox;
    WindowWork* lens;
    u32 flags;

    common_textbox = gameplayCommonTextbox_getObjectFromList();
    lens           = common_textbox->window;
    if (lens != NULL) {
        flags = lens->flags;
        if ((((flags & 0xC000) >> 0xE) == 3) && (((flags & 0x3000) >> 0xC) == 3)) {
            return TRUE;
        }
        return FALSE;
    }
}

/**
 * Finds and returns the gameplay common textbox's object starting from a specific spot
 * in the objects array
 */
ObjMfds* gameplayCommonTextbox_getObject(s32 id, Object* current_object) {
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

/**
 * Finds and returns the gameplay common textbox's object in the objects array
 */
ObjMfds* gameplayCommonTextbox_getObjectFromList() {
    return gameplayCommonTextbox_getObject(MENU_MFDS, ARRAY_START(objects_array) - 1);
}
