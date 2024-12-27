/**
 * @file object_017C.c
 *
 * This is an unused object meant for Tower of Execution.
 *
 * It only has code to display a model, which we don't know the address of,
 * as its pointer was NULL'd out, so we can't tell how it looked like.
 */

#include "objects/map/object_017C.h"
#include "system_work.h"

// clang-format off

u32 obj017C_dlists_shokei_tou[] = {
    NULL
};

// Each entry points to one array of display list pointers per map
u32* obj017C_dlists[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &obj017C_dlists_shokei_tou,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

obj017CFuncs obj017C_functions[] = {
    obj017C_Init,
    obj017C_Loop
};

// clang-format on

void obj017C_Entrypoint(object_017C* self) {
    ENTER(self, obj017C_functions);
}

void obj017C_Init(object_017C* self) {
    ActorConfig* settings;
    Model* model;

    settings    = self->settings;
    model       = Model_createAndSetChild(FIG_TYPE_HIERARCHY_NODE, map_lights[0]);
    self->model = model;
    if (1) {
    }
    Actor_SetPosAndAngle(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = obj017C_dlists[sys.SaveStruct_gameplay.map][settings->variable_1];

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void obj017C_Loop(object_017C* self) {
    Model* model = self->model;

    if (actor_playerOutsideActorSpawnRadius(
            self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
    }
}
