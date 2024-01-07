#include "objects/map/rose/door.h"
#include "objects/map/rose/ventilator.h"

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

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_state_startClosing.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/rose/cv64_ovl_rose_door_state_closing.s")

// clang-format on

void cv64_ovl_rose_door_state_idle(cv64_ovl_rose_door_t* self) {}
