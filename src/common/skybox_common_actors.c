/**
 * @file skybox_common_actors.c
 *
 * This file contains code for three scrapped skybox-related actors.
 *
 * We know they were scrapped because these objects despawn the moment their code starts running, as
 * their `entrypoint` function just calls the destroy function. All of these objects could have
 * appeared in the first 6 maps, but `commonMoon`, the only object with non-NULL addresses on its
 * assets array, only has assets assigned for the Villa Foyer and Hallway maps, so that object can
 * only work on those maps.
 *
 * - object_0172:     Unknown static element. The code assigns the actor with a yellow-ish color, so
 *                    it may have been the sun? A sun is only seen in the ending cutscenes, but that
 *                    one is part of the map objects overlay for the `ENDING` map.
 *
 * - commonMoon:      A moon that was meant to show up at night in the outside windows of Villa
 *                    Foyer and Hallway. This one is actually spawned in those maps, but it's
 *                    destroyed immediatly. Previously seen in prerelease screenshots from a
 *                    magazine. Note that this moon is different from the one that shows up normally
 *                    during gameplay. That one is part of the `skybox` object.
 *
 * - object_8015C368: Unknown element that would have moved sideways, either forwards or backwards.
 *                    This object doesn't have an ID.
 */

#include "objects/map/object_0172.h"
#include "objects/map/commonMoon.h"
#include "objects/map/object_8015C368.h"
#include "system_work.h"

// clang-format off

