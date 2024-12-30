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

// clang-format on

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

void necro_init(Necronomicon* self) {
    Model* full_model;
    Model* book_cover;
    NecroWork* work = self->work;
    page_work* second_page;
    page_work* first_page;

    full_model              = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, work->necro_light);
    self->full_model        = full_model;
    full_model->dlist       = (u32) &NECRO_FULL_MODEL_DL;
    full_model->assets_file = NI_ASSETS_NECRONOMICON;
    full_model->flags |= FIG_FLAG_0080;
    full_model->flags |= FIG_FLAG_APPLY_PRIMITIVE_COLOR;
    full_model->primitive_color.integer = RGBA(85, 85, 85, 255);
    full_model->size.z                  = 1.0f;
    full_model->size.y                  = 1.0f;
    full_model->size.x                  = 1.0f;
    full_model->position.x              = work->position.x;
    full_model->position.y              = work->position.y;
    full_model->position.z              = work->position.z;

    book_cover              = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, full_model);
    self->book_cover        = book_cover;
    book_cover->dlist       = (u32) &NECRO_BOOK_COVER_DL;
    book_cover->assets_file = NI_ASSETS_NECRONOMICON;
    book_cover->flags |= FIG_FLAG_0080;
    book_cover->size.z     = 1.0f;
    book_cover->size.y     = 1.0f;
    book_cover->size.x     = 1.0f;
    book_cover->position.x = work->position.x - 104.5 - 1.5;
    book_cover->position.y = work->position.y + 1.0;
    book_cover->position.z = work->position.z + 51.0;
    book_cover->angle.yaw  = -DEG_TO_FIXED(172.97);

    second_page = (*pageWork_create)(
        self, work->necro_light, ((*guRandom)() % 3) + 1, 0.0f, 0.0f, 2.0f, 0, 5.0f
    );
    self->pages[1] = second_page;
    if (second_page == NULL) {
        self->header.destroy(self);
    }

    first_page     = (*pageWork_create)(self, work->necro_light, PAGE_1, 0.0f, 0.0f, 2.0f, 7, 5.0f);
    self->pages[0] = first_page;
    if (first_page == NULL) {
        self->header.destroy(self);
    }

    work->field_0x21 = (guRandom() % 3) + 1;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/necronomicon/necro_loop.s")

// clang-format on

void necro_close(Necronomicon* self) {
    s32 temp[4];
    Model* book_cover;
    Vec3f position;
    NecroWork* work;
    page_work* page;
    u8 random_page;
    s32 var_a1;
    u8 i;

    work       = self->work;
    book_cover = self->book_cover;
    var_a1     = TRUE;
    if (work->last_page_flipped == FALSE) {
        for (i = 1; i < 10; i++) {
            if (self->pages[i] != NULL) {
                var_a1 = FALSE;
                page   = self->pages[i];
                if (page->flags & PAGE_ANIM_END_KEYFRAME) {
                    page = self->pages[0];
                    page->flags &= ~ANIMATE;
                    page->flags |= DESTROY_PAGE;
                    self->pages[0] = self->pages[i];
                    self->pages[i] = NULL;
                }
            }
        }
        if (var_a1) {
            work->last_page_flipped = TRUE;
            page                    = self->pages[0];
            page->flags &= ~ANIMATE;
            page->flags |= DESTROY_PAGE;
            self->pages[0] = NULL;
        }
    }
    if (book_cover->angle.yaw < 0) {
        book_cover->angle.yaw += DEG_TO_FIXED(3);
        if (book_cover->angle.yaw >= 0) {
            book_cover->angle.yaw = 0;
        }
    } else {
        book_cover->angle.yaw = 0;
        if (self->pages[0] == NULL) {
            for (i = 10; i < 13; i++) {
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
            }
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }
}

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
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
    if (work->time_before_flipping_another_page != 0) {
        work->time_before_flipping_another_page--;
        return;
    }
    if (work->field_0x20 >= 8) {
        work->flags &= ~NECRO_WORK_FLAG_CLOSE;
        if (CONT_BTNS_PRESSED(CONT_0, B_BUTTON | START_BUTTON | RECENTER_BUTTON)) {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    } else {
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
