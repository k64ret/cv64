/**
 * @file konami_kcek_logos.c
 *
 * Handles the Konami / KCEK logo screen
 */

#include "objects/engine/konami_kcek_logos.h"
#include "cv64.h"
#include "gamestate.h"
#include "gfx/camera.h"
#include "gfx/figure.h"
#include "system_work.h"

cv64_ovl_konamilogo_func_t cv64_ovl_konamilogo_funcs[] = {
    cv64_ovl_konamilogo_init,
    cv64_ovl_konamilogo_fade_in,
    cv64_ovl_konamilogo_wait,
    cv64_ovl_konamilogo_fade_out,
    cv64_ovl_konamilogo_kcek_fade_in,
    cv64_ovl_konamilogo_kcek_wait,
    cv64_ovl_konamilogo_kcek_fade_out,
    object_doNothing
};

void cv64_ovl_konamilogo_entrypoint(cv64_ovl_konamilogo_t* self) {
    ENTER(self, cv64_ovl_konamilogo_funcs);
}

void cv64_ovl_konamilogo_check_btn_press(cv64_ovl_konamilogo_t* self) {
    if (CONT_ALL_BTNS_PRESSED(START_BUTTON | RECENTER_BUTTON)) {
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, KONAMILOGO_KCEK_WAIT
        );
    }
}

void cv64_ovl_konamilogo_init(cv64_ovl_konamilogo_t* self) {
    Model* model = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, common_camera_HUD);

    self->model                  = model;
    model->dlist                 = &KONAMI_LOGO_DL;
    model->assets_file           = NI_ASSETS_KONAMI_AND_KCEK_LOGOS;
    model->size.x                = 0.9975f;
    model->size.y                = 1.005f;
    sys.background_color.integer = RGBA(0, 0, 0, 255);
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = RGBA(255, 255, 255, 0);

    GO_TO_NEXT_FUNC_NOW(self, cv64_ovl_konamilogo_funcs);
}

void cv64_ovl_konamilogo_fade_in(cv64_ovl_konamilogo_t* self) {
    Model* model = self->model;

    if (model->primitive_color.a < 243) {
        model->primitive_color.a += 12;
    } else {
        model->primitive_color.a = 255;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
    sys.background_color.r = model->primitive_color.a;
    sys.background_color.g = model->primitive_color.a;
    sys.background_color.b = model->primitive_color.a;
    cv64_ovl_konamilogo_check_btn_press(self);
}

void cv64_ovl_konamilogo_wait(cv64_ovl_konamilogo_t* self) {
    s32 timer = self->header.current_function[self->header.function_info_ID].timer;

    if (timer >= 169) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
        timer = self->header.current_function[self->header.function_info_ID].timer;
    }
    if (timer >= 21) {
        cv64_ovl_konamilogo_check_btn_press(self);
    }
}

void cv64_ovl_konamilogo_fade_out(cv64_ovl_konamilogo_t* self) {
    Model* model = self->model;

    if (model->primitive_color.a >= 10) {
        model->primitive_color.a -= 9;
    } else {
        model->primitive_color.a = 0;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
    cv64_ovl_konamilogo_check_btn_press(self);
}

void cv64_ovl_konamilogo_kcek_fade_in(cv64_ovl_konamilogo_t* self) {
    Model* model = self->model;

    model->size.x = 0.995f;
    model->dlist  = &KCEK_LOGO_DL;
    if (model->primitive_color.a < 252) {
        model->primitive_color.a += 3;
    } else {
        model->primitive_color.a = 255;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
    cv64_ovl_konamilogo_check_btn_press(self);
}

void cv64_ovl_konamilogo_kcek_wait(cv64_ovl_konamilogo_t* self) {
    Model* model = self->model;

    model->size.x = 0.995f;
    if (model->primitive_color.a < 252) {
        model->primitive_color.a += 3;
    } else {
        model->primitive_color.a = 255;
    }
    model->dlist = &KCEK_LOGO_DL;
    if ((s32) self->header.current_function[self->header.function_info_ID].timer >= 97) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cv64_ovl_konamilogo_kcek_fade_out(cv64_ovl_konamilogo_t* self) {
    Model* model = self->model;

    model->dlist = &KCEK_LOGO_DL;
    if (model->primitive_color.a >= 13) {
        model->primitive_color.a -= 12;
    } else {
        model->primitive_color.a = 0;
        (*gamestate_change)(GAMESTATE_INTRO_CUTSCENE);
    }
    sys.background_color.r = model->primitive_color.a;
    sys.background_color.g = model->primitive_color.a;
    sys.background_color.b = model->primitive_color.a;
}