u32 obj0172_dlists[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

// TODO: `extern const u32` for the dlists
u32 commonMoon_dlists[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    0x0601C918,     // BEKKAN 1F
    0x06024EF0      // BEKKAN 2F
};

u32* obj8015C368_dlists[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

obj0172Funcs obj0172_functions[] = {
    obj0172_init,
    obj0172_loop
};

commonMoon_func_t commonMoon_functions[] = {
    commonMoon_init,
    commonMoon_main
};

commonMoon_func_t commonMoon_main_functions[] = {
    commonMoon_main_invisible,
    commonMoon_main_appear,
    commonMoon_main_visible,
    commonMoon_main_disappear
};

obj8015C368_func_t obj8015C368_functions[] = {
    obj8015C368_init,
    obj8015C368_loop
};

// clang-format on

void obj0172_entrypoint(object_0172* self) {
    self->header.destroy(self);
}

void obj0172_init(object_0172* self) {
    s32 temp;
    Model* model;

    model = Model_createAndSetChild(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HIERARCHY_NODE, map_lights[0]
    );
    self->model = model;
    if (model) {
    }
    Actor_SetPosAndAngle(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = obj0172_dlists[sys.SaveStruct_gameplay.map];
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = RGBA(192, 192, 128, 255);
    model->size.x                  = 0.05f;
    model->size.y                  = 0.05f;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void obj0172_loop(object_0172* self) {
    ActorConfig* settings = self->settings;

    if (actor_playerOutsideActorSpawnRadius(
            self, settings->position.x, settings->position.y, settings->position.z
        )) {
        self->header.destroy(self);
    }
}

void commonMoon_entrypoint(commonMoon* self) {
    self->header.destroy(self);
}

void commonMoon_init(commonMoon* self) {
    s32 temp1;
    Model* model;
    s32 temp2;
    s32 temp3;

    model = Model_createAndSetChild(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HIERARCHY_NODE, map_lights[0]
    );
    self->model = model;
    if (model) {
    }
    Actor_SetPosAndAngle(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = commonMoon_dlists[sys.SaveStruct_gameplay.map];
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = RGBA(128, 128, 128, 255);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );

    // Make the moon invisible if daytime.
    if ((sys.SaveStruct_gameplay.hour >= 6) && (sys.SaveStruct_gameplay.hour < 18)) {
        self->transparency       = 0;
        model->primitive_color.a = 0;
        return;
    }

    // Make the moon invisible if it's a new moon.
    /**
     * @bug The game should check for `moonVisibilityVars.moonVisibility`, but
     * `moonVisibilityVars.integer` is checked instead, which yields the wrong results, as it's
     * including the value of `moonVisibilityVars.dontUpdateMoonVisibility` as well.
     */
    if (moonVisibilityVars.integer == MOON_VISIBILITY_NEW_MOON) {
        self->transparency       = 0;
        model->primitive_color.a = 0;
        return;
    }

    // Make the moon visible during regular nights.
    self->transparency       = 192 << 8;
    model->primitive_color.a = 192;

    /**
     * @bug Since the moon is supposed to become visible, the code likely attempted to branch to
     * function `commonMoon_main_visible` here. However, `object_curLevel_goToFunc` is used, instead
     * of `object_nextLevel_goToFunc`, so the game will try accessing a third function in
     * `commonMoon_functions`, rather than in `commonMoon_main_functions`, which is where
     * `commonMoon_main_visible` is.
     *
     * `commonMoon_functions` only has two entries, so this will make the game read out of bounds,
     * and branch into `commonMoon_main_invisible` without going through `commonMoon_main` first.
     *
     * At this point, when function `commonMoon_main_disappear` is accessed, the object will go back
     * to `commonMoon_init` and initialize another moon model, plus the moon is not able to be
     * despawned by getting far away from it most of the time, as
     * `actor_playerOutsideActorSpawnRadius` is only called from `commonMoon_main`, which normally
     * gets skipped due to the bug.
     *
     * Not only that, but the moon's transparency won't be updated properly during day / night
     * transitions most of the time, since the transparency value is set in `commonMoon_main` as
     * well.
     */
    (*object_curLevel_goToFunc)(
        self->header.current_function, &self->header.function_info_ID, COMMON_MOON_MAIN_VISIBLE
    );
}

void commonMoon_main(commonMoon* self) {
    Model* model = self->model;

    if (actor_playerOutsideActorSpawnRadius(
            self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
    } else {
        ENTER(self, commonMoon_main_functions);
        model->primitive_color.a = self->transparency >> 8;
    }
}

void commonMoon_main_invisible(commonMoon* self) {
    /**
     * @bug The game should check for `moonVisibilityVars.moonVisibility`, but
     * `moonVisibilityVars.integer` is checked instead, which yields the wrong results, as it's
     * including the value of `moonVisibilityVars.dontUpdateMoonVisibility` as well.
     */
    if ((sys.SaveStruct_gameplay.hour >= 18) &&
        (moonVisibilityVars.integer == MOON_VISIBILITY_NIGHT)) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void commonMoon_main_appear(commonMoon* self) {
    self->transparency += 0x0147; // Actual transparency gets added up +1
    if (self->transparency >= ((192 << 8) | 1)) {
        self->transparency = 192 << 8;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void commonMoon_main_visible(commonMoon* self) {
    if ((sys.SaveStruct_gameplay.hour >= 6) && (sys.SaveStruct_gameplay.hour < 18)) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void commonMoon_main_disappear(commonMoon* self) {
    self->transparency -= 0x0147; // Actual transparency gets substracted -1
    if (self->transparency < 0) {
        self->transparency = 0;
        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            COMMON_MOON_MAIN_INVISIBLE
        );
    }
}

void obj8015C368_entrypoint(object_8015C368* self) {
    self->header.destroy(self);
}

void obj8015C368_init(object_8015C368* self) {
    ActorConfig* settings = self->settings;
    Model* model;

    model = Model_createAndSetChild(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HIERARCHY_NODE, map_lights[0]
    );
    self->model = model;
    if (model) {
    }
    Actor_SetPosAndAngle(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist = obj8015C368_dlists[sys.SaveStruct_gameplay.map][settings->variable_1 & 0xFF];
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = sys.background_color.integer;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void obj8015C368_loop(object_8015C368* self) {
    Model* model = self->model;
    ActorConfig* settings;

    model->primitive_color.integer = sys.background_color.integer;
    if (actor_playerOutsideActorSpawnRadius(
            self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
    }

    settings = self->settings;
    if (BITS_HAS(settings->variable_1, 0xFF)) {
        model->position.x += 1.0;
        if (((f32) settings->position.x + 32.0) < model->position.x) {
            model->position.x = settings->position.x;
        }
    } else {
        model->position.x -= 1.0;
        if ((model->position.x) < ((f32) settings->position.x - 32.0)) {
            model->position.x = settings->position.x;
        }
    }
}
