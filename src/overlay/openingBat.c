/**
 * @file openingBat.c
 *
 * Creates and initializes the bats seen in the opening cutscene
 * (the one with the camera moving around the castle).
 *
 * Note that the animation and movement of the bats is handled by
 * said cutscene's overlay.
 */

#include "objects/enemy/openingBat.h"
#include "system_work.h"

// clang-format off

// TODO: `extern const u32` for the dlists
hierarchy openingBat_hierarchy = {
    NI_ASSETS_FIRE_BAT,
    {
        { 0x06000C90, CREATE_NEXT_NODE, { 0, 45, 45 } },
        { 0x06000D80, CREATE_NEXT_NODE, { 45, 45, 44 } },
        { 0x06000DA8, DONT_CREATE_SIBLING, { 180, 0, 0 } },
        { 0x06000DD0, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 44, 45, -45 } },
        { 0x06000DF8, DONT_CREATE_SIBLING, { 180, 0, 0 } }
    }
};

Gfx openingBat_materialDlist[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_CULL_BOTH | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_CULL_BACK | G_FOG | G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_PASS2),
    gsSPEndDisplayList(),
};

openingBat_func_t openingBat_functions[] = {
    openingBat_createData,
    openingBat_init,
    openingBat_loop,
    openingBat_destroy
};

// clang-format on

void openingBat_entrypoint(openingBat* self) {
    ENTER(self, openingBat_functions);
}

void openingBat_createData(openingBat* self) {
    openingBatData* data;

    data       = (openingBatData*) (*fig_allocate)(FIG_TYPE_DATA);
    self->data = data;
    if (D_80092F50 < 68) {
        GO_TO_FUNC_NOW(self, openingBat_functions, OPENINGBAT_DESTROY);
    } else {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void openingBat_init(openingBat* self) {
    openingBatData* data = self->data;
    s32 temp1;
    modelLighting* lighting;
    cv64_model_inf_t* model;
    vec3f position;
    u16 variable_1;
    openingBatDataInner* inner = &data->inner;

    if ((*Actor_getPosAndVariable1)(self, &position, &variable_1) == FALSE) {
        GO_TO_FUNC_NOW(self, openingBat_functions, OPENINGBAT_DESTROY);
        return;
    }
    lighting        = (*modelLighting_create)(self);
    inner->lighting = lighting;
    if (lighting == NULL) {
        GO_TO_FUNC_NOW(self, openingBat_functions, OPENINGBAT_DESTROY);
        return;
    }
    model = (*modelInfo_buildHierarchy)(
        FIG_TYPE_HIERARCHY_NODE, lighting->model_light, &openingBat_hierarchy
    );
    self->model  = model;
    inner->model = model;
    if (model == NULL) {
        GO_TO_FUNC_NOW(self, openingBat_functions, OPENINGBAT_DESTROY);
        return;
    }
    model->dlist = FIG_APPLY_VARIABLE_TEXTURE_AND_PALETTE((u32) &OPENINGBAT_DLIST);
    model->type |= -FIG_TYPE_HIDE;
    model->material_dlist = (*osVirtualToPhysical)(openingBat_materialDlist);
    model->palette        = 0;
    model->position.x     = position.x;
    model->position.y     = position.y;
    model->position.z     = position.z;
    (*modelLighting_createList)(lighting, SIZE_AND_LIST_INDEX(sizeof(light_list_t), 0), NULL);
    (*modelLighting_createList)(
        lighting, SIZE_AND_LIST_INDEX(sizeof(point_light_list_t), 1), &model->position
    );
    (*animationMgr_create)(&inner->animMgr, OPENINGBAT_NUMBER_OF_LIMBS, 12, NULL, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void openingBat_loop(openingBat* self) {
    cv64_model_inf_t* model = self->model;

    model->type &= FIG_TYPE_SHOW;
    if (!(sys.cutscene_flags & CUTSCENE_FLAG_PLAYING)) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void openingBat_destroy(openingBat* self) {
    self->header.destroy(self);
}
