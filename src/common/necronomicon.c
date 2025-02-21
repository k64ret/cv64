/**
 * @file necronomicon.c
 *
 * This file contains the code that handles the Necronomicon
 * (the book from the Data and Options menus)
 */

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
    PageWork* second_page;
    PageWork* first_page;

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

    /**
     * Create the first page as `PAGE_1`, then create a random page
     * between `PAGE_2` and `PAGE_3`
     */
    second_page = (*pageWork_create)(
        self, work->necro_light, ((*guRandom)() % 3) + 1, 0.0f, 0.0f, 2.0f, 0, 5.0f
    );
    self->pages[1] = second_page;
    if (second_page == NULL) {
        self->header.destroy(self);
    }

    first_page =
        (*pageWork_create)(self, work->necro_light, PAGE_FLAG_PAGE_1, 0.0f, 0.0f, 2.0f, 7, 5.0f);
    self->pages[0] = first_page;
    if (first_page == NULL) {
        self->header.destroy(self);
    }

    work->time_before_creating_different_page = (guRandom() % 3) + 1;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void necro_loop(Necronomicon* self) {
    NecroWork* work;
    PageWork* page;
    PageWork* page_2;
    u8 i;
    s8 page_type;

    work = self->work;

    // Request the closure of the necronomicon
    if (work->flags & NECRO_WORK_FLAG_CLOSE) {
        // Skip flipping the pages over and directly close the book
        if (work->flags & NECRO_WORK_FLAG_DONT_FLIP_PAGES_BEFORE_CLOSING) {
            work->pages_to_flip_before_closing = NECRO_NUM_PAGES(self);
        }

        // After flipping 10 pages, close the book
        if (work->pages_to_flip_before_closing < NECRO_NUM_PAGES(self)) {
            work->flags |= NECRO_WORK_FLAG_FLIP_PAGES;
        } else {
            page = self->pages[1];
            page->flags |= PAGE_FLAG_ANIMATE;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }
    }

    for (i = 2; i < NECRO_NUM_PAGES(self); i++) {
        // Destroy the page if it has finished flipping over
        if (self->pages[i] != NULL) {
            page = self->pages[i];
            if (page->flags & PAGE_FLAG_ANIM_END_KEYFRAME) {
                page = self->pages[0];
                page->flags &= ~PAGE_FLAG_ANIMATE;
                page->flags |= PAGE_FLAG_DESTROY_PAGE;
                page_2         = self->pages[i];
                self->pages[0] = page_2;
                self->pages[i] = NULL;
            }
            // Create the next page when `time_before_flipping_another_page` reaches 0
        } else if ((work->flags & NECRO_WORK_FLAG_FLIP_PAGES) && (work->time_before_flipping_another_page == 0)) {
            page           = self->pages[1];
            self->pages[i] = self->pages[1];
            page->flags |= PAGE_FLAG_ANIMATE;
            if (1) {
            }

            // Decide whether to the next page created is either `PAGE_FLAG_PAGE_1`,
            // or randomized between `PAGE_2` and `PAGE_3`
            if (work->time_before_creating_different_page != 0) {
                work->time_before_creating_different_page--;
                page_type = PAGE_FLAG_PAGE_1;
            } else {
                work->time_before_creating_different_page = (guRandom() % 3) + 1;
                page_type                                 = (guRandom() % 2) + 2;
            }

            page =
                (*pageWork_create)(self, work->necro_light, page_type, 0.0f, 0.0f, 2.0f, 0, 5.0f);
            self->pages[1] = page;
            if (page == NULL) {
                self->header.destroy(self);
            }

            work->flags &= ~NECRO_WORK_FLAG_FLIP_PAGES;

            // Flip pages faster if the book is requested to be closed
            if (work->flags & NECRO_WORK_FLAG_CLOSE) {
                work->time_before_flipping_another_page = 10;
                work->pages_to_flip_before_closing++;
            } else {
                work->time_before_flipping_another_page = 30;
            }
        }
    }

    if (work->time_before_flipping_another_page != 0) {
        work->time_before_flipping_another_page--;
    }

    // Destroy all pages and force despawning the necronomicon
    if (work->flags & NECRO_WORK_FLAG_DESTROY_NECRO) {
        for (i = 0; i < NECRO_NUM_PAGES(self); i++) {
            page = self->pages[i];
            if (page != NULL) {
                page->flags &= ~PAGE_FLAG_ANIMATE;
                page->flags |= PAGE_FLAG_DESTROY_PAGE;
            }
        }
        GO_TO_FUNC_NOW(self, necro_functions, NECRO_DESTROY);
    }
}

