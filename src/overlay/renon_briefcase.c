/**
 * @file renon_briefcase.c
 *
 * Handles the small cutscene that shows the briefcase spinning
 * prior to entering Renon's Shop.
 */

#include "objects/menu/renon_briefcase.h"
#include "gfx/camera.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

// TODO: `extern const u32` for the dlists
Hierarchy cv64_ovl_renonbriefcase_hierarchy = {
    NI_ASSETS_RENON_BRIEFCASE,
    {
        // RENON_BRIEFCASE_LOWER_LID_DL
        { 0x060026E0, CREATE_NEXT_NODE,    { 0, 7, -75 } },
        // RENON_BRIEFCASE_UPPER_LID_DL
        { 0x06002A40, DONT_CREATE_SIBLING, { 0, 0, 0 } }
    }
};

u8 cv64_ovl_renonbriefcase_open_anim_rot_data[2][12] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05 },
    { 0x0E, 0x40, 0x00, 0x00, 0xB1, 0xC0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00 }
};

cv64_ovl_renonbriefcase_func_t cv64_ovl_renonbriefcase_funcs[] = {
    cv64_ovl_renonbriefcase_init,
    cv64_ovl_renonbriefcase_loop,
    cv64_ovl_renonbriefcase_destroy
};

// clang-format on

void cv64_ovl_renonbriefcase_entrypoint(cv64_ovl_renonbriefcase_t* self) {
    ENTER(self, cv64_ovl_renonbriefcase_funcs);
}

void cv64_ovl_renonbriefcase_init(cv64_ovl_renonbriefcase_t* self) {
    Model* model;
    animation_info* anim_info = &self->anim_info;
    u32 i;
    u32 unused;

    // `common_camera_8009B448` is unused on this cutscene
    (*Camera_SetParams)(common_camera_8009B448, 0);
    common_camera_8009B448->position.x = 0.0f;
    common_camera_8009B448->position.y = 0.0f;
    common_camera_8009B448->position.z = 100.0f;
    // clang-format off
    common_camera_8009B448->look_at_direction.x =
    common_camera_8009B448->look_at_direction.y =
    common_camera_8009B448->look_at_direction.z = 0.0f;
    // clang-format on

    // Initialize the cutscene's camera
    (*Camera_SetParams)(common_camera_8009B44C, 3);
    common_camera_8009B44C->position.x = 0.0f;
    common_camera_8009B44C->position.y = 0.0f;
    common_camera_8009B44C->position.z = 100.0f;
    // clang-format off
    common_camera_8009B44C->look_at_direction.x =
    common_camera_8009B44C->look_at_direction.y =
    common_camera_8009B44C->look_at_direction.z = 0.0f;
    // clang-format on

    // Create and setup the briefcase model
    self->model = (*Model_buildHierarchy)(
        FIG_TYPE_ALLOW_TRANSPARENCY_CHANGE | FIG_TYPE_HIERARCHY_NODE,
        common_camera_8009B44C,
        &cv64_ovl_renonbriefcase_hierarchy
    );
    model = self->model;
    BITS_SET(model->flags, FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_0080);
    model->primitive_color.integer = RGBA(255, 255, 255, 255);
    model->angle.pitch             = 0;
    model->angle.yaw               = DEG_TO_FIXED(90);
    model->angle.roll              = 0;
    model->size.x                  = 1.0f;
    model->size.y                  = 1.0f;
    model->size.z                  = 1.0f;
    model->position.x              = 0.0f;
    model->position.y              = 0.0f;
    model->position.z              = -292.0f;

    // clang-format off
    for (i = 0; i < ARRAY_COUNT(self->field_0x34); i++) { self->field_0x34[i] = 0; }
    // clang-format on

    self->current_cutscene_time    = 0;
    PLAY_SD_RENON_BRIEFCASE_SPIN_2 = FALSE;

    // Initialize briefcase animation
    (*animationInfo_create)(anim_info, RENON_BRIEFCASE_NUMBER_OF_LIMBS, 0);
    (*animationInfo_setParams)(
        anim_info, &cv64_ovl_renonbriefcase_open_anim_rot_data[0][0], RENON_BRIEFCASE_ANIM_SPEED
    );
    (*animationInfo_animateFrame)(anim_info, model);

    (*Fade_SetSettings)(FADE_IN, 15, 0xFF, 0xFF, 0xFF);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void cv64_ovl_renonbriefcase_loop(cv64_ovl_renonbriefcase_t* self) {
    Model* model = self->model;
    f32 volume;

    // Step 1. Briefcase is approaching the camera
    if (self->current_cutscene_time < 90.0) {
        // Move the briefcase towards the camera
        model->position.z -= ((model->position.z - 300.0f) / 90.0);

        // Rotate the briefcase in circles
        model->angle.pitch += 3640.88897705078125;
        model->angle.yaw += 2730.66673278808594;
        model->angle.roll -= 3640.88897705078125;

        // Play the "spinning" sound every third of a second
        if ((self->current_cutscene_time % 10) == 0) {
            // Update the sound's volume based on the briefcase's
            // proximity towards the camera
            volume = 1.0f -
                (*f32_normalize)(
                         (*vec3f_distance)(&model->position, &common_camera_8009B44C->position),
                         10.0f,
                         400.0f
                );

            if (PLAY_SD_RENON_BRIEFCASE_SPIN_2) {
                (*func_800139D4)(SD_RENON_BRIEFCASE_SPIN_2, 0.0f, volume);
                PLAY_SD_RENON_BRIEFCASE_SPIN_2 = FALSE;
            } else {
                (*func_800139D4)(SD_RENON_BRIEFCASE_SPIN_1, 0.0f, volume);
                PLAY_SD_RENON_BRIEFCASE_SPIN_2 = TRUE;
            }
        }
    }

    // Step 2. Stop the briefcase after it reaches its destination
    if (self->current_cutscene_time == 90.0) {
        model->angle.pitch = 0;
        model->angle.yaw   = 0;
        model->angle.roll  = 0;
    }

    // Step 3. Play the "open briefcase" animation
    // The animation is set to play for 60 frames,
    // but it will only play for 19 frames on practice
    if ((u32) (self->current_cutscene_time - 90.0) <= 60.0) {
        (*animationInfo_animateFrame)(&self->anim_info, model);
    }

    self->current_cutscene_time++;

    //  Step 4. Fade out and destroy the object
    if (self->current_cutscene_time == 93) {
        (*Fade_SetSettings)(FADE_OUT, 30, 0, 0, 0);
    }

    if (self->current_cutscene_time >= 109) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void cv64_ovl_renonbriefcase_destroy(cv64_ovl_renonbriefcase_t* self) {
    sys.background_color.integer = RGBA(0, 0, 0, 255);
    self->header.destroy(self);
}
