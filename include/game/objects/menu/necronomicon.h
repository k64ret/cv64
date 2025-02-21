#ifndef NECRONOMICON_H
#define NECRONOMICON_H

#include "objects/menu/page.h"
#include "bit.h"

#define NECRO_NUM_PAGES(self) ARRAY_COUNT(self->pages)

typedef enum NecroWorkFlag {
    NECRO_WORK_FLAG_FLIP_PAGES                     = BIT(1),
    NECRO_WORK_FLAG_CLOSE                          = BIT(2),
    NECRO_WORK_FLAG_DONT_FLIP_PAGES_BEFORE_CLOSING = BIT(6),
    NECRO_WORK_FLAG_DESTROY_NECRO                  = BIT(7)
} NecroWorkFlag;

// Real name: `necro_work`
typedef struct NecroWork {
    FigureLight* necro_light;
    u8 flags;
    u8 field_0x05[11];
    Vec3f position;
    u8 field_0x1C;
    /**
     * The last page was flipped, so display the book cover
     * and fully close the book.
     */
    u8 last_page_flipped;
    u8 time_before_flipping_another_page;
    u8 pages_to_flip_before_closing;
    /**
     * Delay time before the player is able to despawn the necronomicon.
     *
     * @note Due to a check that always passes in `necro_finishedClosing`,
     *       this field is not really used, so the player is still able to despawn
     *       the necronomicon as soon as it reaches the `necro_finishedClosing` function.
     */
    u8 necro_destroy_delay_time;
    /**
     * When this field is NOT 0, the necronomicon will create `PAGE_1`
     * the next time it's requested to create new pages.
     *
     * Otherwise, it will randomly switch between creating either pages `PAGE_2` or `PAGE_3`
     * See `necro_loop`
     */
    s8 time_before_creating_different_page;
    u8 field_0x22[2];
} NecroWork;

// ID: 0x0130
typedef struct Necronomicon {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* full_model;
    Model* book_cover;
    u8 field_0x2C[8];
    PageWork* pages[10];
    u8 field_0x5C[20];
    NecroWork* work;
} Necronomicon;

void necro_entrypoint(Necronomicon* self);
void necro_isWorkCreated(Necronomicon* self);
void necro_init(Necronomicon* self);
void necro_loop(Necronomicon* self);
void necro_close(Necronomicon* self);
void necro_finishedClosing(Necronomicon* self);
void necro_destroy(Necronomicon* self);
NecroWork* necroWork_create(ObjectHeader* parent, FigureLight* light, u8 flags, s32 arg3);

typedef void (*NecroFunc)(Necronomicon*);

typedef enum NecroFuncID {
    NECRO_IS_WORK_CREATED,
    NECRO_INIT,
    NECRO_LOOP,
    NECRO_CLOSE,
    NECRO_FINISHED_CLOSING,
    NECRO_DESTROY
} NecroFuncID;

extern const u32 NECRO_FULL_MODEL_DL;
extern const u32 NECRO_BOOK_COVER_DL;

#endif
