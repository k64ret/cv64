/**
 * File: konami_kcek_logos.c
 * Description: Handles the Konami / KCEK logo screen
 * Associated objects: 0x000E
 *
 * osMapTLB'd? = No
 * Entrypoint address   = 0x801CFCD0
 * Associated files ptr = 0x800958C0
 * Associated files:
 *   0x6B4FC0 - 0x6B5480 (Overlay)
 */

#include "objects/engine/gamestates/konami_kcek_logos.h"
#include "cv64.h"
#include "gamestate.h"
#include "gfx/camera.h"
#include "system_work.h"
#include <ultra64.h>

void cv64_konamilogo_entrypoint(cv64_ovl_konamilogo_t* self) {
    ENTER(self, cv64_konamilogo_funcs);
}

void cv64_konamilogo_check_btn_press(cv64_ovl_konamilogo_t* self) {
    void (*ptr_object_curLevel_goToFunc)(u16[], s16*, s32) =
        object_curLevel_goToFunc;

    if ((sys.controllers[0].buttons_pressed |
         sys.controllers[1].buttons_pressed |
         sys.controllers[2].buttons_pressed |
         sys.controllers[3].buttons_pressed) &
        (START_BUTTON | RECENTER_BUTTON)) {
        ptr_object_curLevel_goToFunc(self->header.current_function,
                                     &self->header.functionInfo_ID,
                                     KONAMILOGO_KCEK_WAIT);
    }
}

void cv64_konamilogo_init(cv64_ovl_konamilogo_t* self) {
    cv64_model_inf_t* model;
    cv64_object_func_inf_t* curFunc;

    cv64_model_inf_t* (*ptr_modelInfo_createRootNode)(u32, void*) =
        modelInfo_createRootNode;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    model = ptr_modelInfo_createRootNode(0x10, common_cameras_array.HUD);
    self->model = model;
    model->dlist = &KONAMI_LOGO_DL;
    model->assets_file_ID = 0x5D;
    model->size.x = 0.9975f;
    model->size.y = 1.005f;
    CV64_COLOR_RGBA_TO_U32(sys.background_color) = 0x000000FF; // Black (opaque)
    model->flags |= 0x800;
    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        0xFFFFFF00; // White (transparent)

    GO_TO_NEXT_FUNC(self, cv64_konamilogo_funcs, curFunc,
                    ptr_object_curLevel_goToNextFuncAndClearTimer);
}

void cv64_konamilogo_fade_in(cv64_ovl_konamilogo_t* self) {
    cv64_model_inf_t* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    if (model->primitive_color.A < 0xF3) {
        model->primitive_color.A += 0x0C;
    } else {
        model->primitive_color.A = 0xFF;
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            self->header.current_function, &self->header.functionInfo_ID);
    }
    sys.background_color.R = model->primitive_color.A;
    sys.background_color.G = model->primitive_color.A;
    sys.background_color.B = model->primitive_color.A;
    cv64_konamilogo_check_btn_press(self);
}

void cv64_konamilogo_wait(cv64_ovl_konamilogo_t* self) {
    s32 timer =
        self->header.current_function[self->header.functionInfo_ID].timer;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    if (timer >= 169) {
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            self->header.current_function, &self->header.functionInfo_ID);
        timer =
            self->header.current_function[self->header.functionInfo_ID].timer;
    }
    if (timer >= 21) {
        cv64_konamilogo_check_btn_press(self);
    }
}

void cv64_konamilogo_fade_out(cv64_ovl_konamilogo_t* self) {
    cv64_model_inf_t* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    if (model->primitive_color.A >= 0x0A) {
        model->primitive_color.A -= 0x09;
    } else {
        model->primitive_color.A = 0x00;
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            self->header.current_function, &self->header.functionInfo_ID);
    }
    cv64_konamilogo_check_btn_press(self);
}

void cv64_konamilogo_kcek_fade_in(cv64_ovl_konamilogo_t* self) {
    cv64_model_inf_t* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    model->size.x = 0.995f;
    model->dlist = &KCEK_LOGO_DL;
    if (model->primitive_color.A < 0xFC) {
        model->primitive_color.A += 0x03;
    } else {
        model->primitive_color.A = 0xFF;
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            self->header.current_function, &self->header.functionInfo_ID);
    }
    cv64_konamilogo_check_btn_press(self);
}

void cv64_konamilogo_kcek_wait(cv64_ovl_konamilogo_t* self) {
    cv64_model_inf_t* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    model->size.x = 0.995f;
    if (model->primitive_color.A < 0xFC) {
        model->primitive_color.A += 0x03;
    } else {
        model->primitive_color.A = 0xFF;
    }
    model->dlist = &KCEK_LOGO_DL;
    if ((s32) self->header.current_function[self->header.functionInfo_ID]
            .timer >= 97) {
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            self->header.current_function, &self->header.functionInfo_ID);
    }
}

void cv64_konamilogo_kcek_fade_out(cv64_ovl_konamilogo_t* self) {
    cv64_model_inf_t* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;
    void (*ptr_gamestate_change)(s32) = gamestate_change;

    model->dlist = &KCEK_LOGO_DL;
    if (model->primitive_color.A >= 0x0D) {
        model->primitive_color.A -= 0x0C;
    } else {
        model->primitive_color.A = 0x00;
        ptr_gamestate_change(GAMESTATE_INTRO_CUTSCENE);
    }
    sys.background_color.R = model->primitive_color.A;
    sys.background_color.G = model->primitive_color.A;
    sys.background_color.B = model->primitive_color.A;
}
