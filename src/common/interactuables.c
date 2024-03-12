#include "cv64.h"
#include "actor.h"
#include "effect.h"
#include "gfx/camera.h"
#include "gfx/struct_47.h"
#include "objects/cutscene/interactuables.h"
#include "objects/menu/contractMgr.h"
#include "objects/player/player.h"
#include "random.h"
#include "system_work.h"

extern f64 D_8018AB60_10DD50;
extern f64 D_8018AB68_10DD58;

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
                (sys.SaveStruct_gameplay.event_flags[self->map_event_flag_ID] &
                 (0, self->event_flag
                 ) // (0, self->event_flag) needed to avoid v0 / t8 regswap
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
            // item_model->material_dlist = &ITEM_MATERIAL_DL;
            item_model->material_dlist = ITEM_MATERIAL_DL;
            if (interactuables_settings_table[self->table_index].flags &
                0x800) {
                item_model->type |= ~0x7FFF;
            }
            if (self->flags & 1) {
                item_model->flags |= 0x800;
            } else {
                item_model->flags |= 0x840;
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
                item_model->position.y += D_8018AB60_10DD50;
                self->position.y += D_8018AB60_10DD50;
                self->height += D_8018AB60_10DD50;
                item_model->angle.roll += 0x1000;
            }

            item_model->position.y += D_8018AB68_10DD58;
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

        self->pickableItemFlash_or_textbox.flash = (pickableItemFlash*) textbox;
        cameraMgr_setReadingTextState(sys.ptr_cameraMgr, TRUE);
        ITEM_FADE_TIMER = 0;
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_selectTextboxOption.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_stopCheck.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_destroy.s")

// clang-format on

void interactuables_stopInteraction(interactuables* self) {
    self->pickableItemFlash_or_textbox.flash = NULL;
    ITEM_FADE_TIMER = 0;
    self->textbox_is_active = FALSE;
    self->interacting_with_interactuable = FALSE;
}