void necro_close(Necronomicon* self) {
    s32 temp[4];
    Model* book_cover;
    Vec3f position;
    NecroWork* work;
    PageWork* page;
    u8 random_position;
    s32 destroy_first_page;
    u8 i;

    work               = self->work;
    book_cover         = self->book_cover;
    destroy_first_page = TRUE;

    if (work->last_page_flipped == FALSE) {
        // Destroy all pages but the first one when they all finished flipping
        for (i = 1; i < NECRO_NUM_PAGES(self); i++) {
            if (self->pages[i] != NULL) {
                destroy_first_page = FALSE;
                page               = self->pages[i];
                if (page->flags & PAGE_FLAG_ANIM_END_KEYFRAME) {
                    page = self->pages[0];
                    page->flags &= ~PAGE_FLAG_ANIMATE;
                    page->flags |= PAGE_FLAG_DESTROY_PAGE;
                    self->pages[0] = self->pages[i];
                    self->pages[i] = NULL;
                }
            }
        }

        // When only the first page is left, destroy it
        if (destroy_first_page) {
            work->last_page_flipped = TRUE;
            page                    = self->pages[0];
            page->flags &= ~PAGE_FLAG_ANIMATE;
            page->flags |= PAGE_FLAG_DESTROY_PAGE;
            self->pages[0] = NULL;
        }
    }

    // Close the book cover
    if (book_cover->angle.yaw < 0) {
        book_cover->angle.yaw += DEG_TO_FIXED(3);
        if (book_cover->angle.yaw >= 0) {
            book_cover->angle.yaw = 0;
        }
    } else {
        book_cover->angle.yaw = 0;

        /**
         * Calculate a random position for the book once it closes,
         * likely to make it shake after it fully closes.

         * This goes unused because a condition is never executed (see below)
         */
        if (self->pages[0] == NULL) {
            for (i = 10; i < 13; i++) {
                (*guRandom)();
                random_position = (*guRandom)() % 3;
                switch (random_position) {
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

                // @note This condition is never executed
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
    u8 random_position;

    work = self->work;

    /**
     * @note This condition always passes
     */
    if ((work->flags & NECRO_WORK_FLAG_DONT_FLIP_PAGES_BEFORE_CLOSING) | TRUE) {
        work->necro_destroy_delay_time = 8;
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

    // Destroy the necronomicon when pressing the `B` or `START` buttons
    if (work->necro_destroy_delay_time >= 8) {
        work->flags &= ~NECRO_WORK_FLAG_CLOSE;
        if (CONT_BTNS_PRESSED(CONT_0, B_BUTTON | START_BUTTON | RECENTER_BUTTON)) {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        }

        /**
     * @note This part of the code is never reached because of the condition that always passes
     *       (see above)
     */
    } else {
        /**
         * Calculate a random position for the book once it closes,
         * likely to make it shake after it fully closes.

         * This goes unused because a condition is never executed (see below)
         */
        (*guRandom)();
        random_position = (*guRandom)() % 3;
        switch (random_position) {
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

        // @note This condition is never executed
        if (FALSE) {
            work->position = position;
        }
        (*guRandom)();
        (*guRandom)();
        (*guRandom)();
        work->necro_destroy_delay_time++;

        // Add an extra delay before destroying the necro, alongside `necro_destroy_delay_time`
        work->time_before_flipping_another_page = 3;
    }
}

void necro_destroy(Necronomicon* self) {
    self->header.destroy(self);
}
