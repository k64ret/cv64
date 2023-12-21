/*
 * File: konamiLogo.c
 * Description: Handles the Konami / KCEK logo screen
 * Associated objects: 0x000E
 * 
 * osMapTLB'd? = No
 * Entrypoint address   = 0x801CFCD0
 * Associated files ptr = 0x800958C0
 * Associated files:
 *   0x6B4FC0 - 0x6B5480 (Overlay)
 */

#include "objects/engine/gamestates/konamiLogo/konamiLogo.h"
#include "unknown_struct.h"
#include "gfx/camera.h"
#include "gfx/color.h"
#include "gamestate.h"

void konamiLogo_entrypoint(konamiLogo* self) {
    ENTER(self, konamiLogo_functions);
}

void konamiLogo_checkButtonPress(konamiLogo* self) {
    void (*ptr_object_curLevel_goToFunc)(u16[], s16*, s32) = object_curLevel_goToFunc;
    
    if ((D_80383AB8.controllers[0].buttons_pressed  |
         D_80383AB8.controllers[1].buttons_pressed  |
         D_80383AB8.controllers[2].buttons_pressed  |
         D_80383AB8.controllers[3].buttons_pressed) & (BTN_START | BTN_RECENTER)) {
        ptr_object_curLevel_goToFunc(self->header.current_function, &self->header.functionInfo_ID, KONAMILOGO_KCEK_WAIT);
    }
}

void konamiLogo_init(konamiLogo* self) {
    model_info* model;
    object_func_info_t* curFunc;
    
    model_info* (*ptr_modelInfo_createRootNode)(u32, void*) = modelInfo_createRootNode;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;

    model = ptr_modelInfo_createRootNode(0x10, common_cameras_array.HUD);
    self->model = model;
    model->dlist = &KONAMI_LOGO_DL;
    model->assets_file_ID = 0x5D;
    model->size.x = 0.9975f;
    model->size.y = 1.005f;
    D_80383AB8.background_color.color_u32 = 0x000000FF;            // Black (opaque)
    model->flags |= 0x800;
    model->primitive_color.color_u32 = 0xFFFFFF00;                 // White (transparent)

    GO_TO_NEXT_FUNC(self, konamiLogo_functions, curFunc, ptr_object_curLevel_goToNextFuncAndClearTimer);
}

void konamiLogo_fade_in(konamiLogo* self) {
    model_info* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;
    
    if (model->primitive_color.color_u8.A < 0xF3) {
        model->primitive_color.color_u8.A += 0x0C;
    }
    else {
        model->primitive_color.color_u8.A = 0xFF;
        ptr_object_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
    }
    D_80383AB8.background_color.color_u8.R = model->primitive_color.color_u8.A;
    D_80383AB8.background_color.color_u8.G = model->primitive_color.color_u8.A;
    D_80383AB8.background_color.color_u8.B = model->primitive_color.color_u8.A;
    konamiLogo_checkButtonPress(self);
}

void konamiLogo_wait(konamiLogo* self) {
    s32 timer = self->header.current_function[self->header.functionInfo_ID].timer;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;

    if (timer >= 169) {
        ptr_object_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
        timer = self->header.current_function[self->header.functionInfo_ID].timer;
    }
    if (timer >= 21) {
        konamiLogo_checkButtonPress(self);
    }
}

void konamiLogo_fade_out(konamiLogo* self) {
    model_info* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;
    
    if (model->primitive_color.color_u8.A >= 0x0A) {
        model->primitive_color.color_u8.A -= 0x09;
    }
    else {
        model->primitive_color.color_u8.A = 0x00;
        ptr_object_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
    }
    konamiLogo_checkButtonPress(self);
}

void konamiLogo_KCEK_fade_in(konamiLogo* self) {
    model_info* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;
    
    model->size.x = 0.995f;
    model->dlist = &KCEK_LOGO_DL;
    if (model->primitive_color.color_u8.A < 0xFC) {
        model->primitive_color.color_u8.A += 0x03;
    }
    else {
        model->primitive_color.color_u8.A = 0xFF;
        ptr_object_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
    }
    konamiLogo_checkButtonPress(self);
}

void konamiLogo_KCEK_wait(konamiLogo* self) {
    model_info* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;

    model->size.x = 0.995f;
    if (model->primitive_color.color_u8.A < 0xFC) {
        model->primitive_color.color_u8.A += 0x03;
    }
    else {
        model->primitive_color.color_u8.A = 0xFF;
    }
    model->dlist = &KCEK_LOGO_DL;
    if ((s32) self->header.current_function[self->header.functionInfo_ID].timer >= 97) {
        ptr_object_curLevel_goToNextFuncAndClearTimer(self->header.current_function, &self->header.functionInfo_ID);
    }
}

void konamiLogo_KCEK_fade_out(konamiLogo* self) {
    model_info* model = self->model;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) = object_curLevel_goToNextFuncAndClearTimer;
    void (*ptr_gamestate_change)(s32) = gamestate_change;

    model->dlist = &KCEK_LOGO_DL;
    if (model->primitive_color.color_u8.A >= 0x0D) {
        model->primitive_color.color_u8.A -= 0x0C;
    }
    else {
        model->primitive_color.color_u8.A = 0x00;
        ptr_gamestate_change(GAMESTATE_INTRO_CUTSCENE);
    }
    D_80383AB8.background_color.color_u8.R = model->primitive_color.color_u8.A;
    D_80383AB8.background_color.color_u8.G = model->primitive_color.color_u8.A;
    D_80383AB8.background_color.color_u8.B = model->primitive_color.color_u8.A;
}
