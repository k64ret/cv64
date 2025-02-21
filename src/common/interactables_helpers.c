/**
 * @file interactables_helpers.c
 *
 * Contains helper functions used for interactions between the player and interactables.
 */

#include "objects/cutscene/interactables_helpers.h"
#include "objects/cutscene/cutsceneMgr.h"
#include "system_work.h"

/**
 * When checking out something with C-Right, this function will return
 * the instance of the interactable / special textbox the player is checking out.
 *
 * If the actor cannot be interacted with, either because the player is far away from its trigger,
 * they're not facing it, or because of other special conditions, the function will return `NULL`.
 */
specialTextbox* Player_getActorCurrentlyInteractingWith() {
    s32 temp;
    Model* player_model;
    specialTextbox* library_puzzle;
    Interactable* actor;
    Interactable* text_spot = NULL;
    InteractableConfig* settings;
    s32 can_interact = FALSE;
    Vec3f pos;

    /**
     * Interactuables
     *
     * Check all the interactables currently spawned,
     * and return the one the player is currently interacting with
     */
    /**
     * Check the first interactable spawned
     *
     * Note that, if the `objectList_findFirstObjectByID` call returns `NULL`,
     * it is assumed that no interactable is spawned
     */
    actor = (Interactable*) objectList_findFirstObjectByID(CUTSCENE_INTERACTABLES);
    if (actor != NULL) {
        pos.x = actor->position.x;
        pos.y = actor->position.y;
        pos.z = actor->position.z;

        can_interact = playerCanInteractWithInteractuable(pos.x, pos.y, pos.z, actor);
        if (can_interact) {
            settings = &interactables_settings[actor->idx];

            // The interactable is a text spot. Continue to the loop.
            if (settings->type == ITEM_KIND_TEXT_SPOT) {
                text_spot = actor;

                // Don't allow interaction with White Jewels if the Controller Pak is not connected
            } else if ((settings->item == ITEM_ID_WHITE_JEWEL) && (sys.contPak_file_no < 0)) {
                can_interact = FALSE;

                // Don't allow picking up a Powerup if the player already has Powerup level 2
            } else if ((settings->item == ITEM_ID_POWERUP) && (sys.current_PowerUp_level >= 2)) {
                can_interact = FALSE;

                // Return the instance (item)
            } else {
                return (Interactable*) actor;
            }
        }

        /**
         * Check the rest of the interactables
         */
        for (actor = (Interactable*) object_findFirstObjectByID(CUTSCENE_INTERACTABLES, actor);
             actor != NULL;
             actor = (Interactable*) object_findFirstObjectByID(CUTSCENE_INTERACTABLES, actor)) {
            pos.x = actor->position.x;
            pos.y = actor->position.y;
            pos.z = actor->position.z;

            can_interact = playerCanInteractWithInteractuable(pos.x, pos.y, pos.z, actor);
            if (can_interact) {
                settings = &interactables_settings[actor->idx];

                // If the interactable is a text spot
                if (settings->type == ITEM_KIND_TEXT_SPOT) {
                    if (text_spot != NULL) {
                        if (settings->event_flag ==
                            interactables_settings[text_spot->idx].event_flag) {
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

                // Don't allow interaction with White Jewels if the Controller Pak is not connected
                if ((settings->item == ITEM_ID_WHITE_JEWEL) && (sys.contPak_file_no < 0)) {
                    can_interact = FALSE;

                    // Don't allow picking up a Powerup if the player already has Powerup level 2
                } else if ((settings->item == ITEM_ID_POWERUP) && (sys.current_PowerUp_level >= 2)) {
                    can_interact = FALSE;

                    // Return the instance (item)
                } else {
                    return (Interactable*) actor;
                }
            }
        }

        // Return the instance (text spot)
        if (text_spot != NULL) {
            return (Interactable*) text_spot;
        }
    }

    // Castle Center Library puzzle
    if (sys.SaveStruct_gameplay.map == HONMARU_4F_MINAMI) {
        library_puzzle = (specialTextbox*) objectList_findFirstObjectByID(CUTSCENE_LIBRARY_PUZZLE);
        if (library_puzzle != NULL) {
            player_model = ptr_PlayerData->visualData.model;
            pos.x        = library_puzzle->position.x;
            pos.y        = library_puzzle->position.y;
            pos.z        = library_puzzle->position.z;
            /**
             * The library puzzle's trigger has a hardcoded
             * XYZ size of (15, 4, 16)
             */
            if (((pos.x - 15.0f) <= player_model->position.x) &&
                (player_model->position.x <= (pos.x + 15.0f))) {
                if (((pos.y - 4.0f) <= player_model->position.y) &&
                    (player_model->position.y <= (pos.y + 4.0f))) {
                    if (((pos.z - 16.0f) <= player_model->position.z) &&
                        (player_model->position.z <= (pos.z + 16.0f))) {
                        return (specialTextbox*) library_puzzle;
                    }
                }
            }
        }
    }

    // Mandragora pick-up spot
    if (sys.SaveStruct_gameplay.map == HONMARU_B1F) {
        player_model = ptr_PlayerData->visualData.model;
        actor        = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_MANDRAGORA_TEXTBOX, player_model
        );
        if (actor != NULL) {
            return (specialTextbox*) actor;
        }
    }

    // Magical Nitro pick-up spot
    if (sys.SaveStruct_gameplay.map == HONMARU_3F_KITA) {
        player_model = ptr_PlayerData->visualData.model;
        actor        = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_NITRO_TEXTBOX, ptr_PlayerData->visualData.model
        );
        if (actor != NULL) {
            return (specialTextbox*) actor;
        }
    }

    if ((sys.SaveStruct_gameplay.map == HONMARU_1F) ||
        (sys.SaveStruct_gameplay.map == HONMARU_2F) ||
        (sys.SaveStruct_gameplay.map == HONMARU_3F_MINAMI)) {
        // Magical Nitro disposal spot
        player_model = ptr_PlayerData->visualData.model;
        actor        = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_NITRO_DISPOSAL_TEXTBOX, player_model
        );
        if (actor != NULL) {
            return (specialTextbox*) actor;
        }

        if (sys.SaveStruct_gameplay.map == HONMARU_1F) {
            // Castle Center bottom elevator activator spot
            actor = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
                CUTSCENE_BOTTOM_ELEVATOR_ACTIVATOR_TEXTBOX, player_model
            );
            if (actor != NULL) {
                return (specialTextbox*) actor;
            }
        }
    }

    // Castle Center explosive walls spots
    if ((sys.SaveStruct_gameplay.map == HONMARU_B1F) ||
        (sys.SaveStruct_gameplay.map == HONMARU_3F_MINAMI)) {
        actor = (specialTextbox*) Player_getSpecialTextboxCurrentlyInteractingWith(
            CUTSCENE_EXPLOSIVE_WALL_SPOT, ptr_PlayerData->visualData.model
        );
        if (actor != NULL) {
            return (specialTextbox*) actor;
        }
    }

    // Return `NULL` if unable to interact
    if (can_interact == FALSE) {
        return NULL;
    }
}

