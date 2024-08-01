/**
 * @file textbox_advance_arrow.c
 *
 * The blinking red arrow that appears when you can press A to advance to the
 * next string in a textbox.
 *
 * Not to be confused with the red arrow used for selecting options in some textboxes.
 */

#include "gfx/camera.h"
#include "objects/menu/textboxAdvanceArrow.h"

// clang-format off

cv64_ovl_textboxadvancearrow_func_t cv64_ovl_textboxadvancearrow_funcs[] = {
    textboxAdvanceArrow_init,
    textboxAdvanceArrow_loop,
    textboxAdvanceArrow_destroy
};

// clang-format on

void textboxAdvanceArrow_entrypoint(textboxAdvanceArrow* self) {
    ENTER(self, cv64_ovl_textboxadvancearrow_funcs);
}

void textboxAdvanceArrow_init(textboxAdvanceArrow* self) {
    light* arrow_light;
    cv64_model_inf_t* model;

    arrow_light       = (*light_create)(FIG_TYPE_LIGHT);
    self->arrow_light = arrow_light;
    (*figure_setChild)(arrow_light, common_camera_HUD);

    // clang-format off
    arrow_light->ambient_color.r = arrow_light->ambient_color.g = arrow_light->ambient_color.b = 160;
    // clang-format on

    arrow_light->number_of_lights = 1;

    // clang-format off
    arrow_light->lights[0].color.r = arrow_light->lights[0].color.g = arrow_light->lights[0].color.b = 207;
    // clang-format on

    arrow_light->lights[0].direction[0] = 240;
    arrow_light->lights[0].direction[1] = 0;
    arrow_light->lights[0].direction[2] = 16;
    model                 = (*modelInfo_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, arrow_light);
    self->model           = model;
    model->dlist          = &TEXTBOX_ADVANCE_ARROW_DL;
    model->assets_file_ID = NI_ASSETS_FILE_SELECT;
    BITS_SET(model->flags, FIG_FLAG_0080);
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = RGBA(255, 0, 0, 255);
    model->size.x                  = 1.3f;
    model->size.y                  = 1.3f;
    model->position.x              = 0.0f;
    model->position.z              = 0.0f;
    model->position.y              = -90.0f;
    self->disable_arrow            = FALSE;
    self->fade_timer               = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void textboxAdvanceArrow_loop(textboxAdvanceArrow* self) {
    u32 fade_timer_prev     = self->fade_timer;
    cv64_model_inf_t* model = self->model;
    u8 red;
    u32 new_var;

    self->fade_timer++;
    if ((fade_timer_prev > 9) != (((fade_timer_prev > 9)) * 0)) { // Likely a fakematch
        new_var = model->primitive_color.r;
        red     = new_var;
        if (red < 8.5) {
            model->primitive_color.r = 255;
            model->primitive_color.a = 255;
            self->fade_timer         = 0;
        } else {
            model->primitive_color.r = red - 8.5;
            model->primitive_color.a -= 8.5;
        }
    }
    if (self->disable_arrow) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void textboxAdvanceArrow_destroy(textboxAdvanceArrow* self) {
    self->header.destroy(self);
}
