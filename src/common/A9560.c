/**
 * @file A9560.c
 *
 * Contains helper functions used for interactions between the player and interactuables.
 */

#include "A9560.h"
#include "objects/cutscene/cutsceneMgr.h"
#include "system_work.h"

specialTextbox* Player_getActorCurrentlyInteractingWith() {
    s32 temp;
    cv64_model_inf_t* player_model;
    specialTextbox* library_puzzle;
    interactuables* actor;
    interactuables* text_spot = NULL;
    interactuables_settings* settings;
    s32 can_interact = FALSE;
    vec3f pos;

    actor = (interactuables*) objectList_findFirstObjectByID(CUTSCENE_INTERACTUABLES);
    if (actor != NULL) {
        pos.x        = actor->position.x;
        pos.y        = actor->position.y;
        pos.z        = actor->position.z;
        can_interact = playerCanInteractWithInteractuable(pos.x, pos.y, pos.z, actor);
        if (can_interact) {
            settings = &interactuables_settings_table[actor->table_index];
            if (settings->type == ITEM_KIND_TEXT_SPOT) {
                text_spot = actor;
            } else if ((settings->item == ITEM_ID_WHITE_JEWEL) && (sys.contPak_file_no < 0)) {
                can_interact = FALSE;
            } else if ((settings->item == ITEM_ID_POWERUP) && (sys.current_PowerUp_level >= 2)) {
                can_interact = FALSE;
            } else {
                return (interactuables*) actor;
            }
        }
        for (actor = (interactuables*) object_findFirstObjectByID(CUTSCENE_INTERACTUABLES, actor);
             actor != NULL;
             actor = (interactuables*) object_findFirstObjectByID(CUTSCENE_INTERACTUABLES, actor)) {
            pos.x        = actor->position.x;
            pos.y        = actor->position.y;
            pos.z        = actor->position.z;
            can_interact = playerCanInteractWithInteractuable(pos.x, pos.y, pos.z, actor);
            if (can_interact) {
                settings = &interactuables_settings_table[actor->table_index];
                if (settings->type == ITEM_KIND_TEXT_SPOT) {
                    if (text_spot != NULL) {
                        if (settings->event_flag ==
                            interactuables_settings_table[text_spot->table_index].event_flag) {
                            if (settings->flags & TEXT_SPOT_DESTROY_IF_EVENT_FLAG_IS_SET) {
                                text_spot = actor;
                                continue;
                            } else {
                                continue;
                            }
                        } else {
                            text_spot = actor;
                            continue;
                        }
                    } else {
                        text_spot = actor;
                        continue;
                    }
                }
                if ((settings->item == ITEM_ID_WHITE_JEWEL) && (sys.contPak_file_no < 0)) {
                    can_interact = FALSE;
                } else if ((settings->item == ITEM_ID_POWERUP) && (sys.current_PowerUp_level >= 2)) {
                    can_interact = FALSE;
                } else {
                    return actor;
                }
            }
        }
        if (text_spot != NULL) {
            return text_spot;
        }
    }

    if (sys.SaveStruct_gameplay.map == HONMARU_4F_MINAMI) {
        library_puzzle = (specialTextbox*) objectList_findFirstObjectByID(CUTSCENE_LIBRARY_PUZZLE);
        if (library_puzzle != NULL) {
            player_model = ptr_PlayerData->visualData.model;
            pos.x        = library_puzzle->position.x;
            pos.y        = library_puzzle->position.y;
            pos.z        = library_puzzle->position.z;
            if (((pos.x - 15.0f) <= player_model->position.x) &&
                (player_model->position.x <= (pos.x + 15.0f))) {
                if (((pos.y - 4.0f) <= player_model->position.y) &&
                    (player_model->position.y <= (pos.y + 4.0f))) {
                    if (((pos.z - 16.0f) <= player_model->position.z) &&
                        (player_model->position.z <= (pos.z + 16.0f))) {
                        return library_puzzle;
                    }
                }
            }
        }
    }
    if (sys.SaveStruct_gameplay.map == HONMARU_B1F) {
        player_model = ptr_PlayerData->visualData.model;
        actor        = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_MANDRAGORA_TEXTBOX, player_model
        );
        if (actor != NULL) {
            return actor;
        }
    }
    if (sys.SaveStruct_gameplay.map == HONMARU_3F_KITA) {
        player_model = ptr_PlayerData->visualData.model;
        actor        = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_NITRO_TEXTBOX, ptr_PlayerData->visualData.model
        );
        if (actor != NULL) {
            return actor;
        }
    }
    if ((sys.SaveStruct_gameplay.map == HONMARU_1F) ||
        (sys.SaveStruct_gameplay.map == HONMARU_2F) ||
        (sys.SaveStruct_gameplay.map == HONMARU_3F_MINAMI)) {
        player_model = ptr_PlayerData->visualData.model;
        actor        = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_NITRO_DISPOSAL_TEXTBOX, player_model
        );
        if (actor != NULL) {
            return actor;
        }
        if (sys.SaveStruct_gameplay.map == HONMARU_1F) {
            actor = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
                CUTSCENE_BOTTOM_ELEVATOR_ACTIVATOR_TEXTBOX, player_model
            );
            if (actor != NULL) {
                return actor;
            }
        }
    }
    if ((sys.SaveStruct_gameplay.map == HONMARU_B1F) ||
        (sys.SaveStruct_gameplay.map == HONMARU_3F_MINAMI)) {
        actor = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_EXPLOSIVE_WALL_SPOT, ptr_PlayerData->visualData.model
        );
        if (actor != NULL) {
            return actor;
        }
    }
    if (can_interact == FALSE) {
        return NULL;
    }
}