/**
 * Given the player and a special textbox's position, this function checks if the player
 * is inside said special textbox's trigger and is also facing it, so that the player can
 * check it out.
 *
 * If the player should interact with the special textbox,
 * the function will return its instance.
 */
specialTextbox*
Player_getSpecialTextboxCurrentlyInteractingWith(s16 actor_ID, Model* player_model) {
    specialTextbox* actor;
    u16 angle_player_textspot;
    u16 player_facing_angle;

    actor = (specialTextbox*) objectList_findFirstObjectByID(actor_ID);
    if (actor != NULL) {
        if (((actor->position.x - actor->trigger_size_X) <= player_model->position.x) &&
            (player_model->position.x <= (actor->trigger_size_X + actor->position.x))) {
            /**
             * Special text spots have a hardcoded trigger height of [-6, 6]
             * relative to its position
             */
            if (((actor->position.y - 6.0f) <= player_model->position.y) &&
                (player_model->position.y <= (actor->position.y + 6.0f))) {
                if (((actor->position.z - actor->trigger_size_Z) <= player_model->position.z) &&
                    (player_model->position.z <= (actor->trigger_size_Z + actor->position.z))) {
                    if (1) {
                    }
                    player_facing_angle = (u16) player_model->angle.yaw + DEG_TO_FIXED(45);
                    if (1) {
                    }
                    angle_player_textspot = getAngleBetweenPlayerAndInteractable(
                                                player_model->position.x,
                                                player_model->position.z,
                                                actor->position.x,
                                                actor->position.z
                                            ) -
                        player_facing_angle;
                    if ((u16) (angle_player_textspot + DEG_TO_FIXED(90)) <= DEG_TO_FIXED(202.5)) {
                        return actor;
                    }
                }
            }
        }
    }
    return NULL;
}

