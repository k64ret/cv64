#include "objects/menu/renon_briefcase.h"
#include "gfx/camera.h"
#include "sound.h"
#include "system_work.h"

hierarchy cv64_ovl_renonbriefcase_hierarchy = {
    NI_ASSETS_RENON_BRIEFCASE,
    {{0x060026E0, CREATE_NEXT_NODE, {0, 7, -75}}, {0x06002A40, DONT_CREATE_SIBLING, {0, 0, 0}}}
};

u32 cv64_ovl_renonbriefcase_anim_rot_data[] = {
    0x00000000,
    0x00000000,
    0x00000005,
    0x0E400000,
    0xB1C00000,
    0x40000000 // ANIM_FLAG_LAST_KEYFRAME
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