specialTextbox*
Player_getSpecialTextboxCurrentlyInteractingWith(s16 actor_ID, cv64_model_inf_t* player_model) {
    specialTextbox* actor;
    u16 angle_player_textspot;
    u16 player_facing_angle;

    actor = (specialTextbox*) objectList_findFirstObjectByID(actor_ID);
    if (actor != NULL) {
        if (((actor->position.x - actor->trigger_size_X) <= player_model->position.x) &&
            (player_model->position.x <= (actor->trigger_size_X + actor->position.x))) {
            if (((actor->position.y - 6.0f) <= player_model->position.y) &&
                (player_model->position.y <= (actor->position.y + 6.0f))) {
                if (((actor->position.z - actor->trigger_size_Z) <= player_model->position.z) &&
                    (player_model->position.z <= (actor->trigger_size_Z + actor->position.z))) {
                    if (1) {
                    }
                    player_facing_angle = (u16) player_model->angle.yaw + 0x2000;
                    if (1) {
                    }
                    angle_player_textspot = getAngleBetweenPlayerAndInteractuable(
                                                player_model->position.x,
                                                player_model->position.z,
                                                actor->position.x,
                                                actor->position.z
                                            ) -
                        player_facing_angle;
                    if ((((angle_player_textspot) + 0x4000) & 0xFFFF) <= 0x9000) {
                        return actor;
                    }
                }
            }
        }
    }
    return NULL;
}

