#include "cv64.h"
#include "actor.h"
#include "effect.h"
#include "event_flags.h"
#include "gfx/camera.h"
#include "gfx/struct_47.h"
#include "objects/cutscene/interactuables.h"
#include "objects/menu/contractMgr.h"
#include "objects/player/player.h"
#include "random.h"
#include "system_work.h"

typedef struct {
    u8 field_0x00[6];
    s16 field_0x06;
    u8 field_0x08[20];
} struct_56;

typedef struct {
    void* field_0x00; // A function pointer
    struct_56* field_0x04;
    u32 dlist;
    s32 file_ID;
    s32 event_flag_ID;
    u32 event_flag;
    s32 sound_ID;
} struct_21;

typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t model;
    u8 field_0x28[12];
    struct_56* field_0x34;
    void* field_0x38; // A function pointer
    struct_21* field_0x3C;
    s32 field_0x40;
    s32 field_0x44;
    s32 current_lever_pull_time;
    s32 max_lever_pull_time;
    s32 model_pitch;
    u8 field_0x54[24];
    s32 activate;
    cv64_actor_settings_t* settings;
} actorLever;

extern actorLever*
actorLever_activate(s16 actor_ID, u16 variable_1, u32 activate);

cv64_interactuables_func_t interactuables_functions[] = {
    interactuables_init,
    interactuables_loop,
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
        // In the actor settings, the ID is stored + 1.
        // Substract -1 to get the actual ID
        self->table_index = settings->variable_1 - 1;
    } else {
        // Set array ID to -1 (invalid entry)
        self->table_index--;
    }
    if (ptr_PlayerData != NULL) {
        self->map_event_flag_ID =
            getMapEventFlagID(sys.SaveStruct_gameplay.map_ID);
        if (settings != NULL) {
            if (interactuables_settings_table[self->table_index].type ==
                ITEM_KIND_ITEM) {
                if (interactuables_settings_table[self->table_index]
                        .item_or_text_ID == ITEM_ID_WHITE_JEWEL) {
                    // Set save jewel number
                    self->event_flag = settings->variable_3;
                } else {
                    // Set item bitflag (variable_2 = upper bits, variable_3 -> lower bits)
                    self->event_flag =
                        settings->variable_3 + (settings->variable_2 << 0x10);
                }
            } else {
                // Text spots don't set bitflags, so doing self is useless
                self->event_flag =
                    settings->variable_3 + (settings->variable_2 << 0x10);
            }
        } else {
            // Extra empty "else" needed for matching
        }
        if ((interactuables_settings_table[self->table_index].type ==
             ITEM_KIND_ITEM) &&
            (interactuables_settings_table[self->table_index].item_or_text_ID !=
             ITEM_ID_WHITE_JEWEL)) {
            // Don't spawn the item if it has been picked up already
            // i.e. if the item's associated bitflag is set
            if ((self->event_flag != 0) &&
                // (0, self->event_flag) needed to avoid v0 / t8 regswap
                CHECK_EVENT_FLAGS(
                    self->map_event_flag_ID, (0, self->event_flag)
                )) {
                self->header.destroy(self);
                return;
            }
        }

        if (interactuables_settings_table[self->table_index].type ==
            ITEM_KIND_ITEM) {
            // Create and setup the item model
            item_model = modelInfo_createRootNode(
                FIG_TYPE_0400 | FIG_TYPE_HIERARCHY_NODE, D_8018CDE0[2]
            );
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
                interactuables_settings_table[self->table_index].item_or_text_ID
            );
            self->flags = item_appearence_settings->flags;
            if (item_appearence_settings->texture != 0xFF) {
                item_model->dlist =
                    item_appearence_settings->dlist | 0x40000000;
                item_model->texture = item_appearence_settings->texture;
                item_model->palette = item_appearence_settings->palette;
            } else {
                item_model->dlist = item_appearence_settings->dlist;
            }
            item_model->material_dlist = &ITEM_MATERIAL_DL;
            if (BITS_HAS(
                    interactuables_settings_table[self->table_index].flags,
                    ITEM_INVISIBLE
                )) {
                BITS_SET(item_model->type, ~0x7FFF);
            }

            if (BITS_HAS(self->flags, ITEM_VANISH)) {
                BITS_SET(item_model->flags, ITEM_INVISIBLE);
            } else {
                BITS_SET(
                    item_model->flags,
                    ITEM_INVISIBLE | TEXT_SPOT_IF_YES_ACTIVATE_LEVER
                );
            }

            CV64_COLOR_RGBA_TO_U32(item_model->primitive_color) = 0xFFFFFFFF;
            // Make all save jewels semi-transparent if not playing in a save file
            if ((interactuables_settings_table[self->table_index]
                     .item_or_text_ID == ITEM_ID_WHITE_JEWEL) &&
                (sys.contPak_file_no < 0)) {
                CV64_COLOR_RGBA_TO_U32(item_model->primitive_color) =
                    0xFFFFFF40;
            }
            CV64_COLOR_RGBA_TO_U32(self->primitive_color) =
                CV64_COLOR_RGBA_TO_U32(item_model->primitive_color);
            item_model->primitive_color.A =
                item_appearence_settings->transparency;
            item_model->size.x *= item_appearence_settings->size;
            item_model->size.y *= item_appearence_settings->size;
            item_model->size.z *= item_appearence_settings->size;

            if ((interactuables_settings_table[self->table_index]
                     .item_or_text_ID == ITEM_ID_AXE) ||
                (interactuables_settings_table[self->table_index]
                     .item_or_text_ID == ITEM_ID_CROSS)) {
                item_model->position.y += 3.2;
                self->position.y += 3.2;
                self->height += 3.2;
                item_model->angle.roll += 0x1000;
            }

            item_model->position.y += 0.1;
            self->trigger_X_size =
                interactuables_settings_table[self->table_index].trigger_size;
        }

        if ((interactuables_settings_table[self->table_index].type ==
             ITEM_KIND_TEXT_SPOT) &&
            (settings != NULL)) {
            self->position.x = settings->position.x;
            self->position.y = settings->position.y;
            self->position.z = settings->position.z;
            self->trigger_X_size = settings->variable_2;
            self->trigger_Z_size = settings->variable_3;
        }

        // The time it takes for the flash that appears over an item is selected
        // by randomly selecting a number between 120 and 150 frames
        // (4 and 5 seconds)
        self->time_when_flash_appears_over_item =
            (u16) ((*random_range)(30) + 120);
        ITEM_FADE_TIMER = 0;
        self->item_falling_height_multiplier = 0;
        self->pickableItemFlash_or_textbox.flash = NULL;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_loop.s")

