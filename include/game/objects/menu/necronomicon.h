#ifndef NECRONOMICON_H
#define NECRONOMICON_H

#include "objects/menu/page.h"
#include "bit.h"

typedef enum NecroWorkFlag {
    NECRO_WORK_FLAG_01                             = BIT(0),
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
    u8 last_page_flipped;
    u8 time_before_flipping_another_page;
    u8 pages_to_flip_before_closing;
    u8 field_0x20;
    u8 field_0x21;
    u8 field_0x22[2];
} NecroWork;

typedef struct Necronomicon {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* full_model;
    Model* book_cover;
    u8 field_0x2C[8];
    page_work* pages[7];
    u8 field_0x50[32];
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
