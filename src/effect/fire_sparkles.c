/**
 * @file fire_sparkles.c
 *
 * Fire sparkles, usually used in conjuction with the `Fire` effect.
 */

#include "objects/effect/fire_sparkles.h"
#include <ultra64.h>

// clang-format off

Gfx FireSparkles_material_dlist[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, TEXEL1, PRIMITIVE_ALPHA, TEXEL1, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, ENVIRONMENT, 0),
    gsSPEndDisplayList(),
};

FireSparklesFuncs FireSparkles_functions[] = {
    FireSparkles_Init,
    FireSparkles_Loop,
    FireSparkles_Destroy
};

// clang-format on

void FireSparkles_Entrypoint(FireSparkles* self) {
    ENTER(self, FireSparkles_functions);
}

void FireSparkles_Init(FireSparkles* self) {
    EffectVisualInfo* visual_info;
    EffectAnimationInfo* anim_info;
    Model* model;

    if (effect_init(self)) {
        (*effect_initParams)(self, EFFECT_ID_FIRE_SPARKLES, ptr_effectMgr->display_camera, 0);
    }

    visual_info        = self->visual_info;
    visual_info->model = self->model = model = effect_getModel(self);

    if (1) {
        if (model == NULL) {
            GO_TO_FUNC_NOW(self, FireSparkles_functions, FIRE_SPARKLES_DESTROY);
            return;
        }

        model->material_dlist = (*osVirtualToPhysical)(FireSparkles_material_dlist);
        model->dlist          = FIG_APPLY_VARIABLE_TEXTURE_AND_PALETTE((u32) &FIRE_SPARKLES_DLIST);
        model->assets_file    = NI_COMMON_GAMEPLAY_EFFECTS;
        effect_updateGraphicParams(self);

        anim_info = &visual_info->anim_info;
        effectAnimationInfo_create(anim_info, 0);
        effectAnimationInfo_init(anim_info, model, visual_info->max_frame_speed, 1.0f);
        if (visual_info->flags & EFF_VISUAL_FLAG_NO_VARIABLE_TRANSPARENCY) {
            visual_info->anim_info.visual_flags &= ~EFF_ANIM_VISUAL_FLAG_VARIABLE_TRANSPARENCY;
        }

        effect_createPointLight(self);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void FireSparkles_Loop(FireSparkles* self) {
    s32 should_despawn = effect_loop(self);

    if (should_despawn) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void FireSparkles_Destroy(FireSparkles* self) {
    self->header.destroy(self);
}
