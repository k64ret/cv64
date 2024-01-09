#include "gfx/struct_47.h"
#include "objects/map/rose/door.h"
#include "objects/map/rose/ventilator.h"
#include "objects/player/player.h"
#include "system_work.h"

void cv64_ovl_rose_ventilator_entrypoint(cv64_ovl_rose_ventilator_t* self) {
    ENTER(self, cv64_ovl_rose_ventilator_funcs);
}

#ifdef NON_MATCHING
// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_ventilator_init.s")
// clang-format on
#else
// Scratch: https://decomp.me/scratch/AQwX9
void cv64_ovl_rose_ventilator_init(cv64_ovl_rose_ventilator_t* self) {
    cv64_model_inf_t* (*ptr_modelInfo_createRootNode)(u32, void*) =
        modelInfo_createRootNode;
    void (*ptr_modelInfo_setMapActorModel)(cv64_model_inf_t*, u32*) =
        modelInfo_setMapActorModel;
    s32 (*ptr_rand)(void) = rand;
    void (*ptr_actor_model_set_pos_and_angle)(void*, cv64_model_inf_t*) =
        actor_model_set_pos_and_angle;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;

    u32* dlist = &VENTILATOR_DOOR_DL;
    cv64_ovl_rose_ventilator_cfg_t* speed_settings = &self->speed_settings;
    cv64_model_inf_t* model;

    if ((model = ptr_modelInfo_createRootNode(4, D_8018CDE0[0])) == NULL) {
        self->header.destroy(self);
        return;
    }

    self->model = model;
    model->dlist = dlist;
    model->assets_file_ID = sys.map_assets_file_IDs[0];
    model->flags |= (0x800 | 0x100);
    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);
    ptr_modelInfo_setMapActorModel(model, dlist);
    speed_settings->current_speed = speed_settings->max_speed =
        (ptr_rand() & 0xFFF) + 0x10;
    speed_settings->time_until_changing_max_speed = (ptr_rand() & 0x1FF) + 0x1E;
    ptr_actor_model_set_pos_and_angle(self, model);
    ptr_object_curLevel_goToNextFuncAndClearTimer(
        self->header.current_function, &self->header.functionInfo_ID);
}
#endif

#ifdef NON_MATCHING
// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_ventilator_loop.s")
// clang-format on
#else
// Scratch: https://decomp.me/scratch/ySf25
void cv64_ovl_rose_ventilator_loop(cv64_ovl_rose_ventilator_t* self) {
    s32 (*ptr_actor_checkSpawn)(cv64_actor_t*, f32, f32, f32) =
        actor_checkSpawn;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;
    s32 (*ptr_rand)(void) = rand;
    cv64_ovl_rose_ventilator_cfg_t* speed_settings = &self->speed_settings;
    cv64_model_inf_t* model = self->model;

    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);
    if (ptr_actor_checkSpawn(self, model->position.x, model->position.y,
                             model->position.z) != FALSE) {
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            (u16*) self->header.current_function,
            &self->header.functionInfo_ID);
        return;
    }

    model->angle.pitch -= speed_settings->current_speed;
    if (speed_settings->current_speed < speed_settings->max_speed) {
        speed_settings->current_speed += 17;
    } else if (speed_settings->max_speed < speed_settings->current_speed) {
        speed_settings->current_speed -= 17;
    }
    speed_settings->time_until_changing_max_speed--;
    if (speed_settings->time_until_changing_max_speed == 0) {
        speed_settings->max_speed = (ptr_rand() & 0xFFF) + 16;
        speed_settings->time_until_changing_max_speed =
            (ptr_rand() & 0x1FF) + 30;
    }
}
#endif

void cv64_ovl_rose_door_entrypoint(cv64_ovl_rose_door_t* self) {
    ENTER(self, cv64_ovl_rose_door_funcs);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_init.s")

// clang-format on

void cv64_ovl_rose_door_loop(cv64_ovl_rose_door_t* self) {
    cv64_model_inf_t* model = self->model;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;
    s32 (*ptr_actor_checkSpawn)(cv64_actor_t*, f32, f32, f32) =
        actor_checkSpawn;

    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);

    if (ptr_actor_checkSpawn(self, model->position.x, model->position.y,
                             model->position.z) != FALSE) {
        self->header.destroy(self);
    } else {
        ENTER(self, cv64_ovl_rose_door_state_funcs);
        model->position.y =
            height_settings->initial_height + height_settings->height;
    }
}

void cv64_ovl_rose_door_state_startClosing(cv64_ovl_rose_door_t* self) {
    u32 (*ptr_checkIfOutsideEntityIsInsideMainEntityRadius)(
        cv64_model_inf_t*, cv64_model_inf_t*, f32, u32) =
        checkIfOutsideEntityIsInsideMainEntityRadius;
    cv64_model_inf_t* model = self->model;
    u8 (*ptr_play_sound_in_position_and_set_volume)(s16, vec3f*, f32) =
        play_sound_in_position_and_set_volume;
    void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
        object_curLevel_goToNextFuncAndClearTimer;
    cv64_ovl_rose_door_cfg_t* height_settings = &self->height_settings;

    if (ptr_checkIfOutsideEntityIsInsideMainEntityRadius(
            model, ptr_PlayerData->visualData.model, 15.0f, AXIS_Z) == FALSE) {
        // Matching version
        if (sys.SaveStruct_gameplay.character == REINHARDT) {
            ptr_play_sound_in_position_and_set_volume(0x029B, &model->position,
                                                      0.5f);
        } else {
            ptr_play_sound_in_position_and_set_volume(0x029B, &model->position,
                                                      1.0f);
        }
        // Cleaner version
        // ptr_play_sound_in_position_and_set_volume(0x029B, &model->position,
        // ((sys.SaveStruct_gameplay.character == REINHARDT) ? 0.5f : 1.0f));
        height_settings->closing_speed = 0.0f;
        ptr_object_curLevel_goToNextFuncAndClearTimer(
            self->header.current_function, &self->header.functionInfo_ID);
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_state_closing.s")

// clang-format on

void cv64_ovl_rose_door_state_idle(cv64_ovl_rose_door_t* self) {}
