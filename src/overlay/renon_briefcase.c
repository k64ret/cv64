/**
 * File: renon_briefcase.c
 * Description: Handles the small cutscene that shows the briefcase spinning
 *              prior to entering Renon's Shop
 * Associated objects: 0x213C
 *
 * Mapped by the TLB? = Yes
 */

#include "objects/menu/renon_briefcase.h"
#include "gfx/camera.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

hierarchy cv64_ovl_renonbriefcase_hierarchy = {
    NI_ASSETS_RENON_BRIEFCASE,
    {
        // RENON_BRIEFCASE_LOWER_LID
        {0x060026E0, CREATE_NEXT_NODE,    {0, 7, -75}},
        // RENON_BRIEFCASE_UPPER_LID
        {0x06002A40, DONT_CREATE_SIBLING, {0, 0, 0}}
    }
};

// clang-format on

u32 cv64_ovl_renonbriefcase_anim_rot_data[] = {
    0x00000000, 0x00000000, 0x00000005, 0x0E400000, 0xB1C00000, ANIM_FLAG_LAST_KEYFRAME
};

cv64_ovl_renonbriefcase_func_t cv64_ovl_renonbriefcase_funcs[] = {
    cv64_ovl_renonbriefcase_init, cv64_ovl_renonbriefcase_loop, cv64_ovl_renonbriefcase_destroy
};

void cv64_ovl_renonbriefcase_entrypoint(cv64_ovl_renonbriefcase_t* self) {
    ENTER(self, cv64_ovl_renonbriefcase_funcs);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/renon_briefcase/cv64_ovl_renonbriefcase_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/renon_briefcase/cv64_ovl_renonbriefcase_loop.s")

// clang-format on

void cv64_ovl_renonbriefcase_destroy(cv64_ovl_renonbriefcase_t* self) {
    sys.background_color.integer = 0x000000FF;
    self->header.destroy(self);
}
