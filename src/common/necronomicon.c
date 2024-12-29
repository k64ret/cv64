#include "objects/menu/necronomicon.h"

// clang-format off

NecroFunc necro_functions[] = {
    necro_isWorkCreated,
    necro_init,
    necro_loop,
    necro_close,
    necro_finishedClosing,
    necro_destroy
};

void necro_entrypoint(Necronomicon* self) {
    ENTER(self, necro_functions);
}

void necro_isWorkCreated(Necronomicon* self) {
    if (self->work != NULL) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/common/necronomicon/necro_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/necronomicon/necro_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/necronomicon/necro_close.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/necronomicon/necro_finishedClosing.s")

void necro_destroy(Necronomicon* self) {
    self->header.destroy(self);
}

// clang-format on