/**
 * Given the player and an interactable's position, this function checks if the player
 * is inside said interactable's trigger and is also facing it, so that the player can
 * check it out.
 *
 * Returns `TRUE` if the player should interact with it.
 */
s32 playerCanInteractWithInteractuable(
    f32 actor_pos_X, f32 actor_pos_Y, f32 actor_pos_Z, Interactable* actor
) {
    Model* player_model          = ptr_PlayerData->visualData.model;
    InteractableConfig* settings = &interactables_settings[0, (s16) actor->idx];
    f32 sine;
    f32 cosine;
    u16 angle_player_item;
    u16 player_facing_angle;

    if (settings->type == ITEM_KIND_ITEM) {
        if (((actor_pos_X - settings->trigger_size) <= player_model->position.x) &&
            (player_model->position.x <= (settings->trigger_size + actor_pos_X))) {
            if (((actor_pos_Y - settings->trigger_size) <= player_model->position.y) &&
                (player_model->position.y <= (settings->trigger_size + actor_pos_Y))) {
                if (((actor_pos_Z - settings->trigger_size) <= player_model->position.z) &&
                    (player_model->position.z <= (settings->trigger_size + actor_pos_Z))) {
                    player_facing_angle = (u16) player_model->angle.yaw + DEG_TO_FIXED(45);
                    sine                = ((*sins)(player_facing_angle) / 32768.0f) * -2.0 * 1.0f;
                    cosine              = ((*coss)(player_facing_angle) / 32768.0f) * -2.0 * 1.0f;
                    angle_player_item   = getAngleBetweenPlayerAndInteractable(
                                            player_model->position.x + sine,
                                            player_model->position.z + cosine,
                                            actor_pos_X,
                                            actor_pos_Z
                                        ) -
                        player_facing_angle;
                    if ((u16) (angle_player_item + DEG_TO_FIXED(90)) <= DEG_TO_FIXED(180)) {
                        return TRUE;
                    }
                }
            }
        }
    } else {
        if (((actor_pos_X - actor->trigger_X_size) <= player_model->position.x) &&
            (player_model->position.x <= (actor->trigger_X_size + actor_pos_X))) {
            /**
             * Text spots have a hardcoded trigger height of [-5, 8]
             * relative to its position
             */
            if (((actor_pos_Y - 5.0f) <= player_model->position.y) &&
                (player_model->position.y <= (actor_pos_Y + 8.0f))) {
                if (((actor_pos_Z - actor->trigger_Z_size) <= player_model->position.z) &&
                    (player_model->position.z <= (actor->trigger_Z_size + actor_pos_Z))) {
                    player_facing_angle = (u16) player_model->angle.yaw + DEG_TO_FIXED(45);
                    angle_player_item   = getAngleBetweenPlayerAndInteractable(
                                            player_model->position.x,
                                            player_model->position.z,
                                            actor_pos_X,
                                            actor_pos_Z
                                        ) -
                        player_facing_angle;
                    if ((u16) (angle_player_item + DEG_TO_FIXED(90)) <= DEG_TO_FIXED(202.5)) {
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

/**
 * Given an actor the player is currently interacting with,
 * it returns a number indicating its interaction "type",
 * which is used by the player to know what exact action
 * they should do next.
 */
s32 interactables_getInteractingType(specialTextbox* actor) {
    InteractableConfig* settings;
    s16 actor_ID = actor->header.ID;

    if (actor_ID == CUTSCENE_INTERACTABLES) {
        settings = &interactables_settings[((Interactable*) actor)->idx];
        if (settings->type == ITEM_KIND_ITEM) {
            return INTERACT_TYPE_ITEM;
        }
        if (settings->type == ITEM_KIND_TEXT_SPOT) {
            if (settings->flags & TEXT_SPOT_IF_YES_PULL_LEVER) {
                return INTERACT_TYPE_PULL_LEVER;
            } else {
                return INTERACT_TYPE_TEXT_SPOT;
            }
        }
    }

    if (actor_ID == CUTSCENE_LIBRARY_PUZZLE) {
        return INTERACT_TYPE_TEXT_SPOT;
    }
    if (actor_ID == CUTSCENE_MANDRAGORA_TEXTBOX) {
        return INTERACT_TYPE_TEXT_SPOT;
    }
    if (actor_ID == CUTSCENE_NITRO_TEXTBOX) {
        return INTERACT_TYPE_TEXT_SPOT;
    }
    if (actor_ID == CUTSCENE_NITRO_DISPOSAL_TEXTBOX) {
        return INTERACT_TYPE_TEXT_SPOT;
    }
    if (actor_ID == CUTSCENE_EXPLOSIVE_WALL_SPOT) {
        return INTERACT_TYPE_TEXT_SPOT;
    }
    if (actor_ID == CUTSCENE_BOTTOM_ELEVATOR_ACTIVATOR_TEXTBOX) {
        return INTERACT_TYPE_TEXT_SPOT;
    }

    return INTERACT_TYPE_NONE;
}

void interactables_enableTextbox(specialTextbox* actor) {
    actor->textbox_is_active = TRUE;
}

void interactables_setInteractingFlag(specialTextbox* actor) {
    actor->interacting_with_interactable = TRUE;
}

/**
 * Returns the ID of the `event_flags` array from `cv64_save_state`
 * that corresponds to each map
 */
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

/**
 * After defeating the White Dragon in Castle Wall, this function will spawn
 * two text spots: one that is used to enable the trigger that opens the grating
 * and another one that is used to tell that the grating has been opened already.
 *
 * `castleWallGratingMechanism_textSpotsActorConfig` contains the actor config
 * that has the information such as the position and the text IDs that correspond to each
 * text spot.
 *
 * While the function implies that `castleWallGratingMechanism_textSpotsActorConfig` has
 * various entries, only one is present in the final game, so this will only work properly
 * when `index` is 0, as any other value will read out of bounds.
 */
void spawnCastleWallGratingMechanismTextboxes(s16 index) {
    Interactable* text_spot;

    // Spawn trigger text spot
    if (castleWallGratingMechanism_textSpotsActorConfig[index][1] != NULL) {
        text_spot =
            (Interactable*) (*object_createAndSetChild)(ptr_cutsceneMgr, CUTSCENE_INTERACTABLES);
        text_spot->settings = castleWallGratingMechanism_textSpotsActorConfig[index][1];
    }
    // Spawn "grating already opened" text spot
    if (castleWallGratingMechanism_textSpotsActorConfig[index][2] != NULL) {
        text_spot =
            (Interactable*) (*object_createAndSetChild)(ptr_cutsceneMgr, CUTSCENE_INTERACTABLES);
        text_spot->settings = castleWallGratingMechanism_textSpotsActorConfig[index][2];
    }
}

/**
 * `door_item_open_verify_list` contains a list of all key items
 * alongside the event flags that get set when the players picks those keys up.
 *
 * If said event flag is set, and the player has the key in the inventory, this function
 * will remove said key from the inventory once the player opens the door.
 */
void removeKeyWhenOpeningDoor(s16 event_flag_ID, u32 event_flag) {
    door_item_open_verify_struct* curr;
    door_item_open_verify_struct* end;

    for (curr = ARRAY_START(door_item_open_verify_list),
        end   = ARRAY_END(door_item_open_verify_list);
         curr != end;
         curr++) {
        // If the "key grabbed" event flag is set
        if ((event_flag_ID == curr->event_flag_ID) && (event_flag == curr->event_flag) &&
            // and the key is in the inventory
            (item_getAmountUntilMaxCapacity(curr->item) == 0)) {
            // remove the key from the inventory
            item_removeAmountFromInventory(curr->item, 1);
            return;
        }
    }
}
