#include "cv64.h"
#include "objects/map/tou_turo/door.h"
#include <ultra64.h>

void cv64_touturo_door_entrypoint(cv64_touturo_door_t* self) {
    ENTER(self, cv64_touturo_door_funcs);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_touturo_door_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_touturo_door_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_touturo_door_exit_check_event_flags.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_touturo_door_entrance_check_event_flags.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_touturo_door_entrance_close_door.s")

// clang-format on
