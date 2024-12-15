/**
 * @file tou_turo.c
 *
 * Contains the code for objects exclusive to TOU TURO
 * (Room of Clocks)
 */

#include "cv64.h"
#include "sound.h"
#include "random.h"
#include "effect.h"
#include "objects/map/tou_turo/door.h"
#include "system_work.h"
#include "gfx/light.h"
#include <ultra64.h>

// clang-format off

cv64_ovl_touturo_door_func_t cv64_ovl_touturo_door_funcs[] = {
    cv64_ovl_touturo_door_init,
    cv64_ovl_touturo_door_loop
};

// TODO: `extern const u32` for the dlists
u32 cv64_ovl_touturo_door_dlists[] = {
    0x0600A300, // TOUTURO_DOOR_EXIT_DL
    0x0600AB00  // TOUTURO_DOOR_ENTRANCE_DL
};

cv64_ovl_touturo_door_exit_func_t cv64_ovl_touturo_door_exit_funcs[] = {
    cv64_ovl_touturo_door_exit_check_event_flags,
    StageProp_Loop
};

cv64_ovl_touturo_door_entrance_func_t cv64_ovl_touturo_door_entrance_funcs[] = {
    cv64_ovl_touturo_door_entrance_check_event_flags,
    cv64_ovl_touturo_door_entrance_close_door,
    StageProp_Loop
};

// clang-format on

const char cv64_ovl_touturo_unused_str[] = "ERROR P27TOBIRA : EFFECT SPAWN ERROR\n";

void cv64_ovl_touturo_door_entrypoint(cv64_ovl_touturo_door_t* self) {
    ENTER(self, cv64_ovl_touturo_door_funcs);
}

void cv64_ovl_touturo_door_init(cv64_ovl_touturo_door_t* self) {
    s32 unused;
    ActorConfig* settings = self->settings;
    Model* model;

    if (settings) {
    } // Needed for matching

    model = self->model = Model_createAndSetChild(FIG_TYPE_STANDALONE, map_lights[0]);

    if (model) {
    } // Needed for matching

    Actor_SetPosAndAngle(self, model);
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_APPLY_FOG_COLOR);

    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = cv64_ovl_touturo_door_dlists[TOU_TURO_DOOR_TYPE];

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;

    BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);

    self->map_actor_model  = getMapActorModelEntryFromArray(model->dlist, model->assets_file);
    model->map_actor_model = self->map_actor_model;

    self->close_time = 30;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_touturo_door_loop(cv64_ovl_touturo_door_t* self) {
    ActorConfig* settings = self->settings;
    Model* model          = self->model;

    if ((*actor_playerOutsideActorSpawnRadius)(
            self, settings->position.x, settings->position.y, settings->position.z
        )) {
        self->header.destroy(self);
        return;
    } else {
        model->primitive_color.integer = sys.primitive_color.integer;
        model->fog_color.integer       = sys.background_color.integer;
        if (TOU_TURO_DOOR_TYPE == TOU_TURO_EXIT_DOOR) {
            ENTER(self, cv64_ovl_touturo_door_exit_funcs);
        } else {
            ENTER(self, cv64_ovl_touturo_door_entrance_funcs);
        }
    }
}

void cv64_ovl_touturo_door_exit_check_event_flags(cv64_ovl_touturo_door_t* self) {
    Model* model = self->model;

    if (CHECK_EVENT_FLAGS(EVENT_FLAG_ID_CLOCK_TOWER, EVENT_FLAG_CLOCK_TOWER_DEFEATED_DEATH) ||
        CHECK_EVENT_FLAGS(EVENT_FLAG_ID_CLOCK_TOWER, EVENT_FLAG_CLOCK_TOWER_DEFEATED_ACTRISE)) {
        model->position.y = 35.0f;
    } else {
        model->position.y = 0.0f;
    }
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_touturo_door_entrance_check_event_flags(cv64_ovl_touturo_door_t* self) {
    Model* model = self->model;

    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_MISC_STAGES, EVENT_FLAG_MISC_STAGES_ENTERED_ROOM_OF_CLOCKS
        )) {
        model->position.y = 6.0f;
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, TOU_TURO_STAGE_PROP_LOOP
        );
    } else {
        SET_EVENT_FLAGS(EVENT_FLAG_ID_MISC_STAGES, EVENT_FLAG_MISC_STAGES_ENTERED_ROOM_OF_CLOCKS);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cv64_ovl_touturo_door_entrance_close_door(cv64_ovl_touturo_door_t* self) {
    s16 i;
    f32 rand_Z_pos;
    Effect* effect;
    Model* model = self->model;

    model->position.y -=
        (0.8166666666666667 * (((self->close_time / 30.0f) * self->close_time) / 30.0f));
    self->close_time++;

    if (model->position.y <= 6.0f) {
        model->position.y = 6.0f;

        // Create dust effects when the door closes
        for (i = 0; i < 6; i++) {
            rand_Z_pos = ((*rand_f32)() * 40.0f) - 20.0f;

            effect = (*createEffectObjectUnderEffectMgr)(EFFECT_ID_01, NULL, 0);

            if (effect != NULL) {
                (*effect_setMaxFrameSpeed)(effect, 3);
                (*effect_setPosition)(
                    effect,
                    model->position.x + 3.0f,
                    model->position.y + 1.0f,
                    model->position.z + rand_Z_pos,
                    8
                );
                (*effect_setScale)(effect, 0.3f, 0.2f, 0.3f, 8);
            } else {
                // Empty else needed for matching
                // ERROR P27TOBIRA : EFFECT SPAWN ERROR\n
            }
        }

        (*play_sound_in_position)(SD_TOU_TURO_DOOR_CLOSE, &model->position);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}
