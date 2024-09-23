#ifndef PAGE_H
#define PAGE_H

#include "object.h"
#include "gfx/model_info.h"
#include "gfx/light.h"
#include "animation.h"

#define PAGE_NUMBER_OF_LIMBS 6 + 1
#define GET_PAGE_TYPE(value) value & 3

typedef enum page_work_flags {
    PAGE_1                           = 0x01,
    PAGE_2                           = 0x02,
    PAGE_3                           = 0x03,
    ANIMATE                          = 0x04,
    PAGE_ANIM_END_KEYFRAME           = 0x08,
    PAGE_HIDE                        = 0x10,
    DESTROY_AFTER_ANIMATION_FINISHES = 0x20,
    DESTROY_PAGE                     = 0x40
} page_work_flags;

typedef struct {
    light* page_light;
    u8 flags;
    u8 flip_anim_keyframe;
    u8 field_0x06[2];
    f32 anim_speed;
    Vec3f position;
} page_work;

// ID: 0x0131
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    animationMgr animMgr;
    u8 field_0x64[8];
    /**
     * Set to `TRUE` after the page has finished flipping over once.
     * Seemingly unused otherwise.
     */
    u32 field_0x6C;
    page_work* work;
} page;

void page_entrypoint(page* self);
void page_isWorkCreated(page* self);
void page_init(page* self);
void page_loop(page* self);
void page_destroy(page* self);

typedef void (*page_func_t)(page*);

#endif // PAGE_H
