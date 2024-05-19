/**
 * @file effect_manager.c
 *
 * Initializes the `effectMgr` object, which serves as a parent and manager
 * that is common to most effects currently spawned.
 */

#include "cv64.h"
#include "objects/effect/effect_manager.h"

// clang-format off

cv64_effectMgr_func_t effectMgr_functions[] = {
    effectMgr_init,
    effectMgr_loop
};

// clang-format on

effectMgr* ptr_effectMgr;

void effectMgr_entrypoint(effectMgr* self) {
    ENTER(self, effectMgr_functions);
}

void effectMgr_init(effectMgr* self) {
    self->display_camera =
        modelInfo_createAndSetChild(FIG_TYPE_HIERARCHY_ROOT, common_camera_game_view);
    ptr_effectMgr = self;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void effectMgr_loop(effectMgr* self) {}

void func_8005AF8C() {}

void func_8005AF94() {}
