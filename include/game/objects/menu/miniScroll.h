#ifndef MINI_SCROLL_H
#define MINI_SCROLL_H

#include "cv64.h"
#include "gfx/camera.h"
#include "object.h"

typedef enum miniScroll_flags {
    MINISCROLL_FLAG_00000001 = 0x00000001,
    MINISCROLL_FLAG_00000004 = 0x00000004,
    MINISCROLL_FLAG_08000000 = 0x08000000
} miniScroll_flags;

typedef struct miniScrollInner {
    u32 flags;
    s32 field_0x04;
    s32 field_0x08;
    s32 field_0x0C;
    Vec3f position;
    f32 open_max_height;
    Vec3f width;
    s32 field_0x2C;
    s32 field_0x30;
    s32 field_0x34;
    Camera* display_camera;
} miniScrollInner;

// ID: 0x213E
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    /**
     * Vertices buffer
     * TODO: This may need its own struct
     */
    void* vtx_buffer;
    miniScrollInner inner;
} miniScroll;

miniScroll* createMiniScroll(void* parent, Camera* camera, s32 param_3, s32 param_4);
u32 miniScroll_checkFlags(miniScroll* self, u32 flags);
void miniScroll_editFlags(miniScroll* self, u32 flags, s32 setFlags);
Model* miniScroll_getModel(miniScroll* self);
void miniScroll_setFlags(miniScroll* self, u32 flags);
void miniScroll_setOpenMaxHeight(miniScroll* self, f32 open_max_height, s32 param_3);
void miniScroll_setPosition(miniScroll* self, f32 X, f32 Y, f32 Z);
void miniScroll_setWidth(miniScroll* self, f32 X, f32 Y, f32 Z);

typedef void (*miniScroll_func_t)(miniScroll*);

#endif
