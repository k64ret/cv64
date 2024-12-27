/**
 * @file fire.c
 *
 * The common decorative fire effect seeing above candles and other elements.
 */

#include "objects/effect/fire.h"

// clang-format off

FireFuncs Fire_functions[] = {
    Fire_Init,
    Fire_Loop,
    Fire_Destroy
};

// clang-format on

void Fire_Entrypoint(Fire* self) {
    ENTER(self, Fire_functions);
}

// https://decomp.me/scratch/sMEKL
#ifdef NON_MATCHING
void Fire_Init(Fire* self) {
    EffectVisualInfo* visual_info;
    EffectAnimationInfo* anim_info;
    Model* model;
    FireSparkles* sparkles;

    if (effect_init(self)) {
        (*effect_initParams)(self, EFFECT_ID_FIRE, ptr_effectMgr->display_camera, 0);
    }

    visual_info = self->visual_info;
    if (visual_info) {
    }
    visual_info->model = self->model = model = effect_getModel(self);

    if (model == NULL) {
        GO_TO_FUNC_NOW(self, Fire_functions, FIRE_DESTROY);
        return;
    }

    model->dlist       = FIG_APPLY_VARIABLE_TEXTURE_AND_PALETTE((u32) &FIRE_DLIST);
    model->assets_file = NI_COMMON_GAMEPLAY_EFFECTS;
    effect_updateGraphicParams(self);

    anim_info = &visual_info->anim_info;
    effectAnimationInfo_create(anim_info, 0);
    effectAnimationInfo_init(anim_info, model, visual_info->max_frame_speed, 1.0f);
    if (visual_info->flags & EFF_VISUAL_FLAG_NO_VARIABLE_TRANSPARENCY) {
        visual_info->anim_info.visual_flags &= ~EFF_ANIM_VISUAL_FLAG_VARIABLE_TRANSPARENCY;
    }

    effect_createPointLight(self);

    // Create the sparkles
    sparkles = (FireSparkles*) (*createEffectObject)(
        EFFECT_ID_FIRE_SPARKLES,
        NULL,
        EFF_VISUAL_FLAG_20000000 | EFF_VISUAL_FLAG_CREATE_MODEL_AND_SET_CHILD |
            EFF_VISUAL_FLAG_200000 | EFF_VISUAL_FLAG_LOOK_AT_CAMERA_YAW |
            EFF_VISUAL_FLAG_DONT_FADE_OUT_WHEN_MARKED_FOR_DELETION | EFF_VISUAL_FLAG_200,
        self
    );
    if (sparkles != NULL) {
        if (model->type & FIG_TYPE_DONT_ANIMATE) {
            (*effect_editVisualInfoFlags)(sparkles, EFF_VISUAL_FLAG_DONT_ANIMATE, SET_FLAGS);
        }
        (*effect_setPosition)(
            sparkles,
            model->position.x,
            model->position.y + (6.0f * (model->size.y * 10.0f)),
            model->position.z,
            POSITION_EQUAL_TO_VISUAL_INFO
        );
        (*effect_setScale)(
            sparkles, model->size.x, model->size.y, model->size.z, SIZE_EQUAL_TO_VISUAL_INFO
        );
        (*effect_setColor)(
            sparkles, (*effect_getColor)(self, EFF_COLOR_TYPE_PRIMITIVE), EFF_COLOR_TYPE_PRIMITIVE
        );
        (*effect_setColor)(
            sparkles,
            (*effect_getColor)(self, EFF_COLOR_TYPE_ENVIRONMENT),
            EFF_COLOR_TYPE_ENVIRONMENT
        );
        self->sparkles = sparkles;
    }

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Init.s")
#endif

// https://decomp.me/scratch/sMEKL
#ifdef NON_MATCHING
void Fire_Loop(Fire* self) {
    s32 should_despawn;
    FireSparkles* sparkles;
    EffectVisualInfo* visual_info;
    Model* model;

    should_despawn = effect_loop(self);
    if (should_despawn) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }

    sparkles    = self->sparkles;
    visual_info = self->visual_info;
    model       = visual_info->model;

    // Hide the sparkles if the fire effect is requested to be hidden
    if (sparkles != NULL) {
        if (FIG_IS_HIDDEN(model)) {
            (*effect_editVisualInfoFlags)(sparkles, EFF_VISUAL_FLAG_HIDE, SET_FLAGS);
        } else {
            (*effect_editVisualInfoFlags)(sparkles, EFF_VISUAL_FLAG_HIDE, REMOVE_FLAGS);
        }
    }
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/effect/fire/Fire_Loop.s")
#endif

void Fire_Destroy(Fire* self) {
    self->header.destroy(self);
}
