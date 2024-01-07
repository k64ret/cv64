#include "cv64.h"
#include "object.h"
#include <ultra64.h>

typedef struct cv64_ovl_rose {
    cv64_obj_hdr_t header;
} cv64_ovl_rose_t;

typedef void (*cv64_ovl_rose_func_t)(cv64_ovl_rose_t*);

extern cv64_ovl_rose_func_t cv64_ovl_rose_funcs[];

void cv64_ovl_rose_entrypoint(cv64_ovl_rose_t* self) {
    ENTER(self, cv64_ovl_rose_funcs);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018EB80_6F0AC0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018EC94_6F0BD4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018ED98_6F0CD8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018EE08_6F0D48.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018EF3C_6F0E7C.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018F024_6F0F64.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018F0D4_6F1014.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/ROSE/func_8018F204_6F1144.s")

// clang-format on
