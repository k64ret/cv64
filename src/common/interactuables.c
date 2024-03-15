#include "cv64.h"
#include "actor.h"
#include "effect.h"
#include "event_flags.h"
#include "cutscene.h"
#include "gfx/camera.h"
#include "gfx/struct_47.h"
#include "objects/cutscene/interactuables.h"
#include "objects/menu/contractMgr.h"
#include "objects/player/player.h"
#include "random.h"
#include "system_work.h"

cv64_interactuables_func_t interactuables_functions[] = {
    interactuables_init,
    interactuables_main,
    interactuables_initCheck,
    interactuables_selectTextboxOption,
    interactuables_stopCheck,
    interactuables_destroy
};

void interactuables_entrypoint(interactuables* self) {
    ENTER(self, interactuables_functions);
}

void interactuables_init(interactuables* self) {
    cv64_actor_settings_t* settings;
    u32 sp18;
    item_model_settings* item_appearence_settings;
    cv64_model_inf_t* item_model;

    settings = self->settings;
    if (settings != NULL) {
        // In the actor settings, the table ID is stored + 1.
        // Substract -1 to get the actual ID
        self->table_index = settings->variable_1 - 1;
    } else {
        // Set the table ID to -1 (invalid entry)
        self->table_index--;
    }
    if (ptr_PlayerData != NULL) {
        self->map_event_flag_ID = getMapEventFlagID(sys.SaveStruct_gameplay.map_ID);
        if (settings != NULL) {
            if (interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) {
                if (interactuables_settings_table[self->table_index].item == ITEM_ID_WHITE_JEWEL) {
                    // Set save jewel number
                    self->event_flag = settings->variable_3;
                } else {
                    // Set item event flag (variable_2 = upper 2-bytes, variable_3 -> lower 2-bytes)
                    self->event_flag = settings->variable_3 + (settings->variable_2 << 0x10);
                }
            } else {
                // Text spots don't set event flags, so doing this is useless
                self->event_flag = settings->variable_3 + (settings->variable_2 << 0x10);
            }
        } else {
            // Extra empty "else" needed for matching
        }
        if ((interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) &&
            (interactuables_settings_table[self->table_index].item != ITEM_ID_WHITE_JEWEL)) {
            // Don't spawn the item if it has been picked up already
            // i.e. if the item's associated event flag is set
            if ((self->event_flag != 0) &&
                // (0, self->event_flag) needed to avoid v0 / t8 regswap
                CHECK_EVENT_FLAGS(self->map_event_flag_ID, (0, self->event_flag))) {
                self->header.destroy(self);
                return;
            }
        }

        if (interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) {
            // Create and setup the item model
            item_model =
                modelInfo_createRootNode(FIG_TYPE_0400 | FIG_TYPE_HIERARCHY_NODE, D_8018CDE0[2]);
            self->model = item_model;
            if (settings != NULL) {
                actor_model_set_pos(self, item_model);
                self->position.x = item_model->position.x;
                self->position.y = item_model->position.y;
                self->position.z = item_model->position.z;
            } else {
                item_model->position.x = self->position.x;
                item_model->position.y = self->position.y;
                item_model->position.z = self->position.z;
            }
            item_model->assets_file_ID = sys.map_assets_file_IDs[1];

            // Configure some of the model variables by loading them from
            // the item appearence settings table
            item_appearence_settings = itemModelSettings_getEntryFromList(
                interactuables_settings_table[self->table_index].item
            );
            self->item_model_settings_flags = item_appearence_settings->flags;

            // Make the item be able to have variable texture and / or palette.
            // This is used for the Sun / Moon card, and for the keys.
            if (item_appearence_settings->texture != 0xFF) {
                item_model->dlist =
                    item_appearence_settings->dlist | FIG_VARIABLE_TEXTURE_AND_PALETTE;
                item_model->texture = item_appearence_settings->texture;
                item_model->palette = item_appearence_settings->palette;
            } else {
                item_model->dlist = item_appearence_settings->dlist;
            }
            item_model->material_dlist = &ITEM_MATERIAL_DL;
            if (BITS_HAS(interactuables_settings_table[self->table_index].flags, ITEM_INVISIBLE)) {
                // Hide the item model
                BITS_SET(item_model->type, ~0x7FFF);
            }

            if (BITS_HAS(self->item_model_settings_flags, ITEM_MODEL_SETTINGS_FLAG_SPINS)) {
                BITS_SET(item_model->flags, FIG_FLAG_0800);
            } else {
                BITS_SET(item_model->flags, FIG_FLAG_0800 | FIG_FLAG_0040);
            }

            CV64_COLOR_RGBA_TO_U32(item_model->primitive_color) = 0xFFFFFFFF;
            // Make all save jewels semi-transparent if not playing in a save file
            if ((interactuables_settings_table[self->table_index].item == ITEM_ID_WHITE_JEWEL) &&
                (sys.contPak_file_no < 0)) {
                CV64_COLOR_RGBA_TO_U32(item_model->primitive_color) = 0xFFFFFF40;
            }
            CV64_COLOR_RGBA_TO_U32(self->primitive_color) =
                CV64_COLOR_RGBA_TO_U32(item_model->primitive_color);
            item_model->primitive_color.A = item_appearence_settings->transparency;
            item_model->size.x *= item_appearence_settings->size;
            item_model->size.y *= item_appearence_settings->size;
            item_model->size.z *= item_appearence_settings->size;

            if ((interactuables_settings_table[self->table_index].item == ITEM_ID_AXE) ||
                (interactuables_settings_table[self->table_index].item == ITEM_ID_CROSS)) {
                item_model->position.y += 3.2;
                self->position.y += 3.2;
                self->height += 3.2;
                item_model->angle.roll += 0x1000;
            }

            item_model->position.y += 0.1;
            self->trigger_X_size = interactuables_settings_table[self->table_index].trigger_size;
        }

        if ((interactuables_settings_table[self->table_index].type == ITEM_KIND_TEXT_SPOT) &&
            (settings != NULL)) {
            self->position.x     = settings->position.x;
            self->position.y     = settings->position.y;
            self->position.z     = settings->position.z;
            self->trigger_X_size = settings->variable_2;
            self->trigger_Z_size = settings->variable_3;
        }

        // The time it takes for the flash that appears over an item is selected
        // by randomly selecting a number between 120 and 150 frames
        // (4 and 5 seconds)
        self->time_when_flash_appears_over_item = (u16) ((*random_range)(30) + 120);
        ITEM_FADE_TIMER                         = 0;
        self->item_falling_height_multiplier    = 0;
        self->flash                             = NULL;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

void interactuables_main(interactuables* self) {
    cv64_model_inf_t* model;
    f32 current_height;
    pickableItemFlash* flash_effect_obj;
    s32 model_alpha;
    f32 temp;
    u16 item;
    interactuables_settings* settings;

    if (interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) {
        model = self->model;

        if (self->flash != NULL) {
            if ((*effect_isMarkForDeletion)(self->flash) != FALSE) {
                self->flash = NULL;
            }
        }

        if (actor_checkSpawn(self, model->position.x, model->position.y, model->position.z) ==
            FALSE) {
            if (self->time_when_flash_appears_over_item == self->current_flash_inactive_time) {
                if (!(interactuables_settings_table[self->table_index].flags & ITEM_DOES_NOT_FLASH
                    ) &&
                    !(sys.cutscene_flags & CUTSCENE_FLAG_PLAYING) &&
                    (self->item_doesnt_flash == FALSE)) {
                    self->flash = (pickableItemFlash*) (*createEffectObjectUnderEffectMgr)(
                        EFFECT_ID_PICKABLE_ITEM_FLASH, common_camera_effects, 0
                    );
                    if (self->flash != NULL) {
                        (*effect_setPosition)(
                            self->flash,
                            model->position.x,
                            interactuables_settings_table[self->table_index]
                                    .pickable_item_flash_height +
                                model->position.y,
                            model->position.z,
                            POSITION_EQUAL_TO_VISUAL_INFO
                        );
                    }
                }
                self->current_flash_inactive_time       = 0;
                self->time_when_flash_appears_over_item = (u16) ((*random_range)(30) + 120);
            } else {
                self->current_flash_inactive_time++;
            }

            if (self->item_model_settings_flags & ITEM_MODEL_SETTINGS_FLAG_SPINS) {
                if ((interactuables_settings_table[self->table_index].item >= ITEM_ID_WHITE_JEWEL
                    ) &&
                    (interactuables_settings_table[self->table_index].item <= ITEM_ID_SPECIAL2)) {
                    model->angle.yaw += 0x400;
                } else {
                    model->angle.yaw += 0x800;
                }
            }
        }

        if (((interactuables_settings*) ((s32) interactuables_settings_table +
                                         self->table_index * 0x14))
                ->flags &
            ITEM_VANISH) {
            if (self->item_doesnt_vanish == FALSE) {
                if (ITEM_FADE_TIMER++ > 300U) {
                    if (((interactuables_settings*) ((s32) interactuables_settings_table +
                                                     self->table_index * 0x14))
                            ->type == ITEM_KIND_ITEM) {
                        model = self->model;

                        model_alpha = model->primitive_color.A - 8;

                        if (model_alpha < 0) {
                            model->primitive_color.A = 0;
                            self->header.destroy(self);

                            return;
                        } else
                            model->primitive_color.A = model_alpha;
                    }
                }

                if (self->height != self->position.y) {
                    temp = (f32) (++self->item_falling_height_multiplier * 1.96);

                    current_height = self->position.y - temp;

                    if (current_height < self->height) {
                        self->position.y                     = self->height;
                        self->item_falling_height_multiplier = 0;
                    } else
                        self->position.y = current_height;
                }
            }
            model->position.x = self->position.x, model->position.y = self->position.y,
            model->position.z = self->position.z;
        }

        switch (((interactuables_settings*) ((s32) interactuables_settings_table +
                                             self->table_index * 0x14))
                    ->item) {
            default:
                break;

            case ITEM_ID_WHITE_JEWEL:
                if (sys.contPak_file_no < 0) {
                    CV64_COLOR_RGBA_TO_U32(model->primitive_color) = 0xFFFFFF40;
                } else {
                    CV64_COLOR_RGBA_TO_U32(model->primitive_color) = 0xFFFFFFFF;
                }
                break;
        }
    }

    if (self->interacting_with_interactuable == TRUE) {
        switch (interactuables_settings_table[self->table_index].type) {
            default:
                break;

            case ITEM_KIND_ITEM:
                if (self->flash != NULL) {
                    (*effect_markForDeletion)(self->flash);
                }
                break;
        }

        self->flash = NULL;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

void interactuables_initCheck(interactuables* self) {
    interactuables_settings* settings = &interactuables_settings_table[self->table_index];
    mfds_state* textbox;
    contractMgr* contract;

    // If picking up an item...
    if (settings->type == ITEM_KIND_ITEM) {
        // Setup and display the item name textbox
        textbox = item_prepareTextbox(itemModelSettings_getEntryFromList(
                                          interactuables_settings_table[self->table_index].item
        )
                                          ->item_ID);

        if (textbox == NULL)
            return;

        self->textbox = textbox;

        // If picking up the contract, create `contractMgr`, which begins
        // the cutscene and warps you to Renon's shop
        if (interactuables_settings_table[self->table_index].item == ITEM_ID_THE_CONTRACT) {
            contract = (contractMgr*) (*object_createAndSetChild)(&self->header, MENU_CONTRACTMGR);
            contract->contract_item = self;
        }

        // If trying to pick up a White Jewel, freeze the players and all enemies in place
        // and begin reading its textbox. Don't actually pick it up
        if (interactuables_settings_table[self->table_index].item == ITEM_ID_WHITE_JEWEL) {
            sys.FREEZE_PLAYER  = TRUE;
            sys.FREEZE_ENEMIES = TRUE;
            cameraMgr_setReadingTextState(sys.ptr_cameraMgr, TRUE);
            ITEM_FADE_TIMER = 0;
            settings        = &interactuables_settings_table[self->table_index];
        }
    }

    // If checking a text spot...
    if (interactuables_settings_table[self->table_index].type == ITEM_KIND_TEXT_SPOT) {
        if (BITS_HAS(
                interactuables_settings_table[self->table_index].flags,
                TEXT_SPOT_DESTROY_IF_EVENT_FLAG_IS_SET
            )) {
            // Destroy it if its associated event flag is set
            if (CHECK_EVENT_FLAGS(
                    self->map_event_flag_ID,
                    interactuables_settings_table[self->table_index].event_flag
                )) {
                self->header.destroy(self);
                return;
            }
        }

        if (BITS_HAS(
                interactuables_settings_table[self->table_index].flags,
                TEXT_SPOT_DISABLE_IF_EVENT_FLAG_IS_NOT_SET
            )) {
            // Disable it if its associated event flag is NOT set
            if (!CHECK_EVENT_FLAGS(
                    self->map_event_flag_ID,
                    interactuables_settings_table[self->table_index].event_flag
                )) {
                interactuables_stopInteraction(self);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.functionInfo_ID,
                    INTERACTUABLES_MAIN
                );
                return;
            }
        }

        // clang-format off
        // Get the message associated to the text spot
        // @bug No matter if flag 0x10 is set or not, the game will grab the very same string
        textbox = (BITS_HAS(interactuables_settings_table[self->table_index].flags, TEXT_SPOT_DO_ACTION_AFTER_SELECTING_OPTION))
            ? map_getMessageFromPool(interactuables_settings_table[self->table_index].text_ID, 0)
            : map_getMessageFromPool(interactuables_settings_table[self->table_index].text_ID, 0);

        // Freeze the player and all enemies in place, then begin reading the message
        sys.FREEZE_PLAYER = TRUE, // comma needed for matching
        sys.FREEZE_ENEMIES = TRUE;
        // clang-format on

        if (textbox == NULL)
            return;

        self->textbox = textbox;
        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, TRUE);
        ITEM_FADE_TIMER = 0;
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void interactuables_selectTextboxOption(interactuables* self) {
    saveGame* saveGameObj;

    if (interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) {
        if (interactuables_settings_table[self->table_index].item == ITEM_ID_WHITE_JEWEL) {
            mfds_state* textbox = self->textbox;

            switch (textbox->textbox_option) {
                default:
                    break;
                case 0:
                    return;
                case 1:
                    saveGameObj =
                        (saveGame*) object_createAndSetChild(&self->header, MENU_SAVEGAME),
                    saveGameObj->save_crystal_number = (s16) self->event_flag;
                    break;
                case 2:
                    sys.FREEZE_PLAYER = FALSE, sys.FREEZE_ENEMIES = FALSE;
                    cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);
                    interactuables_stopInteraction(self);
                    (*object_curLevel_goToFunc)(
                        self->header.current_function,
                        &self->header.functionInfo_ID,
                        INTERACTUABLES_MAIN
                    );
                    return;
            }
        }
    }

    if (interactuables_settings_table[self->table_index].type == (u32) ITEM_KIND_TEXT_SPOT) {
        if (interactuables_settings_table[self->table_index].flags &
            TEXT_SPOT_DO_ACTION_AFTER_SELECTING_OPTION) {
            mfds_state* textbox = self->textbox;

            switch (textbox->textbox_option) {
                default:
                    break;
                case 0:
                    return;
                case 1:
                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index].flags,
                            TEXT_SPOT_IF_YES_START_CUTSCENE
                        )) {
                        sys.FREEZE_PLAYER = FALSE, sys.FREEZE_ENEMIES = FALSE;
                        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);
                        sys.cutscene_ID =
                            interactuables_settings_table[self->table_index].cutscene_ID;
                    }

                    // Empty `if` needed for matching
                    if (1) {
                    }

                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index].flags,
                            TEXT_SPOT_IF_YES_SET_EVENT_FLAG
                        )) {
                        SET_EVENT_FLAGS(
                            self->map_event_flag_ID,
                            interactuables_settings_table[self->table_index].event_flag
                        );
                    }

                    // Empty `if` needed for matching
                    if (1) {
                    }

                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index].flags,
                            TEXT_SPOT_IF_YES_ACTIVATE_LEVER
                        )) {
                        (*cutscene_setActorStateIfMatchingVariable1)(
                            interactuables_settings_table[self->table_index].actor_ID,
                            interactuables_settings_table[self->table_index].actor_variable_1,
                            TRUE
                        );
                    }

                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index].flags,
                            TEXT_SPOT_IF_YES_PULL_LEVER
                        )) {
                        BITS_SET(sys.pull_lever, TRUE);
                    }
                    break;
                case 2:
                    break;
            }
        }
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void interactuables_stopCheck(interactuables* self) {
    u32 temp[2];

    if (interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) {
        if (interactuables_settings_table[self->table_index].item == ITEM_ID_WHITE_JEWEL) {
            if (objectList_findFirstObjectByID(MENU_SAVEGAME) == NULL) {
                sys.FREEZE_PLAYER  = FALSE;
                sys.FREEZE_ENEMIES = FALSE;

                cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);
                interactuables_stopInteraction(self);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.functionInfo_ID,
                    INTERACTUABLES_MAIN
                );
            }
        } else {
            if (self->textbox == (mfds_state*) -1) {
                interactuables_stopInteraction(self);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.functionInfo_ID,
                    INTERACTUABLES_MAIN
                );

                return;
            }

            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
        }
    }

    if ((interactuables_settings_table[self->table_index].type == ITEM_KIND_TEXT_SPOT) &&
        lensAreClosed()) {
        sys.FREEZE_PLAYER  = FALSE;
        sys.FREEZE_ENEMIES = FALSE;
        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);

        if (BITS_HAS(
                interactuables_settings_table[self->table_index].flags,
                TEXT_SPOT_DESTROY_AFTER_INTERACTION
            )) {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
            return;
        }

        interactuables_stopInteraction(self);
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.functionInfo_ID, INTERACTUABLES_MAIN
        );
    }
}