// clang-format on

void interactuables_initCheck(interactuables* self) {
    interactuables_settings* settings =
        &interactuables_settings_table[self->table_index];
    mfds_state* textbox;
    contractMgr* contract;

    // If picking up an item...
    if (settings->type == ITEM_KIND_ITEM) {
        // Setup and display the item name textbox
        textbox = item_prepareTextbox(
            itemModelSettings_getEntryFromList(
                interactuables_settings_table[self->table_index].item_or_text_ID
            )
                ->item_ID
        );

        if (textbox == NULL)
            return;

        self->pickableItemFlash_or_textbox.textbox = (mfds_state*) textbox;

        // If picking up the contract, create `contractMgr`, which begins
        // the cutscene and warps you to Renon's shop
        if (interactuables_settings_table[self->table_index].item_or_text_ID ==
            ITEM_ID_THE_CONTRACT) {
            contract = (contractMgr*) (*object_createAndSetChild)(
                &self->header, MENU_CONTRACTMGR
            );
            contract->contract_item = self;
        }

        // If trying to pick up a White Jewel, freeze the players and all enemies in place
        // and begin reading its textbox. Don't actually pick it up
        if (interactuables_settings_table[self->table_index].item_or_text_ID ==
            ITEM_ID_WHITE_JEWEL) {
            sys.FREEZE_PLAYER = TRUE;
            sys.FREEZE_ENEMIES = TRUE;
            cameraMgr_setReadingTextState(sys.ptr_cameraMgr, TRUE);
            ITEM_FADE_TIMER = 0;
            settings = &interactuables_settings_table[self->table_index];
        }
    }

    // If checking a text spot...
    if (interactuables_settings_table[self->table_index].type ==
        ITEM_KIND_TEXT_SPOT) {
        if (BITS_HAS(
                interactuables_settings_table[self->table_index].flags, 4
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
                interactuables_settings_table[self->table_index].flags, 8
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
                    1
                );
                return;
            }
        }

        // clang-format off
        // Get the message associated to the text spot
        // This code is asinine LOL
        textbox = (BITS_HAS(interactuables_settings_table[self->table_index].flags, 0x10))
            ? map_getMessageFromPool(interactuables_settings_table[self->table_index].item_or_text_ID, 0)
            : map_getMessageFromPool(interactuables_settings_table[self->table_index].item_or_text_ID, 0);

        // Freeze the player and all enemies in place, then begin reading the message
        sys.FREEZE_PLAYER = TRUE, // comma needed for matching
        sys.FREEZE_ENEMIES = TRUE;
        // clang-format on

        if (textbox == NULL)
            return;

        self->pickableItemFlash_or_textbox.textbox = (mfds_state*) textbox;
        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, TRUE);
        ITEM_FADE_TIMER = 0;
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

