#include "cv64.h"
#include "objects/menu/page.h"

// clang-format off

// TODO: `extern const u32` for the dlists
hierarchy page_1_hierarchy = {
    NI_ASSETS_MENU,
    {
        { 0x06007240, CREATE_NEXT_NODE, { -1561, 35, 764 } },
        { 0x06007458, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x060076C8, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06007938, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06007BA8, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06007E18, DONT_CREATE_SIBLING, { 621, 0, 0 } }
    }
};

hierarchy page_2_hierarchy = {
    NI_ASSETS_MENU,
    {
        { 0x06008000, CREATE_NEXT_NODE, { -1561, 35, 764 } },
        { 0x06008210, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06008480, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x060086F0, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06008960, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06008BD0, DONT_CREATE_SIBLING, { 621, 0, 0 } }
    }
};

hierarchy page_3_hierarchy = {
    NI_ASSETS_MENU,
    {
        { 0x06008DB8, CREATE_NEXT_NODE, { -1561, 35, 764 } },
        { 0x06008FC8, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06009238, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x060094A8, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06009718, (DONT_CREATE_SIBLING | CREATE_NEXT_NODE), { 621, 0, 0 } },
        { 0x06009988, DONT_CREATE_SIBLING, { 621, 0, 0 } }
    }
};

u8 page_anims_rot_data[9][28] = {
    { 0x80, 0x34, 0x1C, 0x00, 0x00, 0x3B, 0xF8, 0x00, 0x00, 0x3A, 0xC0, 0x00, 0x00, 0x3B, 0xF0, 0x00, 0x00, 0x3C, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x08 },
    { 0x80, 0x22, 0x3C, 0x00, 0x00, 0x3F, 0x60, 0x00, 0x00, 0x3F, 0x38, 0x00, 0x00, 0x3E, 0x70, 0x00, 0x00, 0x3E, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x01 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x3F, 0xD0, 0x00, 0x00, 0x3F, 0xB0, 0x00, 0x00, 0x3E, 0xC0, 0x00, 0x00, 0x3E, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x01 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x00, 0x00, 0x3F, 0x10, 0x00, 0x00, 0x3E, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x01 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x60, 0x00, 0x00, 0x3F, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x02 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x01 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x01 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x01 },
    { 0x80, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00 }
};

// clang-format on

page_func_t page_functions[] = {page_isWorkCreated, page_init, page_loop, page_destroy};

void page_entrypoint(page* self) {
    ENTER(self, page_functions);
}

void page_isWorkCreated(page* self) {
    if (self->work != NULL) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void page_init(page* self) {
    cv64_model_inf_t* model;
    animationMgr* animMgr             = &self->animMgr;
    animation_info* current_anim_info = &animMgr->current_anim;
    page_work* work                   = self->work;
    u8 page_type                      = work->flags & 3;

    // Create the model (each page has a different texture)
    switch (page_type) {
        default:
            break;
        case PAGE_1:
            model = (*modelInfo_buildHierarchy)(FIG_TYPE_HIERARCHY_NODE, NULL, &page_1_hierarchy);
            self->model       = model;
            model->position.x = work->position.x;
            model->position.y = work->position.y;
            model->position.z = work->position.z;
            break;
        case PAGE_2:
            model = (*modelInfo_buildHierarchy)(FIG_TYPE_HIERARCHY_NODE, NULL, &page_2_hierarchy);
            self->model       = model;
            model->position.x = work->position.x;
            model->position.y = work->position.y;
            model->position.z = work->position.z;
            break;
        case PAGE_3:
            model = (*modelInfo_buildHierarchy)(FIG_TYPE_HIERARCHY_NODE, NULL, &page_3_hierarchy);
            self->model       = model;
            model->position.x = work->position.x;
            model->position.y = work->position.y;
            model->position.z = work->position.z;
            break;
    }

    // Assign the model's lighting
    // Set model flags, size and visibility
    (*figure_setChild)(model, work->page_light);
    model->flags |= FIG_FLAG_0080;
    model->size.z = 1.0f;
    model->size.y = 1.0f;
    model->size.x = 1.0f;
    if (work->flags & PAGE_HIDE) {
        (*figure_hideSelfAndChildren)(model, 0);
    }

    // Setup animation
    (*animationInfo_create)(current_anim_info, PAGE_NUMBER_OF_LIMBS, 0);
    (*animationInfo_setParams)(
        current_anim_info, &page_anims_rot_data[work->anim_ID][0], work->anim_speed
    );
    (*animationInfo_animateFrame)(current_anim_info, model);

    self->field_0x6C = 1;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void page_loop(page* self) {
    cv64_model_inf_t* model;
    u8 work_flags;
    page_work* work                   = self->work;
    animationMgr* animMgr             = &self->animMgr;
    animation_info* current_anim_info = &animMgr->current_anim;
    s8 anim_state;

    if (work->flags & ANIMATE) {
        model = self->model;
        // Pause the page animation if it's invisible
        if (work->flags & PAGE_HIDE) {
            current_anim_info->flags |= ANIM_INFO_FLAG_PAUSE;
        }

        anim_state = (*animationInfo_animateFrame)(current_anim_info, model);
        // Animation has ended overall
        if (anim_state == -1) {
            work->flags = work->flags & ~ANIMATE;
            if (work->flags & DESTROY_AFTER_ANIMATION_FINISHES) {
                work->flags = work->flags | DESTROY_PAGE;
            }
        }
        work_flags = work->flags;
        // Finished flipping over animation
        if (anim_state == 1) {
            work->flags = work_flags | FINISHED_FLIP_ANIMATION;
            if (self->field_0x6C != 0) {
                self->field_0x6C = 0;
            }
        } else {
            work->flags = work_flags & ~FINISHED_FLIP_ANIMATION;
        }
    } else if (work->flags & DESTROY_PAGE) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void page_destroy(page* self) {
    self->header.destroy(self);
}
