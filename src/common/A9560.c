/**
 * @file A9560.c
 *
 * Contains helper functions used for interactions between the player and interactuables.
 */

#include "A9560.h"
#include "objects/cutscene/cutsceneMgr.h"

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/A9560/Player_getActorCurrentlyInteractingWith.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/A9560/Player_getSpecialTextboxCurrentlyInteractingWith.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/A9560/playerCanInteractWithInteractuable.s")

// clang-format on

s32 interactuables_getInteractingType(interactuables* self) {
    interactuables_settings* settings;
    s16 actor_ID = self->header.ID;

    if (actor_ID == CUTSCENE_INTERACTUABLES) {
        settings = &interactuables_settings_table[self->table_index];
        if (settings->type == ITEM_KIND_ITEM) {
            return INTERACT_TYPE_ITEM;
        }
        if (settings->type == ITEM_KIND_TEXT_SPOT) {
            if (settings->flags & TEXT_SPOT_IF_YES_PULL_LEVER) {
                return INTERACT_TYPE_TEXT_SPOT;
            } else {
                return INTERACT_TYPE_OTHERS;
            }
        }
    }

    if (actor_ID == CUTSCENE_LIBRARY_PUZZLE) {
        return INTERACT_TYPE_OTHERS;
    }
    if (actor_ID == CUTSCENE_MANDRAGORA_TEXTBOX) {
        return INTERACT_TYPE_OTHERS;
    }
    if (actor_ID == CUTSCENE_NITRO_TEXTBOX) {
        return INTERACT_TYPE_OTHERS;
    }
    if (actor_ID == CUTSCENE_NITRO_DISPOSAL_TEXTBOX) {
        return INTERACT_TYPE_OTHERS;
    }
    if (actor_ID == CUTSCENE_EXPLOSIVE_WALL_SPOT) {
        return INTERACT_TYPE_OTHERS;
    }
    if (actor_ID == CUTSCENE_BOTTOM_ELEVATOR_ACTIVATOR_TEXTBOX) {
        return INTERACT_TYPE_OTHERS;
    }

    return INTERACT_TYPE_NONE;
}

void interactuables_enableTextbox(interactuables* self) {
    self->textbox_is_active = TRUE;
}

void interactuables_setInteractingFlag(interactuables* self) {
    self->interacting_with_interactuable = TRUE;
}

u32 getMapEventFlagID(s16 stage_ID) {
    switch (stage_ID) {
        case 0:
            return 0U;
        case 1:
            return 0xEU;
        case 2:
            return 0xAU;
        case 3:
            return 9U;
        case 4:
            return 1U;
        case 5:
            return 1U;
        case 6:
            return 0xBU;
        case 7:
            return 0xCU;
        case 8:
            return 2U;
        case 9:
            return 0xDU;
        case 10:
            return 8U;
        case 11:
            return 8U;
        case 12:
            return 3U;
        case 13:
            return 0xBU;
        case 14:
            return 3U;
        case 15:
            return 2U;
        case 16:
            return 4U;
        case 17:
            return 4U;
        case 18:
            return 0xFU;
        case 19:
            return 4U;
        case 20:
            return 5U;
        case 21:
            return 5U;
        case 23:
            return 5U;
        case 24:
            return 6U;
        case 25:
            return 6U;
        case 26:
            return 6U;
        case 27:
            return 6U;
        case 28:
            return 4U;
        default:
            return 0U;
    }
}

void spawnCastleWallGratingMechanismTextboxes(s16 index) {
    interactuables* text_spot;

    if (castleWallGratingMechanism_textSpotsActorSettings[index][1] != NULL) {
        text_spot =
            (interactuables*) (*object_createAndSetChild)(ptr_cutsceneMgr, CUTSCENE_INTERACTUABLES);
        text_spot->settings = castleWallGratingMechanism_textSpotsActorSettings[index][1];
    }
    if (castleWallGratingMechanism_textSpotsActorSettings[index][2] != NULL) {
        text_spot =
            (interactuables*) (*object_createAndSetChild)(ptr_cutsceneMgr, CUTSCENE_INTERACTUABLES);
        text_spot->settings = castleWallGratingMechanism_textSpotsActorSettings[index][2];
    }
}

void checkDoorCanBeOpenedWithKey(s16 event_flag_IDs, u32 event_flag) {
    door_item_open_verify_struct* curr;
    door_item_open_verify_struct* end;

    for (curr = ARRAY_START(door_item_open_verify_list),
        end   = ARRAY_END(door_item_open_verify_list);
         curr != end;
         curr++) {
        if ((event_flag_IDs == curr->event_flag_IDs) && (event_flag == curr->event_flag) &&
            (item_getAmountUntilMaxCapacity(curr->item_ID) == 0)) {
            item_removeAmountFromInventory(curr->item_ID, 1);
            return;
        }
    }
}
