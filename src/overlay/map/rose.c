#include "actor.h"
#include "objects/map/rose/door.h"
#include "objects/map/rose/ventilator.h"
#include "system_work.h"

void cv64_ovl_rose_ventilator_entrypoint(cv64_ovl_rose_ventilator_t* self) {
    ENTER(self, cv64_ovl_rose_ventilator_funcs);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_ventilator_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_ventilator_loop.s")

// clang-format on

void cv64_ovl_rose_door_entrypoint(cv64_ovl_rose_door_t* self) {
    ENTER(self, cv64_ovl_rose_door_funcs);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_init.s")

void cv64_ovl_rose_door_loop(cv64_ovl_rose_door_t* self) {
    cv64_model_inf_t* model = self->model;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    s32 (*ptr_actor_checkSpawn)(cv64_actor_t* actor, f32 actor_pos_X, f32 actor_pos_Y, f32 actor_pos_Z) = actor_checkSpawn;

    CV64_COLOR_RGBA_TO_U32(model->primitive_color) = CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) = CV64_COLOR_RGBA_TO_U32(sys.background_color);
    if (ptr_actor_checkSpawn(self, model->position.x, model->position.y, model->position.z) != FALSE) {
        self->header.destroy(self);
    }
    else {
        ENTER(self, cv64_ovl_rose_door_state_funcs);
        model->position.y = height_settings->initial_height + height_settings->height;
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_state_startClosing.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_state_closing.s")

// clang-format on

void cv64_ovl_rose_door_state_idle(cv64_ovl_rose_door_t* self) {}
