/**
 * @file mini_scroll_setup.c
 *
 * Contains different functions for creating and setting up the mini scroll,
 * used in certain scenarios, such as to display small Yes / No selection messages in front of it.
 */

#include "objects/menu/miniScroll.h"

miniScroll* createMiniScroll(void* parent, Camera* camera, s32 param_3, s32 param_4) {
    miniScroll* obj_mini_scroll;
    miniScrollInner* inner;

    obj_mini_scroll        = (*object_create)(parent, MENU_MINI_SCROLL);
    inner                  = &obj_mini_scroll->inner;
    inner->flags           = 0;
    inner->field_0x04      = 320;
    inner->field_0x08      = 0;
    inner->field_0x0C      = 1;
    inner->width.x         = 1.0f;
    inner->width.y         = 1.0f;
    inner->width.z         = 1.0f;
    inner->position.x      = 0.0f;
    inner->position.y      = 0.0f;
    inner->open_max_height = 20.0f;

    if (param_3 != 0) {
        inner->field_0x2C = param_3;
        inner->field_0x30 = param_4;
    } else {
        inner->field_0x2C = 0;
        inner->field_0x30 = 0;
    }

    inner->field_0x34 = 0;

    if (camera != NULL) {
        inner->display_camera = camera;
    } else {
        inner->display_camera = NULL;
    }

    return obj_mini_scroll;
}

void miniScroll_setPosition(miniScroll* self, f32 X, f32 Y, f32 Z) {
    self->inner.position.x = X;
    self->inner.position.y = Y;
    self->inner.position.z = Z;
}

void miniScroll_setOpenMaxHeight(miniScroll* self, f32 open_max_height, s32 param_3) {
    self->inner.field_0x0C      = param_3;
    self->inner.open_max_height = open_max_height;
}

void miniScroll_setWidth(miniScroll* self, f32 X, f32 Y, f32 Z) {
    self->inner.width.x = X;
    self->inner.width.y = Y;
    self->inner.width.z = Z;
}

Model* miniScroll_getModel(miniScroll* self) {
    return self->model;
}

void miniScroll_setFlags(miniScroll* self, u32 flags) {
    self->inner.flags |= (flags & 0xF);
}

void miniScroll_editFlags(miniScroll* self, u32 flags, s32 setFlags) {
    miniScrollInner* inner = &self->inner;

    if (setFlags) {
        inner->flags |= flags;
    } else {
        inner->flags &= ~flags;
    }
}

u32 miniScroll_checkFlags(miniScroll* self, u32 flags) {
    return self->inner.flags & flags;
}
