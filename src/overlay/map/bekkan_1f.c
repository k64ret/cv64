/**
 * @file bekkan_1f.c
 *
 * Contains the code for objects exclusive to BEKKAN 1F
 * (Villa Foyer)
 *
 * - Bekkan1FSquare: This object consists of a textureless square with no functionality
 *                   other than displaying its model. Two of these are located behind the clouds
 *                   in the room connecting the foyer with the rose garden, next to the entrance
 *                   and exit doors.
 *
 * - DecorativeChandelier: This object is unused, and it just renders an unsolid chandelier model.
 *                         Note that the chandelier from the foyer is part of another object entirely.
 */

#include "objects/map/bekkan_1f/decorative_chandelier.h"
#include "objects/map/bekkan_1f/square.h"
#include "gfx/figure.h"
#include "system_work.h"

// clang-format off

Bekkan1FSquareFuncs Bekkan1FSquare_functions[] = {
    Bekkan1FSquare_Init,
    Bekkan1FSquare_PauseTransformations,
    Bekkan1FSquare_Loop
};

DecorativeChandelierFuncs DecorativeChandelier_functions[] = {
    DecorativeChandelier_Init,
    DecorativeChandelier_PauseTransformations,
    StageProp_Loop,
    StageProp_Destroy
};

// clang-format on

void Bekkan1FSquare_Entrypoint(Bekkan1FSquare* self) {
    ENTER(self, Bekkan1FSquare_functions);
}

void Bekkan1FSquare_Init(Bekkan1FSquare* self) {
    Model* model;

    model       = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    self->model = model;
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = &BEKKAN_1F_SQUARE_DL;
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = sys.background_color.integer;
    (*Model_setMapActorModelNoCollision)(model, &BEKKAN_1F_SQUARE_DL);

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void Bekkan1FSquare_PauseTransformations(Bekkan1FSquare* self) {
    Model* model;

    model = self->model;
    BITS_SET(model->flags, FIG_FLAG_PAUSE_TRANSFORMATIONS);
    (*Figure_UpdateMatrices)(model);

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void Bekkan1FSquare_Loop(Bekkan1FSquare* self) {
    Model* model;

    model = self->model;
    if ((*actor_playerOutsideActorSpawnRadius)(
            self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
        return;
    }
    model->primitive_color.integer = sys.background_color.integer;
}

void DecorativeChandelier_Entrypoint(DecorativeChandelier* self) {
    ENTER(self, DecorativeChandelier_functions);
}

void DecorativeChandelier_Init(DecorativeChandelier* self) {
    s32 temp;
    Model* model;

    // Prepare decoration model
    model = (*Model_createAndSetChild)(
        FIG_TYPE_STANDALONE | FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE, map_lights[0]
    );
    self->decoration = model;
    if (1) {
    }
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = &BEKKAN_1F_CHANDELIER_DECORATION_DL;
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_APPLY_FOG_COLOR);
    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    (*Model_setMapActorModelNoCollision)(model, &BEKKAN_1F_CHANDELIER_DECORATION_DL);

    // Prepare pendant model
    model         = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    self->pendant = model;
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = &BEKKAN_1F_CHANDELIER_PENDANT_DL;
    BITS_SET(
        model->flags,
        FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_APPLY_FOG_COLOR | FIG_FLAG_LOOK_AT_CAMERA_YAW
    );
    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    (*Model_setMapActorModelNoCollision)(model, &BEKKAN_1F_CHANDELIER_PENDANT_DL);

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void DecorativeChandelier_PauseTransformations(DecorativeChandelier* self) {
    Model* decoration_model;

    decoration_model = self->decoration;
    BITS_SET(decoration_model->flags, FIG_FLAG_PAUSE_TRANSFORMATIONS);

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}
