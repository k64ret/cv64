#ifndef MINI_SCROLL_H
#define MINI_SCROLL_H

#include "cv64.h"
#include "gfx/camera.h"
#include "gfx/graphic_container.h"
#include "object.h"

typedef enum miniScrollFlags {
    MINISCROLL_FLAG_DESTROY_IF_CLOSED = BIT(24),
    MINISCROLL_FLAG_SCROLLING_UPWARDS = BIT(24),
    MINISCROLL_FLAG_END_SCROLLING     = BIT(25),
    MINISCROLL_FLAG_CLOSED            = BIT(26),
    MINISCROLL_FLAG_OPENED            = BIT(27)
} miniScrollFlags;

/**
 * The mini scroll's state corresponds to the
 * 15 least significant bits from `miniScrollInner`'s `flags` field
 */
typedef enum miniScrollState {
    MINISCROLL_STATE_OPEN             = 1,
    MINISCROLL_STATE_CLOSE            = 2,
    MINISCROLL_STATE_SCROLL_UPWARDS   = 3,
    MINISCROLL_STATE_SCROLL_DOWNWARDS = 4,
    MINISCROLL_STATE_DESTROY          = 5
} miniScrollState;

typedef struct miniScrollInner {
    u32 flags;
    s32 scrolling_timer;
    s32 scroll_offset; // Determines the vertical location of the texture while scrolling
    s32 scrolling_speed;
    Vec3f position;
    f32 open_max_height;
    Vec3f width;
    s32 field_0x2C;
    s32 field_0x30;
    s32 field_0x34;
    Camera* display_camera;
} miniScrollInner;

typedef struct miniScrollVertexBuffer {
    GraphicContainerHeader header;
    Vtx vertices[2][230];
} miniScrollVertexBuffer;

// ID: 0x213E
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    Model*
        field_0x28; // Assumption based on function 0x0F0011f8 from the `NI_OVL_MINI_SCROLL` overlay
    u8 field_0x2C[8];
    miniScrollVertexBuffer* vtx_buffer;
    miniScrollInner inner;
} miniScroll;

miniScroll* miniScroll_create(void* parent, Camera* camera, s32 param_3, s32 param_4);
u32 miniScroll_checkFlags(miniScroll* self, u32 flags);
void miniScroll_editFlags(miniScroll* self, u32 flags, s32 setFlags);
Model* miniScroll_getModel(miniScroll* self);
void miniScroll_setState(miniScroll* self, u32 state);
void miniScroll_setScrollingParams(miniScroll* self, f32 open_max_height, s32 scrolling_speed);
void miniScroll_setPosition(miniScroll* self, f32 X, f32 Y, f32 Z);
void miniScroll_setWidth(miniScroll* self, f32 X, f32 Y, f32 Z);

typedef void (*miniScroll_func_t)(miniScroll*);

#endif
