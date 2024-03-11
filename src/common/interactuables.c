#include "cv64.h"
#include "objects/cutscene/interactuables.h"
#include "objects/player/player.h"
#include "gfx/struct_47.h"
#include "random.h"
#include "system_work.h"

cv64_interactuables_func_t interactuables_functions[] = {
    interactuables_init,
    interactuables_loop,
    interactuables_initCheck,
    interactuables_selectTextboxOption,
    interactuables_stopCheck,
    interactuables_destroy
};

void interactuables_entrypoint(interactuables* self) {
    ENTER(self, interactuables_functions);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_initCheck.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_selectTextboxOption.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_stopCheck.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/interactuables/interactuables_destroy.s")

// clang-format on

void interactuables_stopInteraction(interactuables* self) {
    self->pickableItemFlash_or_textbox.flash = NULL;
    ITEM_FADE_TIMER = 0;
    self->textbox_is_active = FALSE;
    self->interacting_with_interactuable = FALSE;
}