#ifdef NON_MATCHING
// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_selectTextboxOption.s")
// clang-format on
#else
void interactuables_selectTextboxOption(interactuables* self) {
    saveGame* saveGameObj;

    if (interactuables_settings_table[self->table_index].type ==
        ITEM_KIND_ITEM) {
        if (interactuables_settings_table[self->table_index].item_or_text_ID ==
            ITEM_ID_WHITE_JEWEL) {
            mfds_state* textbox = self->pickableItemFlash_or_textbox.textbox;

            switch (textbox->textbox_option) {
                default:
                    break;
                case 0:
                    return;
                case 1:
                    saveGameObj = (saveGame*) object_createAndSetChild(
                        &self->header, MENU_SAVEGAME
                    ),
                    saveGameObj->save_crystal_number = (s16) self->event_flag;
                    break;
                case 2:
                    sys.FREEZE_PLAYER = FALSE, sys.FREEZE_ENEMIES = FALSE;
                    cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);
                    interactuables_stopInteraction(self);
                    (*object_curLevel_goToFunc)(
                        self->header.current_function,
                        &self->header.functionInfo_ID,
                        INTERACTUABLES_LOOP
                    );
                    return;
            }
        }
    }

    if (interactuables_settings_table[self->table_index].type ==
        (u32) ITEM_KIND_TEXT_SPOT) {
        if (interactuables_settings_table[self->table_index].flags & 0x10) {
            mfds_state* textbox = self->pickableItemFlash_or_textbox.textbox;

            switch (textbox->textbox_option) {
                default:
                    break;
                case 0:
                    return;
                case 1:
                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index]
                                .flags,
                            TEXT_SPOT_IF_YES_START_CUTSCENE
                        )) {
                        sys.FREEZE_PLAYER = FALSE, sys.FREEZE_ENEMIES = FALSE;
                        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);
                        sys.cutscene_ID =
                            interactuables_settings_table[self->table_index]
                                .cutscene_ID_or_actor_ID;
                    }

                    // Empty `if` needed for matching
                    if (1) {
                    }

                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index]
                                .flags,
                            TEXT_SPOT_IF_YES_SET_BITFLAG
                        )) {
                        SET_EVENT_FLAGS(
                            self->map_event_flag_ID,
                            interactuables_settings_table[self->table_index]
                                .event_flag
                        );
                    }

                    // Empty `if` needed for matching
                    if (1) {
                    }

                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index]
                                .flags,
                            TEXT_SPOT_IF_YES_ACTIVATE_LEVER
                        )) {
                        (*actorLever_activate)(
                            interactuables_settings_table[self->table_index]
                                .cutscene_ID_or_actor_ID,
                            interactuables_settings_table[self->table_index]
                                .actor_variable_1,
                            TRUE
                        );
                    }

                    if (BITS_HAS(
                            interactuables_settings_table[self->table_index]
                                .flags,
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
#endif

void interactuables_stopCheck(interactuables* self) {
    u32 temp[2];

    if (interactuables_settings_table[self->table_index].type ==
        ITEM_KIND_ITEM) {
        if (interactuables_settings_table[self->table_index].item_or_text_ID ==
            ITEM_ID_WHITE_JEWEL) {
            if (objectList_findFirstObjectByID(MENU_SAVEGAME) == NULL) {
                sys.FREEZE_PLAYER = FALSE;
                sys.FREEZE_ENEMIES = FALSE;

                cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);
                interactuables_stopInteraction(self);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.functionInfo_ID,
                    INTERACTUABLES_LOOP
                );
            }
        } else {
            if (self->pickableItemFlash_or_textbox.textbox ==
                (mfds_state*) -1) {
                interactuables_stopInteraction(self);
                (*object_curLevel_goToFunc)(
                    self->header.current_function,
                    &self->header.functionInfo_ID,
                    INTERACTUABLES_LOOP
                );

                return;
            }

            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
        }
    }

    if ((interactuables_settings_table[self->table_index].type ==
         ITEM_KIND_TEXT_SPOT) &&
        lensAreClosed()) {
        sys.FREEZE_PLAYER = FALSE;
        sys.FREEZE_ENEMIES = FALSE;
        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, FALSE);

        if (BITS_HAS(
                interactuables_settings_table[self->table_index].flags, 2
            )) {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
            return;
        }

        interactuables_stopInteraction(self);
        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.functionInfo_ID,
            INTERACTUABLES_LOOP
        );
    }
}

