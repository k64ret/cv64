/**
 * @file rose.c
 *
 * Contains the code for objects exclusive to ROSE
 * (Rosa / Actriese Fan Room)
 */

#include "objects/map/rose/rose.h"
#include "actor.h"
#include "gfx/figure.h"
#include "gfx/light.h"
#include "objects/player/player.h"
#include "random.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

cv64_ovl_rose_ventilator_func_t cv64_ovl_rose_ventilator_funcs[] = {
    cv64_ovl_rose_ventilator_init,
    cv64_ovl_rose_ventilator_loop
};

cv64_ovl_rose_door_func_t cv64_ovl_rose_door_funcs[] = {
    cv64_ovl_rose_door_init,
    cv64_ovl_rose_door_loop
};

cv64_ovl_rose_door_func_t cv64_ovl_rose_door_state_funcs[] = {
    cv64_ovl_rose_door_state_startClosing,
    cv64_ovl_rose_door_state_closing,
    cv64_ovl_rose_door_state_idle
};

// clang-format on

const char cv64_ovl_rose_unused_str[] = "VENTILATOR : Can't allocate F3D.\n";

void cv64_ovl_rose_ventilator_entrypoint(cv64_ovl_rose_ventilator_t* self) {
    ENTER(self, cv64_ovl_rose_ventilator_funcs);
}

void cv64_ovl_rose_ventilator_init(cv64_ovl_rose_ventilator_t* self) {
    cv64_ovl_rose_ventilator_cfg_t* speed_settings = &self->speed_settings;
    Model* model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    u32 unused;

    if (model == NULL) {
        // VENTILATOR : Can't allocate F3D.\n
        self->header.destroy(self);
    } else {
        self->model        = model;
        model->dlist       = &ROSE_VENTILATOR_DL;
        model->assets_file = MAP_ASSETS_FILE_ID;
        BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_APPLY_FOG_COLOR);
        model->primitive_color.integer = sys.primitive_color.integer;
        model->fog_color.integer       = sys.background_color.integer;
        (*Model_setMapActorModelNoCollision)(model, &ROSE_VENTILATOR_DL);
        speed_settings->current_speed = speed_settings->max_speed =
            BITS_MASK((*rand)(), 0xFFF) + 16;
        speed_settings->time_until_changing_max_speed = BITS_MASK((*rand)(), 0x1FF) + 30;
        (*Actor_SetPosAndAngle)(self, model);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cv64_ovl_rose_ventilator_loop(cv64_ovl_rose_ventilator_t* self) {
    Model* model                                   = self->model;
    cv64_ovl_rose_ventilator_cfg_t* speed_settings = &self->speed_settings;

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    if ((*actor_playerOutsideActorSpawnRadius)(
            self, model->position.x, model->position.y, model->position.z
        )) {
        // clang-format off
        /* @bug If the player is far away enough from the ventilator, it will try to go to the next function.
                However, `cv64_ovl_rose_ventilator_funcs` only has two functions. This will make the game
                read out of bounds into `cv64_ovl_rose_door_funcs` and essentially turn the current
                ventilator actor into a door.

                One of the side-effects is that the ventilator model will not be destroyed, so multiple ventilator
                models can be created, until `figures_array` is full.

                In practice this will never happen because the spawn radius for the ventilator is larger than the
                map itself, so there's no way to get far away enough from the ventilator to trigger this bug.

                The devs probably intended to create a destroy function specific to the ventilator actor,
                and then placing it into `cv64_ovl_rose_ventilator_funcs`, but no such function exists
                in the final game.
        */
        // clang-format on
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    } else {
        model->angle.pitch -= speed_settings->current_speed;
        if (speed_settings->current_speed < speed_settings->max_speed) {
            speed_settings->current_speed += 17;
        } else if (speed_settings->max_speed < speed_settings->current_speed) {
            speed_settings->current_speed -= 17;
        }
        speed_settings->time_until_changing_max_speed--;
        if (speed_settings->time_until_changing_max_speed == 0) {
            speed_settings->max_speed                     = BITS_MASK((*rand)(), 0xFFF) + 16;
            speed_settings->time_until_changing_max_speed = BITS_MASK((*rand)(), 0x1FF) + 30;
        }
    }
}

void cv64_ovl_rose_door_entrypoint(cv64_ovl_rose_door_t* self) {
    ENTER(self, cv64_ovl_rose_door_funcs);
}

void cv64_ovl_rose_door_init(cv64_ovl_rose_door_t* self) {
    MapActorModel* map_actor_model;
    ActorConfig* settings                     = self->settings;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    Model* model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);

    self->model = model;
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = &ROSE_DOOR_DL;
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_APPLY_FOG_COLOR);
    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);
    map_actor_model        = (*getMapActorModelEntryFromArray)(model->dlist, model->assets_file);
    model->map_actor_model = map_actor_model;
    self->map_actor_model  = map_actor_model;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
    height_settings->initial_height = model->position.y;
    height_settings->height         = 25.0f;
    height_settings->closing_speed  = 0.0f;
    model->position.y               = height_settings->height + height_settings->initial_height;
    if (ROSE_DOOR_DONT_CLOSE) {
        (*object_nextLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, ROSE_DOOR_STATE_IDLE
        );
    }
}

void cv64_ovl_rose_door_loop(cv64_ovl_rose_door_t* self) {
    Model* model                              = self->model;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;

    if ((*actor_playerOutsideActorSpawnRadius)(
            self, model->position.x, model->position.y, model->position.z
        ) != FALSE) {
        self->header.destroy(self);
    } else {
        ENTER(self, cv64_ovl_rose_door_state_funcs);
        model->position.y = height_settings->initial_height + height_settings->height;
    }
}

void cv64_ovl_rose_door_state_startClosing(cv64_ovl_rose_door_t* self) {
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    Model* model                              = self->model;

    if ((*checkIfOutsideEntityIsInsideMainEntityRadius)(
            model, ptr_PlayerData->visualData.model, 15.0f, AXIS_Z
        ) == FALSE) {
        if (sys.SaveStruct_gameplay.character == REINHARDT) {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSING, &model->position, 0.5f);
        } else {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSING, &model->position, 1.0f);
        }
        // Cleaner version
        // (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSING,
        // &model->position,
        // ((sys.SaveStruct_gameplay.character == REINHARDT) ? 0.5f : 1.0f));
        height_settings->closing_speed = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cv64_ovl_rose_door_state_closing(cv64_ovl_rose_door_t* self) {
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    Model* model                              = self->model;

    if (height_settings->closing_speed < 0.4166666666666667) {
        height_settings->closing_speed += 0.01388888888888889;
    }
    height_settings->height -= height_settings->closing_speed;
    if (height_settings->height < 0.0) {
        (*play_sound)(STOP_SOUND(SD_ROSE_DOOR_CLOSING));
        if (sys.SaveStruct_gameplay.character == REINHARDT) {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSE, &model->position, 0.5f);
        } else {
            (*play_sound_in_position_and_set_volume)(SD_ROSE_DOOR_CLOSE, &model->position, 1.0f);
        }
        height_settings->height = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cv64_ovl_rose_door_state_idle(cv64_ovl_rose_door_t* self) {}
