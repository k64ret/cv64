#ifndef PAGE_H
#define PAGE_H

#include "object.h"
#include "gfx/model.h"
#include "gfx/light.h"
#include "animation.h"

#define PAGE_NUMBER_OF_LIMBS 6 + 1
#define GET_PAGE_TYPE(value) value & 3

typedef enum PageWorkFlags {
    PAGE_FLAG_PAGE_1                           = 0x01,
    PAGE_FLAG_PAGE_2                           = 0x02,
    PAGE_FLAG_PAGE_3                           = 0x03,
    PAGE_FLAG_ANIMATE                          = 0x04,
    PAGE_FLAG_ANIM_END_KEYFRAME                = 0x08,
    PAGE_FLAG_HIDE                             = 0x10,
    PAGE_FLAG_DESTROY_AFTER_ANIMATION_FINISHES = 0x20,
    PAGE_FLAG_DESTROY_PAGE                     = 0x40
} PageWorkFlags;

typedef struct PageWork {
    FigureLight* page_light;
    u8 flags;
    u8 flip_anim_keyframe;
    u8 field_0x06[2];
    f32 anim_speed;
    Vec3f position;
} PageWork;

// ID: 0x0131
typedef struct Page {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    animationMgr animMgr;
    u8 field_0x64[8];
    /**
     * Set to `TRUE` after the page has finished flipping over once.
     * Seemingly unused otherwise.
     */
    u32 page_flipped_once;
    PageWork* work;
} Page;

void page_entrypoint(Page* self);
void page_isWorkCreated(Page* self);
void page_init(Page* self);
void page_loop(Page* self);
void page_destroy(Page* self);
PageWork* pageWork_create(
    ObjectHeader* parent,
    FigureLight* page_light,
    u8 flags,
    f32 pos_X,
    f32 pos_Y,
    f32 pos_Z,
    u8 flip_anim_keyframe,
    f32 anim_speed
);

typedef void (*PageFunc)(Page*);

#endif // PAGE_H
