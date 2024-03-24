#include "objects/menu/renon_briefcase.h"
#include "gfx/camera.h"
#include "sound.h"

// extern cv64_ovl_renonbriefcase_func_t cv64_ovl_renonbriefcase_funcs[];

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/renon_briefcase/cv64_ovl_renonbriefcase_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/renon_briefcase/cv64_ovl_renonbriefcase_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/renon_briefcase/cv64_ovl_renonbriefcase_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/renon_briefcase/cv64_ovl_renonbriefcase_destroy.s")

// clang-format on