void interactuables_destroy(interactuables* self) {
    if (interactuables_settings_table[self->table_index].type == ITEM_KIND_ITEM) {
        // If we picked the contract, remove it from the inventory and stop its interaction
        if (interactuables_settings_table[self->table_index].item == ITEM_ID_THE_CONTRACT) {
            // Technically speaking, the contract gets added temporarily to your inventory after picking it up
            // until exiting Renon's shop.
            // This could also be a leftover from early development, where using the contract would've consumed
            // 1 point (see: https://tcrf.net/Castlevania_(Nintendo_64)/Unused_Items)
            (*item_removeAmountFromInventory)(ITEM_ID_THE_CONTRACT, 1);

            if (objectList_findFirstObjectByID(MENU_CONTRACTMGR) == NULL) {
                interactuables_stopInteraction(self);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.functionInfo_ID,
                    INTERACTUABLES_MAIN
                );
            }

            return;
        }

        if (self->event_flag != 0) {
            // Set the appropiate event flag, if the item is meant to set one
            SET_EVENT_FLAGS(self->map_event_flag_ID, self->event_flag);

            // Unlock the Special1 and Special2 rewards after picking them up
            if (interactuables_settings_table[self->table_index].item == ITEM_ID_SPECIAL1) {
                BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HARD_MODE_UNLOCKED);
            }

            if (interactuables_settings_table[self->table_index].item == ITEM_ID_SPECIAL2) {
                if (sys.SaveStruct_gameplay.character != REINHARDT) {
                    BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME);
                } else {
                    BITS_SET(sys.SaveStruct_gameplay.flags, SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME);
                }
            }
        }
    }

    self->header.destroy(self);
}

void interactuables_stopInteraction(interactuables* self) {
    self->textbox                        = NULL;
    ITEM_FADE_TIMER                      = 0;
    self->textbox_is_active              = FALSE;
    self->interacting_with_interactuable = FALSE;
}
