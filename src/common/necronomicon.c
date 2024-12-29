#include "objects/menu/necronomicon.h"
#include "system_work.h"

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

void necro_finishedClosing(Necronomicon* self) {
    s32 temp[4];
    NecroWork* work;
    Vec3f position;
    u8 random_page;

    work = self->work;
    if ((work->flags & NECRO_WORK_FLAG_DONT_FLIP_PAGES_BEFORE_CLOSING) | NECRO_WORK_FLAG_01) {
        work->field_0x20 = 8;
    }
    if (work->flags & NECRO_WORK_FLAG_DESTROY_NECRO) {
        (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
    }
    if (work->time_before_flipping_another_page != 0) {
        work->time_before_flipping_another_page--;
        return;
    }
    if (work->field_0x20 >= 8) {
        work->flags &= ~NECRO_WORK_FLAG_CLOSE;
        if (CONT_BTNS_PRESSED(CONT_0, B_BUTTON | START_BUTTON | RECENTER_BUTTON)) {
            (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function, &self->header.function_info_ID);
        }
    }
    else {
        (*guRandom)();
        random_page = (*guRandom)() % 3;
        switch (random_page) {
            case 0:
                position.x = ((*guRandom)() % 220) - 110;
                position.y = ((*guRandom)() % 10) + 100;
                break;
            case 1:
                position.x = ((*guRandom)() % 220) - 110;
                position.y = (-(*guRandom)() % 10) - 100;
                break;
            case 2:
                position.x = ((*guRandom)() % 10) + 100;
                position.y = ((*guRandom)() % 220) - 110;
                break;
        }
        position.z = 80.0f;

        // @bug This condition is never executed
        if (FALSE) {
            work->position = position;
        }
        (*guRandom)();
        (*guRandom)();
        (*guRandom)();
        work->field_0x20++;
        work->time_before_flipping_another_page = 3;
    }
}

void necro_destroy(Necronomicon* self) {
    self->header.destroy(self);
}

// clang-format on