void interactuables_destroy(interactuables* self) {
    if (interactuables_settings_table[self->table_index].type ==
        ITEM_KIND_ITEM) {
        // If we picked the contract, remove it from the inventory and stop its interaction
        if (interactuables_settings_table[self->table_index].item_or_text_ID ==
            ITEM_ID_THE_CONTRACT) {
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
                    INTERACTUABLES_LOOP
                );
            }

            return;
        }

        if (self->event_flag != 0) {
            // Set the appropiate event flag, if the item is meant to set one
            SET_EVENT_FLAGS(self->map_event_flag_ID, self->event_flag);

            // Unlock the Special1 and Special2 rewards after picking them up
            if (interactuables_settings_table[self->table_index]
                    .item_or_text_ID == ITEM_ID_SPECIAL1) {
                BITS_SET(
                    sys.SaveStruct_gameplay.flags, SAVE_FLAG_HARD_MODE_UNLOCKED
                );
            }

            if (interactuables_settings_table[self->table_index]
                    .item_or_text_ID == ITEM_ID_SPECIAL2) {
                if (sys.SaveStruct_gameplay.character != REINHARDT) {
                    BITS_SET(
                        sys.SaveStruct_gameplay.flags,
                        SAVE_FLAG_HAVE_CARRIE_ALT_COSTUME
                    );
                } else {
                    BITS_SET(
                        sys.SaveStruct_gameplay.flags,
                        SAVE_FLAG_HAVE_REINHARDT_ALT_COSTUME
                    );
                }
            }
        }
    }

    self->header.destroy(self);
}

void interactuables_stopInteraction(interactuables* self) {
    self->pickableItemFlash_or_textbox.flash = NULL;
    ITEM_FADE_TIMER = 0;
    self->textbox_is_active = FALSE;
    self->interacting_with_interactuable = FALSE;
}