s32 playerCanInteractWithInteractuable(f32 pos_X, f32 pos_Y, f32 pos_Z, interactuables* actor) {
    cv64_model_inf_t* player_model    = ptr_PlayerData->visualData.model;
    interactuables_settings* settings = &interactuables_settings_table[0, (s16) actor->table_index];
    f32 sine;
    f32 cosine;
    u16 angle_player_item;
    u16 player_facing_angle;

    if (settings->type == ITEM_KIND_ITEM) {
        if (((pos_X - settings->trigger_size) <= player_model->position.x) &&
            (player_model->position.x <= (settings->trigger_size + pos_X))) {
            if (((pos_Y - settings->trigger_size) <= player_model->position.y) &&
                (player_model->position.y <= (settings->trigger_size + pos_Y))) {
                if (((pos_Z - settings->trigger_size) <= player_model->position.z) &&
                    (player_model->position.z <= (settings->trigger_size + pos_Z))) {
                    player_facing_angle = (u16) player_model->angle.yaw + 0x2000;
                    sine                = ((*sins)(player_facing_angle) / 32768.0f) * -2.0 * 1.0f;
                    cosine              = ((*coss)(player_facing_angle) / 32768.0f) * -2.0 * 1.0f;
                    angle_player_item   = getAngleBetweenPlayerAndInteractuable(
                                            player_model->position.x + sine,
                                            player_model->position.z + cosine,
                                            pos_X,
                                            pos_Z
                                        ) -
                        player_facing_angle;
                    if ((((angle_player_item) + 0x4000) & 0xFFFF) <= 0x8000) {
                        return TRUE;
                    }
                }
            }
        }
    } else {
        if (((pos_X - actor->trigger_X_size) <= player_model->position.x) &&
            (player_model->position.x <= (actor->trigger_X_size + pos_X))) {
            if (((pos_Y - 5.0f) <= player_model->position.y) &&
                (player_model->position.y <= (pos_Y + 8.0f))) {
                if (((pos_Z - actor->trigger_Z_size) <= player_model->position.z) &&
                    (player_model->position.z <= (actor->trigger_Z_size + pos_Z))) {
                    player_facing_angle = (u16) player_model->angle.yaw + 0x2000;
                    angle_player_item =
                        getAngleBetweenPlayerAndInteractuable(
                            player_model->position.x, player_model->position.z, pos_X, pos_Z
                        ) -
                        player_facing_angle;
                    if ((((angle_player_item) + 0x4000) & 0xFFFF) <= 0x9000) {
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

s32 interactuables_getInteractingType(specialTextbox* actor) {
    interactuables_settings* settings;
    s16 actor_ID = actor->header.ID;

    if (actor_ID == CUTSCENE_INTERACTUABLES) {
        settings = &interactuables_settings_table[((interactuables*) actor)->table_index];
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

void interactuables_enableTextbox(specialTextbox* actor) {
    actor->textbox_is_active = TRUE;
}

void interactuables_setInteractingFlag(specialTextbox* actor) {
    actor->interacting_with_interactuable = TRUE;
}

u32 getMapEventFlagID(s16 stage_ID) {
    switch (stage_ID) {
        case MORI:
            return EVENT_FLAG_ID_FOREST_AND_DEFAULT;
        case TOU:
            return EVENT_FLAG_ID_CASTLE_WALL_TOWERS;
        case TOUOKUJI:
            return EVENT_FLAG_ID_CASTLE_WALL_MAIN;
        case NAKANIWA:
            return EVENT_FLAG_ID_VILLA_OUTSIDE;
        case BEKKAN_1F:
            return EVENT_FLAG_ID_VILLA_INSIDE;
        case BEKKAN_2F:
            return EVENT_FLAG_ID_VILLA_INSIDE;
        case MEIRO_TEIEN:
            return EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN;
        case CHIKA_KODO:
            return EVENT_FLAG_ID_TUNNEL;
        case CHIKA_SUIRO:
            return EVENT_FLAG_ID_WATERWAY_AND_CASTLE_CENTER_5F;
        case HONMARU_B1F:
            return EVENT_FLAG_ID_CASTLE_CENTER_MAIN;
        case HONMARU_1F:
            return EVENT_FLAG_ID_CASTLE_CENTER_1F_2F;
        case HONMARU_2F:
            return EVENT_FLAG_ID_CASTLE_CENTER_1F_2F;
        case HONMARU_3F_MINAMI:
            return EVENT_FLAG_ID_CASTLE_CENTER_3F;
        case HONMARU_4F_MINAMI:
            return EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN;
        case HONMARU_3F_KITA:
            return EVENT_FLAG_ID_CASTLE_CENTER_3F;
        case HONMARU_5F:
            return EVENT_FLAG_ID_WATERWAY_AND_CASTLE_CENTER_5F;
        case SHOKEI_TOU:
            return EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING;
        case MAHOU_TOU:
            return EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING;
        case KAGAKU_TOU:
            return EVENT_FLAG_ID_TOWER_SCIENCE;
        case KETTOU_TOU:
            return EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING;
        case TURO_TOKEITOU:
            return EVENT_FLAG_ID_CLOCK_TOWER;
        case TENSHU:
            return EVENT_FLAG_ID_CLOCK_TOWER;
        case TOKEITOU_NAI:
            return EVENT_FLAG_ID_CLOCK_TOWER;
        case DRACULA:
            return EVENT_FLAG_ID_MISC_STAGES;
        case ROSE:
            return EVENT_FLAG_ID_MISC_STAGES;
        case BEKKAN_BOSS:
            return EVENT_FLAG_ID_MISC_STAGES;
        case TOU_TURO:
            return EVENT_FLAG_ID_MISC_STAGES;
        case ENDING:
            return EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING;
        default:
            return EVENT_FLAG_ID_FOREST_AND_DEFAULT;
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
