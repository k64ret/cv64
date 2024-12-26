#ifndef MINI_SCROLL_H
#define MINI_SCROLL_H

#include "object.h"
#include "gfx/model.h"
#include "gfx/camera.h"
#include "gfx/graphic_container.h"

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
    MINISCROLL_STATE_OPEN             = 1, // Real name: `SCROLL_REQ_OPEN`
    MINISCROLL_STATE_CLOSE            = 2, // Real name: `SCROLL_REQ_CLOSE`
    MINISCROLL_STATE_SCROLL_UPWARDS   = 3, // Real name: `SCROLL_REQ_UP`
    MINISCROLL_STATE_SCROLL_DOWNWARDS = 4, // Real name: `SCROLL_REQ_DOWN`
    MINISCROLL_STATE_DESTROY          = 5  // Real name: `SCROLL_REQ_KILL`
} miniScrollState;

typedef struct miniScrollInner {
    u32 flags;
    s32 scrolling_timer;
    s32 scroll_offset; // Determines the vertical location of the texture while scrolling
    s32 scrolling_speed;
    Vec3f position;
    f32 open_max_height;
    Vec2f width;
    f32 scroll_opened_bottom_limit; // How far the scroll opens up downwards
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
typedef struct miniScroll {
    ObjectHeader header;
    u8 field_0x20[4];
    struct Model* model;
    struct Model*
        field_0x28; // Assumption based on `func_0F0011F8` from the `NI_OVL_MINI_SCROLL` overlay
    u8 field_0x2C[8];
    miniScrollVertexBuffer* vtx_buffer;
    miniScrollInner inner;
} miniScroll;

miniScroll* miniScroll_create(void* parent, Camera* camera, s32 param_3, s32 param_4);
u32 miniScroll_checkFlags(miniScroll* self, u32 flags);
void miniScroll_editFlags(miniScroll* self, u32 flags, s32 setFlags);
struct Model* miniScroll_getModel(miniScroll* self);
void miniScroll_setState(miniScroll* self, u32 state);
void miniScroll_setScrollingParams(miniScroll* self, f32 open_max_height, s32 scrolling_speed);
void miniScroll_setPosition(miniScroll* self, f32 X, f32 Y, f32 Z);
void miniScroll_setWidth(miniScroll* self, f32 X, f32 Y, f32 scroll_opened_bottom_limit);

extern void miniScroll_entrypoint(miniScroll* self);
extern void miniScroll_init(miniScroll* self);
extern void miniScroll_loop(miniScroll* self);
extern void miniScroll_open(miniScroll* self);
extern void miniScroll_close(miniScroll* self);
extern void miniScroll_scrollUpwards(miniScroll* self);
extern void miniScroll_scrollDownwards(miniScroll* self);
extern void miniScroll_destroy(miniScroll* self);
extern u32
miniScroll_renderScroll(miniScroll* self, s32 scroll_offset, s32 scroll_vertical_position);
extern void miniScroll_animateOpen(miniScroll* self);
extern void miniScroll_animateClose(miniScroll* self);
extern void miniScroll_animateScrolling(miniScroll* self);
extern void func_0F0011F8(miniScroll* self);
extern void func_0F001248(miniScroll* self);
extern void func_0F001250(miniScroll* self);
extern void func_0F001258(miniScroll* self);

typedef void (*miniScrollFuncs)(miniScroll*);

#endif
